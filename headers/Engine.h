//
// Created by Filip Potočnik on 08/02/2023.
//

#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "../headers/Snake.h"
#include "../headers/Apple.h"
#include "../headers/Wall.h"
#include <SFML/Graphics.hpp>
//oblika
#include <SFML/Graphics/RectangleShape.hpp>
//vector
#include <vector>
// podobno vectorju, pri katerem lahko vzamemo od zacetka ali konca
#include <deque>
#include <fstream>

using namespace sf;
using namespace std;

class Engine {
private:
    // Window
    Vector2f resolucija;
    RenderWindow window;
    const unsigned int FPS = 60;

    vector<Snake> snake;

    int snakeSmer;
    deque<int> smerQueue; // "cakalna vrsta" za ukaze s tipkovnice za smer
    int hitrost;
    int sekcijeZaDodati; // koliko sekcij je treba dodati
    int applesEatenNaTemLevelu;
    int applesEatenTotal;
    int score;
    int highScore;
    const unsigned int applesZaNaslednjiLevel = 5;

    Apple apple;

    vector<Wall> wallSekcije;
    int trenutniLevel;
    int maxLevels;
    vector<String> levels;

    Font font;
    Text naslovText;
    Text applesEatenText;
    Text trenutniLevelText;
    Text scoreText;
    Text highScoreText;
    Text gameOverText;
    Text pritisniEnterText;
    Text pausedText;

    Time casOdZadnjegaPremika;

    int trenutniStatusIgre;
    int zadnjiStatusIgre; // za nadaljevanje igre po PAUSE

public:
    enum Smer { GOR, DOL, DESNO, LEVO}; // namesto stevilk so vrednosti poimenovane
    enum StatusIgre { RUNNING, PAUSED, GAMEOVER };

    Engine();

    void input();

    void dodajSmer(int novaSmer);

    void update();

    void draw();

    static void setupText(Text *textItem, const Font &font, const String &value, int size, Color color);

    void noviSnake();
    void dodajSnakeSekcijo();

    void premakniApple();

    void preveriLevelDatoteke();

    void loadLevel(int levelSt);

    void loadHighScore();

    void saveHighScore(int stevilka);

    void zacniNaslednjiLevel();

    void zacniIgro();

    void pause();

    // Glavni loop
    void run();

};


#endif //SNAKE_ENGINE_H
