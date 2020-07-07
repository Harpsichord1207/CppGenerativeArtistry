//
// Created by liutao3 on 2020/7/7.
//
#include <ctime>
#include <random>

static std::mt19937 mersenne {static_cast<std::mt19937::result_type>(std::time(nullptr)) };

int randomNumber(int min, int max) {
    std::uniform_int_distribution die(min, max);
    return die(mersenne);
}
