//
// Created by Filip Potočnik on 08/02/2023.
//

#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "../headers/Snake.h"
#include "../headers/Apple.h"
#include <SFML/Graphics.hpp>
//oblika
#include <SFML/Graphics/RectangleShape.hpp>
//vector
#include <vector>
// podobno vectorju, pri katerem lahko vzamemo od zacetka ali konca
#include <deque>

using namespace sf;
using namespace std;

class Engine {
private:
    // Window
    Vector2f resolucija;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<Snake> snake;

    int snakeSmer;
    deque<int> smerQueue; // "cakalna vrsta" za ukaze s tipkovnice za smer
    int hitrost;
    int sectionsToAdd; // koliko sekcij je treba dodati

    Apple apple;

    Time casOdZadnjegaPremika;

public:
    enum Smer { GOR, DOL, DESNO, LEVO}; // namesto stevilk so vrednosti poimenovane

    Engine();

    void input();

    void dodajSmer(int novaSmer);

    void update();

    void draw();

    void newSnake();
    void addSnakeSection();

    void moveApple();

    // Glavni loop
    void run();

};


#endif //SNAKE_ENGINE_H
