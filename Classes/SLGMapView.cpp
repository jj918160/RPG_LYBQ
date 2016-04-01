//
//  SLGMapView.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#include "SLGMapView.h"
USING_NS_CC;

SLGMapView*SLGMapView::create(const std::string filename)
{
    SLGMapView *pRet = new(std::nothrow) SLGMapView();
    if (pRet && pRet->init(filename))
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

bool SLGMapView::init(const std::string filename){
    if (!Layer::init()) {
        return false;
    }
    
    winsize=Director::getInstance()->getWinSize();

    _tileMap=TMXTiledMap::create(filename);

    
    size_height=_tileMap->getContentSize().height;
    size_width=_tileMap->getContentSize().width;
    
    _tileMap->setAnchorPoint(ccp(0,0));
    _tileMap->setPosition(0,0);
    this->addChild(_tileMap,0);
    this->_movecost=_tileMap->getLayer("movecost");
    //this->_TileX=_tileMap->getTileSize().width;
    //this->_TileY=_tileMap->getTileSize().height;
    
    this->_movecost->setVisible(false);
    
    auto BornPoint=_tileMap->getObjectGroups();
    _ememyNum = BornPoint.at(0)->getProperty("enemyNum").asInt();
    _myNum = BornPoint.at(0)->getProperty("selfNum").asInt();
    auto vec = BornPoint.at(0)->getObjects();
    
    for(auto it = vec.begin();it!=vec.end();it++){
        auto name =it->asValueMap().at("name").asInt();
     if(name>0&&name<100)
     {
         auto x = it->asValueMap().at("x").asFloat();
         auto y = size_height-it->asValueMap().at("y").asFloat();

         pointOfmy.push_back(this->tileCoordFromPosition(Vec2(x,y)));
     }
     else if(name>100){
         auto x = it->asValueMap().at("x").asFloat();
         auto y = size_height-it->asValueMap().at("y").asFloat();
         pointOfenemy.push_back(this->tileCoordFromPosition(Vec2(x,y)));
     }
    }
    return true;
}


Vec2 SLGMapView::tileCoordFromPosition(Vec2 pos){
    CCLOG("pox:%f,%f",pos.x,pos.y);
    int x=pos.x/_tileMap->getTileSize().width;
    //int y =pos.y/_tileMap->getTileSize().height;
    
    int y=((_tileMap->getMapSize().height*_tileMap->getTileSize().height)-pos.y)/_tileMap->getTileSize().height;
    //CCLOG("x:%d,y:%d",x,y);

    return Vec2(x,y);
}
Vec2 SLGMapView::tileCoordToPosition(Vec2 pos){
   auto layer0 =  _tileMap->getLayer("background");
    return layer0->getPositionAt(pos);
}
