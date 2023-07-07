#include "sprite.hpp"
#include <SDL2/SDL_image.h>

// Sprite Class: A textured rectangle
Sprite::Sprite(SDL_Renderer* renderer, const char* texture_path, int x, int y)
{

  // Initializing the Sprite's texture
  SDL_Texture *sprite_texture = IMG_LoadTexture(renderer, texture_path);

  this->original_path = texture_path;
  this->texture = sprite_texture;

  // I made the texture and now I am changing the rectangle's dimension in order for them to fit the newly created SDL_Texture
  SDL_QueryTexture(this->texture, NULL, NULL, &this->rectangle.w, &this->rectangle.h);


  this->rectangle.x = x;
  this->rectangle.y = y;
  
}


void Sprite::scale(float scalar)
{

  this->rectangle.w *= scalar;
  this->rectangle.h *= scalar;
  
}


bool Sprite::is_hover()
{
  int mouse_x, mouse_y;

  SDL_GetMouseState(&mouse_x, &mouse_y);

  if((mouse_x >= this->rectangle.x && mouse_x <= this->rectangle.w + this->rectangle.x) && (mouse_y >= this->rectangle.y && mouse_y <= this->rectangle.y + this->rectangle.h))
  {
    return true;


  } else { return false; }

}



void Sprite::render(SDL_Renderer* renderer)
{

  SDL_RenderCopy(renderer, this->texture, NULL, &this->rectangle);
}

void Sprite::update_texture(SDL_Renderer* renderer, const char* path)
{

  this->new_path = path;
  this->texture = IMG_LoadTexture(renderer, path);
  
}
