//
// Created by liutao3 on 2020/7/9.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "../utils.h"

typedef std::vector<std::vector<sf::Vector2f>> point2DVector ;

static float sideLength { 600.f / 8 };

sf::Vector2f* randomPoint(float x, float y, bool odd=false) {
    float rX ;
    float rY ;
    // while loop avoid point to get out of border
    while (true) {
        rX = x + randomNumber(-sideLength*0.4, sideLength*0.4) ;
        if (rX>0 && rX<constants::width) {
            break;
        }
    }
    while (true) {
        rY = y + randomNumber(-sideLength*0.4, sideLength*0.4) ;
        if (rY>0 && rY<constants::width) {
            break;
        }
    }
    auto p { new sf::Vector2f(rX, rY) };
    return p;
}

int drawTriangularMesh() {
    auto window { getWindow("Triangular Mesh") };

    point2DVector lines1;
    bool odd;
    for (float c{sideLength/2}; c<constants::width; c+=sideLength) {
        odd = !odd;
        lines1.emplace_back();
        for (float r{sideLength/3}; r<constants::width; r+=sideLength) {
            auto x { r+odd*sideLength/2 };
            auto y { c };
            lines1.back().push_back(*randomPoint(x, y, odd));  // random offset point position
        }
    }

    point2DVector lines2;
    std::vector<sf::VertexArray> triangles;

    for (int i { 0 }; i < lines1.size(); ++i){
        odd = i%2!=0;
        for (int j { 0 }; j<lines1[i].size()-1; ++j){
            if (i == lines1.size() - 1) {
                lines2.emplace_back();
                lines2.back().push_back(lines1[i][j]);
                lines2.back().push_back(lines1[i][j+1]);
                lines2.back().push_back(lines1[i-1][odd?j:j+1]);

            } else if (i == 0) {
                lines2.emplace_back();
                lines2.back().push_back(lines1[i][j]);
                lines2.back().push_back(lines1[i][j+1]);
                lines2.back().push_back(lines1[i+1][j+1]);

            } else {
                lines2.emplace_back();
                lines2.back().push_back(lines1[i][j]);
                lines2.back().push_back(lines1[i][j+1]);
                lines2.back().push_back(lines1[i+(odd?-1:1)][odd?j:j+1]);

                lines2.emplace_back();
                lines2.back().push_back(lines1[i][j]);
                lines2.back().push_back(lines1[i][j+1]);
                lines2.back().push_back(lines1[i+(odd?1:-1)][odd?j:j+1]);
            }
        }
    }

    for (int i { 0 }; i < lines2.size(); ++i) {
        auto color { randomGrayScale() };
        sf::VertexArray triangle(sf::Triangles, 3);
        for (int j { 0 }; j < 3; ++j) {
            triangle[j] = lines2[i][j];
            triangle[j].color = *color;
        }
        triangles.push_back(triangle);
    }

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        window->clear();
        for (auto &t: triangles) {
            window->draw(t);
        }
        window->display();
    }

    return 0;
}