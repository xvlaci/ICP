/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/

#ifndef SERVER_H
#define SERVER_H


#include <algorithm>
#include <cstdlib>
#include <deque>
#include <sstream>
#include <iostream>
#include <set>
#include <glob.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>


#include "controller.h"


struct Player{
    int id;
    Square * position;
    bool alive;
    bool go;
    bool turn;
    bool waitin;
};


using boost::asio::deadline_timer;
using boost::asio::ip::tcp;
using boost::asio::ip::udp;

//----------------------------------------------------------------------

class subscriber
{
public:
  virtual ~subscriber() {}
  virtual void deliver(const std::string& msg) = 0;
};

typedef boost::shared_ptr<subscriber> subscriber_ptr;

//----------------------------------------------------------------------

class channel
{
public:
  void join(subscriber_ptr subscriber);

  void leave(subscriber_ptr subscriber);

  void deliver(const std::string& msg);

private:
  std::set<subscriber_ptr> subscribers_;
};

class tcp_session
  : public subscriber,
    public boost::enable_shared_from_this<tcp_session>
{
public:
  tcp_session(boost::asio::io_service& io_service, channel& ch)
    : channel_(ch),
      socket_(io_service),
      input_deadline_(io_service),
      non_empty_output_queue_(io_service),
      output_deadline_(io_service)
  {
    input_deadline_.expires_at(boost::posix_time::pos_infin);
    output_deadline_.expires_at(boost::posix_time::pos_infin);

    // The non_empty_output_queue_ deadline_timer is set to pos_infin whenever
    // the output queue is empty. This ensures that the output actor stays
    // asleep until a message is put into the queue.
    non_empty_output_queue_.expires_at(boost::posix_time::pos_infin);

  }

  tcp::socket& socket();

  // Called by the server object to initiate the four actors.
  void start();
  int client_cnt; 
private:
  void stop();

  bool stopped() const
  {
    return !socket_.is_open();
  }

  void deliver(const std::string& msg);

  void start_read();

  void handle_read(const boost::system::error_code& ec);

  void await_output();

  void start_write();

  std::string clientMsgHandler();

  bool clientCommandHandler(Player player, std::string command);

  void handle_write(const boost::system::error_code& ec);

  void check_deadline(deadline_timer* deadline);

  bool map_loaded;
  channel& channel_;
  tcp::socket socket_;
  boost::asio::streambuf input_buffer_;
  deadline_timer input_deadline_;
  std::deque<std::string> output_queue_;
  deadline_timer non_empty_output_queue_;
  deadline_timer output_deadline_;
};

typedef boost::shared_ptr<tcp_session> tcp_session_ptr;

//----------------------------------------------------------------------

class udp_broadcaster
  : public subscriber
{
public:
  udp_broadcaster(boost::asio::io_service& io_service,
      const udp::endpoint& broadcast_endpoint)
    : socket_(io_service)
  {
    socket_.connect(broadcast_endpoint);
  }

private:
  void deliver(const std::string& msg)
  {
    boost::system::error_code ignored_ec;
    socket_.send(boost::asio::buffer(msg), 0, ignored_ec);
  }

  udp::socket socket_;
};

//----------------------------------------------------------------------

class server
{
public:

  static server* Instance(boost::asio::io_service& io_service,
                          const tcp::endpoint& listen_endpoint);


  void handle_accept(tcp_session_ptr session,
      const boost::system::error_code& ec);

  static server * getInstance(){
    return m_pInstance;
  }

  void cntPlus();

  int getCnt();

  Player getPlayer(int id);

  void *stepper(void *threadid);

  Controller * getCont();

  Board * getBoard();

  void loadMap(std::string s);

  bool setPlayer(int id, Square * s, bool go);

  std::string newMap(int id);

  int waitin_time_;
  bool want_new_state;
  bool map_loaded;
  bool _finished;
  Player PLAYERS[4];
private:
  server(boost::asio::io_service& io_service,
      const tcp::endpoint& listen_endpoint)
    : io_service_(io_service),
      acceptor_(io_service, listen_endpoint)
  {
    /*subscriber_ptr bc(new udp_broadcaster(io_service_, broadcast_endpoint));
    channel_.join(bc);
    */
    this->_finished = false;
    this->clients_cnt = 0;
    this->map_loaded;

    tcp_session_ptr new_session(new tcp_session(io_service_, channel_));

    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session, _1));
  }

  static void * JHWrapper(void *self){
     server *that = static_cast<server*>(self);
     return that->stepper(self);
  }

  void move();


  pthread_t thread;

  Controller * cont;
  Board * b;
  std::string map_new_state;


  static server* m_pInstance;
  int clients_cnt;

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  channel channel_;
};


#endif // SERVER_H












