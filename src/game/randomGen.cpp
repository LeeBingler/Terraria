#include <randomGen.hpp>
#include <random>

float getRandomFloat(float min, float max) {
  std::ranlux24_base seed(std::random_device{}());

  std::uniform_real_distribution<float> dist(min, max);
  return dist(seed);
}

int getRandomInt(int min, int max) {
  std::ranlux24_base seed(std::random_device{}());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(seed);
}

bool getRandomChance(float chance) {
  float dice = getRandomFloat(0.0, 1.0);
  return dice <= chance;
}
