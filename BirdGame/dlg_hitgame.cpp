#include "dlg_hitgame.h"
#include "ui_dlg_hitgame.h"
#include <QPainter>
#include <QMouseEvent>

#if QT_VERSION >=0x050000
#include <QMessageBox>
#endif
Dlg_HitGame::Dlg_HitGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_HitGame)
{
  //this->setAttribute(Qt::WA_DeleteOnClose,true);
    timer=NULL;
    ui->setupUi(this);
    TimerInit();

    //更改按钮背景颜色
    ui->Btn_ReturnToMain->setAutoFillBackground(true);
    ui->Btn_ReturnToMain->setFlat(true);
    QPalette palette = ui->Btn_ReturnToMain->palette();
    palette.setColor(QPalette::Active,QPalette::Button,QColor(255,255,255,0));
    ui->Btn_ReturnToMain->setPalette(palette);

    //更改按钮背景颜色
    ui->Btn_Help->setAutoFillBackground(true);
    ui->Btn_Help->setFlat(true);
   // QPalette palette = ui->Btn_Game2->palette();
    palette.setColor(QPalette::Active,QPalette::Button,QColor(255,255,255,0));
    ui->Btn_Help->setPalette(palette);
#if QTSound==400
    c_Voice.Init(this);
#endif

}

Dlg_HitGame::~Dlg_HitGame()
{
    if(timer!=NULL)delete timer;
    if(timer_cnt!=NULL)delete timer_cnt;

     delete ui;
}

void Dlg_HitGame::on_Btn_ReturnToMain_clicked()
{
    this->close();
}
//功能：处理窗口重绘消息.QT只能在此时间中绘图
void Dlg_HitGame::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
   //painter.drawEllipse(DrawPos.x,DrawPos.y,15,15);
    cBall.DrawBoard(&painter);
    QWidget::paintEvent(event);
}

void Dlg_HitGame::mousePressEvent(QMouseEvent *event)
{

     if(event->button() == Qt::LeftButton )//
    {
         cBall.MouseDown(event->x(),event->y());

     }
}
void Dlg_HitGame::mouseMoveEvent(QMouseEvent  *event )//鼠标移动
{

        if(cBall.MouseMove(event->x(),event->y()))
          {

            update();//update(0,0,Wid,Hei);//需要刷新的窗口范围
        #if QTSound==400
            c_Voice.OpenFile("://res/pull.wav");
            c_Voice.Play();
        #endif
            }

}

void Dlg_HitGame::mouseReleaseEvent( QMouseEvent  * event)//鼠标弹起
{
    if(event->button() == Qt::LeftButton )//
   {
#if QTSound==400
   c_Voice.OpenFile("://res/beat.wav");
   c_Voice.Play();
#endif
        if(cBall.MouseUp(event->x(),event->y()))
            timer->start(20);//需要刷新的窗口范围
    }

}

//功能：定时器初始化
void Dlg_HitGame::TimerInit(void)
{
    if(timer==NULL){
    timer = new QTimer(this);//定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerServer()));
    }

        timer_cnt = new QTimer(this);
        connect(timer_cnt, SIGNAL(timeout()), this, SLOT(TimerCnt()));
        timer_cnt->start(1000);//计时定时器启动


}

//功能：处理定时器消息
void Dlg_HitGame::TimerServer() //
{
  int ret=cBall.TimerServer();
  if(ret>0)timer->stop();//终止定时器，球停止运动

        if(ret==3){//成功击中
#if QTSound==400

            c_Voice.OpenFile("://res/zhenbang.mp3");
            c_Voice.Play();
#endif
         QMessageBox::information(this, tr("提示"),tr("小朋友，真棒"));
        }
        else if(ret==2)//击错
            {
#if QTSound==400

            c_Voice.OpenFile("://res/budui.mp3");
            c_Voice.Play();
#endif
            QMessageBox::information(this, tr("提示"),tr("不对哦，再想一想！"));
            }

     update();//update(0,0,Wid,Hei);//需要刷新的窗口范围
}
//功能：游戏计时
void Dlg_HitGame::TimerCnt()
{
    cBall.UsedSeconds++;
    if(cBall.UsedSeconds==60)QMessageBox::information(this, tr("帮助"),tr("用时过长！"));
    //update(0,0,Wid,Hei);//需要刷新的窗口范围
    update();//全部刷新

}

void Dlg_HitGame::on_Btn_Help_clicked()
{
#if QTSound==400

    c_Voice.OpenFile("://res/shuyixia.mp3");//://res/shuyixia
    c_Voice.Play();
#endif
    QMessageBox::information(this, tr("帮助"),tr("先数左边的小猪，然后用小鸟去打右边的小猪。\n当被打中的小猪上的数字和左边小猪的数量一样时则正确"));
}
