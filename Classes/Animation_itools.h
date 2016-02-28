//
//  Animation_itools.h
//  animate_homework
//
//  Created by mac on 15-7-15.
//
//

#ifndef __animate_homework__Animation_itools__
#define __animate_homework__Animation_itools__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Animation_itools:public Ref{
public:
    Animation* makeAnimationfromPlist(std::string plist_filename,const char* pictrue_filename,int num,int min=0,float speed=0.1f,bool oringe=true,int Loop=-1);
    
    //参数说明，文件名，图片有的列数，图片的行数，（开始的列数，开始的行数）,（终止的列数，终止的行数）,桢率,回到第一桢，动画次数
    //比如从3行1列开始到3行5列结束，传（1，3）（5，3）
    Animation* makeAnimationfrommixpicture(std::string filename,int lie,int hang,int lie_begin,int hang_begin,int lie_end,int hang_end,float speed=0.1f,bool Original=true,int Loop=-1);
    
    
    Animation* makeAnimationfromVector(std::vector<std::string> vec_of_pictrue,float speed=0.1f,bool oringe=true,int Loop=-1);
    
    //自己写的从txt文件读取信息函数
    std::vector<std::string> load_mssage(const char *txtfilename,std::vector<std::string> obj);
    //分解规则图片获取精灵帧
    void cutPicturewithframe(std::string cutfilename,int hang,int lie,char* nameyouwant);
   
};

#endif /* defined(__animate_homework__Animation_itools__) */
