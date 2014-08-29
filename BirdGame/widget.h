#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include "global.h"
#include "dlg_hitgame.h"
#include "dlg_recognums.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void on_Btn_Game1_clicked();

    void on_Btn_Game2_clicked();
     void  Music_play_finish(void);//音乐播放完毕

private:
     void paintEvent(QPaintEvent * event); //处理重绘消息
    Ui::Widget *ui;
    //添加背景音乐和消行声音
     #if  QTSound==400
       Phonon::MediaObject *background_music;

     #endif
};

#endif // WIDGET_H
