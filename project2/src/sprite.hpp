#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>

class Sprite {

public:
  SDL_Texture* texture = NULL;
  SDL_Rect rectangle;

  const char* original_path, *new_path;

public:
  
  Sprite(SDL_Renderer *renderer,  const char* path, int x, int y);

  void scale(float scalar);

  void update_texture(SDL_Renderer* renderer, const char* path);

  bool is_hover();
  
  void render(SDL_Renderer *renderer);
};

#endif
