﻿#include "GameSprite.hpp"

USING_NS_CC;

GameSprite::GameSprite(void)
	:_vector(ccp(0, 0))
	, _screenSize(Director::getInstance()->getWinSize())
{
}

GameSprite::~GameSprite(void) {}
