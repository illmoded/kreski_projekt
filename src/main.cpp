#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "fun.h"
#include "rnd.h"

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
    const float FPS=60;
    ALLEGRO_TIMER *timer=al_create_timer(1./FPS);
    al_start_timer(timer);

    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,al_get_display_event_source(ekran));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    fstream plik("kreski",fstream::out);
    // srand((unsigned)time(NULL));

    rnd rnd;

    int N = 100;
    wektor wxN[N];

    double a,b;
    double dl=20.;
    bool czy=false;
    double drg2=0, srdrg2;
    double pol2=0, srpol2;
    double Xp, Yp, Xk, Yk;
    int I=0, czas=1000;
    int i=0;
    
    while(i<N && I<=czas)
    {   
        ALLEGRO_EVENT ev;
    	al_wait_for_event(event_queue,&ev);
    	if(ev.type==ALLEGRO_EVENT_TIMER) redraw=true;
    	else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
    	{
    		break;
    	}

        wxN[i].poczatek.x=0;
        wxN[i].poczatek.y=0;

        wxN[i].koniec.x=wxN[i].poczatek.x+rnd.gauss(0,dl);
        wxN[i].koniec.y=wxN[i].poczatek.y+rnd.gauss(0,dl);

        i = 1;

        al_clear_to_color(al_map_rgb(0,0,0));

    	if(redraw && al_is_event_queue_empty(event_queue))
    	{
    		redraw=false;

    		while(i<N && I<=czas)
    		{
                czy=0;
    			wxN[i].poczatek.x=wxN[i-1].koniec.x;
    			wxN[i].poczatek.y=wxN[i-1].koniec.y;

    			/// losowanie po kwadracie
    			a=rnd.gauss(0,dl);
    			b=rnd.gauss(0,dl);

    			wxN[i].koniec.x=wxN[i].poczatek.x+a;
    			wxN[i].koniec.y=wxN[i].poczatek.y+b;

                /// czerwone kreski
                al_draw_line(300+wxN[i].poczatek.x, 300+wxN[i].poczatek.y, 300+wxN[i].koniec.x, 300+wxN[i].koniec.y, al_map_rgb(255,0,0), 2);  

                for (int j = 0; j < i-1; j++)
                {
                    if (wektoryxxxx(wxN[i],wxN[j]))
                        {
                        	czy=true;
                        	break;
                        }
                }

            	if(!czy)
            	{	
            		i++;
            	}
            	/// reset
                I++;
            	czy = 0;

                Xp=wxN[i-1].poczatek.x;
                Yp=wxN[i-1].poczatek.y;
                Xk=wxN[i-1].koniec.x;
                Yk=wxN[i-1].koniec.y;

                pol2+=Xk*Xk+Yk*Yk;
                srpol2=pol2/i;

                drg2+=(Xk-Xp)*(Xk-Xp)+(Yk-Yp)*(Yk-Yp);
                srdrg2=drg2/i;

                plik << I << "\t" << srpol2 << "\t" << srdrg2 << endl;

                for (int k = 0; k < i; k++){///rysuje wszystkie pozostałe, żeby nic nie znikało
                    al_draw_line(300+wxN[k].poczatek.x, 300+wxN[k].poczatek.y, 300+wxN[k].koniec.x, 300+wxN[k].koniec.y, al_map_rgb(0,255,0), 2);
                }

                al_flip_display();
    		}

    		al_flip_display();
    	}
    }
    plik.close();
    al_destroy_display(ekran);

	return 0;
}