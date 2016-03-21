//
//  Scene0_1.cpp
//  RPG_LYBQ
//
//  Created by mac on 15-11-15.
//
//
#include "Player_Base.h"
#include "Scene0_1.h"
#include "UI_Layer.h"
#include "Animation_itools.h"
#include "Talking_Rush.h"
Scene* Scene0_1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = Scene0_1::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Scene0_1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    FileUtils::getInstance()->addSearchPath("res/headpic");
    loadAnimation();
    talk_over=false;
    main_step=0;
    auto size=Director::getInstance()->getVisibleSize();
    
    auto bg=Sprite::create("pic/xuanya.jpg");
    bg->setPosition(size/2);
    addChild(bg,0,9);
//    
    
    auto sp=Player_Base::create("linsu.png", "linsu");
   
    sp->setPosition(1050,150);
    sp->set_chineseName("林殊");
    addChild(sp,1,2);
    sp->walk("linsuleft_up");
    sp->runAction(Sequence::create(MoveBy::create(3,Vec2(-350,50)),CallFuncN::create([=](Node*pSender){
        pSender->stopAllActions();
       
    }),NULL));
    
    auto sp2=Player_Base::create("weizhen.png", "weizhen");
    sp2->set_chineseName("卫铮");
    sp2->setPosition(1050,50);
    addChild(sp2,1,22);
    sp2->walk("weizhenleft_up");
    sp2->runAction(Sequence::create(MoveBy::create(3,Vec2(-350,50)),CallFuncN::create([=](Node*pSender){
        pSender->stopAllActions();
       
    }),NULL));
    
    auto sp3=Player_Base::create("linxie.png", "linxie");
    
    sp3->setPosition(900,100);
    addChild(sp3,1,33);
    sp3->walk("linxieleft_up");
    sp3->runAction(Sequence::create(MoveBy::create(3,Vec2(-350,50)),CallFuncN::create([=](Node*pSender){
        pSender->stopAllActions();
        sp3->set_Image("linxie.png",2,0);
    }),NULL));
    sp3->set_chineseName("林燮");
   
    vec.pushBack(sp);
    vec.pushBack(sp2);
    vec.pushBack(sp3);
    
    auto ui=UI_Layer::getInstance();
    addChild(ui,2);
    
      scheduleOnce(schedule_selector(Scene0_1::step_1), 3.2);
    
   
    
    
    
    return true;
}
bool Scene0_1::touch_oneP(Vec2 pot){
    CCLOG("vec.size:%zd",vec.size());
    for (Player_Base* sp:vec) {
    if(sp->getBoundingBox().containsPoint(pot)){
        
        Player_Base*t=UI_Layer::getInstance()->get_control();
        while(t&&t->getChildByTag(5)) {
            t->removeChildByTag(5);
        }
        if (t) {
             t->set_active(false);
        }
        UI_Layer::getInstance()->set_control(sp);
        auto label=Label::createWithSystemFont(sp->get_chineseName(), "Arial", 24);
        label->setPosition(sp->getContentSize().width/2,sp->getContentSize().height);
        sp->addChild(label,1,5);
       
        return true;
    }
    }
    return false;

}
void Scene0_1::step_1(float dt){
        std::vector<std::string> msg;
        msg=itools->load_mssage("headpic/talk0_1.txt", msg);
        Talking_Rush*tr=Talking_Rush::create(msg);
        addChild(tr,1,1);
       scheduleUpdate();
    
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        
        if ((touch_oneP(touch->getLocation())))
        {
            return true;
        }
        return false;
    };
    listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,-1);
    
}
void Scene0_1::update(float dt){
    Talking_Rush*t=static_cast<Talking_Rush*>(this->getChildByTag(1));
    
    if (t) {
        talk_over=t->over;
    }
    
    if (talk_over) {
            auto edgaline=Sprite::create();
            Point points[]={
                Vec2(566,0),Vec2(820,0),Vec2(960,68),
                Vec2(960,492),Vec2(900,463),Vec2(598,567),Vec2(536,537),Vec2(350,625),Vec2(237,626),
                Vec2(0,515),Vec2(0,103),Vec2(114,183),Vec2(566,0)
        
            };
            auto line=PhysicsBody::createEdgeChain(points,13);
            edgaline->setPhysicsBody(line);
            auto bg=(Sprite*)this->getChildByTag(9);
            bg->addChild(edgaline);

        unscheduleUpdate();
        schedule(schedule_selector(Scene0_1::step_2),1/30,-1,1);
        t->runAction(RemoveSelf::create());
        main_step=1;
       
    }
    if (main_step==1) {
        
         auto sp=(Player_Base*)this->getChildByTag(2);
        UI_Layer::getInstance()->set_control(sp);
        UI_Layer::getInstance()->set_work("任务:控制卫铮到达指定地点");
        
        auto cs=Sprite::create();
        Animation*animation=AnimationCache::getInstance()->getAnimation("chuansong");
        Animate*a=Animate::create(animation);
        cs->runAction(a);
        cs->setPosition(750,20);
        this->addChild(cs,2,8);
        
       
    }
}
void Scene0_1::loadAnimation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*talk=itools->makeAnimationfrommixpicture("CG-1165.png",4,1,1,1,4,1,0.2f,false,-1);
    ac->addAnimation(talk,"talk");
    
    Animation*chuansong=itools->makeAnimationfrommixpicture("CG-1648.png",3,1,1,1,3,1,0.5f,false,-1);
    ac->addAnimation(chuansong,"chuansong");
    
    Animation*des1=itools->makeAnimationfrommixpicture("CG-1175.png",3,3,1,1,3,3,0.2f,false,-1);
    ac->addAnimation(des1,"des1");

    Animation*des2=itools->makeAnimationfrommixpicture("CG-1178.png",3,3,1,1,3,3,0.2f,false,-1);
    ac->addAnimation(des2,"des2");
    
}

void Scene0_1::step_2(float dt){
    
    auto sp2=(Player_Base*)this->getChildByTag(22);
    if (main_step==1&&sp2->getBoundingBox().containsPoint(this->getChildByTag(8)->getPosition())) {
         main_step=2;
        vec.eraseObject(sp2);
        UI_Layer::getInstance()->set_control(nullptr);
        sp2->runAction(Sequence::create(RemoveSelf::create(), CallFunc::create([&](){
            CCLOG("over");
            UI_Layer::getInstance()->set_work("任务:控制林殊到达指定地点");
            this->getChildByTag(8)->setPosition(10,200);
             unschedule(schedule_selector(Scene0_1::step_2));
            schedule(schedule_selector(Scene0_1::step_3),1/30,-1,1);
        }),NULL));
    }
}

void Scene0_1::step_3(float dt){
   //__NotificationCenter
    auto sp2=(Player_Base*)this->getChildByTag(2);
    if (main_step==2&&sp2->getBoundingBox().containsPoint(this->getChildByTag(8)->getPosition())) {
        main_step=3;
        vec.eraseObject(sp2);
        UI_Layer::getInstance()->set_control(nullptr);
        sp2->runAction(Sequence::create(RemoveSelf::create(), CallFunc::create([&](){
            CCLOG("over");
            UI_Layer::getInstance()->set_work("任务:控制林燮到达指定地点");
            this->getChildByTag(8)->setPosition(460,300);
            unschedule(schedule_selector(Scene0_1::step_3));
            schedule(schedule_selector(Scene0_1::step_4),1/30,-1,1);
        }),NULL));
    }
}
void Scene0_1::step_4(float dt){
    auto sp3=(Player_Base*)this->getChildByTag(33);
    if (main_step==3&&sp3->getBoundingBox().containsPoint(this->getChildByTag(8)->getPosition())) {
        main_step=4;
       auto kk=(Player_Base*)UI_Layer::getInstance()->get_control();
        kk->stopAllActions();
        kk->set_active(false);
        sp3->set_Image("linxie.png",2,0);
        _eventDispatcher->pauseEventListenersForTarget(UI_Layer::getInstance());
        UI_Layer::getInstance()->setVisible(false);
    }

}
