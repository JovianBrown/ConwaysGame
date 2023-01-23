//
//  main.cpp
//  ConwaysGame
//
//  Created by Jovian on 2022/12/3.
//  Copyright © 2022 Jovian. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "board.hpp"
#include "gui.hpp"
const int m_WindowWidth = 768;
const int m_WindowHeight = 512;
const int m_BoardWidth = 512;
const int m_BoardHeight = 512;
const int m_TotalCreatures = 1000;
SDL_Rect rect;
SDL_Rect mouseRect;
SDL_Rect currentPosition;
static Uint32 m_MouseButtons;
SDL_Renderer* m_Renderer;
GUI gui(m_BoardWidth,0,m_WindowWidth-m_BoardWidth,m_WindowHeight);
bool m_IsRunning;
bool m_Update = false;
bool m_CreateBoard = true;
void updateBoard(Board &board);
Board getBoard(Board &board);
void updateMouse(SDL_Event event, Board &board);
void updateKeyboard(SDL_Event event, const Uint8* keystates,Board &board);
void renderBoard(SDL_Renderer* m_Renderer, Board& b);


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

    m_Window = SDL_CreateWindow("Conways Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_WindowWidth,m_WindowHeight,SDL_WINDOW_METAL);
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
    rect.x = m_BoardWidth;   //rectangle values for menu
    rect.y = 0;
    rect.w = m_WindowWidth - m_BoardWidth;
    rect.h = m_WindowHeight;
    
   // Board board = Board(m_WindowWidth,m_WindowHeight);
   // board.addTile(16, 16); //for testings a condition
   // board.addTile(16, 32); //
   // board.addTile(16, 48); //
    Board board = getBoard(board);
    gui.addButtons(3);
    while(m_IsRunning)
    {
        SDL_PollEvent(&m_Event);
        renderBoard(m_Renderer,board);
        gui.render(m_Renderer);
        SDL_RenderPresent(m_Renderer);
        updateKeyboard(m_Event,m_KeyStates,board);
        updateMouse(m_Event,board);
        if(m_Update == true)
        {
           // board.update();
            updateBoard(board);
        }
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
       
    }
    return 0;
}

void updateBoard(Board &board)
{
    board.update();
    board.generate();
    board.removeOldTiles();
}
Board getBoard(Board &board)
{

    if(m_CreateBoard)
    {
        Board b = Board(m_BoardWidth,m_BoardHeight);

        for(int i = 0; i < m_TotalCreatures;i++)
        {
            b.addRandomTile();
        }
        return b;
    }
    return board;
}
void updateMouse(SDL_Event event, Board &board)
{
    int mouseX;
    int mouseY;
    
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        m_MouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
        currentPosition.h = 5;
        currentPosition.w = 5;
        currentPosition.x = mouseX;
        currentPosition.y = mouseY;
        gui.update(currentPosition);
        switch (gui.getMenuItem()) {
            case 0:
                updateBoard(board);
                m_Update = true;
                break;
            case 1:
                board = getBoard(board); //create new board
                break;
            case 2:
                std::cout<<"place pieces manually"<<std::endl;
                break;
            case 3:
                m_IsRunning = false;
                break;
                
        }
    }
    if(event.type == SDL_MOUSEBUTTONUP)
    {
       // m_Update = false;
    }
    
}
void updateKeyboard(SDL_Event event, const Uint8* keystates,Board &board)
{
    if(event.type == SDL_QUIT)
    {
        m_IsRunning = false;
    }
    if(keystates[SDL_SCANCODE_Q] )
    {
        m_IsRunning = false;
    }
    if(keystates[SDL_SCANCODE_U] && m_Update == false ) //update board
    {
        m_Update = true;
        m_CreateBoard = true;
        updateBoard(board);
    }
    if(keystates[SDL_SCANCODE_N]) //create new board
    {
        m_Update = false;
        board = getBoard(board);
        m_CreateBoard = false;
    }
}

void renderBoard(SDL_Renderer* m_Renderer, Board& b)
{
    SDL_RenderClear(m_Renderer);
  //  SDL_Delay(50);
    for(Tile &t: b.getBoard())
    {
        if(t.alive())
        {
            SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(m_Renderer,&t.rect);
        }
        if(t.justPlaced)
        {
            SDL_SetRenderDrawColor(m_Renderer, 0, 200, 0, 255);
            SDL_RenderFillRect(m_Renderer,&t.rect);
        }
    }
}
