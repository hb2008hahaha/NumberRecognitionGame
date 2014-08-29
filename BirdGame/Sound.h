#ifndef SOUND_H
#define SOUND_H
#if  QTSound==400
class CSound
{
  public:
    Phonon::MediaObject *sound;
    Phonon::AudioOutput *audio;
    CSound();

  void  Init(void *pointer);

    ~CSound();

    void OpenFile(QString filename);

   void Close();

   void Play();

};
#elif QTSound==500
class CSound
{
public:
    void  Init(void *pointer);//暂未使用
    CSound();
    ~CSound();
  void OpenFile(QString filename);
  void Play();
private:
   QMediaPlayer *player;
};
#endif //
#endif //SOUND_H
