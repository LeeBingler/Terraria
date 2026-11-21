#include <blocks.hpp>
#include <memory>
#include <worldGenerator.hpp>

#include <random>
#include <FastNoiseSIMD.h>

void generateWorld(MapGame &mapGame, int seed) {
  constexpr size_t w = 900;
  constexpr size_t h = 500;
  std::ranlux24_base rng(seed);

  // Create empty map
  mapGame.create(w, h);

  // Settings noise
  std::unique_ptr<FastNoiseSIMD> dirtNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());
  std::unique_ptr<FastNoiseSIMD> stoneNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());

  dirtNoiseGenerator->SetSeed(seed++);
  stoneNoiseGenerator->SetSeed(seed++);

  dirtNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
  dirtNoiseGenerator->SetFractalOctaves(1);
  dirtNoiseGenerator->SetFrequency(0.02);

  stoneNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
  stoneNoiseGenerator->SetFractalOctaves(4);
  stoneNoiseGenerator->SetFrequency(0.01);

  // Generate Noise
  float *dirtNoise = FastNoiseSIMD::GetEmptySet(w);
  float *stoneNoise = FastNoiseSIMD::GetEmptySet(w);

  dirtNoiseGenerator->FillNoiseSet(dirtNoise, 0, 0, 0, w, 1, 1);
  stoneNoiseGenerator->FillNoiseSet(stoneNoise, 0, 0, 0, w, 1, 1);

  // convert the range from [-1, 1] to [0, 1]
  for (int i = 0; i < w; i++) {
    dirtNoise[i] = (dirtNoise[i] + 1) / 2;
    stoneNoise[i] = (stoneNoise[i] + 1) / 2;
  }

  constexpr int dirtOffStart = -5;
  constexpr int dirtOffEnd = 35;

  constexpr int stoneHeightStart = 80;
  constexpr int stoneheightEnd = 170;

  for (size_t x = 0; x < w; ++x) {
    int stoneHeight = stoneHeightStart + (stoneheightEnd - stoneHeightStart) * stoneNoise[x];
    int grassHeight = dirtOffStart + (dirtOffEnd - dirtOffStart) * dirtNoise[x];
    grassHeight = stoneHeight - grassHeight;

    for (size_t y = 0; y < h; ++y) {
      Block b{};

      if (y > grassHeight) {
        b.type = Block::dirt;
      }

      if (y == grassHeight) {
        b.type = Block::grassBlock;
      }

      if (y >= stoneHeight) {
        b.type = getRandomChance(rng, 0.1f) ? Block::gold : Block::stone;
      }

      mapGame.getBlockUnsafe(x, y) = b;
    }
  }

  // Delete Noise data
  // No need to delete unique_ptr because they will be automatically at the end of the function
  FastNoiseSIMD::FreeNoiseSet(dirtNoise);
  FastNoiseSIMD::FreeNoiseSet(stoneNoise);

  return;
}
