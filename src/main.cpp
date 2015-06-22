#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <list>
#include "fun.h"
#include "rnd.h"
#include "Miniball.h"

using namespace std;

void kreska(wektor w, ALLEGRO_COLOR kolor, float szer = 2, bool skala = true)
{
    float x1 = w.poczatek.x;
    float x2 = w.koniec.x;
    float y1 = w.poczatek.y;
    float y2 = w.koniec.y;

    if(skala)   al_draw_line(300+10*x1, 300+10*y1, 300+10*x2, 300+10*y2, kolor, szer);
    else        al_draw_line(x1,y1,x2,y2,kolor,szer);
}

int main(int argc, char const *argv[])
{
    int tryb;   // 0 - tekstowy
    tryb = 1;   // 1 - graficzny

    ///// GRAFICZNY /////
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

        ALLEGRO_COLOR red=al_map_rgb(255,0,0);
        ALLEGRO_COLOR green=al_map_rgb(0,255,0);
        ALLEGRO_COLOR blue=al_map_rgb(0,0,255);

        fstream plik("kreski.txt",fstream::out);
        ofstream hist("czas_uw.txt",ios::app);
        ofstream prom("promien.txt",ios::app);
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
                    kreska(wxN[i],red);

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
                        wxN[i].oblicz_xyz_z_puktow(wxN[i].poczatek, wxN[i].koniec);
                        // pol+=wxN[i].dlugosc;
                        pol+=sqrt(wxN[i].koniec.x*wxN[i].koniec.x+wxN[i].koniec.y*wxN[i].koniec.y);
                        srpol=pol/i;

                        // pol2+=wxN[i].dlugosc*wxN[i].dlugosc;
                        pol2+=wxN[i].koniec.x*wxN[i].koniec.x+wxN[i].koniec.y*wxN[i].koniec.y;
                        srpol2=pol2/i;

                        // drg+=sqrt((wxN[i].x)*(wxN[i].x)+(wxN[i].y)*(wxN[i].y));
                        drg=wxN[i].dlugosc;
                        srdrg=drg/i;

                        // drg2+=(wxN[i].x)*(wxN[i].x)+(wxN[i].y)*(wxN[i].y);
                        drg2+=wxN[i].dlugosc*wxN[i].dlugosc;
                        srdrg2=drg2/i;
                        
                        hist << czas_uw << endl;
                        czas_uw=1;
                        i++;
                    }

                    /// reset
                    czy = 0;
                    t++;                    

                    plik << t << "\t" << srpol << "\t" << srdrg << "\t" << srpol2 << "\t" << srdrg2 << endl;

                    for (int k = 0; k < i; k++){
                        kreska(wxN[k], green, 1);
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

        okrag o = oblicz_okrag(punkt);
        okrag op = przyblizenieokregu(wxN,N);

        al_clear_to_color(al_map_rgb(0,0,0));
        // al_draw_circle(300+10*o.x, 300+10*o.y, 10*o.r, blue, 1);
        // al_draw_circle(300+10*op.x, 300+10*op.y, 10*op.r, blue, 1);
        cout << op.x << "\t" << op.y << "\t" << op.r << endl;
        prom << 300+10*o.x << "\t" << 300+10*o.y << "\t" << 10*o.r << endl;

        for (int k = 0; k < i; k++){
            kreska(wxN[k],green,1);
        }
        al_flip_display();

        hist << czas_uw << endl;
        hist.close();
        prom.close();
        plik.close();
        al_rest(1);

        al_destroy_display(ekran);
    }

    ///// TEKSTOWY /////
    if(!tryb)
    {
        fstream plik("kreski.txt",fstream::out);
        ofstream hist("czas_uw.txt",ios::app);
        ofstream prom("promien.txt",ios::app);
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
        
        {   
            wxN[i].poczatek.x=0;
            wxN[i].poczatek.y=0;

            wxN[i].koniec.x=wxN[i].poczatek.x+rnd.gauss(0,dl);
            wxN[i].koniec.y=wxN[i].poczatek.y+rnd.gauss(0,dl);

            i = 1;

                while(i<N && t<=stop)
                {
                    czy=0;
                    wxN[i].poczatek.x=wxN[i-1].koniec.x;
                    wxN[i].poczatek.y=wxN[i-1].koniec.y;

                    a=rnd.gauss(0,dl);
                    b=rnd.gauss(0,dl);

                    wxN[i].koniec.x=wxN[i].poczatek.x+a;
                    wxN[i].koniec.y=wxN[i].poczatek.y+b;

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
                        wxN[i].oblicz_xyz_z_puktow(wxN[i].poczatek, wxN[i].koniec);
                        // pol+=wxN[i].dlugosc;
                        pol+=sqrt(wxN[i].koniec.x*wxN[i].koniec.x+wxN[i].koniec.y*wxN[i].koniec.y);
                        srpol=pol/i;

                        // pol2+=wxN[i].dlugosc*wxN[i].dlugosc;
                        pol2+=wxN[i].koniec.x*wxN[i].koniec.x+wxN[i].koniec.y*wxN[i].koniec.y;
                        srpol2=pol2/i;

                        // drg+=sqrt((wxN[i].x)*(wxN[i].x)+(wxN[i].y)*(wxN[i].y));
                        drg=wxN[i].dlugosc;
                        srdrg=drg/i;

                        // drg2+=(wxN[i].x)*(wxN[i].x)+(wxN[i].y)*(wxN[i].y);
                        drg2+=wxN[i].dlugosc*wxN[i].dlugosc;
                        srdrg2=drg2/i;
                        
                        hist << czas_uw << endl;
                        czas_uw=1;
                        i++;
                    }

                    /// reset
                    czy = 0;
                    t++;                    

                    plik << t << "\t" << srpol << "\t" << srdrg << "\t" << srpol2 << "\t" << srdrg2 << endl;
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

        okrag o = oblicz_okrag(punkt);
        prom << 300+10*o.x << "\t" << 300+10*o.y << "\t" << 10*o.r << endl;

        hist << czas_uw << endl;
        hist.close();
        prom.close();
        plik.close();
    }

    return 0;
}