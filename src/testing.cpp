#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>\
#include "fun.h"

using namespace std;

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
	ALLEGRO_COLOR kolor;
//----------------------------------------------------------------


	wektor wxN[2];

	wxN[0].poczatek.x=300;
    wxN[0].poczatek.y=300;
    wxN[0].koniec.x=350;
    wxN[0].koniec.y=350;

    wxN[1].poczatek.x=300;
    wxN[1].poczatek.y=300;
    wxN[1].koniec.x=350;
    wxN[1].koniec.y=350;

	while(!al_key_down( &klawiatura, ALLEGRO_KEY_ESCAPE))
	    {
	        al_get_keyboard_state(&klawiatura);
	        al_clear_to_color(al_map_rgb(0,0,0));

	        if (wektoryxx(wxN[0],wxN[1]))
	        {
	        	kolor=red;
	        }
	        else
	        {
	        	kolor=blue;
	        }

	        al_draw_line((float) wxN[0].poczatek.x, (float) wxN[0].poczatek.y, (float) wxN[0].koniec.x,(float) wxN[0].koniec.y,blue,2);
	        al_draw_line((float) wxN[1].poczatek.x, (float) wxN[1].poczatek.y, (float) wxN[1].koniec.x,(float) wxN[1].koniec.y,kolor,2);

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_W))
	        {
	        		wxN[1].poczatek.y+=10;
					al_flip_display();
	        }

	       	if (al_key_down(&klawiatura, ALLEGRO_KEY_S))
       		{		
       				wxN[1].poczatek.y-=10;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_A))
	        {
	        		wxN[1].poczatek.x+=10;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_D))
	        {
	        		wxN[1].poczatek.x-=10;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_UP))
	        {
	        		wxN[1].koniec.y+=10;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_DOWN))
	        {
	        		wxN[1].koniec.y-=10;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_LEFT))
	        {
	        		wxN[1].koniec.x+=10;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_RIGHT))
	        {
	        		wxN[1].koniec.y-=10;
					al_flip_display();
	        }
	}

	return 0;
}