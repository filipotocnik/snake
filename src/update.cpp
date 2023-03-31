//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

void Engine::update() {
    // posodobi pozicijo kace
    // ce je cas od zadnjega premika enak ali vecji od hitrosti
    if(casOdZadnjegaPremika.asSeconds() >= seconds(1.f / float(hitrost)).asSeconds()){
        Rect zadnjaSekcija = snake.front().getOblika().getGlobalBounds();
        // da koordinate iz Rect v Vector2f
        Vector2f pozicijaSekcije = Vector2f(zadnjaSekcija.left, zadnjaSekcija.top); // pozicija glave
        Vector2f zadnjaPozicijaSekcije = pozicijaSekcije;

        // preveri smer queue
        if(!smerQueue.empty()) {
            // preveri, da se kaca ne sme obrniti nazaj
            switch(snakeSmer) {
                case Smer::GOR:
                    if(smerQueue.front() != Smer::DOL) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;

                case Smer::DOL:
                    if(smerQueue.front() != Smer::GOR) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;

                case Smer::LEVO:
                    if(smerQueue.front() != Smer::DESNO) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;

                case Smer::DESNO:
                    if(smerQueue.front() != Smer::LEVO) { // preveri, da ne gre nazaj
                        snakeSmer = smerQueue.front();
                    }
                    break;
            }
            smerQueue.pop_front(); // izbrise smer v queue, ker je bila uporabljena
        }

        // posodobi score
        score+= snake.size() + (applesEatenTotal + 1); // + 1 ker je na zacetku 0 applesEaten
        // preveri, ce je vecji kot highScore
        if(score > highScore) {
            highScore = score;
        }
        scoreText.setString(to_string(score));
        FloatRect scoreTextBounds = scoreText.getLocalBounds(); // velikost texta
        scoreText.setPosition(Vector2f(resolucija.x - scoreTextBounds.width - 15, -6));

        // preverimo, ce se mora kaca podaljsat
        if (sekcijeZaDodati) { // je true, ce je vec kot 0
            dodajSnakeSekcijo();
            sekcijeZaDodati--;
        }

        // posodobimo pozicijo glave kace
        switch(snakeSmer) {
            case Smer::DESNO:
                snake[0].setPozicija(Vector2f(pozicijaSekcije.x + 20, pozicijaSekcije.y));
                break;

            case Smer::LEVO:
                snake[0].setPozicija(Vector2f(pozicijaSekcije.x - 20, pozicijaSekcije.y));
                break;

            case Smer::GOR:
                snake[0].setPozicija(Vector2f(pozicijaSekcije.x, pozicijaSekcije.y - 20));
                break;

            case Smer::DOL:
                snake[0].setPozicija(Vector2f(pozicijaSekcije.x, pozicijaSekcije.y + 20));
                break;
        }

        // posodobimo pozicijo repa kace
        for(int i = 1; i < snake.size(); i++) {
            zadnjaSekcija = snake[i].getOblika().getGlobalBounds();
            // da koordinate iz Rect v Vector2f
            pozicijaSekcije = Vector2f(zadnjaSekcija.left, zadnjaSekcija.top); // pozicija glave
            snake[i].setPozicija(zadnjaPozicijaSekcije); // prejsnja pozicija
            zadnjaPozicijaSekcije = pozicijaSekcije; // premakne prejsnjo pozicijo
        }

        // preveri, ce je kaca pojedla jabolko
        if(snake[0].getOblika().getGlobalBounds().intersects(apple.getOblika().getGlobalBounds())) {
            // kaca zadene jabolko, dodamo vec sekcij kaci, povecamo hitrost, premaknemo jabolko
            applesEatenNaTemLevelu += 1;
            applesEatenTotal += 1;
            applesEatenText.setString("apples " + to_string(applesEatenTotal));
            FloatRect trenutniLevelTextBounds = trenutniLevelText.getGlobalBounds();
            applesEatenText.setPosition(
                    Vector2f(trenutniLevelTextBounds.left + trenutniLevelTextBounds.width + 20, -6));

            bool zacetekNovegaLevela = false;
            if(applesEatenNaTemLevelu >= applesZaNaslednjiLevel) {
                // zacni naslednji level, ce jih je vec
                // drugace ostani na zadnjem levelu
                if(trenutniLevel < maxLevels) {
                    zacetekNovegaLevela = true;
                    zacniNaslednjiLevel();
                }
            }
            if(!zacetekNovegaLevela) {
                sekcijeZaDodati += 4;
                // ko kaca poje jabolko se hitrost ne spremeni
                // hitrost++;
                premakniApple();
            }
        }

        // preverimo, ce se je kaca zadela sama v sebe
        for(int i = 1; i < snake.size(); i++) {
            if(snake[0].getOblika().getGlobalBounds().intersects(snake[i].getOblika().getGlobalBounds())) {
                // Game Over
                trenutniStatusIgre = StatusIgre::GAMEOVER;
            }
        }

        // preverimo, ce se je kaca zadela v zid
        for(auto & i : wallSekcije) {
            if(snake[0].getOblika().getGlobalBounds().intersects(i.getOblika().getGlobalBounds())) {
                // game over
                trenutniStatusIgre = StatusIgre::GAMEOVER;
                saveHighScore(highScore);
            }
        }

        // resetiramo cas od zadnjega premika
        casOdZadnjegaPremika = Time::Zero;

    } // konec if stavka
}