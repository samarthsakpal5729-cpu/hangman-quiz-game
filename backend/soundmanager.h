#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class SoundManager
{
public:
    void playCorrectSound();
    void playWrongSound();
    void playGameOverSound();
    void playBackgroundMusic();
    void stopBackgroundMusic();
};

#endif