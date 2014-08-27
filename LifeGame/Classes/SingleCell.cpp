#include "SingleCell.h"
#include "ConstCells.h"

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

void SingleCell::changeState()
{
    setChangeFlag();
		currentLivingState = getNextState();
    
}

bool SingleCell::init()
{
	if(!LayerColor::init())
	{
		return false;
	}

	this->initWithColor(Color4B(0.0f,0.0f,0.0f,255));
	this->setColor(DEAD_COLOR); 
	currentLivingState = CELL_LIVNG_STATE::DEAD_STATE;
	lastLivingSumAround = 0;
	this->scheduleUpdate();

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

bool  SingleCell::isNeedChange()
{
	return needChangeState;
}



void SingleCell::updateCellState()
{
	int count = cellsAround.size();
	int livingSum = 0;
	for(int i=0; i<count; i++)
	{
		livingSum+= (int)cellsAround.at(i)->getCurrentLivingState();
	}
	 
	if(lastLivingSumAround>3 || lastLivingSumAround < 2)//如果多余三个 活着就去死
	{
		if(currentLivingState == LIVING_STATE)
		{
			changeState();
			needChangeState = true;
		}
	}

	if(lastLivingSumAround ==  3)//如果等于三个 死了就复活
	{
		if(currentLivingState == DEAD_STATE)
		{
			changeState();
			needChangeState = true;
		}
	}

	lastLivingSumAround = livingSum;//更新存货环境
}

 
void SingleCell::setPositionIndex(int valX,int valY )
{
	 xIndex= valX;
	 yIndex = valY;
}

int SingleCell::getPositionIndexX()
{
	return xIndex;
}
int  SingleCell::getPositionIndexY()
{
	return yIndex;
}


void SingleCell::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	LayerColor::draw(renderer,transform,flags);
	_customCommand.init(_globalZOrder);
	renderer->addCommand(&_customCommand);
}

void SingleCell::update( float delta )
{

}

cocos2d::Vector<SingleCell*> SingleCell::getCellsAround()
{
	return cellsAround;
}

void SingleCell::setCellsAround( cocos2d::Vector<SingleCell*> val )
{
	cellsAround = val;
}

void SingleCell::updateCellColor()
{
	if(needChangeState)
	{
		if(currentLivingState == DEAD_STATE)
		{
			this->setColor(DEAD_COLOR); 
		}else{
			this->setColor(LIVING_COLOR);
            this->updateCascadeColor();
		}
	}
}

void SingleCell::updateTheSituation()
{
	int count = cellsAround.size();
	lastLivingSumAround = 0;
	for(int i=0; i<count; i++)//获取初始的周边存活环境
	{ 
		lastLivingSumAround += cellsAround.at(i)->getCurrentLivingState();
	} 
}
