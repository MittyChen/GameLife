#pragma once

#include "cocos2d.h"
#include "SingleCell.h"

class LifeGameGod :
	public cocos2d::Layer
{
public:
	LifeGameGod(void);
	~LifeGameGod(void);
	CREATE_FUNC(LifeGameGod);
	void update(float delta);
	virtual bool init();
	void updateCells(float delta);
	void seedAllCells();
	void addCell();
	int getCellCount();
	void noticeACellToChange( SingleCell *targetCell );
	cocos2d::Vector<SingleCell*> getCellsAroundTargetCell( int x,int y);
	cocos2d::Vector<SingleCell*> getCellList();


	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	bool touchBegain(Ref* pSender);
	void updateWorld( float delta );
	void gameStart();

private:
	cocos2d::Vector<SingleCell*> cellList;
	int horizenCount;//横向方格数
	int verticalCount;//竖向方格数
 

};

