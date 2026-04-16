#include <iostream>
#include "./structures/structures.hpp"
#include "./sorting/sorting.hpp"
#include <mutex>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>

using namespace std;

mutex mtx;

string change_timer(sf::Clock* clock, sf::Text* timerText) {
    float elapsed = clock->getElapsedTime().asMilliseconds();
    int secs = (int) elapsed / 1000;
    int mili = (int) elapsed;
    stringstream ss;
    ss << "Elapsed Time: " << secs << "." << mili;
    timerText->setString(ss.str());
    return ss.str();
}

int main() {
    float tam = (float) randInt(25, 200);
    Vec v = Vec();

    preenche(&v, tam, 100, 400);

    sf::RenderWindow win(sf::VideoMode(1000, 500), "Sorting Algs");
    win.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("./assets/Montserrat/static/Montserrat-Black.ttf");

    sf::Text sortingMText;
    sortingMText.setFont(font);
    sortingMText.setCharacterSize(20);
    sortingMText.setFillColor(sf::Color::White);
    sortingMText.setPosition(sf::Vector2f(50, 30));
    stringstream SMTextStr;
    SMTextStr << "Mode: Quick Sort";
    sortingMText.setString(SMTextStr.str());

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(sf::Vector2f(50, 60));
    stringstream TimerTextStr;
    TimerTextStr << "Elapsed time";
    timerText.setString(TimerTextStr.str());

    sf::Text sizeText;
    sizeText.setFont(font);
    sizeText.setCharacterSize(20);
    sizeText.setFillColor(sf::Color::White);
    sizeText.setPosition(sf::Vector2f(50, 90));
    stringstream sizeTextStr;
    sizeTextStr << "Size: " << tam;
    sizeText.setString(sizeTextStr.str());

    sf::Event e;
    sf::Clock clock;
    thread t_sort;
    bool exit = false;
    bool animation = false;
    bool isSorted = false;
    bool running = false;
    int mode = 0;
    bool clockRun = true;
    string finalElapsedTime;
    while (win.isOpen() && !exit) {

        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                if (t_sort.joinable()) {
                    t_sort.join();
                }
                win.close();
                exit = true;
                break;
            }

            if (e.type == sf::Event::KeyPressed && !running) {
                if (!isSorted && e.key.code == sf::Keyboard::Return) {
                    clockRun = true;
                    running = true;
                    if (mode == 0) {
                        t_sort = thread(quick_sort, &v, ref(mtx));
                    } else if (mode == 1) {
                        t_sort = thread(merge_sort, &v, ref(mtx));
                    } else if (mode == 2) {
                        t_sort = thread(bubble_sort, &v, ref(mtx));
                    } else if (mode == 3) {
                        Heap h = Heap(&v);
                        t_sort = thread(heap_sort, &h, ref(mtx));
                    } else {
                        continue;
                    }
                }

                if (e.key.code == sf::Keyboard::R) {
                    tam = (float) randInt(25, 200);
                    sizeTextStr.str("");
                    sizeTextStr.clear();
                    sizeTextStr << "Size: " << tam;
                    sizeText.setString(sizeTextStr.str());
                    v.clear();
                    preenche(&v, tam, 100, 500);
                    animation = false;
                    isSorted = false;
                }

                if (e.key.code == sf::Keyboard::Num0) {
                    SMTextStr.clear();
                    SMTextStr.str("");
                    SMTextStr << "Mode: Quick Sort";
                    sortingMText.setString(SMTextStr.str());
                    mode = 0;
                } else if (e.key.code == sf::Keyboard::Num1) {
                    SMTextStr.clear();
                    SMTextStr.str("");
                    SMTextStr << "Mode: Merge Sort";
                    sortingMText.setString(SMTextStr.str());
                    mode = 1;
                } else if (e.key.code == sf::Keyboard::Num2) {
                    SMTextStr.clear();
                    SMTextStr.str("");
                    SMTextStr << "Mode: Bubble Sort";
                    sortingMText.setString(SMTextStr.str());
                    mode = 2;
                } else if (e.key.code == sf::Keyboard::Num3) {
                    SMTextStr.clear();
                    SMTextStr.str("");
                    SMTextStr << "Mode: Heap Sort";
                    sortingMText.setString(SMTextStr.str());
                    mode = 3;
                }
            }
        }

        

        if (!isSorted && t_sort.joinable()) {
            if (clockRun) change_timer(&clock, &timerText);
            win.clear(sf::Color::Black);
            if (sorted(&v) && t_sort.joinable()) {
                t_sort.join();
                isSorted = true;
                animation = true;
                clockRun = false;
                finalElapsedTime = change_timer(&clock, &timerText);
            } else if (sorted(&v)) {
                continue;
            }

            {
                lock_guard<mutex> lock(mtx);
                sf::RectangleShape e;
                e.setFillColor(sf::Color::Red);
                //e.setOutlineColor(sf::Color::Black);
                //e.setOutlineThickness(1);
                for (int i = 0; i < v.getSize(); i++) {
                    e.setSize(sf::Vector2f((1000 - tam) / tam, -1 * v[i]));
                    e.setPosition(sf::Vector2f((i*(1000/tam) + 1), 500));
                    win.draw(e);
                }
            }
            
            //this_thread::sleep_for(chrono::milliseconds(16));
        } else {

            clock.restart();
            timerText.setString(finalElapsedTime);
            sf::RectangleShape e;
            //e.setOutlineColor(sf::Color::Black);
            //e.setOutlineThickness(1);
            win.clear(sf::Color::Black);

            if (!isSorted) e.setFillColor(sf::Color::Red);
            else e.setFillColor(sf::Color::Green);

            if (animation) {
                animation = false;
                
                for (int i = 0; i < v.getSize(); i++) {
                    win.clear(sf::Color::Black);

                    for (int j = 0; j <= i; j++) {
                        e.setSize(sf::Vector2f((1000 - tam) / tam, -1 * v[j]));
                        e.setPosition(sf::Vector2f((j*(1000/tam) + 1), 500));
                        win.draw(e);
                    }

                    win.display();
                    this_thread::sleep_for(chrono::milliseconds(20));
                }
                running = false;
            } else {                
                for (int i = 0; i < v.getSize(); i++) {
                    e.setSize(sf::Vector2f((1000 - tam) / tam, -1 * v[i]));
                    e.setPosition(sf::Vector2f((i*(1000/tam) + 1), 500));
                    win.draw(e);
                }
            }          
        }

        win.draw(sizeText);
        win.draw(timerText);
        win.draw(sortingMText);
        win.display();
    }
}