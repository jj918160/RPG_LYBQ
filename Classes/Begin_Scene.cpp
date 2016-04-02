
//  Begin_Scene.cpp
//  RPG_LYBQ
//
//  Created by mac on 15-11-14.
//
//

#include "Begin_Scene.h"
#include "Animation_itools.h"
#include "Loading_Layer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;


//unsigned char* Begin_Scene::loadmsg(const char* filepath){
//    //std::string docPath=FileUtils::getWritablePath();
//    unsigned long bufferSize=0;
//    unsigned char* pBuffer=NULL;
//    
//    std::string fullpath=FileUtils::getInstance()->fullPathForFilename(filepath);
//    auto data=FileUtils::getInstance()->getDataFromFile(filepath);
//    pBuffer=data.getBytes();
//
//    return pBuffer;
//}

Scene* Begin_Scene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Begin_Scene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Begin_Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    load_animation();
    FileUtils::getInstance()->addSearchPath("res/begin");
    title_num=0;
    auto size=Director::getInstance()->getVisibleSize();
    auto bg=Sprite::create("begin_s.png");
    bg->setPosition(size/2);
    addChild(bg);
   
	Label*title1 = Label::createWithBMFont("title.fnt", "琅琊榜前传");

	title1->setPosition(Vec2(size.width * 4 / 5, size.height * 7 / 8));
	addChild(title1);
	for (int i = 0; i < 5; i++) {
		auto sp = title1->getLetter(i);
		sp->setPosition(200, -size.height*i / 8);
		if (i >= 3){
			sp->setScale(0.8);
			sp->setColor(Color3B(200, 0, 0));
		}
	}
    
	Label*title2 = Label::createWithBMFont("arial-14.fnt", "一卷风云琅琊榜，");
	title2->setPosition(size.width / 5 + 100, size.height * 9 / 10);
	title2->setScale(0.6);
	addChild(title2, 0, 1);

	Label*title3 = Label::createWithBMFont("arial-14.fnt", "囊尽天下奇英才。");
	title3->setPosition(size.width * 3 / 10 + 100, size.height * 4 / 5);
	title3->setScale(0.6);
	addChild(title3, 0, 2);


	for (int i = 0; i < 8; i++) {
		title2->getLetter(i)->setOpacity(0);
		title3->getLetter(i)->setOpacity(0);
	}
    
    
    for (int i=0; i<2; i++) {
        create_bird(8.0+2*i,"ying");
        create_bird(8.0+2*i,"bianfu");
        create_bird(8.0+2*i,"flybird");
    }
    
    auto flag=Sprite::create();
    flag->setPosition(60,500);
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("flag");
    Animate* animate=Animate::create(a);
    flag->runAction(animate);
    flag->setScale(0.8);
    this->addChild(flag);

    
    
    
    
    creat_botton(3);
    creat_botton(1);
    creat_botton(5);
    creat_botton(7);
    creat_botton(10);
    auto mu=Menu::createWithArray(vecfoeitem);
    for (int i=0; i<vecfoeitem.size(); i++) {
        MenuItemSprite*p=(MenuItemSprite*)vecfoeitem.at(i);
        p->setPosition(i*100+100,200);
        
    }
    vecfoeitem.at(0)->setCallback(CC_CALLBACK_1(Begin_Scene::callback1,this));
//    vecfoeitem.at(1)->setCallback(CC_CALLBACK_1(Begin_Scene::callback2,this));
//    vecfoeitem.at(2)->setCallback(CC_CALLBACK_1(Begin_Scene::callback3,this));
//    vecfoeitem.at(3)->setCallback(CC_CALLBACK_1(Begin_Scene::callback4,this));
//    vecfoeitem.at(4)->setCallback(CC_CALLBACK_1(Begin_Scene::callback5,this));
    mu->setPosition(0, 0);
    mu->setOpacity(0);
    mu->runAction(Sequence::create(DelayTime::create(2.0),FadeIn::create(2.0),NULL));
    
    this->addChild(mu,1);
    
    
    
    
    for (int i=0; i<5; i++) {
        auto sp=Sprite::create();
        sp->setPosition(1000+100*i,200);
        AnimationCache* ac=AnimationCache::getInstance();
        Animation *a=ac->getAnimation("flymood");
        Animate* animate=Animate::create(a);
        sp->runAction(Spawn::create(animate,MoveTo::create(2, Vec2(200+100*i,200)),NULL));
        this->addChild(sp);
    }

    
    schedule(schedule_selector(Begin_Scene::create_flower), 1.5);
    schedule(schedule_selector(Begin_Scene::title_fadeout), 0.6, 17, 0.6);
    
    return true;
}

void Begin_Scene::onExit(){
    Layer::onExit();
    AnimationCache::getInstance()->destroyInstance();
    SpriteFrameCache::getInstance()->destroyInstance();
}
void Begin_Scene::load_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
   
     itools->cutPicturewithframe("begin/CG-1559.png", 2, 9, "a_%d");
    
    
    Animation*flymood=itools->makeAnimationfrommixpicture("begin/CG-1565.png",5,2,1,1,5,2,0.02f,true,10);
    ac->addAnimation(flymood,"flymood");
    Animation*flybird=itools->makeAnimationfrommixpicture("pic/CG-1560.png",2,3,1,1,2,3,0.2f,false,-1);
    ac->addAnimation(flybird,"flybird");
    Animation*flyflower=itools->makeAnimationfrommixpicture("pic/CG-1564.png",5,5,1,1,3,5,0.2f,false,-1);
    ac->addAnimation(flyflower,"flyflower");
    Animation*ying=itools->makeAnimationfrommixpicture("pic/bird.png", 2,3,1,1,2,3,0.2,false,-1);
    ac->addAnimation(ying,"ying");
    Animation*flag=itools->makeAnimationfrommixpicture("pic/flag.png", 2,2,1,1,2,2,0.2f,false,-1);
    ac->addAnimation(flag,"flag");
    Animation*bianfu=itools->makeAnimationfrommixpicture("pic/wuya.png", 4,3,1,1,4,3,0.1,false,-1);
    ac->addAnimation(bianfu,"bianfu");
    
}



void Begin_Scene::title_fadeout(float dt){
    title_num++;
    Label*l1=static_cast<Label*>(this->getChildByTag(1));
    Label*l2=static_cast<Label*>(this->getChildByTag(2));
    if (title_num>0&&title_num<9) {
        l1->getLetter(title_num-1)->runAction(FadeIn::create(0.5));
    }
    if (title_num>9&&title_num<18) {
        l2->getLetter(title_num-10)->runAction(FadeIn::create(0.5));
    }
    
    
}

void Begin_Scene::creat_botton(int t){
    
    char name[64]={0};
    char name2[64]={0};
    sprintf(name,"a_%d",t);
    sprintf(name2,"a_%d",t+1);
    SpriteFrame* sp=SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    auto sprite=Sprite::createWithSpriteFrame(sp);
    SpriteFrame* sp2=SpriteFrameCache::getInstance()->getSpriteFrameByName(name2);
    auto sprite2=Sprite::createWithSpriteFrame(sp2);
    
    MenuItemSprite*mp=MenuItemSprite::create(sprite, sprite2);
    
    vecfoeitem.pushBack(mp);
    
}


void Begin_Scene::create_bird(float t,std::string name){
    auto bird1=Sprite::create();
    bird1->setPosition(Vec2(CCRANDOM_0_1()*960,CCRANDOM_0_1()*640));
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation(name);
    Animate* animate=Animate::create(a);
    bird1->runAction(animate);
    bird1->runAction(RepeatForever::create(Sequence::create(MoveTo::create(t,Vec2(CCRANDOM_0_1()*960,CCRANDOM_0_1()*640)),
                                                            FlipX::create(true),
                                                            MoveTo::create(t,Vec2(CCRANDOM_0_1()*960,CCRANDOM_0_1()*640)),FlipX::create(false),
                                                            MoveTo::create(t,Vec2(CCRANDOM_0_1()*960,CCRANDOM_0_1()*640)),FlipX::create(true),
                                                            MoveTo::create(t,Vec2(CCRANDOM_0_1()*960,CCRANDOM_0_1()*640)),FlipX::create(false),
                                                            NULL)));
    
    this->addChild(bird1);
    
    
}



void Begin_Scene::create_flower(float dt){
    auto flower=Sprite::create();
    flower->setPosition(Vec2(CCRANDOM_0_1()*100+800,300+CCRANDOM_0_1()*700));
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("flyflower");
    Animate* animate=Animate::create(a);
    flower->runAction(animate);
    flower->runAction(Sequence::create(MoveTo::create(20,Vec2(CCRANDOM_0_1()*760+400,-10)),RemoveSelf::create(),
                                                             
                                                             NULL));
    this->addChild(flower);
    
}

void Begin_Scene::callback1(Ref* psender){
    SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(1.5,Loading_Layer::createScene()));
    
}
