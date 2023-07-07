#include "config.hpp"

Config config;

void Config::initialize()
{
  // Using this font in order to boost performance. (I am using just these font too many times so it's a waste creating many new once every time the program starts)
  font_small = TTF_OpenFont("res/INDUBITA.ttf", 9);
  font_medium = TTF_OpenFont("res/INDUBITA.ttf", 12);
  font_big = TTF_OpenFont("res/INDUBITA.ttf", 15);
  font_bigger = TTF_OpenFont("res/INDUBITA.ttf", 20);
}
