#include "LifeGameGod.h"
#include "ConstCells.h"
using namespace cocos2d;
LifeGameGod::LifeGameGod(void)
{
}


LifeGameGod::~LifeGameGod(void)
{
}

int LifeGameGod::getCellCount()
{
	return cellList.size();
}

void LifeGameGod::update( float delta )
{
}


 


bool LifeGameGod::init()
{
	if(!Node::init())
	{
		return false;
	}
	isRunningLife = false;
	 visibleSize = Director::getInstance()->getVisibleSize();
	  origin = Director::getInstance()->getVisibleOrigin();
	 {//touch event
		 auto event = EventListenerTouchOneByOne::create();
		 event->onTouchBegan = CC_CALLBACK_2(LifeGameGod::onTouchBegan,this);
		 event->onTouchCancelled = CC_CALLBACK_2(LifeGameGod::onTouchCancelled,this);
		 event->onTouchEnded = CC_CALLBACK_2(LifeGameGod::onTouchEnded,this);
		 event->onTouchMoved = CC_CALLBACK_2(LifeGameGod::onTouchMoved,this);
		 event->setSwallowTouches(true);
		 _eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);

	 
	CELLS_HEIGHT = visibleSize.height * 0.9 / CELLS_VERTICAL_COUNT  - CELLS_HEIGHT_SPEACING;
	CELLS_WIDTH = CELLS_HEIGHT; 
	this->setPosition(origin.x+visibleSize.height*0.05,origin.y+visibleSize.height*0.05);
	 }
	 
	  seedAllCells();
	 return true;
}

//��ȡ��Χ�İ˸�cell
cocos2d::Vector<SingleCell*> LifeGameGod::getCellsAroundTargetCell( int x,int y)
{
	cocos2d::Vector<SingleCell*> mcells ;
	CCLOG("LifeGameGod::getCellsAroundTargetCell  [%d %d]",x,y );
	for(int i = 0;i<getCellCount();i++)
	{
		if(abs(cellList.at(i)->getPositionIndexX() - x) <= 1 &&  abs(cellList.at(i)->getPositionIndexY() - y) <=1  )//��Χ��  ���˸�
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
			cell->setContentSize(Size(CELLS_WIDTH,CELLS_HEIGHT));
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
	CCLOG("isRunningLife  %d",isRunningLife);
	if(isRunningLife)
	{
		return false;
	}
    CCLOG("pos  xy [%f  %f]  visibleSize.height *0.95  %f  this->getPosition().x%f ",pos.x ,pos.y,visibleSize.height *0.95  ,this->getPosition().x );
	if(pos.x < this->getPosition().x || pos.x>visibleSize.height *0.95 || pos.y < this->getPosition().y || pos.y>visibleSize.height *0.95)
	{
        CCLOG("out of bounds  %f  %f",pos.x ,pos.y);
		return false;
	}

	int  line= (pos.x-this->getPosition().x)/(CELLS_WIDTH+CELLS_WIDTH_SPEACING);
	int row = (pos.y-this->getPosition().y)/( CELLS_HEIGHT+CELLS_HEIGHT_SPEACING);
	if((row + line * CELLS_HORIZEN_COUNT) < cellList.size() && (row + line * CELLS_HORIZEN_COUNT) >=0 )
	{
        CCLOG("state change  %d  %d",line ,row);
		SingleCell* mcell  =  cellList.at(row + line * CELLS_HORIZEN_COUNT);
		mcell->changeState();
		mcell->updateCellColor();
	} 
	return true;
}
int currentLine = -1;
int currentRow= -1;
void LifeGameGod::onTouchMoved(Touch *touch, Event *unused_event)
{
	Vec2 pos = touch->getLocation();
	if(isRunningLife)
	{
		return;
	}
	if(pos.x < this->getPosition().x || pos.x>visibleSize.height *0.95 || pos.y < this->getPosition().y || pos.y>visibleSize.height *0.95)
	{
		return;
	}
	Vec2 startpo = touch->getStartLocation();
	int  line= (pos.x-this->getPosition().x)/(CELLS_WIDTH+CELLS_WIDTH_SPEACING);
	int row = (pos.y-this->getPosition().y)/( CELLS_HEIGHT+CELLS_HEIGHT_SPEACING);
	if((row + line * CELLS_HORIZEN_COUNT) < cellList.size() && (row + line * CELLS_HORIZEN_COUNT) >=0 )
	{
		if(currentRow != row || currentLine != line)//��Ϊ��ǰ�����е����п�
		{
			SingleCell* mcell  =  cellList.at(row + line * CELLS_HORIZEN_COUNT);
			mcell->changeState();
			mcell->updateCellColor();
		}
	}
	 currentLine = line;
	 currentRow= row;
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


void LifeGameGod::gameStart()
{
	isRunningLife = true;
	schedule(schedule_selector( LifeGameGod::updateCells), CELLS_UPDATE_BREAK_TIME,kRepeatForever, 0.0f);
}


void LifeGameGod::gamePause()
{
	isRunningLife = false;
	unschedule(schedule_selector( LifeGameGod::updateCells));
}
void LifeGameGod::gameResume()
{
	isRunningLife = true;
	schedule(schedule_selector( LifeGameGod::updateCells), CELLS_UPDATE_BREAK_TIME,kRepeatForever, 0.0f);
}


void LifeGameGod::gameReset()
{
	isRunningLife = false;
	gamePause();
	for(int i = 0;i<getCellCount();i++)
	{ 
		SingleCell* mcell = cellList.at(i);
		 if(mcell->getCurrentLivingState() == LIVING_STATE)
		 {
			 mcell->changeState();
		 }
	}

	for(int i = 0;i<getCellCount();i++)
	{ 
		SingleCell* mcell = cellList.at(i);
		mcell->updateCellColor();
	}
}

