//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolucija = Vector2f(800, 600);
    window.create(VideoMode(resolucija.x, resolucija.y), "snake", Style::Default);
    window.setFramerateLimit(fps);

    hitrost = 2;
    smer = Smer::desno;

    casOdZadnjegaPremika = Time::Zero;

    newSnake();
}

// zacetna kaca
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

void Engine::dodajSnake() {
    Vector2f newSectionPosition = snake[snake.size() - 1].getPozicija();
    snake.emplace_back(newSectionPosition);
}

void Engine::run() {
    Clock ura;

    // loop dela dokler je okno odprto
    while (window.isOpen()) {
        Time cas = ura.restart();
        casOdZadnjegaPremika += cas;

        input();
        update();
        draw();
    }
}
