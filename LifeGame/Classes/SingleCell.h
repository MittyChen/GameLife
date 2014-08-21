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
	virtual bool init(); 
	void update(float delta);

	void setPositionIndex(int valX,int valY );
	int getPositionIndexX();
	int getPositionIndexY();
	CELL_LIVNG_STATE getCurrentLivingState();
	void setChangeFlag();
	bool isNeedChange();
	void updateCellState();
	void updateCellColor();
	void changeState( );
	void updateTheSituation();
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	cocos2d::Vector<SingleCell*> getCellsAround();
	void setCellsAround(cocos2d::Vector<SingleCell*> val);
	void startLifeJourney();
	void endLifeJourney();
private: 
	CELL_LIVNG_STATE getNextState();

	CELL_LIVNG_STATE currentLivingState;
	CELL_LIVNG_STATE lastLivingState;

	cocos2d::Vector<SingleCell*> cellsAround;

	int lastLivingSumAround;

	bool needChangeState;
	cocos2d::Vec2 posi;
	int xIndex;
	int yIndex;
protected:
	 cocos2d::CustomCommand _customCommand;
	 cocos2d::EventListenerTouchOneByOne *event;
};

