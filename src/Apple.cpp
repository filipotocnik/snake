//
// Created by Filip Potočnik on 18/03/2023.
//

#include "../headers/Apple.h"

Apple::Apple() {
    Vector2f zacetnaPozicija(400, 300);
    sprite.setSize(Vector2f(20, 20));
    sprite.setFillColor(Color::Red);
    sprite.setPosition(zacetnaPozicija);
}

void Apple::setPozicija(Vector2f novaPozicija) {
    sprite.setPosition(novaPozicija);
}

RectangleShape Apple::getSprite() {
    return sprite;
}
