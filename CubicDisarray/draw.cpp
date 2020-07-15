//
// Created by liutao3 on 2020/7/10.
//
#include <SFML/Graphics.hpp>
#include "../utils.h"

static int gridCnt { 9 };  // how many grid in a row or column
static float gridWidth { 60.f };
static float thickness { 1.f };

sf::RectangleShape* drawRect(float _width, float x, float y);  // function in HypnoticSquares/draw.cpp

int drawCubicDisarray() {
    auto window { getWindow("Cubic Disarray") };

    std::vector<sf::RectangleShape*> rects;

    float halfGirdWidth { gridWidth / 2 };
    for (int row{0}; row < gridCnt; ++row) {
        for (int col{0}, rot { 0 }; col < gridCnt; ++col, rot+=3) {
            auto rect { drawRect(gridWidth, row*gridWidth+thickness+halfGirdWidth, col*gridWidth+thickness+halfGirdWidth) };
            rect->setRotation(randomNumber(-rot, rot));
            rects.push_back(rect);
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
        for (auto rect: rects) {
            window->draw(*rect);
        }

        window->display();
    }

    return 0;
}