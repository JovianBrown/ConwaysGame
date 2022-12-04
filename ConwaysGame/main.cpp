//
//  main.cpp
//  ConwaysGame
//
//  Created by mac on 2022/12/3.
//  Copyright © 2022 Jovian. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "board.hpp"
const int m_WindowWidth = 512;
const int m_WindowHeight = 512;
const int m_TotalCreatures = 150;
SDL_Renderer* m_Renderer;
bool m_IsRunning;
bool m_Update = false;
bool m_CreateBoard = true;
void updateBoard(Board &board)
{
    board.update();
    board.generate();
    board.removeOldTiles();
    m_Update = false;
}
Board getBoard(Board &board)
{
    if(m_CreateBoard)
    {
        Board b = Board(m_WindowWidth,m_WindowHeight);
        for(int i = 0; i < m_TotalCreatures;i++)
        {
            b.addRandomTile();
        }
        return b;
    }
    return board;
}
void updateKeyboard(SDL_Event event, const Uint8* keystates,Board &board)
{
    if(event.type == SDL_QUIT)
    {
        m_IsRunning=false;
    }
    if(keystates[SDL_SCANCODE_Q] )
    {
        m_IsRunning=false;
    }
    if(keystates[SDL_SCANCODE_U] && m_Update == false )
    {
        m_Update = true;
        m_CreateBoard = true;
        updateBoard(board);
        
    }
  
    if(keystates[SDL_SCANCODE_N])
    {
        board = getBoard(board);
        m_CreateBoard = false;
    }
}

void renderBoard(SDL_Renderer* m_Renderer, Board& b)
{
    SDL_RenderClear(m_Renderer);
    for(Tile &t: b.getBoard())
    {
        if(t.alive())
        {
            SDL_SetRenderDrawColor(m_Renderer, 100, 0, 0, 255);
            SDL_RenderFillRect(m_Renderer,&t.rect);
        }
        if(t.justPlaced)
        {
            SDL_SetRenderDrawColor(m_Renderer, 200, 0, 0, 255);
            SDL_RenderFillRect(m_Renderer,&t.rect);
        }
    }
    SDL_RenderPresent(m_Renderer);
}

int main()
{
    SDL_Window* m_Window;
    const Uint8* m_KeyStates;
    srand(SDL_GetTicks());
    m_KeyStates = SDL_GetKeyboardState(NULL);
    if(m_WindowWidth%TILE_SIZE>0 || m_WindowHeight%TILE_SIZE>0)
    {
        std::cout<<"window resolution and tilesize conflict!"<<std::endl;
    }
    m_Window = SDL_CreateWindow("Conways Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_WindowHeight,m_WindowWidth,SDL_WINDOW_METAL);
    if(m_Window!=NULL)
        std::cout<<"Window created"<<std::endl;
    else
        std::cout<<"Unable to create window! "<<SDL_GetError()<<std::endl;
    std::cout<<"Conway's Game"<<std::endl;
    m_Renderer = SDL_CreateRenderer(m_Window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_RenderGetMetalLayer(m_Renderer);
    if(m_Renderer!=NULL)
        std::cout<<"renderer created"<<std::endl;
    else
        std::cout<<"Failed to create renderer"<<SDL_GetError()<<std::endl;
    
    SDL_PLATFORM_SUPPORTS_METAL;
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    SDL_Init(SDL_INIT_EVERYTHING);
    m_IsRunning=true;
    SDL_Event m_Event;
    srand(SDL_GetTicks());
   // Board board = Board(m_WindowWidth,m_WindowHeight);
   // board.addTile(16, 16); //for testings a condition
   // board.addTile(16, 32); //
   // board.addTile(16, 48); //
    Board board = getBoard(board);
    while(m_IsRunning)
    {
        SDL_PollEvent(&m_Event);
        renderBoard(m_Renderer,board);
        updateKeyboard(m_Event,m_KeyStates,board);
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

    }
    return 0;
}
