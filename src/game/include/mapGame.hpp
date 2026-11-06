#pragma once
#include <vector>
#include <blocks.hpp>

struct MapGame {
  int w = 0;
  int h = 0;

  std::vector<Block> mapData;

  void create(int w, int h);

  Block *getBlock(int x, int y);
  Block &getBlockUnsafe(int x, int y);
};
