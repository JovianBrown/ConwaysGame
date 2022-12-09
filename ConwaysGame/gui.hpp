//
//  gui.hpp
//  ConwaysGame
//
//  Created by Jovian on 2022/12/4.
//  Copyright © 2022 Jovian. All rights reserved.
//

#ifndef gui_hpp
#define gui_hpp

#include <stdio.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include <iostream>
struct Button
{
    int x;
    int y;
    int w;
    int h;
    SDL_Color color;
    SDL_Rect *rect;
    std::string text;
    Button(int locationX, int locationY)
    {
        x = locationX+20;
        y = locationY+20;
        w = 200;
        h = 50;
        rect = new SDL_Rect();
        rect->w = w;
        rect->h = h;
        rect->x = x;
        rect->y = y;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
    }
};
class GUI
{
    public:
        GUI(int locationX, int locationY, int width, int height)
        {
            x = locationX;
            y = locationY;
            w = width;
            h = height;
            TTF_Init();
            font = TTF_OpenFont("res/Georgia.ttf",12);
            if(font==NULL)
            {
                std::cout<<"unable to load font"<<std::endl;
            }
        }
        int getMenuItem();
        void update(SDL_Rect &mouseRect);
        void addButtons(int numberOfButtons);
        void render(SDL_Renderer* renderer);
    private:
        int x;
        int y;
        int w;
        int h;
        int menuItem=-1;
        TTF_Font *font;
        SDL_Surface *message;
        SDL_Surface *surf;
        SDL_Texture *text;
        std::vector<Button> buttons;
};

#endif /* gui_hpp */
