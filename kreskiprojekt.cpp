#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

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

bool wejtoryxx(wektor w1, wektor w2) 
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

double losowa_ab(double a, double b)
{
	return a+(b-a)*(double)rand()/RAND_MAX;
}

int main(int argc, char const *argv[])
{
	// if(!al_init())
 //    {
 //        printf("blad allegro\n");
 //        return -1;
 //    }

    // ALLEGRO_DISPLAY *ekran=NULL;
    // al_set_new_display_flags(ALLEGRO_RESIZABLE);
    // ekran=al_create_display(600,600);
    // al_set_window_title(ekran,"Test");
    // ALLEGRO_KEYBOARD_STATE klawiatura;

    // if(!ekran)
    // {
    //     printf("blad ekranu\n");
    //     return -1;
    // }

    // if(!al_init_primitives_addon())
    // {
    //     printf("blad prymitywow\n");
    //     return -1;
    // }

    // if(!al_install_keyboard())
    // {
    //     printf("blad klawiatury\n");
    //     return -1;
    // }

    // if(!al_init_image_addon())
    // {
    //     printf("blad obrazow\n");
    //     return -1;
    // }

    // bool redraw=true;
    // const float FPS=1;
    // ALLEGRO_TIMER *timer=al_create_timer(1./FPS);
    // al_start_timer(timer);

    // ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    // al_register_event_source(event_queue,al_get_display_event_source(ekran));
    // al_register_event_source(event_queue,al_get_timer_event_source(timer));

    fstream plik("kreski",fstream::out);
    srand((unsigned)time(NULL));

    int N = 300;
    wektor wxN[N];

    for (int i = 0; i < N; i++)
    {
    	wxN[i].poczatek.x=300;
    	wxN[i].poczatek.y=300;
    	wxN[i].koniec.x=350;
    	wxN[i].koniec.y=350;
    }


    double a,b;

//    int aa;
//    int bb;
    double aaa;
    
    // while(1)
    {   
     //    ALLEGRO_EVENT ev;
    	// al_wait_for_event(event_queue,&ev);
    	// if(ev.type==ALLEGRO_EVENT_TIMER) redraw=true;
    	// else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
    	// {
    	// 	break;
    	// }

        int i=0;

        wxN[i].poczatek.x=300;
        wxN[i].poczatek.y=300;

        wxN[i].koniec.x=wxN[i].poczatek.x+losowa_ab(-50,50);
        wxN[i].koniec.y=wxN[i].poczatek.y+losowa_ab(-50,50);

        // al_clear_to_color(al_map_rgb(0,0,0));

    	// if(redraw && al_is_event_queue_empty(event_queue))
    	{
    		// redraw=false;

    		do
    		{
                i++;
                aaa=50;

    			wxN[i].poczatek.x=wxN[i-1].koniec.x;
    			wxN[i].poczatek.y=wxN[i-1].koniec.y;

    			a=losowa_ab(-aaa,aaa);
    			b=losowa_ab(-aaa,aaa);

    			wxN[i].koniec.x=(wxN[i].poczatek.x)+a;
    			wxN[i].koniec.y=(wxN[i].poczatek.y)+b;			

                for (int j = 0; j < i; j++)
                {
                    if (wejtoryxx(wxN[i],wxN[j])||
                        wxN[i].poczatek.x<0 ||
                        wxN[i].poczatek.x>600 ||
                        wxN[i].koniec.x<0 ||
                        wxN[i].koniec.x>600 ||
                        wxN[i].poczatek.y<0 ||
                        wxN[i].poczatek.y>600 ||
                        wxN[i].koniec.y<0 ||
                        wxN[i].koniec.y>600
                        )
                    {                                    
                        // a=losowa_ab(-aaa,aaa);
                        // b=losowa_ab(-aaa,aaa);
                        
                        // aaa*=1.;
                        // wxN[i].koniec.x=(wxN[i].poczatek.x)+a;
                        // wxN[i].koniec.y=(wxN[i].poczatek.y)+b;    
                        i--;
                    }
                } 
                cout << i << endl;  			
    		}while(i<N);

            plik << wxN[0].poczatek.x << "\t" << wxN[0].poczatek.y << endl;
    		for (int i = 0; i < N; i++)
    		{
				// al_draw_line((float) wxN[i].poczatek.x, (float) wxN[i].poczatek.y, (float) wxN[i].koniec.x,
    //                          (float) wxN[i].koniec.y,al_map_rgb(0,255,0),2);
                plik << wxN[i].koniec.x << "\t" << wxN[i].koniec.y << endl;

    		}

    		// al_flip_display();
    	}
    }
    plik.close();
    // al_destroy_display(ekran);

	return 0;
}