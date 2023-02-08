//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"


void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        // zapre okno
        if (event.type == Event::Closed) {
            window.close();
        }

        // tipkovnica input
        if (event.type == Event::KeyPressed) {
            // zapre okno
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }
    }
}
