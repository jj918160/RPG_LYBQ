//
//  Animation_itools.cpp
//  animate_homework
//
//  Created by mac on 15-7-15.
//
//

#include "Animation_itools.h"
#include <map>
using namespace std;
Animation* Animation_itools::makeAnimationfromPlist(std::string plist_filename,const char* pictrue_filename,int num,int min,float speed,bool Original,int Loop){
    
    //获取精灵桢缓存实例，并添加桢缓存
    SpriteFrameCache*sfc=SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile(plist_filename);
    //将plist文件中需要的图片从缓存中放入一个数组
      Animation*animation=Animation::create();
          for (int i=min;i<=num; i++) {
        char name[64]={0};
        sprintf(name,pictrue_filename,i);
        SpriteFrame*sf=sfc->spriteFrameByName(name);
         animation->addSpriteFrame(sf);
    }
    animation->setDelayPerUnit(speed);
    animation->setRestoreOriginalFrame(Original);
    animation->setLoops(Loop);
    return animation;
}

//为了符合坐标系的规范，x轴向右增大表示列，y轴向上增大表示行
Animation* Animation_itools::makeAnimationfrommixpicture(std::string filename,int x,int y,int x_begin,int y_begin,int x_end,int y_end,float speed,bool Original,int Loop){
    //获取整张2D图片的纹理
    //x-列，y-行
    Texture2D*texture=TextureCache::getInstance()->addImage(filename);
    float eatch_width=texture->getContentSize().width/x;
    float eatch_height=texture->getContentSize().height/y;
  
      Animation*animation=Animation::create();
    //比如第一排：x=4*y=4:（x_begin=1，y_begin=4）-（x_end=4，y_end=4）
   //  for (int j=x_begin;j<=x_end;j++) {
    for (int i=y_begin;i<=y_end;i++) {
        for (int j=x_begin;j<=x;j++) {
           // x1列,y1行,2列,4行,
              animation->addSpriteFrameWithTexture(texture,Rect((j-1)*eatch_width,(i-1)*eatch_height,eatch_width, eatch_height));
            if (i==y_end&&j==x_end) {
                break;
            }
            

        }
    }
    
    animation->setDelayPerUnit(speed);
    animation->setRestoreOriginalFrame(Original);
    animation->setLoops(Loop);
    return animation;
   
    
    
}
Animation* Animation_itools::makeAnimationfromVector(std::vector<std::string> vec_of_pictrue,float speed,bool oringe,int Loop){
     Animation*animation=Animation::create();
    auto it=vec_of_pictrue.begin();

    for (;it!=vec_of_pictrue.end(); it++) {
            animation->addSpriteFrameWithFile(*it);
    }

    animation->setDelayPerUnit(speed);
    animation->setRestoreOriginalFrame(oringe);
    animation->setLoops(Loop);
    return animation;
}



 std::vector<std::string> Animation_itools::load_mssage(const char *txtfilename,std::vector<std::string> obj){
     unsigned long bufferSize=0;
     unsigned char* p=NULL;
     
     std::string fullpath=FileUtils::getInstance()->fullPathForFilename(txtfilename);
     auto data=FileUtils::getInstance()->getDataFromFile(fullpath.c_str());
     p=data.getBytes();
     std::string temp;
     int i=0;
    while (p[i]!='$') {
        
    if (p[i]!='@') {
        temp+=p[i];
    }
    else{
     obj.push_back(temp);
     temp.clear();
    }
        i++;
     }
  
      //        fclose(fp);//关闭文件
     return obj;
}




void Animation_itools::cutPicturewithframe(std::string cutfilename,int hang,int lie,char* nameyouwant){
    Texture2D*texture=TextureCache::getInstance()->addImage(cutfilename);
    float eatch_width=texture->getContentSize().width/lie;
    float eatch_height=texture->getContentSize().height/hang;
    for (int i=1; i<=hang; i++) {
        for (int j=1; j<=lie;j++) {
          //  CCLOG("num:%d,",((i-1)*lie+j));
            SpriteFrame*sf=SpriteFrame::createWithTexture(texture,Rect((j-1)*eatch_width,(i-1)*eatch_height,eatch_width, eatch_height));
            char name[64]={0};
            int num=(i-1)*lie+j;
            sprintf(name,nameyouwant,num);
            SpriteFrameCache::getInstance()->addSpriteFrame(sf,name);
        }
    }
}

