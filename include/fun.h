#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

#ifndef FUN_
#define FUN_

struct punkt
{
	double x;
	double y;
	double z;
};

struct okrag
{
	double x;
	double y;
	double r;
};

okrag oblicz_okrag(std::list<std::vector<double> > punkt);

class wektor
{
public:

	void oblicz_xyz_z_puktow(punkt p1, punkt p2);
	// wektor iloczynwektorowy(wektor w1, wektor w2);
	// double iloczynskalarny(wektor w1, wektor w2);

	punkt poczatek;
	punkt koniec;

	//jako swobodny
	double x;
	double y;
	double z;

	double dlugosc;
}; 

wektor iloczynwektorowy(wektor w1, wektor w2);
double iloczynskalarny(wektor w1, wektor w2);
bool wektoryxx(wektor w1, wektor w2);
bool wektoryxxxx(wektor w1, wektor w2);
okrag przyblizenieokregu(wektor odcinki[], int N);

#endif