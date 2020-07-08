//
// Created by liutao3 on 2020/7/8.
//

#ifndef CPPGENERATIVEARTISTRY_UTILS_H
#define CPPGENERATIVEARTISTRY_UTILS_H
#include "constants.h"

int randomNumber(int min, int max);
sf::RenderWindow* getWindow(const char* title="SFML", int wdith=constants::width, int height=constants::width);
sf::Color* randomColor();

#endif //CPPGENERATIVEARTISTRY_UTILS_H
