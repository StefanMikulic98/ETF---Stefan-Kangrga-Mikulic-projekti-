#include "SistemJednacina.h"

SistemJednacina::SistemJednacina(const string& ime) : ime_(ime) {
	for (int i = 0; i < 6; i++) {
		resenje_Zajdel_.push_back(0);
	}
}

void SistemJednacina::citajJednacinu(string unos){
	Jednacina* jednacina = new Jednacina();

	jednacina->citajJednacinu(unos);
	jednacine_.push_back(jednacina);

}

void SistemJednacina::pisi() const{
	for (Jednacina* jednacina : jednacine_) {
		jednacina->pisi();
	}
}

void SistemJednacina::pivotiranje(int broj_kolone){
	int maks = broj_kolone;
	for (int i = maks; i+1< 5; i++) {
		if (abs(jednacine_[maks]->koeficijenti_[broj_kolone]) < abs(jednacine_[i + 1]->koeficijenti_[broj_kolone])) {
			maks = i + 1;
		}
	}
	if (maks != broj_kolone) {
		Jednacina* jednacina = new Jednacina();
		jednacina->koeficijenti_.push_back(jednacine_[maks]->koeficijenti_[0]);
		jednacina->koeficijenti_.push_back(jednacine_[maks]->koeficijenti_[1]);
		jednacina->koeficijenti_.push_back(jednacine_[maks]->koeficijenti_[2]);
		jednacina->koeficijenti_.push_back(jednacine_[maks]->koeficijenti_[3]);
		jednacina->koeficijenti_.push_back(jednacine_[maks]->koeficijenti_[4]);
		jednacina->koeficijenti_.push_back(jednacine_[maks]->koeficijenti_[5]);

		jednacine_[maks]->koeficijenti_[0] = jednacine_[broj_kolone]->koeficijenti_[0];
		jednacine_[maks]->koeficijenti_[1] = jednacine_[broj_kolone]->koeficijenti_[1];
		jednacine_[maks]->koeficijenti_[2] = jednacine_[broj_kolone]->koeficijenti_[2];
		jednacine_[maks]->koeficijenti_[3] = jednacine_[broj_kolone]->koeficijenti_[3];
		jednacine_[maks]->koeficijenti_[4] = jednacine_[broj_kolone]->koeficijenti_[4];
		jednacine_[maks]->koeficijenti_[5] = jednacine_[broj_kolone]->koeficijenti_[5];

		jednacine_[broj_kolone]->koeficijenti_[0] = jednacina->koeficijenti_[0];
		jednacine_[broj_kolone]->koeficijenti_[0] = jednacina->koeficijenti_[1];
		jednacine_[broj_kolone]->koeficijenti_[0] = jednacina->koeficijenti_[2];
		jednacine_[broj_kolone]->koeficijenti_[0] = jednacina->koeficijenti_[3];
		jednacine_[broj_kolone]->koeficijenti_[0] = jednacina->koeficijenti_[4];
		jednacine_[broj_kolone]->koeficijenti_[0] = jednacina->koeficijenti_[5];

	}
}

void SistemJednacina::noviMultiplikatori(int broj_vrste){
	int pocetni_red = broj_vrste - 1;
	for (int i = broj_vrste; i < 5; i++) {
		multiplikatori_.push_back(jednacine_[i]->koeficijenti_[broj_vrste-1]/ jednacine_[pocetni_red]->koeficijenti_[broj_vrste-1]);
	}
}

void SistemJednacina::gausMetoda(){
	int i = 5;
	/*pivotiranje(0);
	noviMultiplikatori(1);
	novaMatrica(1);
	multiplikatori_.clear();
	pisi();

	pivotiranje(1);
	noviMultiplikatori(2);
	novaMatrica(2);
	multiplikatori_.clear();
	pisi();

	pivotiranje(2);
	noviMultiplikatori(3);
	novaMatrica(3);
	multiplikatori_.clear();
	pisi();

	pivotiranje(3);
	noviMultiplikatori(4);
	novaMatrica(4);
	multiplikatori_.clear();
	pisi();*/
	for (int i = 0; i < 4; i++) {
		pivotiranje(i);
		noviMultiplikatori(i+1);
		novaMatrica(i + 1);
		cout << endl;
		cout << i+1 << ".korak";
		cout << "======================================================" << endl;
		cout << "multiplikatori: ";
		for (double mp : multiplikatori_) {
			cout << mp << "  ";
		}
		cout << endl;
		cout << "======================================================" << endl;
		multiplikatori_.clear();
		cout << "======================================================" << endl;
		pisi();
		cout << "======================================================" << endl;
	}
	nalazenjeResenja();

	cout << "Resenje sistema jednacina su: ";
	for (double R : resenje_Gaus_) {
		cout << "x" << i-- << ":" << R << "  ";
	}
	cout << endl;

}

void SistemJednacina::gausZajdelovaMetoda(){
	noviSistemJednacina();
	nalazenjeResenja2();
	
}

void SistemJednacina::noviSistemJednacina(){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (i != j) {
				if (j == 5) {
					jednacine_[i]->koeficijenti_[j] = jednacine_[i]->koeficijenti_[j] / jednacine_[i]->koeficijenti_[i];
				}
				else {
					jednacine_[i]->koeficijenti_[j] = (jednacine_[i]->koeficijenti_[j] / jednacine_[i]->koeficijenti_[i])*(-1);
				}
			}			
		}
		jednacine_[i]->koeficijenti_[i] = 0;
	}
}

void SistemJednacina::nalazenjeResenja2(){
	bool radi = true;
	double x1, x2, x3, x4, x5;
	
	while (radi) {
		for (double R : resenje_Zajdel_) {
			cout << R << "  ";
		}
		cout << endl;
		x1 = resenje_Zajdel_[1];
		x2 = resenje_Zajdel_[2];
		x3 = resenje_Zajdel_[3];
		x4 = resenje_Zajdel_[4];
		x5 = resenje_Zajdel_[5];

		for (int i = 1; i <= 5; i++) {
			resenje_Zajdel_[i] = jednacine_[i-1]->koeficijenti_[0] * resenje_Zajdel_[1] + jednacine_[i - 1]->koeficijenti_[1] * resenje_Zajdel_[2] + jednacine_[i - 1]->koeficijenti_[2] * resenje_Zajdel_[3] + jednacine_[i - 1]->koeficijenti_[3] * resenje_Zajdel_[4] + jednacine_[i - 1]->koeficijenti_[4] * resenje_Zajdel_[5] + jednacine_[i - 1]->koeficijenti_[5];
		}
		//if (x1 == resenje_Zajdel_[1] && x2 == resenje_Zajdel_[2] && x3 == resenje_Zajdel_[3] && x4 == resenje_Zajdel_[4] && x5 == resenje_Zajdel_[5]) {
		//	radi = false;
		//}

		if (uporedi(resenje_Zajdel_[1], x1) && uporedi(resenje_Zajdel_[2], x2) && uporedi(resenje_Zajdel_[3], x3) && uporedi(resenje_Zajdel_[4], x4) && uporedi(resenje_Zajdel_[5], x5)) {
			radi = false;
		}

		resenje_Zajdel_[0]++;
		//for (double R : resenje_Zajdel_) {
		//	cout << R << "  ";
		//}
		//cout << endl;
	
	}
}

bool SistemJednacina::uporedi(double trenutni_rezultat, double prethodni_rezultat, double razlika){
	if (fabs(trenutni_rezultat - prethodni_rezultat) < razlika) {
		return true;
	}
	return false;
}

void SistemJednacina::novaMatrica(int broj_vrste){
	int pocetni_red = broj_vrste-1, k=0;
	for (int i = broj_vrste; i < 5; i++) {
		for (int j = broj_vrste-1; j < 6; j++) {
			jednacine_[i]->koeficijenti_[j] = jednacine_[i]->koeficijenti_[j] - multiplikatori_[k] * jednacine_[pocetni_red]->koeficijenti_[j];
		}
		k++;
	}
}

void SistemJednacina::nalazenjeResenja(){
	double sum = 0;
	
	for (int i = 4; i >= 0; i--) {
		sum = 0;
		if (i == 4) {
			resenje_Gaus_.push_back(jednacine_[i]->koeficijenti_[i+1] / jednacine_[i]->koeficijenti_[i]);
		}
		else {
			for (int j = i+1, k=1; j<5 ; j++,k++ ) {
				sum += (jednacine_[i]->koeficijenti_[j]* resenje_Gaus_[(int)(resenje_Gaus_.size())-k]);
			}
			resenje_Gaus_.push_back(1/(jednacine_[i]->koeficijenti_[i])*(jednacine_[i]->koeficijenti_[5] -sum));
		}
	}
}
