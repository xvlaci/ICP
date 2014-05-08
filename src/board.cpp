#include <cstdlib>
#include <cstring>
#include <boost/lexical_cast.hpp>
#include "board.h"

Board::Board(int width, int height, std::string map){
    this->width = width;
    this->height = height;
    this->map = map;
    strcpy(this->symbols, " #Oq^A>DvU<C");

    if((this->board = ( Square*** )malloc( width*sizeof( Square** ))) == 0){
        std::cout << "shit";
    }

    for (int i = 0; i < width; i++ )
    {
      /* x_i here is the size of given row, no need to
       * multiply by sizeof( char ), it's always 1
       */


      if (( this->board[i] = ( Square** )malloc( height*sizeof(Square*))) == NULL )
      { std::cout << "shit"; }

      /* probably init the row here */

    }


    loadMap();
}

void Board::loadMap(){
    int players = 0;
    this->guards = 0;
    const char *ch = this->map.c_str();
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){


            this->board[x][y] = new Square(x,y,((int)*ch) - '0');
            //std::cout << board[i][j]->getX() << "x" << board[i][j]->getY() << " - " << board[i][j]->getObjectType() << std::endl;
            if((int)*ch >= 'e' && (int)*ch <= 'h'){
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
    msg = boost::lexical_cast<std::string>(this->width) + " " \
            + boost::lexical_cast<std::string>(this->height) + "\n";
    Square * s;
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            s = this->board[x][y];
            if(s->getObjectType() >= GUARD){
                //Guard pozice a, b, c, d ... Player pozice e, f, g, h
                char sym = (s->getObjectType() - 4) * 4 + 'a' + s->getCharacter()->facing();
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
                std::cout << symbols[board[x][y]->getObjectType() + (2*board[x][y]->getCharacter()->facing())];
            }
            else{
                std::cout << symbols[board[x][y]->getObjectType()];
            }
        }
        std::cout << std::endl;


    }
}
