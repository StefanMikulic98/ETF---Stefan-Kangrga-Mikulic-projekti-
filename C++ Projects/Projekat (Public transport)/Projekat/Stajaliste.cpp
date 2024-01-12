#include "Stajaliste.h"

Stajaliste::Stajaliste(const int& sifra_stajalista, const string& naziv_stajalista) : sifra_stajalista_(sifra_stajalista), naziv_stajalista_(naziv_stajalista) {}

Stajaliste::~Stajaliste(){
	for (Linija* linija : linije_stajalista) {
		delete linija;
	}
	linije_stajalista.clear();
}

int Stajaliste::dohvatiSifru() const{
	return sifra_stajalista_;
}

string Stajaliste::dohvatiNaziv() const{
	return naziv_stajalista_;
}


