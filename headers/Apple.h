//
// Created by Filip Potočnik on 18/03/2023.
//

#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class Apple {
private:
    RectangleShape appleOblika;

public:
    Apple();

    void setPozicija(Vector2f novaPozicija);

    RectangleShape getOblika();
};


#endif //SNAKE_APPLE_H
