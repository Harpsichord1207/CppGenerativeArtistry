//
// Created by liutao3 on 2020/7/8.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants.h"
#include "../utils.h"

static float thickness { 4.f };
static float length { 40.f };


sf::Vertex* generateLine(float x, float y, float l, sf::Color& color) {
    auto p1 { sf::Vertex(sf::Vector2f(x, y), color )};
    auto p2 { sf::Vertex(sf::Vector2f(x, y+l), color) };
    auto p3 { sf::Vertex(sf::Vector2f(x+thickness, y+l), color) };
    auto p4 { sf::Vertex(sf::Vector2f(x+thickness, y), color) };
    sf::Vertex* line { new sf::Vertex[4] };
    line[0] = p1;
    line[1] = p2;
    line[2] = p3;
    line[3] = p4;
    return line;
}

void rotateLine(sf::Vertex* line, float rX, float rY, int ang) {
    sf::Transform rotation;
    rotation.rotate(ang, rX, rY);
    for (int i {0}; i<4; ++i){
        line[i].position =  rotation.transformPoint(line[i].position);
    }
}

float getMargin(int n, int i) {
    static const float marginMap[3][3] {
            {0.5f, -1.f, -1.f},
            {0.2f, 0.8f, -1.f},
            {0.1f, 0.5f, 0.9f}
    };
    return marginMap[n-1][i];
}

void drawLinesGrid(float pX, float pY, int n, std::vector<sf::Vertex*>& lines) {
    float width { 40.f };

    float midX { pX + width/2 };
    float midY { pY + length/2 };
    int ang { randomNumber(-90, 90) };
    for (int i {0}; i<n; ++i) {
        auto line { generateLine(pX+width*getMargin(n, i), pY, length, *randomColor()) };
        rotateLine(line, midX, midY, ang);
        lines.push_back(line);
    }
}

int drawUnDeuxTrois() {
    auto window { getWindow("Un Deux Trois") };

    std::vector<sf::Vertex*> lines;

    for (int r{0}; r<constants::width; r+=40.f){
        for (int c{0}; c<constants::width; c+=length) {
            drawLinesGrid(r, c, c/(constants::width/3) + 1, lines);
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
            window->draw(line, 4, sf::Quads);
        }
        window->display();
    }
    return 0;
};

