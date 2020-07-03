//
// Created by Harpsichord on 2020/7/3.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

float generatePoint(int maxLength) {
    std::uniform_int_distribution die{ 1, maxLength - 1};
    return die(mersenne);
}

bool circleOverlap(sf::CircleShape* c1, sf::CircleShape* c2) {
    float x1 { c1->getPosition().x };
    float y1 { c1->getPosition().y };
    float x2 { c2->getPosition().x };
    float y2 { c1->getPosition().y };

    double distance { std::pow(std::pow((x1-x2), 2) + std::pow((y1-y2), 2), 0.5) };
    std::cout << "(" << x1 << ", " << y1 << ") <--> (" << x2 << ", " << y2 << ") = " << distance << "\n";
    return distance < c1->getRadius() + c2->getRadius();
}


sf::CircleShape* generateCircle(float x, float y, const std::vector<sf::CircleShape*>& circles) {
    int maxRadius { 150 };

    sf::CircleShape* circle { new sf::CircleShape(maxRadius) };
    circle->setPosition(x, y);
    while (true) {
        bool _break { true };
        for (auto c: circles) {
            if (circleOverlap(c, circle)) {
                circle->setRadius(--maxRadius);
                _break = false;
                break;
            }
        }
        if (_break) {
            break;
        }
    }
    return circle;
}



int main()
{
    int width { 800 };
    int height { 600 };
    int maxCount { 10 };


    sf::RenderWindow window(sf::VideoMode(width, height), "Circle Packing");
    std::vector<sf::CircleShape*> circles;

    for (int i {0}; i<maxCount; ++i) {
        float x { generatePoint(width) };
        float y { generatePoint(height) };

        auto circle { generateCircle(x, y, circles) };
        circles.push_back(circle);

        std::cout << "Circle: x=" <<  x << ",\ty=" << y << ",\tr=" << circle->getRadius() << "\n";
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