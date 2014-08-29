#ifndef CTARGET_H
#define CTARGET_H
#include "global.h"
typedef struct _Point{
int x;
int y;
}
Point;
//功能：用于描述打击的目标的类
class CTarget{
private:
#ifdef QTImage
        QPixmap ImgTarget;//目标的背景图片
#endif
   int x;
   int y;
public :
   char IsAlive;//存活标志，1表示存活
    int value;//目标上的数值
   CTarget(){
       IsAlive=1;
       #ifdef QTImage
        ImgTarget.load("://res/target.png");
      #endif
   }
   //功能：设置目标的位置
   //输入:点坐标
   void SetPos(int x,int y)
   {
       this->x=x;
       this->y=y;

   }
   //功能：判断是否击中目标
   //输入：球的当前坐标
   //返回1表示击中
   char IsHit(Point pt)
   {

       if(abs(pt.x-x)<MaxHitDis&&abs(pt.y-y)<MaxHitDis)
       {
        IsAlive=0;
        return 1;
       }
       return 0;
   }
   //绘制
   void Draw(QPainter *painter)
   {
       if(IsAlive==0)return;
    #ifdef QTImage
       if(ImgTarget.isNull()!=true)
       painter->drawPixmap(x-TarSize/2,y-TarSize/2,TarSize,TarSize,ImgTarget);
       else
       painter->drawEllipse(x-TarSize/2,y-TarSize/2,TarSize,TarSize);
    #else
       painter->setPen(Qt::blue);
       painter->setBrush(Qt::green);
      painter->drawEllipse(x-TarSize/2,y-TarSize/2,TarSize,TarSize);
    #endif

      QFont qfont("Times",18);
      painter->setFont(qfont);
       painter->drawText(QRect(x-TarSize/4,y-TarSize/2+3,TarSize,TarSize),QString::number(value));

   }
};
#endif // CTARGET_H
