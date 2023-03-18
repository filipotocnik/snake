//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    // nastavljanje in kreiranje okna
    resolucija = Vector2f(800, 600);
    window.create(VideoMode(resolucija.x, resolucija.y), "Nibbles", Style::Default);
    window.setFramerateLimit(FPS);

    // zacetna hitrost in smer
    hitrost = 2;
    snakeSmer = Smer::DESNO;

    // cas od zadnjega premika je 0
    casOdZadnjegaPremika = Time::Zero;

    sectionsToAdd = 0;
    newSnake();
    moveApple();
}

// Kreiranje nove kace
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

// podaljsa kaco
void Engine::addSnakeSection() {

    // doda novi del kace na isti pozicijo, kot prejsnji del
    Vector2f newSectionPosition = snake[snake.size() - 1].getPozicija();
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    // poisci lokacijo, kjer je varno postaviti jabolko
    // nesme biti v kaci, ali v zidu

    // razdeli polje na sekcije v velikosti jabolke - odstrani 2 zaradi zunanjih zidov
    Vector2f appleResolucija = Vector2f(resolucija.x / 20 - 2, resolucija.y / 20 - 2);
    Vector2f novaAppleLokacija;
    bool slabaLokacija = false;
    srand(time(nullptr));
    // loop dokler ne najdemo dobre lokacije
    do {
        slabaLokacija = false;
        // generiramo nakljucno lokacijo
        novaAppleLokacija.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolucija.x)) * 20;
        novaAppleLokacija.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolucija.y)) * 20;

        // preveri, ce je v kaci
        for (auto & i : snake) {
            if(i.getShape().getGlobalBounds()
            .intersects(Rect<float>(novaAppleLokacija.x, novaAppleLokacija.y, 20, 20))) {
                slabaLokacija = true;
                break;
            }
        }

        // TODO - dodaj check za apple v zidih


    } while(slabaLokacija);

    apple.setPozicija(novaAppleLokacija);
}

void Engine::run() {
    Clock ura;

    // Glavni loop
    while (window.isOpen()) {
        Time cas = ura.restart(); // resetira cas, vrne cas, ki je pretekel
        casOdZadnjegaPremika += cas; // doda cas do casu od zadnjega premika

        input();
        update();
        draw();
    }
}