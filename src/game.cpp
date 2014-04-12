#include "game.h"

Game *Game::game = NULL;


Game::Game(QObject *parent) :
    QObject(parent)
{
}

bool Game::startGameSlot()
{
    board = new Board(this);
    return true;
}

Game::~Game()
{

}


Game * Game::getInstance()
{
    if (game == NULL)
    {
        game = new Game();
    }
    return game;
}


