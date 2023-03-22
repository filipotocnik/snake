//
// Created by Filip Potočnik on 18/03/2023.
//

#include "../headers/Apple.h"

Apple::Apple() {
    Vector2f zacetnaPozicija(400, 300);
    appleOblika.setSize(Vector2f(20, 20));
    appleOblika.setFillColor(Color::Red);
    appleOblika.setPosition(zacetnaPozicija);
}

void Apple::setPozicija(Vector2f novaPozicija) {
    appleOblika.setPosition(novaPozicija);
}

RectangleShape Apple::getOblika() {
    return appleOblika;
}
