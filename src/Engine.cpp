//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

Engine::Engine() {
    // nastavljanje in kreiranje okna
    resolucija = Vector2f(800, 600);
    window.create(VideoMode(resolucija.x, resolucija.y), "Nibbles", Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    preveriLevelDatoteke();

    zacniIgro();

    font.loadFromFile("../datoteke/fonts/retro.ttf");
    setupText(&naslovText, font, "SNAKE", 26, Color::White);
    FloatRect naslovTextBounds = naslovText.getLocalBounds();
    naslovText.setPosition(Vector2f(resolucija.x / 2 - naslovTextBounds.width / 2, -6));

    setupText(&trenutniLevelText, font, "level 1", 26, Color::White);
    trenutniLevelText.setPosition(Vector2f(15, -6));
    // GlobalBounds, zato ker rabimo tudi pozicijo ne samo velikosti
    FloatRect trenutniLevelTextBounds = trenutniLevelText.getGlobalBounds();

    setupText(&applesEatenText, font, "apples 0", 26, Color::White);
    applesEatenText.setPosition(
            Vector2f(trenutniLevelTextBounds.left + trenutniLevelTextBounds.width + 20, -6));

    setupText(&scoreText, font, to_string(score), 26, Color::White);
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolucija.x - scoreTextBounds.width - 15, -6));
}

void Engine::zacniIgro() {
    score = 0;
    // zacetna hitrost in smer
    hitrost = 4;
    snakeSmer = Smer::DESNO;
    // cas od zadnjega premika je 0
    casOdZadnjegaPremika = Time::Zero;

    // resetira podatke
    applesEatenNaTemLevelu = 0;
    applesEatenTotal = 0;
    sekcijeZaDodati = 0;
    trenutniLevel = 1;

    smerQueue.clear(); // da se kaca ne zacne premikat kar nekam
    wallSekcije.clear(); // izbrise zide iz prejsnjega levela

    // nastavi StatusIgre na RUNNING, ce tega ni pause ne dela, ker ne izvede if stavka
    trenutniStatusIgre = StatusIgre::RUNNING;
    zadnjiStatusIgre = trenutniStatusIgre;

    loadLevel(trenutniLevel);
    noviSnake();
    premakniApple();

    trenutniLevelText.setString("level " + to_string(trenutniLevel));
    applesEatenText.setString("apples " + to_string(applesEatenTotal));
    FloatRect trenutniLevelTextBounds = trenutniLevelText.getGlobalBounds();
    applesEatenText.setPosition(
            Vector2f(trenutniLevelTextBounds.left + trenutniLevelTextBounds.width + 20, -6));
    scoreText.setString(to_string(score));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolucija.x - scoreTextBounds.width - 15, -6));

    setupText(&gameOverText, font, "GAME OVER", 60, Color::Red);
    // nevem zakaj tu textBounds ne dela, tak da sem sam izracunal x vrednost
    gameOverText.setPosition(Vector2f(200, 100));
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);

    setupText(&pritisniEnterText, font, "Pritisni ENTER, da zacnes znova", 30, Color::Blue);
    // nevem zakaj tu textBounds ne dela, tak da sem sam izracunal x vrednost
    pritisniEnterText.setPosition(Vector2f(100, 200));
    pritisniEnterText.setOutlineColor(Color::Black);
    pritisniEnterText.setOutlineThickness(2);

    setupText(&pausedText, font, "PAUSED", 60, Color::Yellow);
    // nevem zakaj tu textBounds ne dela, tak da sem sam izracunal x vrednost
    pausedText.setPosition(Vector2f(280, 200));
    pausedText.setOutlineColor(Color::Black);
    pausedText.setOutlineThickness(2);
}

/**
 * Poveca stevilko levela, zalaufa naslednji level in resetira kaco
 */
void Engine::zacniNaslednjiLevel() {
    trenutniLevel += 1;
    wallSekcije.clear();
    smerQueue.clear();
    hitrost = 4 + trenutniLevel;
    snakeSmer = Smer::DESNO;
    sekcijeZaDodati = 0;
    applesEatenNaTemLevelu = 0;

    loadLevel(trenutniLevel);
    noviSnake();
    premakniApple();

    trenutniLevelText.setString("level " + to_string(trenutniLevel));
    FloatRect trenutniLevelTextBounds = trenutniLevelText.getGlobalBounds();
    applesEatenText.setPosition(
            Vector2f(trenutniLevelTextBounds.left + trenutniLevelTextBounds.width + 20, -6));

}

// Kreiranje nove kace
void Engine::noviSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

// podaljsa kaco
void Engine::dodajSnakeSekcijo() {

    // doda novi del kace na isti pozicijo, kot prejsnji del
    Rect zadnjaSekcija = snake.back().getOblika().getGlobalBounds();
    // da koordinate iz Rect v Vector2f
    Vector2f novaPozicijaSekcije = Vector2f(zadnjaSekcija.left, zadnjaSekcija.top);
    snake.emplace_back(novaPozicijaSekcije);
}

void Engine::premakniApple() {
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
            if(i.getOblika().getGlobalBounds()
            .intersects(Rect<float>(novaAppleLokacija.x, novaAppleLokacija.y, 20, 20))) {
                slabaLokacija = true;
                break;
            }
        }

        // preveri, ce je v zidu
        for (auto & i : wallSekcije) {
            if(i.getOblika().getGlobalBounds()
            .intersects(Rect<float>(novaAppleLokacija.x, novaAppleLokacija.y, 20, 20))) {
                slabaLokacija = true;
                break;
            }
        }

    } while(slabaLokacija);

    apple.setPozicija(novaAppleLokacija);
}

void Engine::pause() {
    if(trenutniStatusIgre == StatusIgre::RUNNING) {
        zadnjiStatusIgre = trenutniStatusIgre;
        trenutniStatusIgre = StatusIgre::PAUSED;
    } else if(trenutniStatusIgre == StatusIgre::PAUSED) {
        trenutniStatusIgre = zadnjiStatusIgre;
    }
}

void Engine::setupText(Text *textItem, const Font &font, const String &value, int size, Color color) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(color);
}

/**
 * Preveri, da lahko odpremo vse datoteke
 * Dodaj imena datotek, ki se lahko odprejo v levels vector, povecaj vrednost maxLevels
 */
void Engine::preveriLevelDatoteke() {
    // Load levels
    ifstream levelsDatoteka("../datoteke/levels/levels.txt");
    ifstream testDatoteke;
    for(string levelVrstica; getline(levelsDatoteka, levelVrstica);) {
        // Preveri, da lahko odpremo level datoteko
        testDatoteke.open("../datoteke/levels/" + levelVrstica);
        if(testDatoteke.is_open()) {
            // level se odpre, dodamo ga na listo dosegljivih levelov
            levels.emplace_back("../datoteke/levels/" + levelVrstica);
            testDatoteke.close();
            maxLevels++;
        }
    }
}

/**
 * zalaufaj level iz datoteke in preveri za 'x' znake, da lahko dodamo zid
 * @param levelSt int - stevilov levelov
 */
void Engine::loadLevel(int levelSt) {
    string levelDatoteka = levels[levelSt - 1];
    ifstream level (levelDatoteka);
    string vrstica;
    if(level.is_open()) {
        for(int y = 0; y < 30; y++) {
            getline(level, vrstica);
            for(int x = 0; x < 40; x++) {
                if(vrstica[x] == 'x') {
                    wallSekcije.emplace_back(Wall(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
                }
            }
        }
    }
    level.close();
}

void Engine::run() {
    Clock ura;

    // Glavni loop
    while (window.isOpen()) {
        Time cas = ura.restart(); // resetira cas, vrne cas, ki je pretekel

        if(trenutniStatusIgre == StatusIgre::PAUSED || trenutniStatusIgre == StatusIgre::GAMEOVER) {
            // ce je na pavzi, preverimo za input, tak da lahko nadaljujemo igro
            input();

            // Narisi GAMEOVER
            if(trenutniStatusIgre == StatusIgre::GAMEOVER) {
                draw();
            }

            sleep(milliseconds(2)); // damo igro v sleep, da nene laufa loopov prehitro, ko je na pauzi
            continue; // skippa vse naslednje, dokler ne pride iz if stavka

        }

        casOdZadnjegaPremika += cas; // doda cas do casu od zadnjega premika

        input();
        update();
        draw();
    }
}