//
//  Game.cpp
//  Game
//
//  Created by krzysp on 25/09/2022.
//

#include <iostream>
#include "Game.hpp"
#include "GamePriv.hpp"

void Game::HelloWorld(const char * s)
{
    GamePriv *theObj = new GamePriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void GamePriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

void PictelScriptInit(void)
{
    printf("Pictel Script Init!\n");
}
