#ifndef _CONFIG_H
#define _CONFIG_H

#include <SDL2/SDL_ttf.h>


struct Config
{
  TTF_Font *font_small, *font_medium, *font_big, *font_bigger;

  void initialize();

};


extern Config config;


#endif
