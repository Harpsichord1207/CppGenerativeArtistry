//
// Created by liutao3 on 2020/7/17.
//

#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants.h"
#include "../utils.h"

static float thickness { 1.f };
static float length { 30.f };

std::vector<sf::Vector2f> CalcCubicBezier(
        const sf::Vector2f &start,
        const sf::Vector2f &end,
        const sf::Vector2f &startControl,
        const sf::Vector2f &endControl,
        const size_t numSegments)
{
    std::vector<sf::Vector2f> ret;
    if (!numSegments) // Any points at all?
        return ret;

    ret.push_back(start); // First point is fixed
    float p = 1.f / numSegments;
    float q = p;
    for (size_t i = 1; i < numSegments; i++, p += q) // Generate all between
        ret.push_back(p * p * p * (end + 3.f * (startControl - endControl) - start) +
                      3.f * p * p * (start - 2.f * startControl + endControl) +
                      3.f * p * (startControl - start) + start);
    ret.push_back(end); // Last point is fixed
    return ret;
}



sf::RectangleShape* drawLine(float x, float y, float l) {
    auto rect { new sf::RectangleShape };
    rect->setSize(sf::Vector2f(l, thickness));
    rect->setPosition(x, y);
    return rect;

}

//std::vector<sf::VertexArray> drawCurve(float x, float y, float l) {
//    std::vector<sf::VertexArray> curve;
//    for (float i {x}; i<x+l; i+=(l-x)/5) {
//        sf::VertexArray
//    }
//    return curve;
//}

sf::VertexArray* drawCurve(float x, float y, float l) {
    auto curve { new sf::VertexArray(sf::LineStrip, 0) };
    auto s { sf::Vector2f(x, y) };
    auto e { sf::Vector2f(x+l, y+2*l) };
    auto sC { sf::Vector2f(x+l/4, l/2) };
    auto eC { sf::Vector2f(x+l/4*3, l/2*3) };
    std::vector<sf::Vector2f> points { CalcCubicBezier(s, e, sC, eC, 100) };

    for (auto & point : points)
        curve->append(sf::Vertex(point, sf::Color::White));
    return curve;
}


int drawJoyDivision() {
    std::vector<sf::RectangleShape*> lines;
    for (int row{0}; row<constants::width-length; row+=length) {
        for (int col{0}; col<constants::width; col+=length/2) {
            auto line = drawLine(row+length/2, col+length/2, length);
            lines.push_back(line);
        }
    }



    auto window { getWindow("Joy Division") };
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        window->draw(*drawCurve(50, 50, 100));
        window->display();
    }
}