#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#ifndef kreski_
#define kreski_

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

// void wektor::oblicz_xyz_z_puktow(punkt p1, punkt p2);
wektor iloczynwektorowy(wektor w1, wektor w2);
double iloczynskalarny(wektor w1, wektor w2);
bool wejtoryxx(wektor w1, wektor w2);
double losowa_ab(double a, double b);

#endif