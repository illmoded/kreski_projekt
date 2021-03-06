#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
// #include "fun.h"

using namespace std;

struct punkt
{
	double x;
	double y;
	double z;
};

class wektor
{
public:

	void oblicz_xyz_z_puktow(punkt p1, punkt p2);
	// wektor iloczynwektorowy(wektor w1, wektor w2);
	// double iloczynskalarny(wektor w1, wektor w2);

	punkt poczatek;
	punkt koniec;

	double x;
	double y;
	double z;
}; 


void wektor::oblicz_xyz_z_puktow(punkt p1, punkt p2)
{
	poczatek.x=p1.x;
	poczatek.y=p1.y;
	koniec.x=p2.x;
	koniec.y=p2.y;

	x=p1.x-p2.x;
	y=p1.y-p2.y;
	z=p1.z-p2.z;
}

wektor iloczynwektorowy(wektor w1, wektor w2)
{
	wektor w3;
	w3.x = w1.y*w2.z - w1.z*w2.y;
	w3.y = w1.z*w2.x - w1.x*w2.z;
	w3.z = w1.x*w2.y - w1.y*w2.x;
	return w3;
}

double iloczynskalarny(wektor w1, wektor w2)
{
	double ils;
	ils = (w1.x*w2.x)+(w1.y*w2.y)+(w1.z*w2.z);
	return ils;
}

bool wektoryxx(wektor w1, wektor w2) 
{
	wektor ilw1,ilw2, wpom1 = wektor(), wpom2 = wektor();
	double ils;

    w1.oblicz_xyz_z_puktow(w1.poczatek,w1.koniec);
    w2.oblicz_xyz_z_puktow(w2.poczatek,w2.koniec);

	wpom1.oblicz_xyz_z_puktow(w2.poczatek,w1.poczatek);
	wpom2.oblicz_xyz_z_puktow(w2.koniec,w1.poczatek);

	ilw1 = iloczynwektorowy(w1,wpom1);
	ilw2 = iloczynwektorowy(w1,wpom2);
	ils = iloczynskalarny(ilw1,ilw2);

    return ils < 0;
}

bool wektoryxxxx(wektor w1, wektor w2)
{
	return (wektoryxx(w1, w2) && wektoryxx(w2, w1));
}

int losowa_ab(int a, int b)
{
	return a+rand()%(int)(b-a+1);
}

int main(int argc, char const *argv[])
{
	fstream plik("kreski",fstream::out);
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
	// ALLEGRO_COLOR kolor;

//----------------------------------------------------------------

	int N=5;
	wektor wxN[N];

	// 283.932	306.921
	// 276.542	269.284

// 	275.897	275.554
// 	313.473	313.424

	wxN[0].poczatek.x=283.932;
    wxN[0].poczatek.y=306.921;
    wxN[0].koniec.x=276.542;
    wxN[0].koniec.y=269.284;

    wxN[1].poczatek.x=275.897;
    wxN[1].poczatek.y=275.554;
    wxN[1].koniec.x=313.473;
    wxN[1].koniec.y=313.424;

    wxN[2].poczatek.x=400;
    wxN[2].poczatek.y=400;
    wxN[2].koniec.x=500;
    wxN[2].koniec.y=250;

    wxN[3].poczatek.x=555;
    wxN[3].poczatek.y=111;
    wxN[3].koniec.x=222;
    wxN[3].koniec.y=222;

    wxN[4].poczatek.x=115;
    wxN[4].poczatek.y=75;
    wxN[4].koniec.x=12;
    wxN[4].koniec.y=34;

	while(!al_key_down( &klawiatura, ALLEGRO_KEY_ESCAPE))
	    {
	        al_get_keyboard_state(&klawiatura);
	        al_clear_to_color(al_map_rgb(0,0,0));
	        for (int i = 0; i < N; ++i)
	        {
	        	al_draw_line((float) wxN[i].poczatek.x, (float) wxN[i].poczatek.y, (float) wxN[i].koniec.x,(float) wxN[i].koniec.y,blue,2);
			}
	        for (int i = 1; i < N; i++)
	        {
	           	if(wektoryxxxx(wxN[0],wxN[i]))
	        	{
	        		al_draw_line((float) wxN[0].poczatek.x, (float) wxN[0].poczatek.y, (float) wxN[0].koniec.x,(float) wxN[0].koniec.y,red,5);
	        	}
	        	else
	        	{
	        		al_draw_line((float) wxN[0].poczatek.x, (float) wxN[0].poczatek.y, (float) wxN[0].koniec.x,(float) wxN[0].koniec.y,blue,2);		
	        	}
	        }

	        al_flip_display();

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_W))
	        {
	        		wxN[0].poczatek.y-=2;
					al_flip_display();
	        }

	       	if (al_key_down(&klawiatura, ALLEGRO_KEY_S))
       		{		
       				wxN[0].poczatek.y+=2;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_A))
	        {
	        		wxN[0].poczatek.x-=2;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_D))
	        {
	        		wxN[0].poczatek.x+=2;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_UP))
	        {
	        		wxN[0].koniec.y-=2;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_DOWN))
	        {
	        		wxN[0].koniec.y+=2;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_LEFT))
	        {
	        		wxN[0].koniec.x-=2;
					al_flip_display();
	        }

	        if (al_key_down(&klawiatura, ALLEGRO_KEY_RIGHT))
	        {
	        		wxN[0].koniec.x+=2;
					al_flip_display();
	        }

	        // if(al_key_down(&klawiatura, ALLEGRO_KEY_SPACE)){
	        // 	plik << wxN[0].poczatek.x << "\t" << wxN[0].poczatek.y << "\t" << wxN[0].poczatek.x << "\t" << wxN[0].poczatek.y << endl;
	        // 	plik << wxN[0].koniec.x << "\t" << wxN[0].koniec.y << "\t" << wxN[1].koniec.x << "\t" << wxN[1].koniec.y << endl;
	        // }
	}
	plik.close();
	return 0;
}