//
// Created by liutao3 on 2020/7/17.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include "../constants.h"
#include "../utils.h"


static float length { 30.f };

sf::VertexArray drawLine(float x, float y, float l, int r1, int r2) {
    auto point1 { sf::Vertex(sf::Vector2f(x, y-r2)) };
    auto point2 { sf::Vertex(sf::Vector2f(x+l, y-r1-r2)) };
    auto line { sf::VertexArray(sf::Lines, 2) };
    line.append(point1);
    line.append(point2);
    return line;
}

int drawJoyDivision() {
    std::vector<std::vector<sf::Vector2f>> points;

    for (int col{0}; col<=constants::width; col+=length/2) {
        points.emplace_back();
        for (int row{0}; row<constants::width; row+=length) {
            auto distanceToCenter { std::abs(row - constants::width/2) };
            auto variance { constants::width/2 - distanceToCenter };
            variance = variance > 0 ? variance : 0;
            auto randomH { randomNumber(0, variance / 2 ) };
            if (randomH <= 15) {
                randomH = 0;
            }
             std::cout << "(row, h) = (" << row << ", " << randomH << ")\n";
            points.back().emplace_back(row+length/2, col+length/2-randomH+100);
        }
    }

    std::vector<sf::VertexArray> lines;
    for (auto line: points) {
        for (int i{0}; i<line.size()-1; ++i){
            auto l { sf::VertexArray(sf::Lines, 2) };
            l.append(line[i]);
            l.append(line[i+1]);
            lines.emplace_back(l);
        }
    }

    auto window { getWindow("Joy Division") };
    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        window->clear();
        for (const auto& line: lines) {
            window->draw(line);
        }
        window->display();
    }
    return 0;
}
