//
// Created by Filip Potočnik on 19/03/2023.
//

#include "../headers/Wall.h"

Wall::Wall(Vector2f pozicija, Vector2f velikost) {
    wallOblika.setSize(velikost);
    wallOblika.setFillColor(Color::Blue);
    wallOblika.setPosition(pozicija);
}

RectangleShape Wall::getOblika() {
    return wallOblika;
}
