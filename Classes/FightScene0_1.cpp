//
//  FightScene0_1.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#include "FightScene0_1.h"
#include "SLGMapView.h"
#include "PathManager.h"
#include "SLGCharacter.h"

USING_NS_CC;

Scene* FightScene0_1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FightScene0_1::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FightScene0_1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto map = SLGMapView::create("TileMap/map_0_0.tmx");
    this->addChild(map);
    auto pathmanager =  PathManager::create(map);
    pathmanager->retain();
    
    auto c1=SLGCharacter::create("SLGElement/lx", map);
   // Vec2 c1p = map->pointOfmy.at(0);
    c1->setTilePosition(4,5);
   // CCLOG("X:%f,Y:%f",c1->getPositionX(),c1->getPositionY());
    map->addChild(c1);
    c1->setPathManager(pathmanager);
    //c1->drawMovieRange();
    openGo=false;
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        return true;
    };
    
    
    
    listener->onTouchEnded=[=](Touch*touch,Event*event){
        if(c1->getBoundingBox().containsPoint(c1->getParent()->convertToNodeSpace( touch->getLocation()))){
           c1->drawMovieRange();
            
        }
        else{
            auto p = map->convertToNodeSpace(touch->getLocation());
            auto intp=map->tileCoordFromPosition(p);
            
            CCLOG("StartX:%d,StartY:%d,endX:%d,endY:%d",c1->getTileX(),c1->getTileY(),(int)intp.x,(int)intp.y);
            auto temp=pathmanager->getPathWay(c1->getTileX(),c1->getTileY(),(int)intp.x,(int)intp.y);
            
           
            
            //CCLOG("gotWay");
            if(temp.size()>0){
                
                c1->goDestnation(temp);
                pathmanager->removeAllRange();
                c1->setTilePosition((int)intp.x,(int)intp.y,false);
            }
            else
            {
            pathmanager->removeAllRange();
            }
        }
    };
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    
//    auto npc1 =SLGCharacter::create("npc1", map);
//    auto npc2=SLGCharacter::create("npc2", map);
//    auto npc3=SLGCharacter::create("npc3", map);
    
    return true;
}
