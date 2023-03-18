//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Snake.h"

Snake::Snake(Vector2f zacetnaPozicija) {
    section.setSize(Vector2f(20, 20));
    section.setFillColor(Color::Green);
    section.setPosition(zacetnaPozicija);
    pozicija = zacetnaPozicija;
}

Vector2f Snake::getPozicija() {
    return pozicija;
}

void Snake::setPozicija(Vector2f novaPozicija) {
    pozicija = novaPozicija;
}

RectangleShape Snake::getShape() {
    return section;
}

void Snake::update() {
    section.setPosition(pozicija);
}