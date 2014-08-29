#include "cballhit.h"

CBallHit::CBallHit()
{

    DownFlag=0;
    BallPos.x=150;
    BallPos.y=Hei-Hei/4;
    LastPt=BallPos;
    SupportPos=BallPos;

    InitGame();

#ifdef QTImage

     ImgBackground.load("://res/background2.jpg");
     ImgBall.load("://res/ball.png");
     ImgSupport.load("://res/tree.png");
#endif
}
void CBallHit::MouseDown(int x,int y)
 {
     if((BallPos.x-x)*(BallPos.x-x)+(BallPos.y-y)*(BallPos.y-y)<=BallSize*BallSize)
     {
         DownFlag=1;

     }

 }
 //����1����ʾ��Ҫˢ�½���
 char CBallHit::MouseMove(int x,int y)
 {
     if(DownFlag==1)
     {
        SetBallPos(x,y);
         return 1;
     }
     return 0;
 }
 char CBallHit::MouseUp(int x,int y)
 {

     if(DownFlag==1)
     {
        SetBallPos(x,y);

        CalcMovePara(x,y);
        DownFlag=0;
         return 1;
     }
     DownFlag=0;
     return 0;
 }
 void CBallHit::DrawBoard(QPainter *painter)
 {
#ifdef QTImage
painter->drawPixmap(0,0,ImgBackground);//����ͼƬ������ԭʼ��С
#endif

   DrawSupport(painter);
   DrawTime(painter);
   DrawBall(painter);
     if(DownFlag==1)
     painter->drawLine(SupportPos.x,SupportPos.y,BallPos.x,BallPos.y);
    for(int i=0;i<TarNums;i++)
     {
         cTarget[i].Draw(painter);
     }
    cGridNums.DrawBoard(painter);
 }

 void CBallHit::SetBallPos(int x,int y)
 {
     BallPos.x=x;
     BallPos.y=y;
     LastPt=BallPos;
 }
 //����0����������1����ʾ����Խ�磬������ֹ��ʱ������
 //2 means not right;3 means right
 char CBallHit::TimerServer()
 {
     GetNextBallPos();
     //qDebug()<<QString::number(DrawPos.x)<<","<<QString::number(DrawPos.y)<<endl;
     if(LastPt.y>Hei||LastPt.y<0||LastPt.x<0 ||LastPt.x>Wid  )
       BallRebound();
     //if(LastPt.y>Hei  ||LastPt.x<0 ||LastPt.x>Wid )//�Ƿ�Խ��||LastPt.y<0
      if(LastPt.y>Hei-3 && v<2 )
      {
          SetBallPos(150,Hei-Hei/4);//
         return 1;
     }

     for(int i=0;i<TarNums;i++)//�ж��Ƿ����
     {
         if(cTarget[i].IsAlive==1&&cTarget[i].IsHit(LastPt))
         {
             if(cGridNums.Nums!=cTarget[i].value)
             {
                 SetBallPos(150,Hei-Hei/4);
                 return 2;
             }
             else
             {
                 SetBallPos(150,Hei-Hei/4);
                 InitGame();//���³�ʼ����Ϸ
                 return 3;
             }

         }
             //HittedBallValue=cTarget[i].value;
     }
     return 0;

 }
 void CBallHit::SetResultItem()
 {
    int RightResult=cGridNums.Nums;
     int TmpValue;
     for(int i=0;i<TarNums;i++)
     {
         do{
             TmpValue=rand()%BlockNums;
             if(RightResult!=TmpValue)
             {
                cTarget[i].value=TmpValue;
                break;
             }
         }
         while(1);

     }
     int RndIndex=rand()%TarNums;
     cTarget[RndIndex].value=RightResult;

 }
 //function:calc ball move parameter:v,alpha
   //input:ball start postion
   void CBallHit::CalcMovePara(int x,int y)
   {
       t=0;
       int dx=SupportPos.x- x;
       int dy=SupportPos.y- y;
        x1=x;
        y1=y;
       float r=sqrt(1.0*dx*dx+dy*dy);
        v=r>20?20:r;
        sin_Alpha=-dy*1.0/r;
        cos_Alpha=dx*1.0/r;
   }
   //function ,the ball hit the bound and change move direction
   //input:the wall direction
   //1 up,2 right,3 down,4 left
   void CBallHit::BallRebound()
   {
       float a=0.3;
       float v_x=v*cos_Alpha;
       float v_y=v*sin_Alpha-a*t;
       float v_=sqrt(1.0*v_x*v_x+v_y*v_y);
       v=v_/2;//
       sin_Alpha=v_y/v_;
       cos_Alpha=v_x/v_;

       t=0;
       if(LastPt.x<0)
       {
           x1=1;
           cos_Alpha=-cos_Alpha;
       }
       else if(LastPt.x>Wid)
       {
           x1=Wid-2;
            cos_Alpha=-cos_Alpha;
       }
       else x1=LastPt.x;

       if(LastPt.y<0)
       {
           y1=1;
           sin_Alpha=-sin_Alpha;
       }
       else if(LastPt.y>Hei)
       {
           y1=Hei-2;
           sin_Alpha=-sin_Alpha;
       }
       else y1=LastPt.y;


   }

//���ܣ����³�ʼ����Ϸ
   void CBallHit::InitGame()
   {
       UsedSeconds=0;
       srand(clock());//��ʼ�������
       for(int i=0;i<TarNums;i++)
          {
           cTarget[i].IsAlive=1;
           cTarget[i].SetPos(500+rand()%100,Hei/TarNums*i+50);// //����4��Ŀ���λ��
          }
       cGridNums.InitGame();
       SetResultItem();
       //��4������������

   }
   //
     Point CBallHit::GetNextBallPos()
      {

           Point NextPoint;

           float a=0.3;
           NextPoint.x=x1+v*cos_Alpha*t;
           NextPoint.y=y1-(v*sin_Alpha*t-0.5*a*t*t);
           t=t+1;
          // if(t>1000)t=0;
          LastPt=NextPoint;//�����ϴεĵ�����
        return NextPoint;

      }
   //���ܣ���������˶��켣��������һ��ʱ���������
/* Point GetNextBallPos()
{

   int dx=SupportPos.x-BallPos.x;
   int dy=SupportPos.y-BallPos.y;
   int x1=BallPos.x;
   int y1=BallPos.y;
   char sx=dx>0?MovePixel:-MovePixel;
   char sy=dy>0?MovePixel:-MovePixel;

   Point NextPoint;
   if(abs(dy)<abs(dx))
   {
       NextPoint.x=LastPt.x+sx;
       NextPoint.y=(int)(dy*1.0*(NextPoint.x-x1)/dx+y1+0.5);

   }
   else
   {
       NextPoint.y=LastPt.y+sy;
       NextPoint.x=(int)(dx*1.0*(NextPoint.y-y1)/dy+x1+0.5);
   }

   LastPt=NextPoint;//�����ϴεĵ�����
   return NextPoint;
}*/
void CBallHit::DrawTime(QPainter *painter)
{
 int Min=UsedSeconds/60;
 int Sec=UsedSeconds%60;
 QFont qfont("Times",18);
 painter->setFont(qfont);
 painter->drawText(QRect(TimeX,TimeY,80,TarSize),QString("%1:%2").arg(Min).arg(Sec));

}

void CBallHit::DrawSupport(QPainter *painter)
{
#ifdef QTImage
if(ImgSupport.isNull()!=true)
 painter->drawPixmap(SupportPos.x-30,SupportPos.y,60,Hei-SupportPos.y,ImgSupport);//ͼƬ���Զ�ѹ��
else
   painter->drawLine(SupportPos.x,SupportPos.y,SupportPos.x,Hei);

#else
   painter->drawLine(SupportPos.x,SupportPos.y,SupportPos.x,Hei);
#endif
  // painter->drawArc(SupportPos.x-BallSize,SupportPos.y-BallSize,BallSize*2,BallSize*2,180*16,180*16);//qt��1�ȷֳ�16�֣��ʽ��Ƕ�*16
}
void CBallHit::DrawBall(QPainter *painter)
{

#ifdef QTImage
if(ImgBall.isNull()!=true)
painter->drawPixmap(LastPt.x-BallSize/2,LastPt.y-BallSize/2,BallSize,BallSize,ImgBall);
else
painter->drawEllipse(LastPt.x-BallSize/2,LastPt.y-BallSize/2,BallSize,BallSize);
#else
painter->setPen(Qt::blue);
painter->setBrush(Qt::blue);
painter->drawEllipse(LastPt.x-BallSize/2,LastPt.y-BallSize/2,BallSize,BallSize);
#endif

}
