//
// Created by Filip Potočnik on 14/02/2023.
//

#include "../headers/Engine.h"

void Engine::update() {
    // update pozicijo kace
    if (casOdZadnjegaPremika.asSeconds() >= seconds(1.f / float(hitrost)).asSeconds()) {
        Vector2f trenutnaSnakePozicija = snake[0].getPozicija();
        Vector2f zadnjaSnakePozicija = trenutnaSnakePozicija;

        // preveri smer queue
        if(smerQueue.empty()) {
            // kaca ne sme iti nazaj
            switch (smer) {
                case Smer::gor:
                    if(smerQueue.front() != Smer::dol) {
                        smer = smerQueue.front();
                    }
                    break;

                case Smer::dol:
                    if(smerQueue.front() != Smer::gor) {
                        smer = smerQueue.front();
                    }
                    break;

                case Smer::levo:
                    if(smerQueue.front() != Smer::desno) {
                        smer = smerQueue.front();
                    }
                    break;

                case Smer::desno:
                    if(smerQueue.front() != Smer::levo) {
                        smer = smerQueue.front();
                    }
                    break;
            }
            smerQueue.pop_front();
        }

        // update glavo kace
        switch(smer) {
            case Smer::gor:
                snake[0].setPozicija(Vector2f(trenutnaSnakePozicija.x, trenutnaSnakePozicija.y + 20));
                break;

            case Smer::dol:
                snake[0].setPozicija(Vector2f(trenutnaSnakePozicija.x, trenutnaSnakePozicija.y - 20));
                break;


            case Smer::desno:
                snake[0].setPozicija(Vector2f(trenutnaSnakePozicija.x + 20, trenutnaSnakePozicija.y));
                break;

            case Smer::levo:
                snake[0].setPozicija(Vector2f(trenutnaSnakePozicija.x - 20, trenutnaSnakePozicija.y));
                break;

        }

        // update rep kace
        for (int i = 1; i < snake.size(); i++) {
            trenutnaSnakePozicija = snake[i].getPozicija();
            snake[i].setPozicija(zadnjaSnakePozicija);
            zadnjaSnakePozicija = trenutnaSnakePozicija;
        }

        // resetiramo timer
        casOdZadnjegaPremika = Time::Zero;
    } // konec update
}