#pragma once

#define TILE_H_SIZE 6
#define TILE_W_SIZE 8

#include "cocos2d.h"
#include "Block.hpp"
#include "Player.hpp"

USING_NS_CC;
using namespace std;


class CustomTerrain : public Sprite {

	vector<Block*> blockPool;
	size_t _blockPoolIndex;

	vector<Block*> blocks;
	int _lastBlockHeight;
	int _lastBlockWidth;
	int _minTerrainWidth;

	bool _showGap;
	Size _screenSize;

	size_t _currentPatternIndex;
	int _currentPatternCnt;
	size_t _currentWidthIndex;
	size_t _currentHeightIndex;
	size_t _currentTypeIndex;

	int _increaseGapInterval;
	float _increaseGapTimer;
	int _gapSize;

	void initTerrain(void);
	void addBlocks(int currentWidth);

	void distributeBlocks();
	void initBlock(Block * block);

	inline float getWidth() {

		int count = blocks.size();
		int width = 0;
		Block * block;
		for (int i = 0; i < count; i++) {
			block = blocks.at(i);
			width += block->getWidth();
		}
		return width;
	}


public:

	CustomTerrain(void);
	~CustomTerrain(void);

	CC_SYNTHESIZE(bool, _startTerrain, StartTerrain);

	static CustomTerrain * create();

	void checkCollision(Player * player);

	void move(float xMove);
	void reset(void);


};
