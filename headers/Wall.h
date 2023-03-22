//
// Created by Filip Potočnik on 19/03/2023.
//

#ifndef SNAKE_WALL_H
#define SNAKE_WALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class Wall {
private:
    RectangleShape wallOblika;

public:
    Wall(Vector2f pozicija, Vector2f velikost);

    RectangleShape getOblika();
};


#endif //SNAKE_WALL_H
