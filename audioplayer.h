#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QDir>

static const QString s_curDir = "D:/homework/LiuXi_gogogo/music";
//此处使用到了音乐文件夹的绝对路径，因此，当从有学网上重新下载时，
//路径会发生变化而无法播放所有BGM和音效，但是我在B站的视频中展示了音效的效果。
//如果需要从Qt工程中启动而期望得到正常的音效效果，那么麻烦助教师兄或者老师
//把AudioPlayer类中以下代码的目录路径（只到music文件夹即可）进行一下修改，
//以获得最好的游戏体验和效果。谢谢！

class QMediaPlayer;
class EasyMode;

enum SoundType
{
    TowerPlaceSound,
    LifeLoseSound,
    NormalBulletSound,
    IceBulletSound,
    FireBulletSound,
    normalEnemyDestorySound,
    iceEnemyDestorySound,
    fireEnemyDestorySound,
    bossEnemyDestorySound,
    BreakTowerSound,
};

class AudioPlayer : public QObject
{
public:
    explicit AudioPlayer(QUrl backgroundMusicUrl,QObject *parent = nullptr);
    void startBGM();
    void stopBGM();
    void playSound(SoundType soundType);
    void playWinSound();
    void playLoseSound();
    QMediaPlayer * getMusic();
private:
    QMediaPlayer *m_backgroundMusic;
    QMediaPlayer *m_winMusic;
    QMediaPlayer *m_loseMusic;
};

#endif // AUDIOPLAYER_H
