#ifndef SISTEMJEDNACINA_H
#define SISTEMJEDNACINA_H

#include "Jednacina.h"

#include <cmath>
#include <vector>
using namespace std;

class SistemJednacina {
public:
	SistemJednacina(const string& ime = "sistem jednacina");

	void citajJednacinu(string unos);
	void pisi() const;

	void pivotiranje(int);
	void noviMultiplikatori(int);
	void gausMetoda();
	void novaMatrica(int);
	void nalazenjeResenja();

	void gausZajdelovaMetoda();
	void noviSistemJednacina();
	void nalazenjeResenja2();
	bool uporedi(double trenutni_rezultat, double prethodni_rezultat, double razlika=0.00001f);

private:
	vector<Jednacina*> jednacine_;
	string ime_;
	vector<double> multiplikatori_;
	vector<double> resenje_Gaus_;
	vector<double> resenje_Zajdel_;
};

#endif
