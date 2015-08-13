#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //dokmeh ye bazgasht be safhe ye menu
    auto mainMenuItem = MenuItemImage::create("Menu_Button.png",
    "Menu_Button(Click).png", CC_CALLBACK_1(GameScreen::GoToMainMenuScene, this));

	mainMenuItem->setPosition(Point(mainMenuItem->getContentSize().width -
		(mainMenuItem->getContentSize().width / 4) + origin.x,
			visibleSize.height - mainMenuItem->getContentSize().height +
				(mainMenuItem->getContentSize().height / 4) + origin.y));
	auto menu = Menu::create(mainMenuItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//zamin e bazi!
	auto backgroundSprite = Sprite::create("soccer_field.png");
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
	origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);

	//3ta toop ro ta'arif mikonim
	ball1 = Sprite::create("ball.png");
	ball2 = Sprite::create("ball.png");
	ball3 = Sprite::create("ball.png");

	//toop ha ro too zamin michinim
	ball1->setPosition(Point(visibleSize.width / 2,
		mainMenuItem->getPosition().y - (mainMenuItem->getContentSize().height / 2)
		 - (ball1->getContentSize().height / 2)));
	ball2->setPosition(Point(visibleSize.width / 3, visibleSize.height / 3));
	ball3->setPosition(Point(2*visibleSize.width / 3, visibleSize.height / 3));
	this->addChild(ball1, -1);
	this->addChild(ball2, -1);
	this->addChild(ball3, -1);

	//initialize kardan e touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScreen::onTouchCancelled, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	isTouching = false;
	touchPositionX = 0;
	touchPositionY = 0;

	this->scheduleUpdate();

    return true;
}

//felan in function mohem nist, vali baraye taeen gozar e zaman ba'adan lazem mishe
void GameScreen::update(float dt)
{
	Size visibleSize = Director::getInstance()->
	getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// check if the screen is being touched
	if (true == isTouching)
	{
		// check which half of the screen is being touched
		//if (touchPosition < playerSprite->getPosition().x)
		//if (accleration < 0)
		//{
			// move the space pod left
		//	playerSprite->setPositionX(playerSprite->getPosition().x - (0.50 * visibleSize.width * dt));
			// check to prevent the space pod from going off the screen (left side)
		//	if (playerSprite->getPosition().x <= 0 + (playerSprite->getContentSize().width / 2))
		//	{
		//		playerSprite->setPositionX(playerSprite->getContentSize().width / 2);
		//	}
		//}
		//else
		//{
			// move the space pod right
		//	playerSprite->setPositionX(playerSprite->getPosition().x + (0.50 * visibleSize.width * dt));
			// check to prevent the space pod from going off the screen (right side)
		//	if (playerSprite->getPosition().x >= visibleSize.width - (playerSprite->getContentSize().width / 2))
		//	{
		//		playerSprite->setPositionX(visibleSize.width - (playerSprite->getContentSize().width / 2));
		//	}
		//}
	}
}

//inja mirim be safhe ye menu
//in function vaghti dokmeh ye menu too safheh ye bazi touch misheh seda zadeh mishe
void GameScreen::GoToMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool GameScreen::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{

	touchPositionX = touch->getLocation().x;
	touchPositionY = touch->getLocation().y;

	//inja tashkhis midim ke aya yeki az toopha touch shodeh ya na
	//agar shode bood, harekat shoru misheh
	//touch ta faseleh ye 25px az toop ro ham tashkhis midim
	if(ball1->getPosition().x-25 < touchPositionX and touchPositionX < ball1->getPosition().x+ball1->getContentSize().width+25 and ball1->getPosition().y-25 < touchPositionY and touchPositionY < ball1->getPosition().y+ball1->getContentSize().height+25)
	{
		isTouching = true;
		moving_ball = ball1;
		static_ball1 = ball2;
		static_ball2 = ball3;
		startX = moving_ball->getPosition().x;
		startY = moving_ball->getPosition().y;
		whichSide();
		betweenSign();
	}
	else if(ball2->getPosition().x-25 < touchPositionX and touchPositionX < ball2->getPosition().x+ball2->getContentSize().width+25 and ball2->getPosition().y-25 < touchPositionY and touchPositionY < ball2->getPosition().y+ball2->getContentSize().height+25)
	{
		isTouching = true;
		moving_ball = ball2;
		static_ball1 = ball3;
		static_ball2 = ball1;
		startX = moving_ball->getPosition().x;
		startY = moving_ball->getPosition().y;
		whichSide();
		betweenSign();
	}
	else if(ball3->getPosition().x-25 < touchPositionX and touchPositionX < ball3->getPosition().x+ball3->getContentSize().width+25 and ball3->getPosition().y-25 < touchPositionY and touchPositionY < ball3->getPosition().y+ball3->getContentSize().height+25)
	{
		isTouching = true;
		moving_ball = ball3;
		static_ball1 = ball1;
		static_ball2 = ball2;
		startX = moving_ball->getPosition().x;
		startY = moving_ball->getPosition().y;
		whichSide();
		betweenSign();
	}

	return true;
}

void GameScreen::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if(isTouching)
	{
		touchPositionX = touch->getLocation().x;
		touchPositionY = touch->getLocation().y;
		moving_ball->setPositionX(touchPositionX);
		moving_ball->setPositionY(touchPositionY);

		//agar toop az khat e vasel e 2ta toop e ista rad shod
		if (checkCrossBall()){

			//agar toop bein e 2ta khat e vasele bein e noghte ye aghaz va 2ta toop e ista nabood
			if(!isBetween()){

				//yaane bazikon khata karde va bakhteh(felan az safhe ye bazi mirim biroon)
				auto scene = MainMenu::createScene();
				Director::getInstance()->replaceScene(scene);
			}
		}
	}
}

void GameScreen::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event)
{
	isTouching = false;
	//agar toop az khat e vasel e 2ta toop e ista rad nashodeh bood
	//ya agar toop bein e 2ta khat e vasele bein e noghte ye aghaz va 2ta toop e ista nabood
	if(!checkCrossBall() or !isBetween()){

		//yaane bazikon khata karde va bakhteh(felan az safhe ye bazi mirim biroon)
		auto scene = MainMenu::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void GameScreen::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event)
{
	onTouchEnded(touch, event);
}

//ta'aeen mikinim ke toop az khat e vasel e bein e 2ta toop ista rad shode ya na
//inja az in nokteh estefadeh mishe ke agar toop az khat rad beshe va ma positionesh ro too
//moadeleh ye khat bezrim, oonvaght alamatesh ba ghabl az oboor e toop fargh mikoneh
bool GameScreen::checkCrossBall(){
	//tashkil e moadeleh ye khat e bein e 2ta toop e ista
	float y1 = static_ball1->getPosition().y;
	float y2 = static_ball2->getPosition().y;
	float x1 = static_ball1->getPosition().x;
	float x2 = static_ball2->getPosition().x;
	float y = moving_ball->getPosition().y;
	float x = moving_ball->getPosition().x;
	float m = (y2-y1)/(x2-x1);
	float distance = (y-y1)-(m*(x-x1));

	//side, az gharar dadan e postition e toop dar aghaz e harekat bedast oomadeh
	if((side < 0 and distance > 0) or (side > 0 and distance < 0)){
		return true;
	}

	return false;
}

//inja variable side ro meghdar dehi mikonim
//side, too function e checkCrossBall() estefadeh mishe
void GameScreen::whichSide(){
	float y1 = static_ball1->getPosition().y;
	float y2 = static_ball2->getPosition().y;
	float x1 = static_ball1->getPosition().x;
	float x2 = static_ball2->getPosition().x;
	float y = moving_ball->getPosition().y;
	float x = moving_ball->getPosition().x;
	float m = (y2-y1)/(x2-x1);
	float distance = (y-y1)-(m*(x-x1));
	if(distance<0){
		side = -1;
	}
	else{
		side = 1;
	}
}

//inja yek noghteh bein e 2ta khat e vasel e bein e noghteh ye start e harekat va 2ta toop e ista dar nazar migirim
//va ta'aeen mikonim ke age ye noghteh bein e in 2ta khat bashe bayad che alamati dashteh bashe(too variable between)
void GameScreen::betweenSign(){
	float betweenX = (static_ball1->getPosition().x+static_ball2->getPosition().x)/2;
	float betweenY = (static_ball1->getPosition().y+static_ball2->getPosition().y)/2;
	float y1 = static_ball2->getPosition().y;
	float x1 = static_ball2->getPosition().x;
	float m = (startY-y1)/(startX-x1);
	float distance1 = (betweenY-y1)-(m*(betweenX-x1));

	y1 = static_ball1->getPosition().y;
	x1 = static_ball1->getPosition().x;
	m = (startY-y1)/(startX-x1);
	float distance2 = (betweenY-y1)-(m*(betweenX-x1));

	if(distance1*distance2<0){
		between = -1;
	}
	else{
		between = 1;
	}
}

//inja ta'aeen mikonim ke aya toop bein e 2ta khat e vasel e bein e noghteh ye start e harekat va 2ta toop e ista, hast ya na
//agar nabood ya'anee bakhteh
bool GameScreen::isBetween(){
	float movingBallX = moving_ball->getPosition().x;
	float movingBallY = moving_ball->getPosition().y;
	float y1 = static_ball2->getPosition().y;
	float x1 = static_ball2->getPosition().x;
	float m = (startY-y1)/(startX-x1);
	float distance1 = (movingBallY-y1)-(m*(movingBallX-x1));

	y1 = static_ball1->getPosition().y;
	x1 = static_ball1->getPosition().x;
	m = (startY-y1)/(startX-x1);
	float distance2 = (movingBallY-y1)-(m*(movingBallX-x1));

	//bayad alamatesh ba alamat e noghte ye bein 2ta khat yeki basheh
	if(distance1*distance2<0){
		if(between>0){
			return false;
		}
	}
	else{
		if(between<0){
			return false;
		}
	}
	return true;
}

