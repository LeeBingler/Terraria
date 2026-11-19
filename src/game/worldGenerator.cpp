#include "blocks.hpp"
#include "randomGen.hpp"
#include <random>
#include <worldGenerator.hpp>

void generateWorld(MapGame &mapGame, int seed) {
  constexpr size_t w = 900;
  constexpr size_t h = 500;

  int grassSize = 50;
  int stoneSize = 380;

  mapGame.create(w, h);

  std::ranlux24_base rng(seed);

  for (size_t x = 0; x < w; ++x) {

    stoneSize += getRandomChance(rng, 0.5f) ? 1 : -1;
    grassSize += getRandomChance(rng, 0.5f) ? 1 : -1;

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
