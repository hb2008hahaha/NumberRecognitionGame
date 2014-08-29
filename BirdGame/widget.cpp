#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //更改按钮背景颜色
    ui->Btn_Game1->setAutoFillBackground(true);
    ui->Btn_Game1->setFlat(true);
    QPalette palette = ui->Btn_Game1->palette();
    palette.setColor(QPalette::Active,QPalette::Button,QColor(255,255,255,100));
    ui->Btn_Game1->setPalette(palette);

    //更改按钮背景颜色
    ui->Btn_Game2->setAutoFillBackground(true);
    ui->Btn_Game2->setFlat(true);
   // QPalette palette = ui->Btn_Game2->palette();
    palette.setColor(QPalette::Active,QPalette::Button,QColor(255,255,255,100));
    ui->Btn_Game2->setPalette(palette);
#if  QTSound==400

    //设置声音
       background_music = new Phonon::MediaObject(this);//背景音乐对象，必须放在窗体类中

       //AudioOutput是一个将数据送到音频输出的设备
       Phonon::AudioOutput *audio1 = new Phonon::AudioOutput(Phonon::MusicCategory, this);
      Phonon::createPath(background_music, audio1);//
     connect(background_music, SIGNAL(aboutToFinish()), this, SLOT(Music_play_finish()));//结束时执行的函数，保证背景音乐循环播放

     audio1->setVolume(0.3);//调节音量
     background_music->setCurrentSource(Phonon::MediaSource("://res/background.mp3"));
     background_music->play();//初始化的时候直接播放背景音乐*/4


#endif

}
//功能：音乐播放完毕时，再次播放
void Widget::Music_play_finish(void)
{
#if QTSound==400
    background_music->enqueue(background_music->currentSource());//设置后续的播放序列为当前的音频文件，达到重复播放的目的
#endif
}
Widget::~Widget()
{
   #if  QTSound==400
    background_music->stop();
    #endif
    delete ui;
}
//功能：处理窗口重绘消息
void Widget::paintEvent(QPaintEvent *event)
{
   QPainter *painter=new QPainter(this);
#ifdef QTImage
  painter->drawPixmap(0,0, QPixmap("://res/background.jpg"));//绘制图片，并且保持图片原始大小
#endif
  delete(painter);
   QWidget::paintEvent(event);
}

void Widget::on_Btn_Game1_clicked()
{
    Dlg_RecogNums  *pDialog=new Dlg_RecogNums(this);
    this->hide();
    pDialog->show();
    pDialog->exec();
    delete pDialog;//释放内存
    this->show();
}

void Widget::on_Btn_Game2_clicked()
{

    Dlg_HitGame *pDialog=new Dlg_HitGame(this);
    this->hide();
    pDialog->show();
    pDialog->exec();
    delete pDialog;//释放内存
    this->show();



}
