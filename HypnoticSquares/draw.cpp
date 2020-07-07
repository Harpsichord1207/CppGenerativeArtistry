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

// give a square's position(eg: x=0, y=0, _width=10), randomly return a point from:
//   (2.5, 2.5), (2.5, 5.0), (2.5, 7.5)
//   (5.0, 2.5), (5.0, 5.0), (5, 7.5)
//   (7.5, 2.5), (7.5, 5.0), (7.5, 7.5)
sf::Vector2<float>* randomMidPoint(float x, float y, float _width) {
    float minStep { _width / 4 };
    int randomX { randomNumber(1, 3) };
    int randomY { randomNumber(1, 3) };
    sf::Vector2<float>* res { new sf::Vector2<float>(randomX*minStep+x, randomY*minStep+y) };
    return res;
}

// get a square's position by its mid point
sf::Vector2<float>* getPositionFromMidPoint(sf::Vector2<float>* p, float _wdith) {
    sf::Vector2<float>* res { new sf::Vector2<float>(p->x-(_wdith/2), p->y-(_wdith/2)) };
    return res;
}

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
    // position and width of r
    float x { r->getPosition().x };
    float y { r->getPosition().y };
    float _width { r->getSize().x };

    // position and width of the most inner grid
    float minWidth { 5.f };  // must have a fixed width
    sf::Vector2<float>* mid { randomMidPoint(x, y, _width) };
    sf::Vector2<float>* pos { getPositionFromMidPoint(mid, minWidth) };
    float maxX { pos->x };
    float maxY { pos->y };

    // random count of total inner grids
    int totalInnerGridCnt { randomNumber(3, 4) };

    // decrease or increase of width and position of those grids
    float widthDecr { (gridWidth-minWidth) / totalInnerGridCnt };
    float xIncr { (maxX-x) / totalInnerGridCnt };
    float yIncr { (maxY-y) / totalInnerGridCnt };

    for (int i {1}; i<=totalInnerGridCnt; ++i) {
        rs.push_back(drawRect(_width-widthDecr*i, x+xIncr*i, y+yIncr*i));
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