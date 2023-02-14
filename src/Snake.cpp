//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Snake.h"

Snake::Snake(Vector2f startPosition) {
    sekcija.setSize(Vector2f(20, 20));
    sekcija.setFillColor(Color::Blue);
    sekcija.setPosition(startPosition);
    pozicija = startPosition;
}

Vector2f Snake::getPozicija() {
    return pozicija;
}

void Snake::setPozicija(Vector2f newPosition) {
    pozicija = newPosition;
}

RectangleShape Snake::getShape() {
    return sekcija;
}

void Snake::update() {
    sekcija.setPosition(pozicija);
}
