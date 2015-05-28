#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "fun.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if(!al_init())
    {
        printf("blad allegro\n");
        return -1;
    }

    ALLEGRO_DISPLAY *ekran=NULL;
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    ekran=al_create_display(600,600);
    al_set_window_title(ekran,"Test");
    ALLEGRO_KEYBOARD_STATE klawiatura;

    if(!ekran)
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
        return -1;
    }

    if(!al_init_image_addon())
    {
        printf("blad obrazow\n");
        return -1;
    }

    bool redraw=true;
    const float FPS=1;
    ALLEGRO_TIMER *timer=al_create_timer(1./FPS);
    al_start_timer(timer);

    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,al_get_display_event_source(ekran));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    fstream plik("kreski",fstream::out);
    // srand((unsigned)time(NULL));

    int N = 100;
    wektor wxN[N];

    // for (int i = 0; i < N; i++)
    // {
    // 	wxN[i].poczatek.x=300;
    // 	wxN[i].poczatek.y=300;
    // 	wxN[i].koniec.x=350;
    // 	wxN[i].koniec.y=350;
    // }

    int a,b;
    int dl=50.;
    bool czy=false;
    
    while(1)
    {   
        ALLEGRO_EVENT ev;
    	al_wait_for_event(event_queue,&ev);
    	if(ev.type==ALLEGRO_EVENT_TIMER) redraw=true;
    	else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
    	{
    		break;
    	}

        int i=0;

        wxN[i].poczatek.x=300;
        wxN[i].poczatek.y=300;

        wxN[i].koniec.x=wxN[i].poczatek.x+losowa_ab(-dl,dl);
        wxN[i].koniec.y=wxN[i].poczatek.y+losowa_ab(-dl,dl);

        i = 1;

        al_clear_to_color(al_map_rgb(0,0,0));

    	if(redraw && al_is_event_queue_empty(event_queue))
    	{
    		redraw=false;

    		while(i<N)
    		{
    			wxN[i].poczatek.x=wxN[i-1].koniec.x;
    			wxN[i].poczatek.y=wxN[i-1].koniec.y;

    			a=losowa_ab(-dl,dl);
    			b=losowa_ab(-dl,dl);

    			wxN[i].koniec.x=wxN[i].poczatek.x+a;
    			wxN[i].koniec.y=wxN[i].poczatek.y+b;

                for (int k = 0; k < i; k++){
                    al_draw_line(wxN[k].poczatek.x, wxN[k].poczatek.y, wxN[k].koniec.x, wxN[k].koniec.y, al_map_rgb(0,255,0), 1);
                }

                al_draw_line(wxN[i].poczatek.x, wxN[i].poczatek.y, wxN[i].koniec.x, wxN[i].koniec.y, al_map_rgb(255,0,0), 1);

                for (int j = 0; j < i; j++)
                {
                    if (wektoryxxxx(wxN[i],wxN[j]) ||
                        wxN[i].poczatek.x<0 || wxN[i].poczatek.x>600 ||
                        wxN[i].koniec.x<0 || wxN[i].koniec.x>600 ||
                        wxN[i].poczatek.y<0 || wxN[i].poczatek.y>600 ||
                        wxN[i].koniec.y<0 || wxN[i].koniec.y>600
                        ) {czy=true;}
                }

            	if(!czy)
            	{
            		i++;
            		czy=false;
            	}
            	else czy = false;

                // al_clear_to_color(al_map_rgb(0,0,0));
                cout << i << " " << "\r";
                al_flip_display();
                al_rest(0.4);
    		}

            // plik << wxN[0].poczatek.x << "\t" << wxN[0].poczatek.y << endl;
            // for (int i = 0; i < N; i++)
            // {
            //     al_draw_line(wxN[i].poczatek.x, wxN[i].poczatek.y, wxN[i].koniec.x, wxN[i].koniec.y, al_map_rgb(0,255,0), 1);
            //     plik << wxN[i].koniec.x << "\t" << wxN[i].koniec.y << endl;
            // }

    		al_flip_display();
    	}
    }
    plik.close();
    al_destroy_display(ekran);

	return 0;
}