//
// Created by Harpsichord on 2020/7/3.
//

#include <SFML/Graphics.hpp>

#include <ctime>
#include <iostream>
#include <random>
#include <vector>

static int width { 600 };
static int height { 600 };
static int maxCount { 1000 };
static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

float generateRandomNumber(int maxLength) {
    std::uniform_int_distribution die{ 1, maxLength - 1};
    return die(mersenne);
}

bool circleOverlap(sf::CircleShape* c1, sf::CircleShape* c2) {
    float x1 { c1->getPosition().x };
    float y1 { c1->getPosition().y };
    float r1 { c1->getRadius() };

    float x2 { c2->getPosition().x };
    float y2 { c2->getPosition().y };
    float r2 { c2->getRadius() };

    float mid1X { x1 + r1 };
    float mid1Y { y1 + r1 };

    float mid2X { x2 + r2 };
    float mid2Y { y2 + r2 };

    double distance { std::sqrt( std::pow((mid1X-mid2X), 2) + std::pow((mid1Y-mid2Y), 2) ) };
    // std::cout << "(" << mid1X << ", " << mid1Y << ") <--> (" << mid2X << ", " << mid2Y << ") = " << distance << "\n";
    return distance < r1 + r2;
}


sf::CircleShape* generateCircle(float x, float y, const std::vector<sf::CircleShape*>& circles) {
    float radius { generateRandomNumber( 144 ) };

    sf::CircleShape* circle { new sf::CircleShape(radius) };

    auto widthF = static_cast<float>(width);
    auto heightF = static_cast<float>(height);

    if (x + radius * 2 > widthF) {
        radius = (widthF - x) / 2;
    }

    if (y + radius * 2 > heightF) {
        radius = (heightF - y) / 2;
    }

    circle->setPosition(x, y);
    circle->setRadius(radius);

    while (true) {
        bool breakFlag { true };
        for (auto c: circles) {
            if (circleOverlap(c, circle)) {
                --radius;
                if (radius <= 0) {
                    return nullptr;
                }
                circle->setRadius(radius);
                breakFlag = false;
            }
        }
        if ( breakFlag ) {
            break;
        }
    }

    float r { generateRandomNumber(255) };
    float g { generateRandomNumber(255) };
    float b { generateRandomNumber(255) };

    circle->setFillColor(sf::Color(0, 0, 0));
    circle->setOutlineColor(sf::Color(r, g, b));
    circle->setOutlineThickness(1.f);
    circle->setPointCount(static_cast<int>(radius*3));  // make circle more smooth
    return circle;
}

int drawCirclePacking() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Circle Packing");
    std::vector<sf::CircleShape*> circles;

    for (int i {0}; i<maxCount;) {
        float x { generateRandomNumber(width) };
        float y { generateRandomNumber(height) };

        auto circle { generateCircle(x, y, circles) };
        if (circle) {
            ++i;
            circles.push_back(circle);
            std::cout << "Circle: x=" <<  x << ",\ty=" << y << ",\tr=" << circle->getRadius() << "\n";
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto circle: circles)
            window.draw(*circle);
        window.display();
    }

    return 0;
}
