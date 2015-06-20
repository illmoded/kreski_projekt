#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <list>
#include "fun.h"
#include "rnd.h"
#include "Miniball.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int tryb;
    tryb = 1;
    if(tryb)
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

        fstream plik("kreski.txt",fstream::out);
        ofstream hist("hist.txt",ios::app);
        // srand((unsigned)time(NULL));

        rnd rnd;

        int N = 200;
        wektor wxN[N];

        double a,b;
        double dl=1.;
        bool czy=false;
        double drg=0, drg2=0, srdrg, srdrg2;
        double pol=0, pol2=0, srpol, srpol2;
        int t=0, stop=100;
        int i=0, czas_uw=1;
        
        while(i<N && t<=stop)
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

                while(i<N && t<=stop)
                {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    czy=0;
                    wxN[i].poczatek.x=wxN[i-1].koniec.x;
                    wxN[i].poczatek.y=wxN[i-1].koniec.y;

                    a=rnd.gauss(0,dl);
                    b=rnd.gauss(0,dl);

                    wxN[i].koniec.x=wxN[i].poczatek.x+a;
                    wxN[i].koniec.y=wxN[i].poczatek.y+b;

                    /// czerwone kreski
                    al_draw_line(300+10*wxN[i].poczatek.x, 300+10*wxN[i].poczatek.y, 300+10*wxN[i].koniec.x, 300+10*wxN[i].koniec.y, al_map_rgb(255,0,0), 2);  

                    for (int j = 0; j < i-1; j++)
                    {
                        if (wektoryxxxx(wxN[i],wxN[j]))
                            {
                                czy=true;
                                czas_uw++;
                                break;
                            }
                    }

                    if(!czy)
                    {   
                        pol+=wxN[i].dlugosc;
                        srpol=pol/i;
                        pol2+=wxN[i].dlugosc*wxN[i].dlugosc;
                        srpol2=pol2/i;

                        drg+=sqrt((wxN[i].x)*(wxN[i].x)+(wxN[i].y)*(wxN[i].y));
                        srdrg=drg/i;
                        drg2+=(wxN[i].x)*(wxN[i].x)+(wxN[i].y)*(wxN[i].y);
                        srdrg2=drg2/i;
                        
                        hist << czas_uw << endl;
                        czas_uw=1;
                        i++;
                    }
                    /// reset
                    t++;
                    czy = 0;

                    plik << t << "\t" << srpol << "\t" << srdrg << "\t" << srpol2 << "\t" << srdrg2 << endl;

                    for (int k = 0; k < i; k++){///rysuje wszystkie pozostałe, żeby nic nie znikało
                        al_draw_line(300+10*wxN[k].poczatek.x, 300+10*wxN[k].poczatek.y, 300+10*wxN[k].koniec.x, 300+10*wxN[k].koniec.y, al_map_rgb(0,255,0), 1);
                    }

                    al_flip_display();
                }

                al_flip_display();
            }
        }

        std::list<std::vector<double> > punkt;
        std::vector<double> q(2);
        q[0] = wxN[0].poczatek.x;
        q[1] = wxN[0].poczatek.y;
        punkt.push_back(q);
        for (int n = 0; n < i; n++){
            std::vector<double> p(2);
            p[0] = wxN[n].koniec.x;
            p[1] = wxN[n].koniec.y;
            punkt.push_back(p);
        }

        // szukanie najmniejszego okręgu
        typedef std::list<std::vector<double> >::const_iterator PointIterator; 
        typedef std::vector<double>::const_iterator CoordIterator;
        typedef Miniball::Miniball <Miniball::CoordAccessor<PointIterator, CoordIterator> > MB;
        MB mb(2, punkt.begin(), punkt.end());

        float srodek[2];
        float promien = sqrt(mb.squared_radius());
        const double* center = mb.center();
        for (int n = 0; n < 2; ++n, ++center) srodek[n] = *center;

        cout << 300+10*srodek[0] << "\t" << 300+10*srodek[1] << "\t" << 10*promien << endl;

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_circle(300+10*srodek[0], 300+10*srodek[1], 10*promien, al_map_rgb(1, 1, 0), 1);
        for (int k = 0; k < i; k++){
            al_draw_line(300+10*wxN[k].poczatek.x, 300+10*wxN[k].poczatek.y, 300+10*wxN[k].koniec.x, 300+10*wxN[k].koniec.y, al_map_rgb(0,255,0), 1);
        }
        al_flip_display();

        hist << czas_uw << endl;
        plik.close();
        hist.close();

        sleep(5);

        al_destroy_display(ekran);
    }

    if(!tryb)
    {}

    return 0;
}