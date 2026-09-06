#include <windows.h>
#include <mmsystem.h>

#include "SoundManager.h"

void SoundManager::playCorrectSound()
{
    PlaySound(
        TEXT("sounds/correct.wav"),
        NULL,
        SND_FILENAME | SND_ASYNC
    );
}

void SoundManager::playWrongSound()
{
    PlaySound(
        TEXT("sounds/wrong.wav"),
        NULL,
        SND_FILENAME | SND_ASYNC
    );
}

void SoundManager::playGameOverSound()
{
    PlaySound(
        TEXT("sounds/gameover.wav"),
        NULL,
        SND_FILENAME | SND_ASYNC
    );
}

void SoundManager::playBackgroundMusic()
{
    PlaySound(
        TEXT("sounds/background.wav"),
        NULL,
        SND_FILENAME | SND_ASYNC | SND_LOOP
    );
}

void SoundManager::stopBackgroundMusic()
{
    PlaySound(NULL, NULL, 0);
}