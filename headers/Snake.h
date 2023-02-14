//
// Created by Filip Potočnik on 08/02/2023.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;


class Snake {
private:
    Vector2f pozicija;
    RectangleShape sekcija;
public:
    explicit Snake(Vector2f startPosition);

    Vector2f getPozicija();
    void setPozicija(Vector2f newPosition);

    RectangleShape getShape();

    void update();
};


#endif //SNAKE_SNAKE_H
