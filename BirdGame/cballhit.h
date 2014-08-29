#ifndef CBALLHIT_H
#define CBALLHIT_H
#include <math.h>
#include <QPainter>
#include <time.h>
#define BallSize 32
#define TarSize 48
#define BlockSize 32
#define LocX 75
#define LocY 100
#define TimeX 375
#define TimeY 13
#define MaxHitDis BallSize
#define Wid 680
#define Hei 480
#define MovePixel 7  //球每次移动的像素
#define TarNums 4  //目标的个数
#include "global.h"
#include "CGridNums.h"
#include "CTarget.h"
class CBallHit
{
public:
    int UsedSeconds;//该局用时，单位为秒
    CBallHit();
    ~CBallHit()
    {

    }
	//功能：鼠标按下的事件处理
	//输入：鼠标的位置坐标
   void MouseDown(int x,int y);
    //功能: 鼠标移动的事件处理
    //返回1，表示需要刷新界面
    char MouseMove(int x,int y);
	//功能：鼠标弹起时的事件处理
	//返回：1表示鼠标弹起有效，定时器启动
    char MouseUp(int x,int y);
	//功能：绘制总游戏面板
    void DrawBoard(QPainter *painter);
	//功能：设置球的位置
    void SetBallPos(int x,int y);
	//功能：定时器事件处理
	//返回：1表示球因撞到边界停止运动，2表示撞到错误的球，3表示正确击中，其他返回0
    char TimerServer();
	//功能：设置选项值
    void SetResultItem();
private:
    char DownFlag;//鼠标按下标志，1表示按下
    CGridNums cGridNums;//数数区对象
    CTarget cTarget[TarNums];//打击的目标对象

    Point SupportPos;//基站点位置
    Point BallPos;//球的当前位置
    //球的运动参数。球发射出去后做抛物运动
	//球运动速度v的参考方向为右上
    int t;//the time ball has flyyed
    float v,sin_Alpha,cos_Alpha;//move speed,direction
    int x1,y1;//ball start position
    Point LastPt; //上一位置球的位置
#ifdef QTImage
        QPixmap ImgBall;//球的图片
        QPixmap ImgBackground;//背景图片
        QPixmap ImgSupport;//球托图片

#endif
     //功能：根据球的发射位置确定球的初始位置、初速度
        //function:calc ball move parameter:v,alpha
        //input:ball start postion
        void CalcMovePara(int x,int y);
	//功能：球撞到边界后处理
  //撞到边界后会反弹，速度方向为对称方向，速度大小减半	
        //function ,the ball hit the bound and change move direction
        void BallRebound();
   //功能；重新初始化游戏
        void InitGame();
	//功能：根据球的初始位置和初速度计算当前球的位置	
    Point GetNextBallPos();
	//功能：绘制游戏用时
    void DrawTime(QPainter *painter);
	//功能：绘制球托 
    void DrawSupport(QPainter *painter);
	//功能：绘制球
    void DrawBall(QPainter *painter);
};

#endif // CBALLHIT_H
