#include "fun.h"


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

double losowa_ab(double a, double b)
{
	return a+(b-a)*rand()/RAND_MAX;
}
