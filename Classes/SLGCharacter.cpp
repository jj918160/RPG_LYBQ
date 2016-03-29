//
//  SLGCharacter.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#include "SLGCharacter.h"
#include "Animation_itools.h"


SLGCharacter*SLGCharacter::create(const std::string filename,SLGMapView*map)
{
    SLGCharacter *pRet = new(std::nothrow) SLGCharacter();
    if (pRet && pRet->init(filename,map))
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

bool SLGCharacter::init(const std::string filename,SLGMapView*map){
    if (!Sprite::init()) {
        return false;
    }
    this->map=map;
    this->imageSource=filename;
    loading_animation();
    
    return true;
}



void SLGCharacter::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture(imageSource+"_move.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,imageSource+"godown");
    Animation*goleft=itool->makeAnimationfrommixpicture(imageSource+"_move.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,imageSource+"goleft");
    Animation*goright=itool->makeAnimationfrommixpicture(imageSource+"_move.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,imageSource+"goright");
    Animation*goup=itool->makeAnimationfrommixpicture(imageSource+"_move.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,imageSource+"goup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture(imageSource+"_attack.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,imageSource+"Adown");
    Animation*attackleft=itool->makeAnimationfrommixpicture(imageSource+"_attack.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,imageSource+"Aleft");
    Animation*attackright=itool->makeAnimationfrommixpicture(imageSource+"_attack.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,imageSource+"Aright");
    Animation*attackup=itool->makeAnimationfrommixpicture(imageSource+"_attack.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,imageSource+"Aup");
    
    Animation*diedown=itool->makeAnimationfrommixpicture(imageSource+"_die.png",3,4,1,1,3,1,0.2f,true,1);
    ac->addAnimation(diedown,imageSource+"diedown");
    Animation*dieft=itool->makeAnimationfrommixpicture(imageSource+"_die.png",3,4,1,2,3,2,0.2f,true,1);
    ac->addAnimation(dieft,imageSource+"dieleft");
    Animation*dieright=itool->makeAnimationfrommixpicture(imageSource+"_die.png",3,4,1,3,3,3,0.2f,true,1);
    ac->addAnimation(dieright,imageSource+"dieright");
    Animation*dieup=itool->makeAnimationfrommixpicture(imageSource+"_die.png",3,4,1,4,3,4,0.2f,true,1);
    ac->addAnimation(dieup,imageSource+"dieup");
}
std::string SLGCharacter::enumToString(SLGCharacter::Direction direction){
    switch (direction) {
        case SLGCharacter::Direction::left:
            return "left";
         
        case SLGCharacter::Direction::right:
            return "right";
          
        case SLGCharacter::Direction::up:
            return "up";
      
        case SLGCharacter::Direction::down:
            return "down";
       
    }
}

void SLGCharacter::walk(SLGCharacter::Direction direction){
    AnimationCache* ac=AnimationCache::getInstance();
    std::string godirection =imageSource+"go"+enumToString(direction);
    Animation *a=ac->getAnimation(godirection);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void SLGCharacter::attack(SLGCharacter::Direction direction){
    AnimationCache* ac=AnimationCache::getInstance();
    std::string Adirection =imageSource+"A"+enumToString(direction);
    Animation *a=ac->getAnimation(Adirection);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void SLGCharacter::dieAnimation(SLGCharacter::Direction direction){
    AnimationCache* ac=AnimationCache::getInstance();
    std::string diedirection =imageSource+"die"+enumToString(direction);
    Animation *a=ac->getAnimation(diedirection);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
