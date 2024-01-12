#include <cmath>
#include <iostream>
using namespace std;

bool uporedi(float trenutni_rezultat, float prethodni_rezultat) {
	if (fabs(trenutni_rezultat - prethodni_rezultat) < 0.000001f) {
		return true;
	}
	return false;
}

int main() {
	float q = 0.00000000000000000016022;
	float kB = 0.000000000000000000000013806;
	float Voc = 0.5;
	float T = 297;
	float Vmp_pocetno = 0.5;
	double pomocna_promenljiva = 0, prethodni_rezultat = 0;
	int broj_iteracije = 0;
	bool radi = true;

	cout << "Pocetna jednacina se moze tranformisati u:\n Vmp= " <<  (kB * T)/(2*q) << " * ( " << (q * Voc) / (kB * T) << " - ln( " << q / (kB * T) << "*Vmp))" << endl << endl;
	pomocna_promenljiva = Vmp_pocetno;

	cout << broj_iteracije << "		" << pomocna_promenljiva << endl;
	while (radi) {
		prethodni_rezultat = pomocna_promenljiva;
		pomocna_promenljiva = (kB * T) / (2 * q) *((q * Voc) / (kB * T) - log((q * pomocna_promenljiva) / (kB * T)));
		broj_iteracije++;
		cout << broj_iteracije << "		" << pomocna_promenljiva << endl;
		if (broj_iteracije == 10 || radi == uporedi(pomocna_promenljiva, prethodni_rezultat)) { break; }
	}

}