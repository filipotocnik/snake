//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Snake.h"

Snake::Snake(Vector2f zacetnaPozicija) {
    sekcija.setSize(Vector2f(20, 20));
    sekcija.setFillColor(Color::Green);
    sekcija.setPosition(zacetnaPozicija);
    pozicija = zacetnaPozicija;
}

void Snake::setPozicija(Vector2f novaPozicija) {
    sekcija.setPosition(novaPozicija);
}

RectangleShape Snake::getOblika() {
    return sekcija;
}