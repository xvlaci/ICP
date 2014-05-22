/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "server.h"

//= Channel

void channel::join(subscriber_ptr subscriber)
{
    subscribers_.insert(subscriber);
}

void channel::leave(subscriber_ptr subscriber)
{
    subscribers_.erase(subscriber);
}

void channel::deliver(const std::string& msg)
{
    std::for_each(subscribers_.begin(), subscribers_.end(),
        boost::bind(&subscriber::deliver, _1, boost::ref(msg)));
}


//=================================================================\\


//= TCP_SEASSION

tcp::socket& tcp_session::socket()
{
    return socket_;
}

void tcp_session::start()
{
    channel_.join(shared_from_this());
    start_read();

    input_deadline_.async_wait(
        boost::bind(&tcp_session::check_deadline,
        shared_from_this(), &input_deadline_));

    await_output();

    output_deadline_.async_wait(
        boost::bind(&tcp_session::check_deadline,
        shared_from_this(), &output_deadline_));
}


//= Private tcp_session

void tcp_session::stop()
{
    channel_.leave(shared_from_this());

    socket_.close();
    input_deadline_.cancel();
    non_empty_output_queue_.cancel();
    output_deadline_.cancel();
}

void tcp_session::deliver(const std::string& msg)
{
    output_queue_.push_back(msg + "\n");
    non_empty_output_queue_.expires_at(boost::posix_time::neg_infin);
}

void tcp_session::start_read()
{
    input_deadline_.expires_from_now(boost::posix_time::seconds(30));
    boost::asio::async_read_until(socket_, input_buffer_, '\n',
        boost::bind(&tcp_session::handle_read, shared_from_this(), _1));
}

void tcp_session::handle_read(const boost::system::error_code& ec)
{
    if(stopped())
        return;

    if(!ec){
        std::string msg;
        std::istream is(&input_buffer_);
        std::getline(is, msg);

        if(msg == "new")
            server::getInstance()->cntPlus();

        if (!msg.empty()){
            channel_.deliver(msg);
        }
        else{
            if(output_queue_.empty()){
            output_queue_.push_back("\n");
                non_empty_output_queue_.expires_at(boost::posix_time::neg_infin);
            }
        }

        start_read();
    }
    else{
        stop();
    }
}

void tcp_session::await_output()
{
    if (stopped())
        return;

    if (output_queue_.empty()){
        non_empty_output_queue_.expires_at(boost::posix_time::pos_infin);
        non_empty_output_queue_.async_wait(
        boost::bind(&tcp_session::await_output, shared_from_this()));
    }
    else{
        start_write();
    }
}

void tcp_session::start_write()
{
    output_deadline_.expires_from_now(boost::posix_time::seconds(30));

    std::string s = clientMsgHandler();

    if(server::getInstance()->want_new_state){
        server::getInstance()->want_new_state = false;
        char *message_reply = new char[2550];
        message_reply[s.size()]=0;
        message_reply[s.size()+1]=0;
        memcpy(message_reply,s.c_str(),s.size());
        boost::asio::async_write(socket_,
            boost::asio::buffer(message_reply,2550),
            boost::bind(&tcp_session::handle_write, shared_from_this(), _1));

    }
    else if(s[0] == 'L')
    {
        std::cout << "posilam ulozene pozice" << std::endl;
        char *message_reply = new char[2550];

        message_reply[s.size()]=0;
        message_reply[s.size()+1]=0;
        memcpy(message_reply,s.c_str(),s.size());

        boost::asio::async_write(socket_,
            boost::asio::buffer(message_reply,2550),
            boost::bind(&tcp_session::handle_write, shared_from_this(), _1));
    }
    else{
        char *message_reply = new char[2550];

        message_reply[s.size()]=0;
        message_reply[s.size()+1]=0;
        memcpy(message_reply,s.c_str(),s.size());

        boost::asio::async_write(socket_,
            boost::asio::buffer(message_reply,2550),
            boost::bind(&tcp_session::handle_write, shared_from_this(), _1));
    }

    }

std::string tcp_session::clientMsgHandler()
{
    std::string s;
    std::string msg = output_queue_.front();
    int id_cl = -1;
    if(msg == "new\n"){
        if(server::getInstance()->getCnt() < 4){
            std::stringstream ss;
            int id = server::getInstance()->getCnt() - 1;

            ss << id;
            s = ss.str();
            Player pl = server::getInstance()->getPlayer(id);
            pl.alive = true;
            pl.id = id;
        }
        else{
            s = "-Plno";
        }
    }

    else if(msg.find(":::LOAD") == 1 && (msg[0] - '0') == 0){
        /*server::getInstance()->waitin_time_ = msg[11] - '0';
        //std::cout << "|" << msg[11] - '0' << "|" << msg.substr(14, msg.length()-15) << "|" << std::endl;
        server::getInstance()->loadMap(msg.substr(14, msg.length()-15));
        server::getInstance()->want_new_state = true;
        return server::getInstance()->getBoard()->generateMsg();
        */

        //cout << "bla" << endl;
        s = "Loads";
        string tmp;
        glob_t glob_result;
        glob("*",GLOB_TILDE,NULL,&glob_result);
        for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
            tmp = glob_result.gl_pathv[i];;
            if(tmp.find(".map") == (tmp.length() - 4)){
                s.append("\n");
                s.append(tmp);
            }
        }
        cout << s << endl;
    }
    else if(msg.find(":::SAVE:::") == 1){
        Controller* c = server::getInstance()->getCont();
        //std::cout << "|" << msg.substr(11, msg.length() - 12) << "|" << std::endl;
        c->save(msg.substr(11, msg.length() - 12));
    }
    else{
        int id_end = msg.find(":::");
        if(id_end == 1){
            id_cl = msg[0] - '0';
            if(id_cl >= 0 && id_cl <= 3){
                if(msg.find(":::COMMAND:::") == 1){

                    clientCommandHandler(server::getInstance()->getPlayer(id_cl), msg);
                }
                if(msg.find(":::NEWSTATE:::") == 1){
                    if(server::getInstance()->getPlayer(id_cl).waitin){
                        return server::getInstance()->newMap(id_cl);
                        //return "Nova mapa";
                    }
                    else
                        return "DENIED";
                }
            }
        }
    }

    return s;
}

void tcp_session::clientCommandHandler(Player player, std::string command){
    bool alive;

    Controller * cont = server::getInstance()->getCont();
    Board * b = server::getInstance()->getBoard();

    if(player.turn)
        return;

    if(command.find(":::GO:::") == 11){
        //std::cout << "Jdu dopredu!!" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->move(player.position), true);
    }
    else if(command.find(":::STOP:::") == 11){
        //std::cout << "Stojim!!" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, player.position, false);
    }
    else if(command.find(":::LEFT:::") == 11){
        //std::cout << "Otacim se vlevo!!" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->turn(player.position, LEFT), player.go);
    }
    else if(command.find(":::RIGHT:::") == 11){
        //std::cout << "Otacim se vpravo!!" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->turn(player.position, RIGHT), player.go);
    }
    else if(command.find(":::DOWN:::") == 11){
        //std::cout << "Otacim se dolu!!" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->turn(player.position, DOWN), player.go);
    }
    else if(command.find(":::UP:::") == 11){
        //std::cout << "Otacim se nahoru!!" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->turn(player.position, UP), player.go);
    }
    else if(command.find(":::PICK:::") == 11){
        //std::cout << "Zvedam klic" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->pickUpKey(player.position), false);
    }
    else if(command.find(":::OPEN:::") == 11){
        //std::cout << "Oteviram branu" << std::endl;
        alive = server::getInstance()->setPlayer(player.id, cont->openGate(player.position), false);
    }
    else{}
}



void tcp_session::handle_write(const boost::system::error_code& ec)
{
    if (stopped())
        return;

    if (!ec){
        output_queue_.pop_front();
        await_output();
    }
    else{
        stop();
    }
}

void tcp_session::check_deadline(deadline_timer* deadline)
{
    if (stopped())
        return;

    if (deadline->expires_at() <= deadline_timer::traits_type::now()){
        stop();
    }
    else{
        deadline->async_wait(
            boost::bind(&tcp_session::check_deadline,
            shared_from_this(), deadline));
    }
}


//===================================================================\\

//= server

server* server::m_pInstance = NULL;

server* server::Instance(boost::asio::io_service& io_service,
                          const tcp::endpoint& listen_endpoint)
{
   if (!m_pInstance)
       m_pInstance = new server(io_service, listen_endpoint);

   return m_pInstance;
}



void server::handle_accept(tcp_session_ptr session,
    const boost::system::error_code& ec)
{

    if (!ec){
        session->start();

        tcp_session_ptr new_session(new tcp_session(io_service_, channel_));

        acceptor_.async_accept(new_session->socket(),
            boost::bind(&server::handle_accept, this, new_session, _1));
    }
}

void server::cntPlus()
{
    this->m_pInstance->clients_cnt++;
}

int server::getCnt()
{
    return this->m_pInstance->clients_cnt;
}

Player server::getPlayer(int id)
{
    return this->m_pInstance->PLAYERS[id];
}

void * server::stepper(void *threadid)
{
    while(true){
        sleep(server::getInstance()->waitin_time_);
        this->m_pInstance->move();
    }
    pthread_exit(NULL);
}

Controller * server::getCont()
{
  return this->m_pInstance->cont;
}

Board * server::getBoard()
{
    return this->m_pInstance->b;

}

void server::loadMap(std::string s)
{
    using namespace boost;
    s.append(".map");
    srand(time(NULL));

    this->m_pInstance->cont = new Controller();
    maze_map maze = cont->load(s);


    this->m_pInstance->b = new Board(maze.width,maze.height, maze.maze);
    this->m_pInstance->cont->setBoard(this->m_pInstance->b);

    for(int i = 0; i < 4; i++){
        this->m_pInstance->PLAYERS[i].position = this->m_pInstance->b->player_start_pos[i];
        this->m_pInstance->PLAYERS[i].id = i;
        this->m_pInstance->PLAYERS[i].alive = false;
        this->m_pInstance->PLAYERS[i].go = false;
    }

    this->m_pInstance->map_loaded = true;

    int rc = pthread_create(&this->m_pInstance->thread, NULL, server::JHWrapper, static_cast<void *>(m_pInstance));

    if (rc){
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
}

std::string server::newMap(int id)
{
    if(this->m_pInstance->PLAYERS[id].waitin && this->m_pInstance->map_loaded){
        this->m_pInstance->PLAYERS[id].waitin = false;
        this->m_pInstance->want_new_state = true;
        return this->m_pInstance->map_new_state;
    }

    return "DENIED";
}

void server::move()
{
    bool alive;
    for(int i = 0; i < 4; i++){
        if(!this->m_pInstance->PLAYERS[i].turn && this->m_pInstance->PLAYERS[i].go){
            alive = this->m_pInstance->setPlayer(i, this->m_pInstance->cont->move(this->m_pInstance->PLAYERS[i].position), true);
        }
        this->m_pInstance->PLAYERS[i].turn = false;
        this->m_pInstance->PLAYERS[i].waitin = true;
    }
    this->m_pInstance->b->printMap();

    this->m_pInstance->map_new_state = this->m_pInstance->b->generateMsg();
    this->m_pInstance->cont->moveGuard();
}

bool server::setPlayer(int id, Square * s, bool go)
{
    //this->m_pInstance->PLAYERS[id].position->getCharacter()->alive = true;

    this->m_pInstance->PLAYERS[id].position = s;
    if(s == 0)
        return (this->m_pInstance->PLAYERS[id].alive = false);
    else
        this->m_pInstance->PLAYERS[id].alive = true;
    this->m_pInstance->PLAYERS[id].go = go;
    this->m_pInstance->PLAYERS[id].turn = true;

    return true;
}


