#include "crecognums.h"
#include <time.h>
CRecogNums::CRecogNums()
{
    srand(time(NULL));
    MouseDownFlag=0;
    Lastpos=-1;
    InitGame();
#ifdef QTImage

     ImgBackground.load("://res/background1.jpg");
     ImgBlock.load("://res/block.jpg");
#endif
}

//����:���Ϳ�ķ�����������������Ƿ�һ��
char CRecogNums::CheckResult()
{
    int sum=0;
    for(int i=0;i<MaxNum;i++)
    {
        sum+= IsSelected[i];
    }
    if(sum==DispNums)
        return 1;
    else
        return 0;
}

//����1��ʾ��Ҫˢ��UI
char CRecogNums::MouseDown(int x,int y)
 {
    MouseDownFlag=1;
    int X1=(x-LocX1)/BlockSize;
    int Y1=(y-LocY1)/BlockSize;
    if(X1<0||X1>=ColNum||Y1<0||Y1>=MaxNum/ColNum)
    return 0;
    int pos=Y1*ColNum+X1;
    IsSelected[pos]=!IsSelected[pos];
    Lastpos=pos;
    return 1;
 }
char CRecogNums::MouseMove(int x,int y)
 {

    if(MouseDownFlag==0)return 0;
    int X1=(x-LocX1)/BlockSize;
    int Y1=(y-LocY1)/BlockSize;
    if(X1<0||X1>=ColNum||Y1<0||Y1>=MaxNum/ColNum)
    return 0;
    int pos=Y1*ColNum+X1;
    if(Lastpos!=pos)
    {
       Lastpos=pos;
      IsSelected[pos]=!IsSelected[pos];
    }
    return 1;
 }
void CRecogNums::MouseUp(void)
 {
    MouseDownFlag=0;

 }
void CRecogNums::InitGame()
{
    UsedSeconds=0;
    DispNums=rand()%(MaxNum-1)+1;
    SelectedNums=0;
    memset(IsSelected,0,sizeof(IsSelected));

}
void CRecogNums::DrawBoard(QPainter *painter)
{
#ifdef QTImage
painter->drawPixmap(0,0,ImgBackground);//����ͼƬ������ԭʼ��С
#endif
DrawTime(painter);
    for(int i=0;i<MaxNum;i++)
       DrawBlock(painter,i);
    QFont qfont("Times",20);
    painter->setFont(qfont);
     painter->drawText(QRect(LocX1+BlockSize*2,LocY1-BlockSize,BlockSize,BlockSize),QString::number(DispNums));
}

void CRecogNums::DrawTime(QPainter *painter)
{
  int Min=UsedSeconds/60;
  int Sec=UsedSeconds%60;
  QFont qfont("Times",18);
  painter->setFont(qfont);
  painter->drawText(QRect(TimeX1,TimeY1,80,48),QString("%1:%2").arg(Min).arg(Sec));

}
//����:
void CRecogNums::DrawBlock(QPainter *painter,int pos)     //
{
if(pos<0||pos>=MaxNum)return ;
int x=pos%ColNum;
int y=pos/ColNum;
int m=x*BlockSize+1+LocX1;	 //����任
int n=y*BlockSize+1+LocY1;

QColor penColor = Qt::green;
//penColor.setAlpha(80);//����ɫ��͸���ȼ�С��ʹ����߽�����ɫֱ�������ֿ�
if(IsSelected[pos]==0)//�����ѡ�еĻ����ɫ
  painter->setBrush(Qt::NoBrush);
else
   painter->setBrush(Qt::blue);
painter->setPen(penColor);//ɫ���ƻ���
painter->drawRect(m,n,BlockSize-1,BlockSize-1);//�����������Ϊ���Ͻ����꣬������

#ifdef QTImage
if(IsSelected[pos]!=0)painter->drawPixmap(m,n,BlockSize,BlockSize,ImgBlock);
#endif
}
