#pragma once
#include <random>

float getRandomFloat(std::ranlux24_base &seed, float min, float max);

int getRandomInt(std::ranlux24_base &seed, int min, int max);

bool getRandomChance(std::ranlux24_base &seed, float chance);
