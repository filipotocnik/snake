//
// Created by Filip Potočnik on 08/02/2023.
//

#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "../headers/Snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Engine {
private:
    // Okno
    Vector2f resolution;
    RenderWindow window;
    const unsigned int fps = 60;
    static const Time TimePerFrame;

    vector<Snake> snake;

public:
    Engine();

    void input();

    void draw();

    void newSnake();

    void addSnake();

    void run();
};


#endif //SNAKE_ENGINE_H
