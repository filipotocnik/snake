//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

void Engine::draw() {
    window.clear(Color::Black);

    // narise jabolko
    window.draw(apple.getSprite());

    // narise sekcije kace
    for (auto & i : snake) {
        window.draw(i.getShape());
    }

    window.display();
}
