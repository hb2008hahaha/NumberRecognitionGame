#ifndef CGRIDNUMS_H
#define CGRIDNUMS_H
////��������
#define BlockNums 10 //������32
#define ColNum 5 //ÿ��5������
#include "global.h"
class CGridNums{
public:
    CGridNums()
    {
      #ifdef QImage
        ImgBlock.load("://res/pig.png");
       #endif
    }

 int Nums;
 char BlockFlag[BlockNums];
 void InitGame()
 {
     int TmpNum=(2<<BlockNums)-1;
     int Value=rand()%(TmpNum-1)+1;
     for(int i=0;i<BlockNums;i++)
         BlockFlag[i]=(Value&1<<i)!=0;
        Nums=0;
     for(int i=0;i<BlockNums;i++)
     {
         Nums+= BlockFlag[i];
     }
 }
 void DrawBoard(QPainter *painter)
 {
     for(int i=0;i<BlockNums;i++)
        DrawBlock(painter,i);
 }



private:
#ifdef QTImage
  QPixmap ImgBlock;
#endif

 void DrawBlock(QPainter *painter,int pos)     //
 {
   if(pos<0||pos>=BlockNums)return ;
  int x=pos%ColNum;
  int y=pos/ColNum;
  int m=x*BlockSize+1+LocX;	 //����任
  int n=y*BlockSize+1+LocY;
 #ifdef QTImage
  if(ImgBlock.isNull()!=true)
  {
      if(BlockFlag[pos]!=0)painter->drawPixmap(m,n,BlockSize,BlockSize,ImgBlock);
  }
  else
  {
      QColor penColor = Qt::green;
       penColor.setAlpha(80);//����ɫ��͸���ȼ�С��ʹ����߽�����ɫֱ�������ֿ�
      if(BlockFlag[pos]==0)//�����ѡ�еĻ����ɫ
         painter->setBrush(Qt::NoBrush);
      else
          painter->setBrush(Qt::blue);
      painter->setPen(penColor);//ɫ���ƻ���
      painter->drawRect(m,n,BlockSize-1,BlockSize-1);//�����������Ϊ���Ͻ����꣬������
  }
 #else
    QColor penColor = Qt::green;
    //penColor.setAlpha(80);//����ɫ��͸���ȼ�С��ʹ����߽�����ɫֱ�������ֿ�
    if(BlockFlag[pos]==0)//�����ѡ�еĻ����ɫ
       painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(Qt::blue);
    painter->setPen(penColor);//ɫ���ƻ���
    painter->drawRect(m,n,BlockSize-1,BlockSize-1);//�����������Ϊ���Ͻ����꣬������
 #endif
 }


};
#endif // CGRIDNUMS_H
