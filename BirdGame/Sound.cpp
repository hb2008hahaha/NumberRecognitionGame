//#include "Sound.h"
#include "global.h"
#if QTSound==400
#include "widget.h"
#include "dlg_hitgame.h"
CSound::CSound()
{
    sound=NULL;
    audio=NULL;
}
void  CSound::Init(void *pointer)
{
    Dlg_HitGame *pWindow=(Dlg_HitGame *)pointer;
     sound = new Phonon::MediaObject(pWindow);//消行声音对象
    audio = new Phonon::AudioOutput(Phonon::MusicCategory, pWindow);
     Phonon::createPath(sound, audio);//绑定音源和音频输出控件
     sound->connect(sound, SIGNAL(finished()), sound, SLOT(stop()));//音效播放结束时执行的函数，保证背景音乐结束后能再次播放
}
CSound::~CSound()
{
    Close();
}
void CSound::OpenFile(QString filename)
{

   sound->setCurrentSource(Phonon::MediaSource(filename));

}
void CSound::Close()
{
    sound->stop();
  if(sound!=NULL)delete sound;
  if(audio!=NULL)delete audio;//

}
void CSound::Play()
{

   sound->play();
}
#elif  QTSound==500//

void  CSound::Init(void *pointer)//暂未使用
{
  // pointer=pointer;//为了保持兼容，暂未使用
    //
}

CSound::CSound()
{
  player = new QMediaPlayer();
}

CSound::~CSound()
{
 delete player;
}
void CSound::OpenFile(QString filename)
{

   player->setMedia(QUrl::fromLocalFile(filename));
 //存在问题：不支持：//开头的，从qrc中获取音乐文件
}

void CSound::Play()
{

  player->setVolume(50);
  player->play();

}
#endif
