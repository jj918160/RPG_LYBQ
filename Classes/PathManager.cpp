//
//  PathManager.cpp
//  RPG_LYBQ
//
//  Created by mac on 16-3-30.
//
//

#include "PathManager.h"
#include "SLGMapView.h"
#include <iostream>
USING_NS_CC;
PathManager*PathManager::create(SLGMapView*map)
{
    PathManager *pRet = new(std::nothrow) PathManager();
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

bool PathManager::init(SLGMapView*map){
    if(!Node::init())
    {
        return false;
    }
    this->map=map;
    Vec2 tilesize = map->_movecost->getLayerSize();
    this->intSize=tilesize;
    for(int i=0;i<tilesize.y;i++){
        std::vector<int> temp ;
        for (int j=0; j<tilesize.x; j++) {
            int gid = map->_movecost->getTileGIDAt(Vec2(j,i));
            Value vv = map->_tileMap->getPropertiesForGID(gid);
            if(vv.isNull()){
                temp.push_back(1);
            }
            else{
            ValueMap vp=vv.asValueMap();
            auto cost = vp.at("MoveCost").asInt();
            temp.push_back(cost);
            }
            
            
        }
        this->vecOfmoveCost.push_back(temp);
    }
//    auto gid = Gird::create(1, 4);
//    findRange(gid,7);
//    auto gid2=getGirdByXY(1, 4);
//    auto p = getPathWay(gid,gid2);
//    CCLOG("p:%zd",p.size());
    return true;
}
Gird*PathManager::getGirdByXY(int x,int y){
    return this->canMove.at(y).at(x);
}
void PathManager::findRange(Gird*orige,int range,std::vector<cocos2d::Vec2>attackPoint){
    for(int i=0;i<canMove.size();i++){
        canMove.at(i).clear();
    }
    this->canMove.clear();
    for(int i=0;i<this->intSize.y;i++){
        Vector<Gird*> temp ;
        for (int j=0; j<this->intSize.x; j++) {
            auto gid = Gird::create(j,i);
            temp.pushBack(gid);
        }
        this->canMove.push_back(temp);
    }
    auto gid=getGirdByXY(orige->getX(), orige->getY());
    checkFour(gid,range);
    drawRange(attackPoint,orige->getX(),orige->getY());
    show();

   // int k = this->vecOfmoveCost[y][x];
    
}
//void PathManager::checkFour(Gird*p,int costeLess){
//    //用♻️
//    //left
//    int x = p->getX();
//    int y = p->getY();
//    if(x>0){
//        if(costeLess>=this->vecOfmoveCost[y][x-1]&&!this->canMove[y][x-1]->getPass()){
//            //CCLOG("in");
//            this->canMove[y][x-1]->setPass(true);
//            this->canMove[y][x-1]->parent=p;
//            int temp = costeLess-this->vecOfmoveCost[y][x-1];
//            this->checkFour(canMove[y][x-1], temp);
//        }
//    }
//    //right
//    if(x<this->intSize.x-1){
//        if(costeLess>=this->vecOfmoveCost[y][x+1]&&!this->canMove[y][x+1]->getPass()){
//            this->canMove[y][x+1]->setPass(true);
//            this->canMove[y][x+1]->parent=p;
//            int temp = costeLess-this->vecOfmoveCost[y][x+1];
//            this->checkFour(canMove[y][x+1], temp);
//        }
//    }
//    //top
//    if(y>0){
//        if(costeLess>=this->vecOfmoveCost[y-1][x]&&!canMove[y-1][x]->getPass()){
//            this->canMove[y-1][x]->setPass(true);
//            this->canMove[y-1][x]->parent=p;
//            int temp = costeLess-this->vecOfmoveCost[y-1][x];
//            this->checkFour(canMove[y-1][x], temp);
//        }
//    }
//    //down
//    if(y<this->intSize.y-1){
//        if(costeLess>=this->vecOfmoveCost[y+1][x]&&!canMove[y+1][x]->getPass()){
//            this->canMove[y+1][x]->setPass(true);
//            this->canMove[y+1][x]->parent=p;
//            int temp = costeLess-this->vecOfmoveCost[y+1][x];
//            this->checkFour(canMove[y+1][x], temp);
//        }
//    }
//}
void PathManager::checkFour(Gird*p,int costeLess){
    //循环  广度遍历
  
    Vector<Gird*>quene;
    p->setValue(costeLess);
    p->setPass(true);
    quene.pushBack(p);
 //   int x = p->getX();
  //  int y = p->getY();
    while (quene.size()>0) {
        auto obj = quene.front();
       int x=obj->getX();
       int y=obj->getY();
        costeLess=obj->getValue();
        if(x>0&&costeLess>=this->vecOfmoveCost[y].at(x-1)&&!this->canMove[y].at(x-1)->getPass())
        {
            this->canMove[y].at(x-1)->setPass(true);
            this->canMove[y].at(x-1)->parent=obj;
            this->canMove[y].at(x-1)->setValue(obj->getValue()-this->vecOfmoveCost[y][x-1]);
            quene.pushBack(this->canMove[y].at(x-1));
            
        }
        if(x<this->intSize.x-1&&costeLess>=this->vecOfmoveCost[y][x+1]&&!this->canMove[y].at(x+1)->getPass())
        {
            this->canMove[y].at(x+1)->setPass(true);
            this->canMove[y].at(x+1)->parent=obj;
            this->canMove[y].at(x+1)->setValue(obj->getValue()-this->vecOfmoveCost[y][x+1]);
            quene.pushBack(this->canMove[y].at(x+1));
            
        }
        if(y>0&&costeLess>=this->vecOfmoveCost[y-1][x]&&!canMove[y-1].at(x)->getPass())
        {
            this->canMove[y-1].at(x)->setPass(true);
            this->canMove[y-1].at(x)->parent=obj;
            this->canMove[y-1].at(x)->setValue(obj->getValue()-this->vecOfmoveCost[y-1][x]);
            quene.pushBack(this->canMove[y-1].at(x));
            
        }

        if(y<this->intSize.y-1&&costeLess>=this->vecOfmoveCost[y+1][x]&&!canMove[y+1].at(x)->getPass())
        {
            this->canMove[y+1].at(x)->setPass(true);
            this->canMove[y+1].at(x)->parent=obj;
            this->canMove[y+1].at(x)->setValue(obj->getValue()-this->vecOfmoveCost[y+1][x]);
            quene.pushBack(this->canMove[y+1].at(x));
        }
        quene.eraseObject(obj);
        //CCLOG("Qsize:%zd",quene.size());
    }
}

void PathManager::show(){
    for(int i=0;i<this->intSize.y;i++){
        for (int j=0; j<this->intSize.x; j++) {
            std::cout<<this->canMove[i].at(j)->getValue()<<" ";
        }
     std::cout<<" "<<std::endl;
    }
}
void PathManager::removeAllRange(){
    CCLOG("Gsize:%zd",GirdSprites.size());
    if(GirdSprites.empty())
        return;
    for (auto temp : GirdSprites){
        temp->removeFromParent();
    }
    GirdSprites.clear();
}

void PathManager::drawRange(std::vector<cocos2d::Vec2>vec,int x,int y){
    removeAllRange();
    for(int i=0;i<this->intSize.y;i++){
        for (int j=0; j<this->intSize.x; j++) {
            if(this->canMove[i].at(j)->getPass())
            {
                int py=this->intSize.y-i;
                auto sp = Sprite::create("TileMap/tileBlue.png");
                sp->setOpacity(100);
                sp->setPosition(j*PERTILEWIDTH+32,py*PERTILEHEIGHT-32);
                map->_tileMap->addChild(sp);
                GirdSprites.pushBack(sp);
               // CCLOG("x:%d,y:%d",j,i);
               // CCLOG("GSsize:%zd",GirdSprites.size());
            }
            
        }
    }
    drawAttackRange(vec,x, y);
}
void PathManager::drawAttackRange(std::vector<cocos2d::Vec2>vec,int x,int y){
    for (auto temp:vec) {
        int py=this->intSize.y-(temp.y+y);
        int px=temp.x+x;
        auto sp = Sprite::create("TileMap/tileRed.png");
        sp->setColor(Color3B::RED);
        sp->setOpacity(100);
        sp->setPosition(px*PERTILEWIDTH+32,py*PERTILEHEIGHT-32);
        map->_tileMap->addChild(sp);
        GirdSprites.pushBack(sp);
    }
}
std::vector<cocos2d::Vec2> PathManager::getPathWay(int startX, int startY,int endX,int endY){
    std::vector<cocos2d::Vec2>vec;
    CCLOG("size:%zd",canMove.size());
     //CCLOG("endpass%d====startvalue%d",getGirdByXY(startX,startY)->getPass(),getGirdByXY(startX,startY)->getValue());
    auto start=getGirdByXY(startX,startY);
    auto end = getGirdByXY(endX,endY);
    //CCLOG("endvalue%d====startvalue%d",end->getValue(),start->getValue());
    if(start->getValue()==end->getValue()){
        CCLOG("same");
        return vec;
    }
    if(!end->getPass())
    {
        CCLOG("false");
        return vec;
    }
    auto temp = end;
    while (temp->parent) {
        int x = temp->getX();
        int y = temp->getY();
        vec.push_back(this->map->tileCoordToPosition(Vec2(x,y))+Vec2(this->map->_tileMap->getTileSize()/2));
        CCLOG("x:%d,y:%d",temp->getX(),temp->getY());
        temp=temp->parent;
    }
    int x = temp->getX();
    int y = temp->getY();
    vec.push_back(this->map->tileCoordToPosition(Vec2(x,y))+Vec2(this->map->_tileMap->getTileSize()/2));
    CCLOG("x:%d,y:%d",temp->getX(),temp->getY());
    CCLOG("findover");
    return vec;
}



