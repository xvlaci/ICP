#include <cstdlib>
#include "board.h"


Board::Board(int width, int height, std::string map){
    this->width = width;
    this->height = height;
    this->map = map;


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
    for (int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            this->board[i][j] = new Square(i,j,0);
            std::cout << board[i][j]->getX() << "x" << board[i][j]->getY();
        }
    }

}

Square * Board::getSquare(int x, int y){
    return 0;
}

std::string Board::generateMsg(){
    return "bla";
}

void Board::printMap(){
    std::cout << "alb";
}
