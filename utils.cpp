//
// Created by liutao3 on 2020/7/7.
//
#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
#include "constants.h"
#include "utils.h"

static std::mt19937 mersenne {static_cast<std::mt19937::result_type>(std::time(nullptr)) };

int randomNumber(int min, int max) {
    std::uniform_int_distribution die(min, max);
    return die(mersenne);
}

sf::RenderWindow* getWindow(const char* title, int wdith, int height) {
    auto window { new sf::RenderWindow(sf::VideoMode(wdith, height), title, sf::Style::Close) };
    sf::Image icon;
    icon.loadFromFile(constants::iconPath);
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    return window;
}

sf::Color* randomColor() {

    int r { randomNumber(0, 255) };
    int g { randomNumber(0, 255) };
    int b { randomNumber(0, 255) };

    auto color { new sf::Color(r, g, b) };
    return color;
}