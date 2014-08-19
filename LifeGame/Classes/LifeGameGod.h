#pragma once

#include "cocos2d.h"
#include "SingleCell.h"

class LifeGameGod :
	public cocos2d::Node
{
public:
	LifeGameGod(void);
	~LifeGameGod(void);
	CREATE_FUNC(LifeGameGod);
	void update(float delta);
	virtual bool init();

	void seedAllCells();
	void addCell();
	int getCellCount();
	void noticeACellToChange( SingleCell *targetCell );
	cocos2d::Vector<SingleCell*> getCellsAroundTargetCell(cocos2d::Vec2 val);
	cocos2d::Vector<SingleCell*> getCellList();
private:
	cocos2d::Vector<SingleCell*> cellList;
	int horizenCount;//���򷽸���
	int verticalCount;//���򷽸���
};

