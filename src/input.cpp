//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"


void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        // Okno zaprto
        if (event.type == Event::Closed) {
            window.close();
        }

        // input s tipkovnice
        if (event.type == Event::KeyPressed) {
            // zapri program z ESC
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }

            // Pause
            if(event.key.code == Keyboard::Space) {
                pause();
            }

            // Nova igra
            if(trenutniStatusIgre == StatusIgre::GAMEOVER) {
                if(event.key.code == Keyboard::Enter) {
                    zacniIgro();
                }
            }

            // Smer
            if(event.key.code == Keyboard::Up) {
                dodajSmer(Smer::GOR);
            } else if(event.key.code == Keyboard::Down) {
                dodajSmer(Smer::DOL);
            } else if(event.key.code == Keyboard::Right) {
                dodajSmer(Smer::DESNO);
            } else if(event.key.code == Keyboard::Left) {
                dodajSmer(Smer::LEVO);
            }
        }
    }
}

void Engine::dodajSmer(int novaSmer) {
    if(smerQueue.empty()) { // preveri, ce je queue prazen
        smerQueue.emplace_back(novaSmer);
    } else { // ce ni prazna
        if(smerQueue.back() != novaSmer) { // preveri, da nova smer ni enaka prejsnji
            smerQueue.emplace_back(novaSmer);
        }
    }
}