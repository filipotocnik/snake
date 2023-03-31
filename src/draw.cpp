//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

void Engine::draw() {
    window.clear(Color::Black);

    // narise zide
    for(auto & i : wallSekcije) {
        window.draw(i.getOblika());
    }

    // narise jabolko
    window.draw(apple.getOblika());

    // narise sekcije kace
    for (auto & i : snake) {
        window.draw(i.getOblika());
    }

    // narisi text
    window.draw(naslovText);
    window.draw(trenutniLevelText);
    window.draw(applesEatenText);
    window.draw(scoreText);

    // narisi GameOver
    if(trenutniStatusIgre == StatusIgre::GAMEOVER) {
        window.draw(gameOverText);
        window.draw(pritisniEnterText);
        window.draw(highScoreText);
    }

    // narisi paused
    if(trenutniStatusIgre == StatusIgre::PAUSED) {
        window.draw(pausedText);
    }

    window.display();
}
