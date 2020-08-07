//
// Created by liutao3 on 2020/8/7.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants.h"
#include "../utils.h"

sf::VertexArray getRandomLine(float x, float y, float l) {
    auto r { randomNumber(0, 1) };
    auto line { sf::VertexArray(sf::Lines, 2) };

    if (r == 0) {
        auto point1 { sf::Vertex(sf::Vector2f(x, y)) };
        auto point2 { sf::Vertex(sf::Vector2f(x+l, y+l)) };
        line.append(point1);
        line.append(point2);
    } else {
        auto point1 { sf::Vertex(sf::Vector2f(x+l, y)) };
        auto point2 { sf::Vertex(sf::Vector2f(x, y+l)) };
        line.append(point1);
        line.append(point2);
    }
    return line;
}



int drawTiledLines() {

    std::vector<sf::VertexArray> lines;
    int length { 20 };

    for (int x{0}; x<constants::width; x+=length) {
        for (int y{0}; y<constants::width; y+=length) {
            lines.emplace_back(getRandomLine(x, y, length));
        }
    }

    auto window { getWindow("Tiled Lines") };

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            window->clear();
            for (const auto& line: lines) {
                window->draw(line);
            }
            window->display();
        }
    }

    return 0;
}