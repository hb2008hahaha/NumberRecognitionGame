#ifndef DLG_HITGAME_H
#define DLG_HITGAME_H
#include <QtGui>
#include <QDialog>
#include "cballhit.h"
#include "global.h"
namespace Ui {
class Dlg_HitGame;
}

class Dlg_HitGame : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dlg_HitGame(QWidget *parent = 0);
    ~Dlg_HitGame();
    
private slots:
    void on_Btn_ReturnToMain_clicked();//返回主菜单
    void TimerServer();//定时器服务
    void TimerCnt();//定时器计时
    void on_Btn_Help_clicked();// 帮助


private:
    //相关变量
    CBallHit cBall;
#ifdef  QTSound

        CSound c_Voice;
#endif

    Ui::Dlg_HitGame *ui;
    void paintEvent(QPaintEvent * event); //处理重绘消息
    void mousePressEvent(QMouseEvent *event);//鼠标按下
    void mouseMoveEvent(QMouseEvent  *event );//鼠标移动
    void mouseReleaseEvent( QMouseEvent  * event);//鼠标弹起

    //定时器
    QTimer * timer; //游戏定时器
    QTimer *timer_cnt;//计时定时器
    void TimerInit(void);

};

#endif // DLG_HITGAME_H
