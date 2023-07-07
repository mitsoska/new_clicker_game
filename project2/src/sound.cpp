#include "sound.hpp"


void play_sound(const char* path)
{

  // 2 for stereo
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);


  // The function Mix_LoadWAV doesn't support just wav files like it used to...
  Mix_Chunk* sound =  Mix_LoadWAV(path);


  // 0 -> play once... -1 -> first available channel you find
  Mix_PlayChannel(-1, sound, 0);

  //Mix_FreeChunk(sound);
  Mix_Quit();

}
