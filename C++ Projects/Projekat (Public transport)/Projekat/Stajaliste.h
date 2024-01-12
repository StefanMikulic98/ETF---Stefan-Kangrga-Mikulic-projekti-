#ifndef STAJALISTE_H
#define STAJALISTE_H

#include "Linija.h"

#include <string>
#include <vector>

using namespace std;

class Stajaliste {

public:
	Stajaliste(const int& sifra_stajalista, const string& naziv_stajalista);
	~Stajaliste();

	Stajaliste(const Stajaliste&) = delete;
	Stajaliste(Stajaliste&&) = delete;

	int dohvatiSifru() const;
	string dohvatiNaziv() const;

	vector<Linija*> linije_stajalista;  //vektor linija koje prolaze kroz stajaliste

private:
	int sifra_stajalista_;
	string naziv_stajalista_;
};

#endif