//
//  FightScene0_1.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#include "FightScene0_1.h"
#include "SLGMapView.h"
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
    
    
    
    return true;
}
