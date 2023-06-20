#include "Hex.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Hex::Hex(int bpX, int bpY, int owner2) {
    owner = owner2;
    setHex(bpX, bpY);
}
Hex::~Hex() {

}

void Hex::setHex(int bpX, int bpY) {
    boardPositionX = bpX;
    boardPositionY = bpY;

    hexagon.setRadius(50);
    hexagon.setOutlineColor(Color::White);
    hexagon.setOutlineThickness(3);
    hexagon.setPointCount(6);
    hexagon.setOrigin(0,0);
    hexagon.setRotation(30);

    colorHex();
    setPosition();
}

void Hex::setPosition() {
    double moveX = getRadius2() * 2;
    double moveY = (getRadius2() * (sqrt(3)/2));

    //pozmieniac nazwy

    double offsetX = moveX/2 + 31.5;
    double offsetY = 0;

    if(boardPositionX>4)
    {
        offsetY += (moveY+2.5)*(boardPositionX-4);
    }
    else if(boardPositionX<4)
    {
        offsetY += (moveY+2.5)*(4-boardPositionX);
    }
    windowPositionX = (boardPositionX * offsetX) + 475;
    windowPositionY = (boardPositionY)*2 * moveY+offsetY + (5 * boardPositionY) + 20;

    hexagon.setPosition(windowPositionX, windowPositionY);
}

bool Hex::isInsideHexagon(Vector2i pos) {
    float upY = hexagon.getTransform().transformPoint(hexagon.getPoint(5)).y;
    float leftX = hexagon.getTransform().transformPoint(hexagon.getPoint(4)).x;
    float downY = hexagon.getTransform().transformPoint(hexagon.getPoint(3)).y;
    float rightX = hexagon.getTransform().transformPoint(hexagon.getPoint(1)).x;

    if(pos.x >= leftX && pos.x <= rightX && pos.y >= upY && pos.y <= downY){
        return true;
    }else{
        return false;
    }
}

void Hex::colorHex() {
    int number = 0;
    for(int i = 0; i < 4; i++){
        if(hexState[i] == state){
            number = i;
        }
    }

    switch(number){
        case 0: hexagon.setOutlineColor(Color::White);
            break;
        case 1: hexagon.setOutlineColor(Color(5,47,115));
            break;
        case 2: hexagon.setOutlineColor(Color(5,47,115));
            break;
        case 3: hexagon.setOutlineColor(Color(20,92,2));
            break;
    }

    switch (getOwner()) {
        case 0: hexagon.setFillColor(Color(50,1,1));
            break;
        case 1: hexagon.setFillColor(Color(150,3,3));
            break;
        case 2: hexagon.setFillColor(Color(94,91,3));
            break;
        case 3: hexagon.setFillColor(Color::Black);
            break;
    }
}

void Hex::draw(RenderWindow &boardWindow) {
    colorHex();
    boardWindow.draw(hexagon);
}







void Hex::setOwner(int o) {
    this->owner = o;
}

void Hex::setState(const String &s) {
    state = s;
}

float Hex::getWindowPositionX() const {
    return windowPositionX;
}

int Hex::getOwner() const {
    return owner;
}

float Hex::getWindowPositionY() const {
    return windowPositionY;
}

const String &Hex::getState() const {
    return state;
}

int Hex::getBoardPositionX() const {
    return boardPositionX;
}

int Hex::getBoardPositionY() const {
    return boardPositionY;
}





