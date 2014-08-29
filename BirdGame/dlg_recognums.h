#ifndef DLG_RECOGNUMS_H
#define DLG_RECOGNUMS_H
#include "crecognums.h"
#include <QDialog>

namespace Ui {
class Dlg_RecogNums;
}

class Dlg_RecogNums : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dlg_RecogNums(QWidget *parent = 0);
    ~Dlg_RecogNums();
    
private slots:
    void on_Btn_Submit_clicked();

    void on_Btn_GoBack_clicked();
     void TimerCnt();//定时器计时

private:
#ifdef QTSound

        CSound c_Voice;
#endif
      QTimer *timer_cnt;//计时定时器
    Ui::Dlg_RecogNums *ui;
    CRecogNums cRecogNums;//类成员
    void paintEvent(QPaintEvent * event); //处理重绘消息
    void mousePressEvent(QMouseEvent *event);//鼠标按下
    void mouseMoveEvent(QMouseEvent  *event );//鼠标移动
     void mouseReleaseEvent( QMouseEvent  * event);//鼠标弹起
};

#endif // DLG_RECOGNUMS_H
