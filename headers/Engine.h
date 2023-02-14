//
// Created by Filip Potočnik on 08/02/2023.
//

#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "../headers/Snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
// vector, pri katerem lahko vzamemo od zacetka ali konca
#include <deque>

using namespace sf;
using namespace std;

class Engine {
private:
    // Okno
    Vector2f resolucija;
    RenderWindow window;
    const unsigned int fps = 60;
    static const Time TimePerFrame;

    vector<Snake> snake;

    int smer;
    // smer levo, desno, gor, dol
    deque<int> smerQueue;
    int hitrost;

    Time casOdZadnjegaPremika;

public:
    Engine();

    enum Smer {gor, desno, levo, dol};

    void input();

    void dodajSmer(int novaSmer);

    void update();

    void draw();

    void newSnake();

    void dodajSnake();

    void run();
};


#endif //SNAKE_ENGINE_H
