#include <iostream>
#include "sprite.hpp"
#include "label.hpp"
#include "config.hpp"
#include "button.hpp"
#include <cmath>
#include <string>
#include <sstream>
#include "particle_generator.hpp"
#include "sound.hpp"


int main()
{

  Button* buttons[4];
  
  const char* paths[] =
    {
      "res/button_image.jpg",
      "res/chef.jpg",
      "res/factory.jpg",
      "res/god.jpg"
    };

  const int prices[] =
    {
      10,
      50,
      200,
      1000

    };

   const char* titles[] =
    {
      "Grandmother",
      "Chef",
      "Factory",
      "God"


    };

   const char * descriptions[] =
     {
       "Cooks cookies for ya! Gives you 0.1 cookies per second",
       "Studied cookie mechanics. Gives 0.8 cookies per second",
       "Machines are better. Each factory gives 4 cookies per second",
       "God. Self-explanatory... Makes 25 cookies per second"
     };

    float all_cps[] =
    {
      0.1,
      0.8,
      4,
      25
    };

   //std::ostringstream oss;

  bool is_clicked = false;
  
  int cpc = 1;
  float cps = 0.0f;
  
  float balance = 0.0f;
  
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  config.initialize();
    
  SDL_Window* window = SDL_CreateWindow("Cookie Clicker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_UTILITY);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  Sprite cookie(renderer, "res/cookie.png", 300 - 90, 200);
  cookie.scale(0.5f);
  Sprite main_background(renderer, "res/background.png", 0, 0);

  Sprite background(renderer, "res/button_texture.jpeg", 0, 0);

  SDL_Color white = {255, 255, 255};
  SDL_Color whitish = {200, 200, 200};

  for (int i = 0; i < sizeof(all_cps) / sizeof(float); i++)
    {
      Sprite* current_icon_sprite = new Sprite(renderer, paths[i], 10, 10 + i * 60);
      Label* current_title = new Label(renderer, config.font_big, whitish, titles[i], 0 , 0);
      buttons[i] = new Button(renderer, *current_title, config.font_small, descriptions[i], whitish, *current_icon_sprite, background, prices[i], all_cps[i], 10, 10 + i * (background.rectangle.h + 10) );

      

    }


  // Sprite icon(renderer, "res/button_image.jpg", 0, 0);

  //Label label(renderer, config.font_big, whitish, "Grandmother", 150, 200);
    
  //Button first_button(renderer, label, config.font_small, "Bakes cookies for ya! xD Costs 10 cookies. Gives 1 cps ", whitish, icon, background, 10, 1, 10, 10);
  
  float delta;
  float dtime;
  
  ParticleGenerator cookie_particles(renderer, 0, 0, 5, "res/cookie.png", 0.5, 20, 20);

  char text_content[60];    

  while (true)
  {

    sprintf(text_content, "Total Cookies %.2f", balance);

    Label cookie_text(renderer, config.font_bigger, white, text_content, 300 - cookie_text.rectangle.w / 2, 150);

    float time = SDL_GetTicks();
    cookie.rectangle.w = 180 + 5 * sin(0.003 * time);
    cookie.rectangle.h = 180 + 5 * sin(0.003 * time);
    
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
	  goto clean_game;
	  break;

        case SDL_MOUSEBUTTONDOWN:
	  if (event.button.button == SDL_BUTTON_LEFT)
	  {
	    if(cookie.is_hover())
	      {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		cookie_particles.move(mouse_x, mouse_y);
		cookie_particles.is_active = true;

		play_sound("res/click.mp3");

		is_clicked = true;
	    
		balance += cpc;
	      }


	    for (int i = 0; i < sizeof(prices) / sizeof(int); i ++)
	      {
		if(buttons[i]->background.is_hover())
		  {
		    if(balance >= buttons[i]->price)
		      {
			balance -= buttons[i]->price;
			cps += buttons[i]->cps;
			play_sound("res/money.mp3");
		      }

		    else { play_sound("res/error.aiff"); }


		  }
	      }
	    
	  }

      }
    }

    // 0.06 is the magic number
    delta += 0.06;

    balance += cps / 60.0f;
    
    SDL_SetRenderDrawColor(renderer, 90, 100, 100, 255);
    SDL_RenderClear(renderer);

    main_background.render(renderer);
    //icon.render(renderer);

    for (int i = 0; i < sizeof(prices) / sizeof(int); i++)
      {
	buttons[i]->render(renderer, "res/hover_texture.jpeg");

      }
    //first_button.render(renderer, "res/hover_texture.jpeg");
    //label.render(renderer);
    if(is_clicked)
      {
	float new_width = 2 * sin(dtime * 8 * 3.14159); 
	cookie.rectangle.w = 190 + new_width;
	cookie.rectangle.h = 190 + new_width;

	dtime += 1/15.0;

	if(dtime >= 0.25f)
	  {
	    is_clicked = false;
	    dtime = 0.0f;
	  }


      }

    SDL_RenderCopyEx(renderer, cookie.texture, NULL, &cookie.rectangle, delta, NULL, SDL_FLIP_NONE);

    if (cookie_particles.is_active)
    {
      cookie_particles.update_and_render(renderer, 100.0);
    }
    //cookie.render(renderer);
    cookie_text.render(renderer);
    //label2.render(renderer);
      
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

clean_game:

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}
