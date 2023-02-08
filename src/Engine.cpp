//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(800, 600);
    window.create(VideoMode(resolution.x, resolution.y), "snake", Style::Default);
    window.setFramerateLimit(fps);

    newSnake();
}

// zacetna kaca
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

void Engine::addSnake() {
    Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Engine::run() {

    // loop dela dokler je okno odprto
    while (window.isOpen()) {
        input();
        draw();
    }
}
