#include "cocos2d.h"
using namespace cocos2d;

static const int CELLS_HORIZEN_COUNT = 100;//ˮƽ��Ŀ
static const int CELLS_VERTICAL_COUNT = 100;//��ֱ��Ŀ

 

static const Color3B DEAD_COLOR= Color3B(110,110,110);
static const Color3B LIVING_COLOR= Color3B(1,255,1);

static const float CELLS_WIDTH_SPEACING = 1.0f;
static const float CELLS_HEIGHT_SPEACING = 1.0f;

static const float CELLS_UPDATE_BREAK_TIME =0.1f;
