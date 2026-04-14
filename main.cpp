#include <iostream>
#include "./structures/vec.hpp"
#include "./sorting/quick_sort.hpp"
#include <mutex>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;

mutex mtx;

int main() {
    int tam = 50;
    Vec v = Vec();

    preenche(&v, tam, 100, 400);

    sf::RenderWindow win(sf::VideoMode(1000, 500), "Sorting Algs");
    win.setFramerateLimit(60);
    sf::Event e;
    thread t_sort;
    bool exit = false;
    bool animation = true;
    bool slow = false;
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

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Return) {
                    t_sort = thread(quick_sort, &v, ref(mtx));
                    animation = false;
                    slow = true;
                }

                if (e.key.code == sf::Keyboard::R) {
                    v.clear();
                    preenche(&v, tam, 100, 500);
                    animation = true;
                    slow = false;
                }
            }
        }

        

        if (t_sort.joinable()) {
            win.clear(sf::Color::Black);
            if (sorted(&v) && t_sort.joinable()) {
                t_sort.join();
            } else if (sorted(&v)) {
                continue;
            }

            {
                lock_guard<mutex> lock(mtx);
                sf::RectangleShape e;
                e.setFillColor(sf::Color::Red);
                e.setOutlineColor(sf::Color::Black);
                e.setOutlineThickness(1);
                for (int i = 0; i < v.getSize(); i++) {
                    e.setSize(sf::Vector2f((1000 - tam) / tam, -1 * v[i]));
                    e.setPosition(sf::Vector2f((i*(1000/tam) + 1), 500));
                    win.draw(e);
                }
            }
            
            this_thread::sleep_for(chrono::milliseconds(16));
        } else {
            sf::RectangleShape e;
            e.setFillColor(sf::Color::Green);
            e.setOutlineColor(sf::Color::Black);
            e.setOutlineThickness(1);
            if (!animation) {
                animation = true;
            } else {
                win.clear(sf::Color::Black);
            }

            for (int i = 0; i < v.getSize(); i++) {
                e.setSize(sf::Vector2f((1000 - tam) / tam, -1 * v[i]));
                e.setPosition(sf::Vector2f((i*(1000/tam) + 1), 500));
                win.draw(e);
                if (slow) {
                    this_thread::sleep_for(chrono::milliseconds(16));
                    win.display();
                }
            }

            if (slow) slow = false;
            
        }

        win.display();
    }
}