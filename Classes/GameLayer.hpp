#pragma once

#include "cocos2d.h"
#include "Terrain.hpp"
#include "Player.hpp"

USING_NS_CC;

typedef enum {
	kGameIntro,
	kGamePlay,
	kGameOver

} GameState;


class GameLayer : public cocos2d::CCLayer
{

	CustomTerrain * _terrain;
	Player * _player;

	SpriteBatchNode * _gameBatchNode;

	Size _screenSize;

	bool _running;
	int _speedIncreaseInterval;
	float _speedIncreaseTimer;

	void createGameScreen();
	void resetGame();


public:

	~GameLayer();

	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();

	// there's no 'id' in cpp, so we recommend to return the class instance pointer
	static cocos2d::Scene* scene();

	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(GameLayer);

	void update(float dt);

	virtual void onTouchesBegan(std::vector<Touch*> pTouches, Event* event);
	virtual void onTouchesEnded(std::vector<Touch*> pTouches, Event* event);
};
