//
// Created by liutao3 on 2020/7/6.
//

#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
#include <vector>


static int width { 600 };
static float thickness { 10.f };
static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

bool randomBool() {
    std::uniform_int_distribution die{ 1, 100 };
    return die(mersenne) >= 50;
}

sf::RectangleShape* generateRect(float width, float height, float x=0.f, float y=0.f) {
    auto rect { new sf::RectangleShape };
    float fitWidth{ width - 2 * thickness };
    float fitHeight{ height - 2 * thickness };

    rect->setSize(sf::Vector2(fitWidth, fitHeight));
    rect->setOutlineThickness(thickness);
    rect->setOutlineColor(sf::Color(128, 128, 128));
    rect->setFillColor(sf::Color(0, 0, 0));
    rect->setPosition(x+thickness, y+thickness);
    return rect;
}

void splitRect(float p, char xORy, std::vector<sf::RectangleShape*>& rects) {
    for (int i { static_cast<int>(rects.size())-1 }; i>=0; --i) {
        auto rect { rects[i] };
        float x { rect->getPosition().x };
        float y { rect->getPosition().y };
        float w { rect->getSize().x };
        float h { rect->getSize().y };

        if (xORy == 'X') {
            if (randomBool() && x < p && x+w > p) {
                rect->setSize(sf::Vector2(p-x-thickness, h));
                rects.push_back(generateRect(x+w-p+thickness, h+2*thickness, p, y-thickness));
            }
        } else if (xORy == 'Y') {
            if (randomBool() && y < p && y+h > p) {
                rect->setSize(sf::Vector2(w, p-y-thickness));
                rects.push_back(generateRect(w+2*thickness, y+h-p+thickness, x-thickness, p));
            }
        }

    }
}

int drawPietMondrian() {
    sf::RenderWindow window(sf::VideoMode(width, width), "Piet Mondrian");
    std::vector<sf::RectangleShape*> rects;
    rects.push_back( generateRect(static_cast<float>(width), static_cast<float>(width)) );

    for (auto c: "XY") {
        splitRect(100.f, c, rects);
        splitRect(200.f, c, rects);
        splitRect(300.f, c, rects);
        splitRect(400.f, c, rects);
        splitRect(500.f, c, rects);

    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (auto rect: rects)
            window.draw(*rect);
        window.display();
    }
}