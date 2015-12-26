//
//  Loading_Layer.cpp
//  RPG_LYBQ
//
//  Created by mac on 15-11-14.
//
//

#include "Loading_Layer.h"
#include "Animation_itools.h"
#include "Talking_Rush.h"
#include "Scene0_1.h"
Scene* Loading_Layer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Loading_Layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Loading_Layer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    main_step=0;
    talk_over=false;
    FileUtils::getInstance()->addSearchPath("res/headpic");
    auto bg=Sprite::create("pic/jieshao.jpg");
    bg->setPosition(480,320);
    addChild(bg);
    
    char*msg=loadmsg("headpic/dubai.txt");
    auto label=Label::createWithSystemFont(msg,"Arial", 28,Size::ZERO, TextHAlignment::CENTER,
                                            TextVAlignment::TOP);
    label->setPosition(Vec2(480,-300));
    addChild(label);
    label->runAction(Sequence::create(MoveTo::create(20,Vec2(480,840)),FadeOut::create(2.f),RemoveSelf::create(), NULL));
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        main_step++;
        label->stopAllActions();
        label->setPosition(480,640);
        label->runAction(Sequence::create(FadeOut::create(2.f),RemoveSelf::create(), NULL));
        std::vector<std::string> msg;
        msg=itools->load_mssage("headpic/talk1.txt", msg);
        Talking_Rush*tr=Talking_Rush::create(msg);
        addChild(tr,1,1);
        scheduleUpdate();
        return true;
    };
    listener->onTouchEnded=[=](Touch*touch,Event*event){
        _eventDispatcher->removeEventListener(listener);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    
    scheduleOnce(schedule_selector(Loading_Layer::step_2), 22);
    
    return true;
}
char* Loading_Layer::loadmsg(const char* filepath){
    std::string fullpath=FileUtils::getInstance()->fullPathForFilename(filepath);
    
    FILE*fp=fopen(fullpath.c_str(), "r");
    fseek(fp,0,SEEK_END);
    int len=ftell(fp);
    char*p=new char[len+1];
    memset(p, 0, len+1);
    fseek(fp, 0, SEEK_SET);
    fread(p,1, len, fp);
    fclose(fp);//关闭文件
    return p;
}
void Loading_Layer::step_2(float dt){
    if (main_step==0) {
    std::vector<std::string> msg;
    msg=itools->load_mssage("headpic/talk1.txt", msg);
    Talking_Rush*tr=Talking_Rush::create(msg);
    addChild(tr,1,1);
    scheduleUpdate();
    }
}
void Loading_Layer::update(float dt){
    Talking_Rush*t=static_cast<Talking_Rush*>(this->getChildByTag(1));
    if (t) {
          talk_over=t->over;
    }
    if (talk_over) {
        CCLOG("123");
        unscheduleUpdate();
         Director::getInstance()->replaceScene(TransitionFade::create(1.5,Scene0_1::createScene()));
    }
}
