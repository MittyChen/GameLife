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
	virtual void update(float delta);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	//Î»ÖÃË÷Òý
	void setPositionIndex(int valX,int valY );
	int getPositionIndexX();
	int getPositionIndexY();

	//´æ»î×´Ì¬
	CELL_LIVNG_STATE getCurrentLivingState();
	void setChangeFlag();
	bool isNeedChange();


	void updateCellState();
	void changeState( );
	void updateCellColor();
	void updateTheSituation();
	  
	cocos2d::Vector<SingleCell*> getCellsAround();
	void setCellsAround(cocos2d::Vector<SingleCell*> val);
private: 
	CELL_LIVNG_STATE getNextState();
	CELL_LIVNG_STATE currentLivingState;
	cocos2d::Vector<SingleCell*> cellsAround;
	int lastLivingSumAround;
	bool needChangeState;
	int xIndex;
	int yIndex;
protected:
	 cocos2d::CustomCommand _customCommand;
	 
};

