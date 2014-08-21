#include "LifeGameGod.h"
#include "ConstCells.h"
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
}


 

void LifeGameGod::gameStart()
{
	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i);
		mcell->updateTheSituation();
	}
	schedule(schedule_selector( LifeGameGod::updateCells), CELLS_UPDATE_BREAK_TIME,kRepeatForever, 0.0f);
}


bool LifeGameGod::init()
{
	if(!Node::init())
	{
		return false;
	}

	 seedAllCells();
	  
	 {//touch event
		 auto event = EventListenerTouchOneByOne::create();
		 event->onTouchBegan = CC_CALLBACK_2(LifeGameGod::onTouchBegan,this);
		 event->onTouchCancelled = CC_CALLBACK_2(LifeGameGod::onTouchCancelled,this);
		 event->onTouchEnded = CC_CALLBACK_2(LifeGameGod::onTouchEnded,this);
		 event->onTouchMoved = CC_CALLBACK_2(LifeGameGod::onTouchMoved,this);
		 event->setSwallowTouches(true);
		 _eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
	 } 

	return true;
}

//获取周围的八个cell
cocos2d::Vector<SingleCell*> LifeGameGod::getCellsAroundTargetCell( int x,int y)
{
	cocos2d::Vector<SingleCell*> mcells ;
	CCLOG("LifeGameGod::getCellsAroundTargetCell  [%d %d]",x,y );
	for(int i = 0;i<getCellCount();i++)
	{
		if(abs(cellList.at(i)->getPositionIndexX() - x) <= 1 &&  abs(cellList.at(i)->getPositionIndexY() - y) <=1  )//周围的  最多八个
		{
			if(!(cellList.at(i)->getPositionIndexX() == x  && cellList.at(i)->getPositionIndexY() == y) )
			{
				mcells.pushBack(cellList.at(i));
			}

		}
	}

	return mcells;
}


void LifeGameGod::seedAllCells()
{
	for(int i = 0 ;i < CELLS_VERTICAL_COUNT ; i++)
	{
		for(int j = 0 ;j < CELLS_HORIZEN_COUNT; j++)
		{
			SingleCell* cell = SingleCell::create();
			cell->setTag(cellList.size()); 
			cell->setPositionIndex(i,j); 
			cell->setPosition(Vec2(i*(CELLS_WIDTH+CELLS_WIDTH_SPEACING),j*(CELLS_HEIGHT+CELLS_HEIGHT_SPEACING))); 
			cellList.pushBack(cell);
			this->addChild(cell);
		}
	}
	 
	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i);
		mcell->setCellsAround(getCellsAroundTargetCell(mcell->getPositionIndexX(),mcell->getPositionIndexY()));
	} 
}

cocos2d::Vector<SingleCell*> LifeGameGod::getCellList()
{
	return cellList;
}


bool LifeGameGod::onTouchBegan(Touch *touch, Event *unused_event)
{
	Vec2 pos = touch->getLocation();
	int  line= (pos.x-this->getPosition().x)/(CELLS_WIDTH+CELLS_WIDTH_SPEACING);
	int row = (pos.y-this->getPosition().y)/( CELLS_HEIGHT+CELLS_HEIGHT_SPEACING);
	if((row + line * CELLS_HORIZEN_COUNT) < cellList.size() && (row + line * CELLS_HORIZEN_COUNT) >=0 )
	{
		SingleCell* mcell  =  cellList.at(row + line * CELLS_HORIZEN_COUNT);
		mcell->changeState();
		mcell->updateCellColor();
	} 
	return true;
}
void LifeGameGod::onTouchMoved(Touch *touch, Event *unused_event)
{
	Vec2 pos = touch->getLocation();
	int  line= (pos.x-this->getPosition().x)/(CELLS_WIDTH+CELLS_WIDTH_SPEACING);
	int row = (pos.y-this->getPosition().y)/( CELLS_HEIGHT+CELLS_HEIGHT_SPEACING);
	if((row + line * CELLS_HORIZEN_COUNT) < cellList.size() && (row + line * CELLS_HORIZEN_COUNT) >=0 )
	{
		SingleCell* mcell  =  cellList.at(row + line * CELLS_HORIZEN_COUNT);
		mcell->changeState();
		mcell->updateCellColor();
	}
}

void LifeGameGod::onTouchEnded(Touch *touch, Event *unused_event)
{
}

void LifeGameGod::onTouchCancelled(Touch *touch, Event *unused_event)
{
}

void LifeGameGod::updateCells( float delta )
{
	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i);

		mcell->updateTheSituation();
	}
	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i); 
		mcell->updateCellState();
	} 

	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i); 
		mcell->updateCellColor();
	} 

}
