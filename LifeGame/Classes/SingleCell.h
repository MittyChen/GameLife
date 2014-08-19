#pragma once
#include "cocos2d.h"

enum CELL_LIVNG_STATE
{
	LIVING_STATE = 1,
	DEAD_STATE = 0
};


class SingleCell :
	public cocos2d::LayerColor
{
public:
	SingleCell(void);
	~SingleCell(void);
	CREATE_FUNC(SingleCell);
	void update(float delta);
	virtual bool init();


	void setPosition(cocos2d::Vec2 val);
	cocos2d::Vec2 getPosition();
	CELL_LIVNG_STATE getCurrentLivingState();
	void setChangeFlag();
	bool updateChangeFlag( cocos2d::Vector<SingleCell*> cellsAround );

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);


private: 
	CELL_LIVNG_STATE getNextState();
	CELL_LIVNG_STATE currentLivingState;
	CELL_LIVNG_STATE lastLivingState;
	bool needChangeState;
	cocos2d::Vec2 posi;
};

