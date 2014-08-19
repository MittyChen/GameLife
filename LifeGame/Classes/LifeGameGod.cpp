#include "LifeGameGod.h"

using namespace cocos2d;
LifeGameGod::LifeGameGod(void)
{
}


LifeGameGod::~LifeGameGod(void)
{
}
//通知状态改变
void LifeGameGod::noticeACellToChange( SingleCell *targetCell )
{
	targetCell->setChangeFlag();
}

int LifeGameGod::getCellCount()
{
	return cellList.size();
}

void LifeGameGod::update( float delta )
{
	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i);
		mcell->updateChangeFlag(getCellsAroundTargetCell(mcell->getPosition()) );
		mcell->update(delta);
	}
}

bool LifeGameGod::init()
{
	if(!Node::init())
	{
		return false;
	}
	 horizenCount = 10;
	 verticalCount =10;

	 seedAllCells();

	schedule(schedule_selector( LifeGameGod::update) ,0.5f,kRepeatForever, 0.0f);

	return true;
}

//获取周围的八个cell
cocos2d::Vector<SingleCell*> LifeGameGod::getCellsAroundTargetCell( cocos2d::Vec2 val )
{
	cocos2d::Vector<SingleCell*> mcells ;

	for(int i = 0;i<getCellCount();i++)
	{
		if(abs(cellList.at(i)->getPosition().x - val.x) == 1 || abs(cellList.at(i)->getPosition().y - val.y) ==1  )//周围的八个
		{
			mcells.pushBack(cellList.at(i));
		}
	}
	return mcells;
}


void LifeGameGod::seedAllCells()
{
	for(int i = 0 ;i < horizenCount; i++)
	{
		for(int j = 0 ;j < verticalCount; j++)
		{
			SingleCell* cell = SingleCell::create();
			cell->setPosition(Vec2(i,j));
			cellList.pushBack(cell);
		}
	}
}

cocos2d::Vector<SingleCell*> LifeGameGod::getCellList()
{
	return cellList;
}
