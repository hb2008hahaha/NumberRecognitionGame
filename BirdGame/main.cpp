#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //以下四句防止出现乱码
    #ifdef _MSC_VER //VC++编译采用GBK编码
        QTextCodec *codec = QTextCodec::codecForName("GBK");//VC下采用GBK编码
    #else  // 若采用MinGW和linux下采用UTF8
        QTextCodec *codec = QTextCodec::codecForName("UTF8");//UTF8
    #endif
           QTextCodec::setCodecForLocale(codec);
 #if QT_VERSION < 0x050000 //QT5中无下面几个函数
           QTextCodec::setCodecForCStrings(codec);
           QTextCodec::setCodecForTr(codec);
 #endif
    Widget w;
    w.show();
    
    return a.exec();
}
