#include <mapGame.hpp>
#include <assert.h>

void MapGame::create(int w, int h) {
  *this = {};

  mapData.resize(w * h);
  mapDataBg.resize(w * h);

  this->w = w;
  this->h = h;

  for (auto &e : mapData)
    e = {};

  for (auto &e : mapDataBg)
    e = {};
}

// Get a block without the check of OOB
Block &MapGame::getBlockUnsafe(int x, int y) {
  assert(mapData.size() == w * h);

  return mapData[x + y * w];
}

Block *MapGame::getBlock(int x, int y) {
  assert(mapData.size() == w * h);

  if (x < 0 || y < 0 || x >= w || y >= h)
    return nullptr;

  return &mapData[x + y * w];
}

Block &MapGame::getBlockUnsafeBg(int x, int y) {
  assert(mapDataBg.size() == w * h);

  return mapDataBg[x + y * w];
}

Block *MapGame::getBlockBg(int x, int y) {
  assert(mapDataBg.size() == w * h);

  if (x < 0 || y < 0 || x >= w || y >= h)
    return nullptr;

  return &mapDataBg[x + y * w];
}
