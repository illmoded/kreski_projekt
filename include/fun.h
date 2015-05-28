#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#ifndef FUN_
#define FUN_

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

wektor iloczynwektorowy(wektor w1, wektor w2);
double iloczynskalarny(wektor w1, wektor w2);
bool wektoryxx(wektor w1, wektor w2);
bool wektoryxxxx(wektor w1, wektor w2);
int losowa_ab(int a, int b);

#endif