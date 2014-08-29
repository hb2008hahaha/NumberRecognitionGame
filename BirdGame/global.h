#ifndef GLOBAL_H
#define GLOBAL_H


#define QTImage//启用图片
/*#if QT_VERSION >=0x050000
#define QTSound 500
#elif  QT_VERSION <=0x050000 && QT_VERSION >0x040700
#define QTSound 400
#endif*/

#if QTSound==400 //QT4音乐支持，QT5中的音乐支持有待完善
#include <phonon>//音乐支持
#include "Sound.h"
#elif QTSound==500
#include <QMediaPlayer>
#include "Sound.h"
#endif
#endif // GLOBAL_H
