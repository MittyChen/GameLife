#include "GameScene.h"
#include "CommonUtils.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    //auto titleText = LabelTTF::create("Game Scene", "epson1", 70);
    //titleText->setColor(Color3B(0.0f,128.0f,255.0f));
    //titleText->setPosition(Vec2(origin.x + visibleSize.width/2,   origin.y + visibleSize.height -  titleText->getContentSize().height));
    //this->addChild(titleText, 1);

 
	 god =LifeGameGod::create();

	 god->getCellList();

	{//touch event
		auto event =EventListenerTouchOneByOne::create();
		event->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
		event->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
		event->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
		event->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
	} 
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}




bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("HelloWorld::onTouchBegan");
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(GameScene::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}
void GameScene::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
	CHECK_GL_ERROR_DEBUG();


	Vec2 points[] = { Vec2(300,300)};
	DrawPrimitives::setPointSize(16);
	DrawPrimitives::setDrawColor4B(0,100,255,255);
	DrawPrimitives::drawPoints( points, 1);
 
	//end draw
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}