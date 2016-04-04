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
#include "SLGCharacterPlayer.h"
#include "SLGCharacterManager.h"

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
    this->map=map;
    auto pathmanager =  PathManager::create(map);
    this->addChild(pathmanager);
    this->pmg=pathmanager;
    auto mg=SLGCharacterManager::create(map);
    this->addChild(mg);
    
    
    auto button = MenuItemFont::create("NextRoud", [=](Ref*target){
        mg->NextRound();
    });
    button->setPosition(-320,300);
    Menu*mn=Menu::create(button,NULL);
    this->addChild(mn);
    
    createPlayerCr("SLGElement/npc1", map->pointOfenemy.at(0),mg);
    createPlayerCr("SLGElement/lx", map->pointOfmy.at(0),mg);
    
    createPlayerCr("SLGElement/npc2", map->pointOfenemy.at(1),mg);
    createPlayerCr("SLGElement/npc3", map->pointOfenemy.at(2),mg);
    

    return true;
}

void FightScene0_1::createPlayerCr(const char*filename,cocos2d::Vec2 point,SLGCharacterManager*sm){
    auto c1=SLGCharacterPlayer::create(filename, this->map,this->pmg);
    c1->setTilePosition(point.x,point.y);
    c1->_tilexLastRound=point.x;
    c1->_tileyLastRound=point.y;
    map->addChild(c1);
    sm->pushBackPlayerCharacter(c1);
    c1->setManager(sm);
}