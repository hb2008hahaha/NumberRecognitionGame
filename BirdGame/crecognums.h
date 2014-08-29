#ifndef CRECOGNUMS_H
#define CRECOGNUMS_H
#include <stdlib.h>
#include <string.h>
#include <QtGui>
#define LocX1 60
#define LocY1 100
#define TimeX1 75
#define TimeY1 20
#define BlockSize 32
#define ColNum 5 //每列5个图形
#define MaxNum 10 //最多10
#include "global.h"

class CRecogNums
{
public:
    CRecogNums();
    int UsedSeconds;//用的秒数
    //功能:检测涂的方块数量与给的数字是否一致
    char CheckResult();
    //返回1表示需要刷新UI
    char MouseDown(int x,int y);
    char MouseMove(int x,int y);
    void MouseUp(void);
    void InitGame();

    void DrawBoard(QPainter *painter);
private:
    int DispNums;
    int SelectedNums;
    char IsSelected[MaxNum];
    char MouseDownFlag;
    int Lastpos;//上次按下时候的方块位置
#ifdef QTImage
        QPixmap ImgBlock;
        QPixmap ImgBackground;
#endif
        void DrawTime(QPainter *painter);

    //功能:
    void DrawBlock(QPainter *painter,int pos);     //
};

#endif // CRECOGNUMS_H
