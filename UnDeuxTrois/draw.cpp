//
// Created by liutao3 on 2020/7/8.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../constants.h"
#include "../utils.h"

static float thickness { 4.f };
static float length { 30.f };

sf::RectangleShape* generateLine(float x, float y, float l, sf::Color& color, int rotateMin=-90, int rorateMax=90) {
    auto line { new sf::RectangleShape };
    line->setPosition(x, y);
    line->setSize(sf::Vector2(thickness, l));
    line->rotate(randomNumber(rotateMin, rorateMax));
    line->setFillColor(color);
    return line;
}

int drawUnDeuxTrois() {
    auto window { getWindow("Un Deux Trois") };

    std::vector<sf::RectangleShape*> lines;

    for (int i{0}; i<constants::width;i+=40) {
        int j { 0 };
        while (j<constants::width) {
            float x { i+15.f };
            float y { j+5.f };
            auto color { randomColor() };

            if (j<constants::width/3) {
                lines.push_back(generateLine(x, y, length, *color));
            } else if (j<2*constants::width/3) {
                int rotateNumber { randomNumber(-90, 90) };
                lines.push_back(generateLine(x-3, y, length, *color, rotateNumber-10, rotateNumber+10));
                lines.push_back(generateLine(x+12, y, length, *color, rotateNumber-10, rotateNumber+10));
            } else {
                int rotateNumber { randomNumber(-90, 90) };
                int rMin { rotateNumber - 3 };
                int rMax { rotateNumber + 3 };

                lines.push_back(generateLine(x-12, y, length, *color, rMin, rMax));
                lines.push_back(generateLine(x+7, y, length, *color, rMin, rMax));
                lines.push_back(generateLine(x+15, y, length, *color, rMin, rMax));
            }

            j+=length;
        }
    }

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        for (auto line: lines) {
            window->draw(*line);
        }
        window->display();
    }
};

