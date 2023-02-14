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
            // preveri event za escape key
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }

            // smer
            if(event.key.code == sf::Keyboard::Up) {
                dodajSmer(Smer::gor);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                dodajSmer(Smer::dol);
            }
            else if (event.key.code == sf::Keyboard::Left) {
                dodajSmer(Smer::levo);
            }
            else if (event.key.code == sf::Keyboard::Right) {
                dodajSmer(Smer::desno);
            }
        }
    }
}

void Engine::dodajSmer(int novaSmer) {
    if (smerQueue.empty()) {
        smerQueue.emplace_back(novaSmer);
    } else {
        if (smerQueue.back() != novaSmer) {
            smerQueue.emplace_back(novaSmer);
        }
    }
}