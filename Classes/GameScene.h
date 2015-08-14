#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <string>

class GameScreen : public cocos2d::Layer
{
	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();
		void GoToMainMenuScene(Ref *pSender);
		//tozihe har function dar mahhalle implement neveshteh shodeh
		bool checkCrossBall();
		void whichSide();
		bool isBetween();
		void betweenSign();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// implement the "static create()" method manually
		CREATE_FUNC(GameScreen);

		//ta'arif e 3 ta toop
		cocos2d::Sprite *ball1;
		cocos2d::Sprite *ball2;
		cocos2d::Sprite *ball3;

		//toop e dar hale harekat va 2ta toop e ista ro too in variable ha zakhireh mikonim
		cocos2d::Sprite *moving_ball;
		cocos2d::Sprite *static_ball1;
		cocos2d::Sprite *static_ball2;

		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
		void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
		void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);

		void update(float dt);

		//taaeen harekat kardan
		bool isTouching;

		//mahhalle touch
		float touchPositionX;
		float touchPositionY;

		//taaeen mikonim ke toop kodum tarafe khate vasele 2ta toop ista hast
		int side;

		//too in variable alamat e yek noghteh vasat 2ta toop e ista ro zakhireh mikonim
		int between;

		//mahhalle ahgaz e touch ro zakhireh mikonim
		float startX;
		float startY;

};

#endif // __HELLOWORLD_SCENE_H__
