//
//  board.hpp
//  ConwaysGame
//
//  Created by Jovian on 2022/12/4.
//  Copyright © 2022 Jovian. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
static int TILE_SIZE = 8;
#define EAST 8;
#define WEST -TILE_SIZE;
#define SOUTH TILE_SIZE;
#define NORTH -TILE_SIZE;
struct Tile
{
    Tile(int xPos, int yPos)
    {
        x = xPos;
        y = yPos;
        rect.x = x;
        rect.y = y;
        rect.w = TILE_SIZE;
        rect.h = TILE_SIZE;
    }
    bool alive();
    int x;
    int y;
    bool isAlive = true;
    bool justPlaced = true;
    SDL_Rect rect;
};

class Board
{
    public:
        Board(int bWidth, int bHeight)
        {
            width = bWidth;
            height = bHeight;
            m_TilesX = width/TILE_SIZE;
            m_TilesY = height/TILE_SIZE;
            m_TotalTiles = (width / TILE_SIZE)*(height/ TILE_SIZE);
        }
        void addTile(int x, int y);
        void removeOldTiles();
        std::vector<Tile> getBoard();
        void addRandomTile();
        bool locateTile(int x, int y);
        bool justPlaced(int x, int y);
        void generate();
        int getNeighbors(Tile tile);
        int getNeighbors(Tile tile, int flags);
        void deleteAllTiles();
        void update();
    private:
        int width;
        int height;
        int m_TotalTiles;
        int m_TilesX;
        int m_TilesY;
        std::vector <Tile> tiles;
};
#endif /* board_hpp */
