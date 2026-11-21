#include <blocks.hpp>
#include <worldGenerator.hpp>

#include <random>
#include <FastNoiseSIMD.h>

void generateWorld(MapGame &mapGame, int seed) {
  constexpr size_t w = 900;
  constexpr size_t h = 500;
  std::ranlux24_base rng(seed);

  int grassSize = 70;
  int stoneSize = 90;

  mapGame.create(w, h);

  for (size_t x = 0; x < w; ++x) {

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
