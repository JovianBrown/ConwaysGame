//
//  gui.cpp
//  ConwaysGame
//
//  Created by Jovian on 2022/12/4.
//  Copyright © 2022 Jovian. All rights reserved.
//

#include "gui.hpp"

void GUI::addButtons(int numberOfButtons)
{
    
    int y = 0;
    Button buttonNewBoard = Button(512,y);
    buttonNewBoard.text = "update sim";
    y+=60;
    Button buttonUpdate = Button(512,y);
    buttonUpdate.text = "new random board";
    y+=60;
    Button buttonManual = Button(512,y);
    buttonManual.text = "manually place entities";
    y+=60;
    Button buttonQuit = Button(512,y);
    buttonQuit.text = "quit sim";
    y+=90;
    Button infoButton = Button(512,y);
    infoButton.h = 20;
    infoButton.text = "u)pdate  n)ew board  m)anual mode";
    
    buttons.emplace_back(buttonNewBoard);
    buttons.emplace_back(buttonUpdate);
    buttons.emplace_back(buttonManual);
    buttons.emplace_back(buttonQuit);

    buttons.emplace_back(infoButton);


}
void GUI::update(SDL_Rect &mouseRect)
{
    for(int i = 0; i < buttons.size(); i++)
    {
        if(SDL_HasIntersection(buttons[i].rect, &mouseRect))
        {
            menuItem = i;
        }
    }
}
int GUI::getMenuItem()
{
    return menuItem;
}
void GUI::render(SDL_Renderer* renderer)
{
    SDL_Rect buttonRect;
    for(Button &b: buttons)
    {
        buttonRect.x = b.x;
        buttonRect.y = b.y;
        buttonRect.w = b.w;
        buttonRect.h = b.h;
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 50);
        SDL_RenderDrawRect(renderer,&buttonRect);
        const char* buttonText = b.text.c_str();
        surf=TTF_RenderText_Solid(font,buttonText,b.color);
        text=SDL_CreateTextureFromSurface(renderer,surf);
        SDL_FreeSurface(surf);
        SDL_RenderCopy(renderer,text,NULL,&buttonRect);
    }
}
