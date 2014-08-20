#include "SingleCell.h"


using namespace cocos2d;

SingleCell::SingleCell(void)
{
	
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

void SingleCell::changeState( )
{
		currentLivingState = getNextState();
		if(currentLivingState == DEAD_STATE)
		{
			this->setColor(Color3B(255,0,255));
		}else{
			this->setColor(Color3B(0,100,0));
		}
}

bool SingleCell::init()
{
	if(!LayerColor::init())
	{
		return false;
	}

	this->initWithColor(Color4B(0.0f,0.0f,0.0f,255));

	currentLivingState = CELL_LIVNG_STATE::DEAD_STATE;
	this->setColor(Color3B(255,0,255));


	this->setContentSize(Size(30,30));

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



void SingleCell::updateChangeFlag( cocos2d::Vector<SingleCell*> cellsAround )
{
	int count = cellsAround.size();
	int livingSum = 0;
	for(int i=0; i<count; i++)
	{
		livingSum+= (int)cellsAround.at(i)->getCurrentLivingState();
	}

	CCLOG("SingleCell::updateChangeFlag  [ %d  %d] ",livingSum,currentLivingState);

	if(livingSum>3 || livingSum < 2)//如果多余三个 活着就去死
	{
		if(currentLivingState == LIVING_STATE)
		{
			changeState();
		}
	}
	if(livingSum = 3)//如果等于三个 死了就复活
	{
		if(currentLivingState == DEAD_STATE)
		{
			changeState();
		}
	}
	if(livingSum = 2)//如果等于两个 保持不变
	{
		needChangeState = false;
	}
}

 
void SingleCell::setPositionIndex( cocos2d::Vec2 val )
{
	posi = val;
}

cocos2d::Vec2 SingleCell::getPositionIndex()
{
	return posi;
}

void SingleCell::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	LayerColor::draw(renderer,transform,flags);
	_customCommand.init(_globalZOrder);
	renderer->addCommand(&_customCommand);
}