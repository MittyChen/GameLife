#include "SingleCell.h"


using namespace cocos2d;

SingleCell::SingleCell(void)
{
	currentLivingState = CELL_LIVNG_STATE::DEAD_STATE;
}


SingleCell::~SingleCell(void)
{
}

CELL_LIVNG_STATE SingleCell::getNextState()
{
	switch(currentLivingState)
	{
	case::CELL_LIVNG_STATE::LIVING_STATE: 
		{
			return CELL_LIVNG_STATE::DEAD_STATE;
			break;
		} 
	case::CELL_LIVNG_STATE::DEAD_STATE:
		{
			return CELL_LIVNG_STATE::LIVING_STATE;
			break;
		} 
	}
	return currentLivingState;
}

void SingleCell::update( float delta )
{
	if(needChangeState)
	{
		currentLivingState = getNextState();
		needChangeState = false;
	}
}

bool SingleCell::init()
{
	if(!Node::init())
	{
		return false;
	}



	{//touch event
		auto event = EventListenerTouchOneByOne::create();
		event->onTouchBegan = CC_CALLBACK_2(SingleCell::onTouchBegan,this);
		event->onTouchCancelled = CC_CALLBACK_2(SingleCell::onTouchCancelled,this);
		event->onTouchEnded = CC_CALLBACK_2(SingleCell::onTouchEnded,this);
		event->onTouchMoved = CC_CALLBACK_2(SingleCell::onTouchMoved,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
	}


	return true;

}

CELL_LIVNG_STATE SingleCell::getCurrentLivingState()
{
	return currentLivingState;
}

void SingleCell::setChangeFlag()
{
	needChangeState = true;
}

void SingleCell::setPosition( cocos2d::Vec2 val )
{
	posi = val;
}

cocos2d::Vec2 SingleCell::getPosition()
{
	return posi;
}

bool SingleCell::updateChangeFlag( cocos2d::Vector<SingleCell*> cellsAround )
{
	int count = cellsAround.size();
	int livingSum = 0;
	for(int i=0; i<count; i++)
	{
		livingSum+= (int)cellsAround.at(i)->getCurrentLivingState();
	}

	if(livingSum>3 || livingSum < 2)//如果多余三个 活着就去死
	{
		if(currentLivingState == LIVING_STATE)
		{
			needChangeState = true;
		}
	}
	if(livingSum = 3)//如果等于三个 死了就复活
	{
		if(currentLivingState == DEAD_STATE)
		{
			needChangeState = true;
		}
	}
	if(livingSum = 2)//如果等于两个 保持不变
	{
		needChangeState = false;
	}
}


bool SingleCell::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("SingleCell::onTouchBegan");
	return true;
}

void SingleCell::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void SingleCell::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void SingleCell::onTouchCancelled(Touch *touch, Event *unused_event)
{

}