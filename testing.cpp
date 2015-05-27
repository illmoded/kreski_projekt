#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

int main(int argc, char const *argv[])
{

	if(!al_init())
    {
        printf("blad allegro\n");
        return -1;
    }
    ALLEGRO_DISPLAY *ekran1=NULL;

    ekran1=al_create_display(600,600);

    al_set_window_title(ekran1,"testing");

    ALLEGRO_KEYBOARD_STATE klawiatura;

    if(!ekran1)
    {
        printf("blad ekranu\n");
        return -1;
    }

    if(!al_init_primitives_addon())
    {
        printf("blad prymitywow\n");
        return -1;
    }

    if(!al_install_keyboard())
    {
        printf("blad klawiatury\n");
    }

	ALLEGRO_COLOR red=al_map_rgb(255,0,0);	
	ALLEGRO_COLOR blue=al_map_rgb(0,0,255);	
//----------------------------------------------------------------


	while(!al_key_down( &klawiatura, ALLEGRO_KEY_ESCAPE))
	    {
	        al_get_keyboard_state(&klawiatura);
	        al_clear_to_color(al_map_rgb(0,0,0));

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_F1))
	        {
		       
						
					
					al_flip_display();

	        }

	       	if (al_key_down(&klawiatura, ALLEGRO_KEY_F2))
       		{
		        
					al_flip_display();

	        }
	}

	return 0;
}