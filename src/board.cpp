/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/

#include "board.h"
#include <cstdlib>
#include <cstring>
#include <boost/lexical_cast.hpp>


Board::Board(int width, int height, std::string map)
{
    this->width = width;
    this->height = height;
    this->map = map;
    strcpy(this->symbols, " #Oq^A>DvU<C@");

    if((this->board = ( Square*** )malloc( width*sizeof( Square** ))) == 0){
        std::cerr << "Chyba";
    }

    for (int i = 0; i < width; i++ ){
        if (( this->board[i] = ( Square** )malloc( height*sizeof(Square*))) == NULL ){
            std::cerr << "Chyba";
        }
    }
    loadMap();
}

void Board::loadMap()
{
    int players = 0;
    this->guards = 0;
    const char *ch = this->map.c_str();
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            this->board[x][y] = new Square(x,y,((int)*ch) - '0');
            //std::cout << board[i][j]->getX() << "x" << board[i][j]->getY() << " - " << board[i][j]->getObjectType() << std::endl;
            if((int)*ch >= 'e' && (int)*ch <= 't'){
                //this->board[x][y]->getCharacter()->setColor(players);
                this->player_start_pos[players++] = this->board[x][y];

            }

            if((int)*ch >= 'a' && (int)*ch <= 'd'){
                this->guards_pos[this->guards++] = this->board[x][y];
            }
            ch++;
        }
    }
}

Square * Board::getSquare(int x, int y){
    return this->board[x][y];
}

std::string Board::generateMsg(){
    std::string msg;
    msg = boost::lexical_cast<std::string>(this->width) + "\n" \
            + boost::lexical_cast<std::string>(this->height) + "\n";
    Square * s;
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            s = this->board[x][y];
            if(s->getObjectType() >= GUARD){
                //Guard pozice a, b, c, d ... Player pozice e, f, g, h
                char sym = (s->getObjectType() - GUARD) * 4 + 'a' + s->getCharacter()->facing() + (4 * s->getCharacter()->getColor());

                msg.push_back(sym);
            }
            else
            {
                msg.append(boost::lexical_cast<std::string>(s->getObjectType()));
                //std::cout << board[i][j]->getX() << "x" << board[i][j]->getY() << " - " << board[i][j]->getObjectType() << std::endl;
            }
        }
    }
    return msg;
}

void Board::printMap(){
    for(int y = 0; y < this->height; y++)
    {
        for(int x = 0; x < this->width; x++){
            if(board[x][y]->getObjectType() >= GUARD){
                std::cout << symbols[(board[x][y]->getObjectType() -1) + (2*board[x][y]->getCharacter()->facing())];
            }
            else if(board[x][y]->getObjectType() == FINISH){
                std::cout << symbols[12];
            }
            else{
                std::cout << symbols[board[x][y]->getObjectType()];
            }
        }
        std::cout << std::endl;
    }
}

int Board::getWidth(){
    return this->width;
}

int Board::getHeight(){
    return this->height;
}
