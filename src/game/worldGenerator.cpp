#include "blocks.hpp"
#include "randomGen.hpp"
#include <random>
#include <worldGenerator.hpp>

void getFall(int &fall, int &direction, int &height, std::ranlux24_base &rng) {

  direction--;

  if (direction > 0) {

    if (fall == -1)
      if (getRandomChance(rng, 0.25))
        height--;

    if (fall == -2) {
      if (getRandomChance(rng, 0.25))
        height--;
      if (getRandomChance(rng, 0.25))
        height--;
    }

    if (fall == 1)
      if (getRandomChance(rng, 0.25))
        height++;

    if (fall == 2) {
      if (getRandomChance(rng, 0.25))
        height++;
      if (getRandomChance(rng, 0.25))
        height++;
    }

  } else {
    fall = getRandomInt(rng, -2, 2);
    direction = getRandomInt(rng, 5, 40);
  }
}

void generateWorld(MapGame &mapGame, int seed) {
  constexpr size_t w = 900;
  constexpr size_t h = 500;
  std::ranlux24_base rng(seed);

  int grassSize = 70;
  int stoneSize = 90;

  int grassfall = getRandomInt(rng, -2, 2);
  int stonefall = getRandomInt(rng, -2, 2);

  int grassDirection = getRandomInt(rng, 5, 40);
  int stoneDirection = getRandomInt(rng, 5, 40);

  mapGame.create(w, h);

  for (size_t x = 0; x < w; ++x) {

    getFall(grassfall, grassDirection, grassSize, rng);
    getFall(stonefall, stoneDirection, stoneSize, rng);

    if (grassSize < 50)
      grassSize = 50;
    else if (grassSize > 90)
      grassSize = 90;

    if (stoneSize < 60)
      stoneSize = 60;
    else if (stoneSize > 120)
      stoneSize = 120;

    for (size_t y = 0; y < h; ++y) {
      Block b{};

      if (y < h - (grassSize + stoneSize)) {
        b.type = Block::air;
      } else if (y == h - (grassSize + stoneSize)) {
        b.type = Block::grassBlock;
      } else if (y < h - stoneSize) {
        b.type = Block::dirt;
      } else {
        b.type = getRandomChance(rng, 0.1f) ? Block::gold : Block::stone;
      }

      mapGame.getBlockUnsafe(x, y) = b;
    }
  }
  return;
}
