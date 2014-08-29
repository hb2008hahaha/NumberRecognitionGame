#ifndef CTARGET_H
#define CTARGET_H
#include "global.h"
typedef struct _Point{
int x;
int y;
}
Point;
//���ܣ��������������Ŀ�����
class CTarget{
private:
#ifdef QTImage
        QPixmap ImgTarget;//Ŀ��ı���ͼƬ
#endif
   int x;
   int y;
public :
   char IsAlive;//����־��1��ʾ���
    int value;//Ŀ���ϵ���ֵ
   CTarget(){
       IsAlive=1;
       #ifdef QTImage
        ImgTarget.load("://res/target.png");
      #endif
   }
   //���ܣ�����Ŀ���λ��
   //����:������
   void SetPos(int x,int y)
   {
       this->x=x;
       this->y=y;

   }
   //���ܣ��ж��Ƿ����Ŀ��
   //���룺��ĵ�ǰ����
   //����1��ʾ����
   char IsHit(Point pt)
   {

       if(abs(pt.x-x)<MaxHitDis&&abs(pt.y-y)<MaxHitDis)
       {
        IsAlive=0;
        return 1;
       }
       return 0;
   }
   //����
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
