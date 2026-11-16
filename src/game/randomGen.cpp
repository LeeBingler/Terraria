#include <randomGen.hpp>

float getRandomFloat(std::ranlux24_base &seed, float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(seed);
}

int getRandomInt(std::ranlux24_base &seed, int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(seed);
}

bool getRandomChance(float chance) {
  std::ranlux24_base seed(std::random_device{}());

  float dice = getRandomFloat(seed, 0.0, 1.0);
  return dice <= chance;
}
