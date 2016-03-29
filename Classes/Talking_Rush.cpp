//
//  Talking_Rush.cpp
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#include "Talking_Rush.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Talking_Rush*Talking_Rush:: create(std::vector<std::string>talk)
{
    Talking_Rush *pRet = new(std::nothrow) Talking_Rush();
    if (pRet && pRet->init(talk))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool Talking_Rush::init(std::vector<std::string>talk)
{
    if (!Layer::init()) {
        return false;
    }
    count_page=talk.size();
    re_page=0;
    over=false;
    
    auto touch=Sprite::create();
    Animation*animation=Animation::create();
    animation->addSpriteFrameWithFile("36-18.png");
    animation->addSpriteFrameWithFile("36-19.png");
    animation->setDelayPerUnit(0.5);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);
    Animate*ani=Animate::create(animation);
    touch->runAction(ani);
    touch->setPosition(480,320);
    this->addChild(touch,1);
    
    
    
    
    
    
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
        
        if (re_page==count_page) {
            
            over=true;
            _eventDispatcher->removeEventListener(listener);
            
            return false;
        }
        return true;
    };
    
    
    
    listener->onTouchEnded=[=](Touch*touch,Event*event){
        this->removeAllChildren();
       // CCLOG("page:%d,coun_page:%d",re_page,count_page);
        Sprite*sp=Sprite::create("talk2.png");
        sp->setPosition(420,100);
        sp->setFlippedX(true);
        this->addChild(sp);
        
        
        
        std::string first=talk.at(re_page);
        //CCLOG("%s",first.c_str());
//        Label*la=Label::create(first, "Arial", 20);
//        la->setColor(Color3B(255, 0, 0));
//        la->setPosition(420,120);
//        sp->addChild(la,1);
//        sp->setOpacity(0);
//        sp->runAction(FadeIn::create(0.1));
        
        std::string name;
        std::string say;
        auto it=first.begin();
        for (; *it!='*'; it++) {
            if (*it!='\n') {
                 name+=*it;
            }
        }
        it++;
        for(;it!=first.end();it++){
                say+=*it;
        }
                Label*la=Label::create(say, "Arial", 20);
                la->setColor(Color3B(255, 0, 0));
                la->setPosition(420,120);
                sp->addChild(la,1);
                sp->setOpacity(0);
                sp->runAction(FadeIn::create(0.1));
        
        
        
         _name=name;
        std::string player_filename;
        player_filename=name+".png";
        CCLOG("name:%s",name.c_str());
        CCLOG("say:%s",say.c_str());
        
        Sprite*my=Sprite::create(player_filename.c_str());
        my->setPosition(760,100);
        this->addChild(my);
        
        
        
        
        
                re_page++;
    };
    
    listener->setSwallowTouches(true);
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,-12);
   // listener->setFixedPriority(-10);
    
    return true;
}
    
    





Talking_Rush*Talking_Rush:: create(std::vector<std::string>talk,char*player_filename,char*npc_filename,int n)
{
    Talking_Rush *pRet = new(std::nothrow) Talking_Rush();
    if (pRet && pRet->init(talk,player_filename,npc_filename,n))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool Talking_Rush::init(std::vector<std::string>talk,char*player_filename,char*npc_filename,int n)
{
    if (!Layer::init()) {
        return false;
    }
    count_page=talk.size();
    re_page=0;
    over=false;
 
    auto touch=Sprite::create();
    Animation*animation=Animation::create();
    animation->addSpriteFrameWithFile("36-18.png");
    animation->addSpriteFrameWithFile("36-19.png");
    animation->setDelayPerUnit(0.5);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);
    Animate*ani=Animate::create(animation);
    touch->runAction(ani);
    touch->setPosition(480,320);
    this->addChild(touch,1);
    

    
    
    
    
    
    auto listener=EventListenerTouchOneByOne::create();
 
    listener->onTouchBegan=[=](Touch*touch,Event*event){
          SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
      
        if (re_page==count_page) {
            over=true;
            
            _eventDispatcher->removeEventListener(listener);
            
            return false;
        }
        return true;
    };
    

    
    listener->onTouchEnded=[=](Touch*touch,Event*event){
         this->removeAllChildren();
        CCLOG("page:%d,coun_page:%d",re_page,count_page);
        if (n==2) {
        if (re_page%n==0) {
            Sprite*sp=Sprite::create("talk.png");
            sp->setPosition(560,100);
            this->addChild(sp);
            
            Sprite*my=Sprite::create(player_filename);
            my->setPosition(160,100);
            this->addChild(my);
            
            std::string first=talk.at(re_page);
            CCLOG("%s",first.c_str());
            Label*la=Label::create(first, "Arial", 20);
            la->setColor(Color3B(255, 0, 0));
            la->setPosition(300,100);
            sp->addChild(la,1);
            sp->setOpacity(0);
            sp->runAction(FadeIn::create(0.1));
        }

        
       else if (re_page%n==1) {
           Sprite*sp=Sprite::create("talk.png");
           sp->setPosition(400,540);
           sp->setFlippedX(true);
           this->addChild(sp);
           
           Sprite*npc=Sprite::create(npc_filename);
           npc->setPosition(800,540);
           this->addChild(npc);
           
           std::string first=talk.at(re_page);
           Label*la=Label::create(first, "Arial", 20);
           la->setColor(Color3B(255, 0, 0));
           la->setPosition(300,100);
           sp->addChild(la,1);
           sp->setOpacity(0);
           sp->runAction(FadeIn::create(0.1));
        }
        }
        else if(n==1){
            Sprite*sp=Sprite::create("10.1.png");
            sp->setPosition(480,420);
            sp->setScaleY(0.8);
            this->addChild(sp);
            std::string first=talk.at(re_page);
            Label*la=Label::create(first, "Helvetica", 30);
            la->enableShadow(Color4B(255,0,0,255),Size(1,0));
            la->setColor(Color3B(0,20,0));
            la->setPosition(sp->getContentSize().width/2,sp->getContentSize().height/2+30);
            sp->addChild(la,1);
            sp->setOpacity(0);
            sp->runAction(FadeIn::create(0.1));
        }
           re_page++;
    };
  
    listener->setSwallowTouches(true);
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,-12);
    
    
    return true;
}
