//
//  SLGCharacterManager.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-4-2.
//
//

#include "SLGCharacterManager.h"
#include "SLGCharacter.h"
#include "SLGMapView.h"
#include "PathManager.h"
#include "SLGCharacterPlayer.h"

SLGCharacterManager*SLGCharacterManager::create(SLGMapView*map)
{
    SLGCharacterManager *pRet = new(std::nothrow) SLGCharacterManager();
    if (pRet && pRet->init(map))
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

bool SLGCharacterManager::init(SLGMapView*map){
    if(!Node::init())
    {
        return false;
    }
    selected=nullptr;
    this->map=map;
    moving=false;
    initTouchFunc();
     _eventDispatcher->addCustomEventListener("MovingEnd",[&](EventCustom*p){
         moving=false;
     });
    return true;
}

bool SLGCharacterManager::attackView(SLGCharacter*attackfrom,Vec2 des){
    auto attrange=attackfrom->getAttackRange(attackfrom->_AttakType);
    auto hurtrange=attackfrom->gethurtRange(attackfrom->_HurtType);
    for (auto target:quene) {
        for (auto attDes:attackfrom->getAttackRange(attackfrom->_AttakType)) {
            //点中，并且在攻击范围内
            if ((target->getTileX()==des.x&&target->getTileY()==des.y)&&(target->getTileX()==attDes.x+attackfrom->getTileX()&&target->getTileY()==attDes.y+attackfrom->getTileY())) {
                attackfrom->attackCharactor(target,true);
                map->removeSwitch();
                return true;
            }
        }
    }
    return false;
}

void SLGCharacterManager::pushBackPlayerCharacter(SLGCharacterPlayer*obj){
    quene.pushBack(obj);
}
void SLGCharacterManager::initTouchFunc(){
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        if(moving){
            CCLOG("Moving");
        return false;
        }
        return true;
    };
    
    
    
    listener->onTouchEnded=[=](Touch*touch,Event*event){
    for(SLGCharacterPlayer* c1:quene){
        
        if(!selected&&c1->getBoundingBox().containsPoint(c1->getParent()->convertToNodeSpace( touch->getLocation()))){
            if(c1->getMoved())
                return;
            CCLOG("if");
            this->selected=c1;
            selected->drawMovieRange();
            canMove=true;
            return;
            
        }
        else{
            CCLOG("else");
            if(!this->selected||moving)
                continue;
            //第二次选择的情况
            auto c1=this->selected;
            auto p = map->convertToNodeSpace(touch->getLocation());
            auto intp=map->tileCoordFromPosition(p);
            //再次选中自己
            if (c1->selectedSelf(intp)) {
                c1->showRender();
                c1->removeSelfRange();
                return;
            }
            //第二次选中其他人
            auto other=selectedOther(intp);
            if(other){
                c1->removeSelfRange();
                selected=other;
                selected->drawMovieRange();
                canMove=true;
                return;
            }
           
            //选中空地
            CCLOG("StartX:%d,StartY:%d,endX:%d,endY:%d",c1->getTileX(),c1->getTileY(),(int)intp.x,(int)intp.y);
            auto temp=c1->getPathManager()->getPathWay(c1->getTileX(),c1->getTileY(),(int)intp.x,(int)intp.y);
           
            
            //移动范围内
            if(temp.size()>0&&canMove){
                moving=true;
                c1->goDestnation(temp);
                c1->removeSelfRange();
                c1->setTilePosition((int)intp.x,(int)intp.y,false);
                
            }
            //移动范围外
            else
            {
                c1->removeSelfRange();
                selected=nullptr;
            }
            
        }
        }
    };
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}

SLGCharacterPlayer* SLGCharacterManager::selectedOther(Vec2 point){
    for(SLGCharacterPlayer* it :quene)
    {
        if(it->getTileX()==point.x&&it->getTileY()==point.y)
            return it;
    }
    return nullptr;
}

void SLGCharacterManager::NextRound(){
    for (auto target:quene) {
        target->CheckMoved(false);
    }
}
