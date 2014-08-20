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
}


void LifeGameGod::updateWorld( float delta )
{
	for(int i = 0;i<getCellCount();i++)
	{
		SingleCell* mcell = cellList.at(i);
		 
		mcell->updateChangeFlag(getCellsAroundTargetCell(mcell->getPositionIndexX(),mcell->getPositionIndexY()) );
	}
}

void LifeGameGod::gameStart()
{
	this->unschedule(schedule_selector( LifeGameGod::update));
	schedule(schedule_selector( LifeGameGod::updateWorld) ,1.0f,kRepeatForever, 0.0f);
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
	  
	 {//touch event
		 auto event = EventListenerTouchOneByOne::create();
		 event->onTouchBegan = CC_CALLBACK_2(LifeGameGod::onTouchBegan,this);
		 event->onTouchCancelled = CC_CALLBACK_2(LifeGameGod::onTouchCancelled,this);
		 event->onTouchEnded = CC_CALLBACK_2(LifeGameGod::onTouchEnded,this);
		 event->onTouchMoved = CC_CALLBACK_2(LifeGameGod::onTouchMoved,this);
		 event->setSwallowTouches(true);
		 _eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
		/*_eventDispatcher->addEventListenerWithFixedPriority(event,-100);*/

	 }
	  
	schedule(schedule_selector( LifeGameGod::update) ,0.1f,kRepeatForever, 0.0f);

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
			if(!(abs(cellList.at(i)->getPositionIndexX() - x)  == 0 && abs(cellList.at(i)->getPositionIndexY() - y)==0) )
			{
				CCLOG("mcell add   %d %d",cellList.at(i)->getPositionIndexX(),cellList.at(i)->getPositionIndexY());
				mcells.pushBack(cellList.at(i));
			}

		}
	}
	return mcells;
}


void LifeGameGod::seedAllCells()
{
	for(int i = 0 ;i < verticalCount ; i++)
	{
		for(int j = 0 ;j < horizenCount; j++)
		{
			SingleCell* cell = SingleCell::create();
			cell->setTag(cellList.size()); 
			
			cell->setPositionIndex(i,j);
			cell->setPosition(Vec2(i*40,j*40)); 
			cellList.pushBack(cell);
			this->addChild(cell);
		}
	}
}

cocos2d::Vector<SingleCell*> LifeGameGod::getCellList()
{
	return cellList;
}


bool LifeGameGod::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("LifeGameGod::onTouchBegan 0  ");
	Vec2 pos = touch->getLocation();
	int  line= (pos.x-this->getPosition().x)/40;
	int row = (pos.y-this->getPosition().y)/40;
	if((row + line * 10) < cellList.size() && (row + line * 10) >=0 )
	{
		SingleCell* mcell  =  cellList.at(row + line * 10);
		mcell->changeState();
	} 
	return true;
}
void LifeGameGod::onTouchMoved(Touch *touch, Event *unused_event)
{
	CCLOG("LifeGameGod::onTouchMoved");

	Vec2 pos = touch->getLocation();
	int  line= (pos.x-this->getPosition().x)/40;
	int row = (pos.y-this->getPosition().y)/40;
	if((row + line * 10) < cellList.size() && (row + line * 10) >=0 )
	{
		SingleCell* mcell  =  cellList.at(row + line * 10);
		mcell->changeState();
	}
}

void LifeGameGod::onTouchEnded(Touch *touch, Event *unused_event)
{
	CCLOG("LifeGameGod::onTouchEnded");
}

void LifeGameGod::onTouchCancelled(Touch *touch, Event *unused_event)
{
	CCLOG("LifeGameGod::onTouchCancelled");
}