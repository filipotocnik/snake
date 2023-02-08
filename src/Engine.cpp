//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(800, 600);
    window.create(VideoMode(resolution.x, resolution.y), "snake", Style::Default);
    window.setFramerateLimit(fps);
}

void Engine::run() {
    // Loop traja dokler se okno ne zapre
    while(window.isOpen()) {
        draw();
    }
}
