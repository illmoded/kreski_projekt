#ifndef _RND_H
#define _RND_H

#include "math.h"
#include "iostream"

class rnd
{
public:
	rnd();
	double jedn(double pocz, double kon);
	double unint(double pocz, double kon);
	double gauss(double x, double sigma);
	double expo(double lambda);
	double cauchy(double x, double gamma);
	double levy(double alfa);
};

rnd::rnd()
{
	srand((unsigned)time(NULL));
}

double rnd::jedn(double pocz=0, double kon=1)
{
	return pocz+(kon-pocz)*(double)rand()/RAND_MAX;
}

double rnd::unint(double pocz=0, double kon=1)
{
	return pocz+rand()%(int)(kon-pocz+1);
}

double rnd::gauss(double x=0, double sigma=1)
{
	double u1=rnd::jedn(1e-10);
	double u2=rnd::jedn();
	return x+sqrt(-2.*log(u1))*cos(2.0*M_PI*u2)*sigma;
}

double rnd::expo(double lambda=1)
{
	double F=rnd::jedn(0,1.-1e-10);
	return -log(1-F)/lambda;
}

double rnd::cauchy(double x=0, double gamma=1)
{
	double u=rnd::jedn();
	return x+tan(M_PI*(u-0.5))*gamma/2.;
}

double rnd::levy(double alfa = 1.)
{
    double T=rnd::jedn(-M_PI/2+1e-10,M_PI/2.-1e-10);
    double U=rnd::jedn(1e-10);
    double W=-log(U);
    double p1=sin(alfa*T)/pow(cos(T),1./alfa);
    double p2=cos(alfa*T-T)/W;
    return p1*pow(p2,(1.-alfa)/alfa);
}
#endif