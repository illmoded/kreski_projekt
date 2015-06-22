#include "fun.h"
#include <math.h>
#include "Miniball.h"
#include <vector>
#include <list>

void wektor::oblicz_xyz_z_puktow(punkt p1, punkt p2)
{
	poczatek.x=p1.x;
	poczatek.y=p1.y;
	poczatek.z=p1.z;

	koniec.x=p2.x;
	koniec.y=p2.y;
	koniec.z=p2.z;

	x=p2.x-p1.x;
	y=p2.y-p1.y;
	z=p2.z-p1.z;

	dlugosc=sqrt(x*x+y*y+z*z);
}

okrag oblicz_okrag(std::list<std::vector<double> > punkt)
{	
	okrag o;
    typedef std::list<std::vector<double> >::const_iterator PointIterator; 
    typedef std::vector<double>::const_iterator CoordIterator;
    typedef Miniball::Miniball <Miniball::CoordAccessor<PointIterator, CoordIterator> > MB;
    MB mb(2, punkt.begin(), punkt.end());

    float srodek[2];
    float promien = sqrt(mb.squared_radius());
    const double* center = mb.center();
    for (int n = 0; n < 2; ++n, ++center) srodek[n] = *center;

    o.x=srodek[0];
	o.y=srodek[1];
	o.r=promien;

    // al_clear_to_color(al_map_rgb(0,0,0));
    // al_draw_circle(300+10*srodek[0], 300+10*srodek[1], 10*promien, al_map_rgb(255, 255, 0), 1);

    return o;
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

    return ils < 1e-5;
}

bool wektoryxxxx(wektor w1, wektor w2)
{
	return (wektoryxx(w1, w2) && wektoryxx(w2, w1));
}

okrag przyblizenieokregu(wektor odcinki[], int N)
{
	okrag o;
	//szukanie ekstremow
	double xmax,xmin,ymax,ymin;
	xmin=xmax=ymin=ymax=0;

	for (int i = 0; i < N; i++)
	{
		if (odcinki[N].poczatek.x<xmin)
		{
			xmin=odcinki[N].poczatek.x;
		}
		if (odcinki[N].poczatek.x>xmax)
		{
			xmax=odcinki[N].poczatek.x;
		}
		if (odcinki[N].poczatek.y<ymin)
		{
			ymin=odcinki[N].poczatek.y;
		}
		if (odcinki[N].poczatek.y>ymax)
		{
			ymax=odcinki[N].poczatek.y;
		}
	}
	o.x=(xmax+xmin)/2.;
	o.y=(ymin+ymax)/2.;

	
	double X = abs(xmax-xmin)/2.;
	double Y = abs(ymin-ymax)/2.;
	double r1=0;

	if (abs(xmax-xmin)>abs(ymax-ymin))
	{
		r1 = Y;		
	}
	else
	{
		r1 = X;
	}

	double r2 = sqrt(X*X+Y*Y);
	o.r=(r1+r2)/2.;

	return o;
}