//
//  board.cpp
//  ConwaysGame
//
//  Created by Jovian on 2022/12/4.
//  Copyright © 2022 Jovian. All rights reserved.
//

#include "board.hpp"
void Board::generate()
{
    for(int i = 0; i < this->m_TilesX; i++ )
        for(int j = 0; j < this->m_TilesY; j++ )
        {
            if(getNeighbors(Tile(i*TILE_SIZE,j*TILE_SIZE ), 1) == 3 && !locateTile(i*TILE_SIZE, j*TILE_SIZE) && !justPlaced(i*TILE_SIZE,j*TILE_SIZE))
            {
                Board::addTile(i*TILE_SIZE, j*TILE_SIZE);
            }
        }

}
std::vector<Tile> Board::getBoard()
{
    return this->tiles;
}
void Board::removeOldTiles()
{
    std::vector<Tile> nextGen;

    for(Tile &t: this->tiles)
    {
        if(t.alive())
        {
            nextGen.emplace_back(t);
        }
    }
    tiles.clear();
    for(Tile &t: nextGen)
        tiles.emplace_back(t);
    
}
bool Board::justPlaced(int x, int y)
{
    for(Tile &t: tiles)
        if(t.x == x && t.y == y && t.justPlaced)
            return true;
    return false;
}
bool Board::locateTile(int x, int y)
{
    for(Tile &t: tiles)
        if(t.x == x && t.y == y)
            return true;
    return false;
}
void Board::addTile(int x, int y)
{
    Tile tile = Tile(x,y);
    tile.justPlaced = true;
    tiles.push_back(tile);
}
void Board::addRandomTile()
{
    int x = rand()%32*16;
    int y = rand()%32*16;
    for(int i = 0; i < tiles.size(); i++)
        if(tiles[i].x == x && tiles[i].y == y)
            addRandomTile();
    Tile t = Tile(x,y);
    tiles.push_back(t);
}
void Board::update()
{
    for(Tile &t: this->tiles)
    {
        t.justPlaced = false;
        if(getNeighbors(t) < 2 || getNeighbors(t) > 3)
            t.isAlive = false;
    }
}
int Board::getNeighbors(Tile tile, int flags)
{
    int neighbors = 0;
    if(flags == 1)
    {
        for(Tile &t: tiles)
        {
            
            if(!t.justPlaced)
            {
                
                if(t.x-t.TILE_SIZE == tile.x && t.y == tile.y) //East
                {
                    neighbors++;
                }
                if(t.x+t.TILE_SIZE == tile.x && t.y == tile.y) //West
                {
                    neighbors++;
                }
                if(t.x == tile.x && t.y-t.TILE_SIZE == tile.y) //north
                {
                    neighbors++;
                }
                if(t.x == tile.x && t.y+t.TILE_SIZE == tile.y) //south
                {
                    neighbors++;
                }
                if(t.x-t.TILE_SIZE == tile.x && t.y-t.TILE_SIZE == tile.y) //north west
                {
                    neighbors++;
                }
                if(t.x+t.TILE_SIZE == tile.x && t.y-t.TILE_SIZE == tile.y) //north east
                {
                    neighbors++;
                }
                if(t.x-t.TILE_SIZE == tile.x && t.y+t.TILE_SIZE == tile.y) //southwest
                {
                    neighbors++;
                }
                if(t.x+t.TILE_SIZE == tile.x && t.y+t.TILE_SIZE == tile.y) //southeast
                {
                    neighbors++;
                }
            }
        }
    }
    
    return neighbors;
}

int Board::getNeighbors(Tile tile)
{
    int neighbors = 0;
    for(Tile &t: tiles)
    {

            if(t.x-t.TILE_SIZE == tile.x && t.y == tile.y) //East
            {
                neighbors++;
            }
            if(t.x+t.TILE_SIZE == tile.x && t.y == tile.y) //West
            {
                neighbors++;
            }
            if(t.x == tile.x && t.y-t.TILE_SIZE == tile.y) //north
            {
                neighbors++;
            }
            if(t.x == tile.x && t.y+t.TILE_SIZE == tile.y) //south
            {
                neighbors++;
            }
            if(t.x-t.TILE_SIZE == tile.x && t.y-t.TILE_SIZE == tile.y) //north west
            {
                neighbors++;
            }
            if(t.x+t.TILE_SIZE == tile.x && t.y-t.TILE_SIZE == tile.y) //north east
            {
                neighbors++;
            }
            if(t.x-t.TILE_SIZE == tile.x && t.y+t.TILE_SIZE == tile.y) //southwest
            {
                neighbors++;
            }
            if(t.x+t.TILE_SIZE == tile.x && t.y+t.TILE_SIZE == tile.y) //southeast
            {
                neighbors++;
            }
    }
    return neighbors;
}
