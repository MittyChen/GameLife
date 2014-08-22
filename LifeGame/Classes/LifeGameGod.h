#pragma once

#include "cocos2d.h"
#include "SingleCell.h"
using namespace cocos2d;
class LifeGameGod :
	public cocos2d::Layer
{
public:
	LifeGameGod(void);
	~LifeGameGod(void);
	CREATE_FUNC(LifeGameGod);
	void update(float delta);
	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void updateCells(float delta);
	void seedAllCells();
	int getCellCount();

	cocos2d::Vector<SingleCell*> getCellsAroundTargetCell( int x,int y);
	cocos2d::Vector<SingleCell*> getCellList();

	void gameStart();
private:
	cocos2d::Vector<SingleCell*> cellList;
	int horizenCount;//���򷽸���
	int verticalCount;//���򷽸���
	float CELLS_WIDTH;
	float CELLS_HEIGHT;
	 Size visibleSize ;
	  Vec2 origin ;
};

