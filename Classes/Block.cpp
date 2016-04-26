
#define TILE_H_SIZE 6
#define TILE_W_SIZE 8

#include "Block.hpp"

Block::~Block() {
}

Block::Block() {

	//get screen size
	_screenSize = Director::getInstance()->getWinSize();
	_tileWidth = _screenSize.width / TILE_W_SIZE;
	_tileHeight = _screenSize.height / TILE_H_SIZE;

	this->setVisible(false);

}

Block * Block::create() {

	Block * block = new Block();
	if (block && block->initWithFile("blank.png")) {
		block->initBlock();
		block->autorelease();
		return block;
	}
	CC_SAFE_DELETE(block);
	return NULL;
}


void Block::setupBlock(int width, int height, int type) {


}

void Block::initBlock() {


}
