//
//  board.hpp
//  ConwaysGame
//
//  Created by mac on 2022/12/4.
//  Copyright © 2022 Jovian. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
static int TILE_SIZE = 16;
struct Tile
{
    Tile(int xPos, int yPos)
    {
        x = xPos;
        y = yPos;
        rect.x = x;
        rect.y = y;
        rect.w = 16;
        rect.h = 16;
    }
    bool alive()
    {
        return isAlive;
    }
    const int TILE_SIZE = 16;
    int x;
    int y;
    bool isAlive = true;
    bool justPlaced = true;
    SDL_Rect rect;
};

class Board
{
    public:
        Board(int width, int height)
        {
            this->width = width;
            this->height = height;
            this->m_TilesX = width/TILE_SIZE;
            this->m_TilesY = height/TILE_SIZE;

            this->m_TotalTiles = (width / TILE_SIZE)*(height/ TILE_SIZE);
        }
        void addTile(int x, int y);
        void removeOldTiles();

        std::vector<Tile> getBoard()
        {
            return this->tiles;
        }
        void addRandomTile()
        {
            int x = rand()%32*16;
            int y = rand()%32*16;
            for(int i = 0; i < tiles.size(); i++)
                if(tiles[i].x == x && tiles[i].y == y)
                    addRandomTile();
            Tile t = Tile(x,y);
            tiles.push_back(t);
        }
        bool locateTile(int x, int y)
        {
            for(Tile &t: tiles)
                if(t.x == x && t.y == y)
                    return true;
            return false;
        }
        bool justPlaced(int x, int y)
        {
            for(Tile &t: tiles)
                if(t.x == x && t.y == y && t.justPlaced)
                    return true;
            return false;
        }
        void generate();
        int getNeighbors(Tile tile);
        int getNeighbors(Tile tile, int flags);

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
