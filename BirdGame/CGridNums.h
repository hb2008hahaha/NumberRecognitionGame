#ifndef CGRIDNUMS_H
#define CGRIDNUMS_H
////网格数字
#define BlockNums 10 //不超过32
#define ColNum 5 //每列5个方块
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
  int m=x*BlockSize+1+LocX;	 //坐标变换
  int n=y*BlockSize+1+LocY;
 #ifdef QTImage
  if(ImgBlock.isNull()!=true)
  {
      if(BlockFlag[pos]!=0)painter->drawPixmap(m,n,BlockSize,BlockSize,ImgBlock);
  }
  else
  {
      QColor penColor = Qt::green;
       penColor.setAlpha(80);//将颜色的透明度减小，使方框边界和填充色直接能区分开
      if(BlockFlag[pos]==0)//如果被选中的话则变色
         painter->setBrush(Qt::NoBrush);
      else
          painter->setBrush(Qt::blue);
      painter->setPen(penColor);//色绘制画笔
      painter->drawRect(m,n,BlockSize-1,BlockSize-1);//输入参数依次为左上角坐标，长，宽
  }
 #else
    QColor penColor = Qt::green;
    //penColor.setAlpha(80);//将颜色的透明度减小，使方框边界和填充色直接能区分开
    if(BlockFlag[pos]==0)//如果被选中的话则变色
       painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(Qt::blue);
    painter->setPen(penColor);//色绘制画笔
    painter->drawRect(m,n,BlockSize-1,BlockSize-1);//输入参数依次为左上角坐标，长，宽
 #endif
 }


};
#endif // CGRIDNUMS_H
