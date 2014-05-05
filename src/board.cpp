#include <cstdlib>
#include <cstring>
#include <boost/lexical_cast.hpp>
#include "board.h"

Board::Board(int width, int height, std::string map){
    this->width = width;
    this->height = height;
    this->map = map;
    strcpy(this->symbols, " #OqIF");

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
    const char *ch = this->map.c_str();

    for (int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){

            this->board[i][j] = new Square(i,j,((int)*ch++) - '0');
            //std::cout << board[i][j]->getX() << "x" << board[i][j]->getY() << " - " << board[i][j]->getObjectType() << std::endl;
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
    for (int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            s = this->board[i][j];
            if(s->getObjectType() > 3){
                //Guard pozice a, b, c, d ... Player pozice e, f, g, h
                char sym = (s->getObjectType() - 4) * 4 + 'a' + s->getCharacter()->facing();
                std::cout << s->getCharacter()->facing() << std::endl;
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
    for(int i = 0; i < this->width; i++)
    {
        for(int j = 0; j < this->height; j++)
            std::cout << symbols[board[i][j]->getObjectType()];
        std::cout << std::endl;
    }
}
