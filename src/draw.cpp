//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

void Engine::draw() {
    window.clear(Color::Black);

    // narise rep kace
    for (auto & s : snake) {
        window.draw(s.getShape());
    }

    window.display();
}
