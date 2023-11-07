#include "Linija.h"

Linija::Linija(const string& oznaka_linije) : oznaka_linije_(oznaka_linije) {}

Linija::~Linija(){
	smer_A.clear();
	smer_B.clear();
}

string Linija::dohvatiOznaku() const {
	return oznaka_linije_;
}
