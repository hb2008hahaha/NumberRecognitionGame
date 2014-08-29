#include "dlg_recognums.h"
#include "ui_dlg_recognums.h"
#if QT_VERSION >=0x050000
#include <QMessageBox>
#endif
Dlg_RecogNums::Dlg_RecogNums(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_RecogNums)
{
    ui->setupUi(this);

        timer_cnt = new QTimer(this);//定时器
        connect(timer_cnt, SIGNAL(timeout()), this, SLOT(TimerCnt()));
        timer_cnt->start(1000);
#if QTSound==400
    c_Voice.Init(this);

#endif

    //更改按钮背景颜色
    ui->Btn_GoBack->setAutoFillBackground(true);
    ui->Btn_GoBack->setFlat(true);
    QPalette palette = ui->Btn_GoBack->palette();
    palette.setColor(QPalette::Active,QPalette::Button,QColor(255,255,255,10));
    ui->Btn_GoBack->setPalette(palette);

    //更改按钮背景颜色
    ui->Btn_Submit->setAutoFillBackground(true);
    ui->Btn_Submit->setFlat(true);
   // QPalette palette = ui->Btn_Game2->palette();
    palette.setColor(QPalette::Active,QPalette::Button,QColor(255,255,255,10));
    ui->Btn_Submit->setPalette(palette);

}

Dlg_RecogNums::~Dlg_RecogNums()
{
    if(timer_cnt!=NULL)delete timer_cnt;
    delete ui;
}
void Dlg_RecogNums::paintEvent(QPaintEvent * event) //处理重绘消息
{
    QPainter painter(this);
    cRecogNums.DrawBoard(&painter);
    QWidget::paintEvent(event);

}

void Dlg_RecogNums::mousePressEvent(QMouseEvent *event)//鼠标按下
{
    if(cRecogNums.MouseDown(event->x(),event->y()))
    {
#if QTSound==400

                c_Voice.OpenFile("://res/click.wav");
                c_Voice.Play();
 #endif
        repaint();
    }

}
void Dlg_RecogNums::mouseMoveEvent(QMouseEvent  *event )//鼠标移动
{

        if(cRecogNums.MouseMove(event->x(),event->y()))
            repaint();
            //update(0,0,Wid,Hei);//需要刷新的窗口范围

}

void Dlg_RecogNums::mouseReleaseEvent( QMouseEvent  * event)//鼠标弹起
{
    cRecogNums.MouseUp();

}

void Dlg_RecogNums::on_Btn_Submit_clicked()
{
    if(cRecogNums.CheckResult())
    {
#if QTSound==400

                c_Voice.OpenFile("://res/zhenbang.mp3");
                c_Voice.Play();
 #endif
        QMessageBox::information(this, tr("提示"),tr("小朋友,真棒！"));
         cRecogNums.InitGame();
         repaint();
    }
    else{
#if QTSound==400

                c_Voice.OpenFile("://res/budui.mp3");
                c_Voice.Play();
 #endif
        QMessageBox::information(this, tr("提示"),tr("不太对哦，再想一想。"));
        }
}

void Dlg_RecogNums::on_Btn_GoBack_clicked()
{
    this->close();
}

void Dlg_RecogNums::TimerCnt()
{
    cRecogNums.UsedSeconds++;
    if(cRecogNums.UsedSeconds==60)
        QMessageBox::information(this, tr("帮助"),tr("用时过长！"));
    //update(0,0,Wid1,Hei1);//指定刷新窗口范围
    update();//需要刷新的窗口范围

}
