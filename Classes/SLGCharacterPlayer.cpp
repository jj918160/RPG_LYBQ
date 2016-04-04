//
//  SLGCharacterPlayer.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-4-3.
//
//

#include "SLGCharacterPlayer.h"
#include "SLGCharacterManager.h"
#include "PathManager.h"
#include "SLGMapView.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

SLGCharacterPlayer*SLGCharacterPlayer::create(const std::string filename,SLGMapView*map,PathManager*pm)
{
    SLGCharacterPlayer *pRet = new(std::nothrow) SLGCharacterPlayer();
    if (pRet && pRet->init(filename,map,pm))
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

bool SLGCharacterPlayer::init(const std::string filename,SLGMapView*map,PathManager*pm){
    if (!SLGCharacter::init(filename,map,pm)) {
        return false;
    }
    
    return true;
}




void SLGCharacterPlayer::switchAttackTarget(){
    std::vector<Vec2> temp=getAttackRange(_AttakType);
    _pathManager->drawAttackRange(temp, _tilex, _tiley);
    auto sp = Sprite::create("TileMap/tileRed.png");
    sp->setColor(Color3B::BLUE);
    int py = map->size_height/PERTILEHEIGHT-_tiley;
    sp->setPosition(_tilex*PERTILEWIDTH+32,py*PERTILEHEIGHT-32);
    sp->setName("attackBox");
    map->_tileMap->addChild(sp);
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        sp->setPosition(Vec2(PERTILEWIDTH/2,PERTILEHEIGHT/2)+map->tileCoordToPosition(map->tileCoordFromPosition(touch->getLocation())));
        return true;
        
    };
    listener->onTouchMoved=[=](Touch*touch,Event*event){
        sp->setPosition(Vec2(PERTILEWIDTH/2,PERTILEHEIGHT/2)+map->tileCoordToPosition(map->tileCoordFromPosition(touch->getLocation())));
    };
    
    
    listener->onTouchEnded=[=](Touch*touch,Event*event){
        auto pp=map->tileCoordFromPosition(touch->getLocation());
        sp->setPosition(map->tileCoordToPosition(pp)+Vec2(PERTILEWIDTH/2,PERTILEHEIGHT/2));
        //攻击成功 删除
        if(manager->attackView(this,pp)){
             _pathManager->removeAllRange();
            _tilexLastRound=_tilex;
            _tileyLastRound=_tiley;
            this->runAction(Sequence::create(DelayTime::create(attackDuration*2),CallFuncN::create([&](Node* pSender){
                this->CheckMoved(true);
            }),NULL));
            
            this->removeRender();
        }
        //攻击失败
        else{
            this->replacing();
            this->removeRender();

        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,sp);
}
void SLGCharacterPlayer::removeRender(){
    auto temp=this->getParent()->getChildByName("ConmondNode");
    if(temp){
        temp->removeFromParent();
    }
}
void SLGCharacterPlayer::showRender(){
    auto renderNode=CSLoader::createNode("SLGComondNode.csb");
    renderNode->setName("ConmondNode");
    int x=120;
    if(this->_tilex>map->size_width/PERTILEWIDTH-3){
        x=-120;
    }
    renderNode->setPosition(x+this->getPositionX(), PERTILEHEIGHT/2+this->getPositionY());
    this->getParent()->addChild(renderNode,99);

    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        if(manager->selected){
            manager->selected->replacing();
            manager->selected=nullptr;
        }
        
        return true;
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,renderNode);
    
    auto attack = (ImageView*)renderNode->getChildByName("commond1");
    attack->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            renderNode->setVisible(false);
            switchAttackTarget();
            this->manager->selected=nullptr;
            
        }
    });
    
    
    auto daiming = (ImageView*)renderNode->getChildByName("commond2");
    daiming->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        
        if(type==Widget::TouchEventType::ENDED){
            this->CheckMoved(true);
            renderNode->removeFromParent();
            _tilexLastRound=_tilex;
            _tileyLastRound=_tiley;
            this->manager->selected=nullptr;
        }
    });
    
    
    renderNode->getChildByName("commond3")->setVisible(false);
    renderNode->getChildByName("commond4")->setVisible(false);
    
}

void SLGCharacterPlayer::goDestnation(std::vector<Vec2>p){
    auto vecOfAction=initActioninterval(p,_speed);
    auto sqa=Sequence::create(vecOfAction);
    this->runAction(sqa);
    
    this->runAction(Sequence::create(DelayTime::create(sqa->getDuration()),
                                     CallFuncN::create([=](Node* pSender){
        this->showRender();
    }),NULL));

}
bool SLGCharacterPlayer::selectedSelf(Vec2 pot)
{
    if (pot.x==_tilex&&pot.y==_tiley) {
        return true;
    }
    return false;
}
void SLGCharacterPlayer::replacing(){
    this->removeRender();
    _pathManager->removeAllRange();
    removeAttackBox();
    setTilePosition(_tilexLastRound,_tileyLastRound);
    _eventDispatcher->dispatchCustomEvent("MovingEnd");
}
void SLGCharacterPlayer::removeAttackBox(){
    if(map->_tileMap->getChildByName("attackBox"))
        map->_tileMap->getChildByName("attackBox")->removeFromParent();
}
