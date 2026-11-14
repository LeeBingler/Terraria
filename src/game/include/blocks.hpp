#pragma once
#include <cstdint>
#include <randomGen.hpp>

struct Block {
  enum {
    air = 0,
    dirt,
    grassBlock,
    stone,
    grass,
    sand,
    sandRuby,
    sandStone,
    woodPlank,
    stoneBricks,
    clay,
    woodLog,
    leaves,
    copper,
    iron,
    gold,
    copperBlock,
    ironBlock,
    goldBlock,
    bricks,
    snow,
    ice,
    rubyBlock,
    platform,
    workBench,
    glass,
    furnace,
    painting,
    sappling,
    snowBlueRuby,
    blueRubyBlock,
    door,
    jar,
    table,
    wordrobe,
    bookShelf,
    snowBricks,
    iceTable,
    iceWordrobe,
    iceBookShelf,
    icePlatform,
    sandTable,
    sandWordrobe,
    sandBookShelf,
    sandPlatform,
    woodenChest,
    iceChest,
    sandChest,
    boneChest,
    boneBricks,
    boneBench,
    boneWordrobe,
    boneBookShelf,
    bonePlatform,

    BLOCK_BACKGROUND,

    // Block Background
    dirtWall,
    stoneWall,
    woodPlankWall,
    sandStoneWall,
    bricksWall,
    glassWall,
    copperBlockWall,
    ironBlockWall,
    goldBlockWall,
    snowWall,
    sandWall,
    stoneBrickWall,
    rubyBlockWall,
    egyptInscriptionWall,
    blueRubyBlockWall,
    plankWall,
    snowBrickWall,
    boneBrickWall,

    BLOCKS_COUNT,

  };

  std::uint16_t type = 0;
  std::uint16_t variation = 0;

  Block() { variation = getRandomInt(0, 3); };

  bool isBackground() { return type > Block::BLOCK_BACKGROUND; };
};
