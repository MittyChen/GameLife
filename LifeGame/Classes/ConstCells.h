#include "cocos2d.h"
using namespace cocos2d;

static const int CELLS_HORIZEN_COUNT = 15;//ˮƽ��Ŀ
static const int CELLS_VERTICAL_COUNT = 15;//��ֱ��Ŀ


static const float CELLS_WIDTH = 30.0f;
static const float CELLS_HEIGHT = 30.0f;

static const Color3B DEAD_COLOR= Color3B(110,110,110);
static const Color3B LIVING_COLOR= Color3B(0,255,0);

static const float CELLS_WIDTH_SPEACING = 1.0f;
static const float CELLS_HEIGHT_SPEACING = 1.0f;

static const float CELLS_UPDATE_BREAK_TIME =0.5f;