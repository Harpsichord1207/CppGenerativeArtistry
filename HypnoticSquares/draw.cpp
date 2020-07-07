//
// Created by liutao3 on 2020/7/7.
//

#include <SFML/Graphics.hpp>
#include <vector>


static int gridCnt { 10 };  // how many grid in a row or column
static float gridWidth { 60.f };
static float thickness { 1.f };
static float windowWidth { gridCnt * gridWidth + 2*thickness };

int randomNumber(int min, int max);

sf::RectangleShape* drawRect(float _width, float x, float y) {
    auto rect { new sf::RectangleShape };
    rect->setSize(sf::Vector2(_width, _width));
    rect->setPosition(x, y);
    rect->setFillColor(sf::Color::Transparent);
    rect->setOutlineThickness(thickness);
    rect->setOutlineColor(sf::Color(222, 222, 222));
    return rect;
}

void drawInnerRects(sf::RectangleShape* r, std::vector<sf::RectangleShape*>& rs) {
    float x { r->getPosition().x };
    float y { r->getPosition().y };
    float width { r->getSize().x };

    int totalInnerGridCnt { randomNumber(3, 4) };

    float minWidth { 5.f };  // must have a smallest grid inside
    float widthDecr { (gridWidth-minWidth) / totalInnerGridCnt };  // each step decrease the width of grid

    int offset { randomNumber(8-totalInnerGridCnt, 13-totalInnerGridCnt) };  // for random position
    for (int i {1}; i<=totalInnerGridCnt; ++i) {
        rs.push_back(drawRect(width-widthDecr*i, x+offset*i, y+offset*i));
    }
    rs.back()->setFillColor(sf::Color(123, 234, 111));
}

int drawHypnoticSquares() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowWidth), "Hypnotic Squares", sf::Style::Close);
    std::vector<sf::RectangleShape*> rects;

    for (int row{0}; row < gridCnt; ++row) {
        for (int col{0}; col < gridCnt; ++col) {
            rects.push_back(drawRect(gridWidth, row*gridWidth+thickness, col*gridWidth+thickness));
        }
    }

    for (int i { static_cast<int>(rects.size())-1 }; i>=0; --i) {
        drawInnerRects(rects[i], rects);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        for (auto rect: rects) {
            window.draw(*rect);
        }
        window.display();
    }
}