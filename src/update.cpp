//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

void Engine::update() {
    // posodobi pozicijo kace
    // ce je cas od zadnjega premika enak ali vecji od hitrosti
    if(casOdZadnjegaPremika.asSeconds() >= seconds(1.f / float(hitrost)).asSeconds()){
        Vector2f thisSectionPosition = snake[0].getPozicija(); // pozicija glave
        Vector2f lastSectionPosition = thisSectionPosition;

        // preveri smer queue
        if(!smerQueue.empty()) {
            // preveri, da se kaca ne sme obrniti nazaj
            switch(snakeSmer) {
                case Smer::GOR:
                    if(smerQueue.front() != Smer::DOL) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;

                case Smer::DOL:
                    if(smerQueue.front() != Smer::GOR) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;

                case Smer::LEVO:
                    if(smerQueue.front() != Smer::DESNO) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;

                case Smer::DESNO:
                    if(smerQueue.front() != Smer::LEVO) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;
            }
            smerQueue.pop_front(); // izbrise smer v queue, ker je bila uporabljena
        }

        // posodobimo pozicijo glave kace
        switch(snakeSmer) {
            case Smer::DESNO:
                snake[0].setPozicija(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;

            case Smer::LEVO:
                snake[0].setPozicija(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;

            case Smer::GOR:
                snake[0].setPozicija(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;

            case Smer::DOL:
                snake[0].setPozicija(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
        }

        // posodobimo pozicijo repa kace
        for(int i = 1; i < snake.size(); i++) {
            thisSectionPosition = snake[i].getPozicija();
            snake[i].setPozicija(lastSectionPosition); // prejsnja pozicija
            lastSectionPosition = thisSectionPosition; // premakne prejsnjo pozicijo
        }

        // zazenemo update funkcije za vsaki del kace
        for (auto & i : snake) {
            i.update();
        }

        // resetiramo cas od zadnjega premika
        casOdZadnjegaPremika = Time::Zero;

    } // konec if stavka
}