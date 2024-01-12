#include "Jednacina.h"

Jednacina::Jednacina(const string& ime) : ime_(ime) {}

void Jednacina::citajJednacinu(string unos){
	int poz = 0;
	int promenljiva = 1;
	string broj = "";
	float i;

	while (poz < unos.length()) {
		while (((unos[poz] >= '0' && unos[poz] <= '9') || unos[poz] == '.' || unos[poz] == '-') && poz < unos.length()) {
			broj += unos[poz];
			poz++;
		}
		if (poz >= unos.length()) { 
			while (promenljiva <= 5) {
				koeficijenti_.push_back(0);
				promenljiva++;
			}
			koeficijenti_.push_back(stod(broj));
			break; 
		}
		if (unos[poz+1] == promenljiva) {
			koeficijenti_.push_back(stod(broj));
			promenljiva++;
		}
		else {
			while ((int)(unos[poz + 1]-'0') > promenljiva) {
				koeficijenti_.push_back(0);
				promenljiva++;
			}
			koeficijenti_.push_back(stod(broj));
			promenljiva++;
		}
		poz += 3;
		broj = "";
		if(unos[poz-1] == '-'){ broj += '-'; }
	}
}

void Jednacina::pisi() const{
	for (float koeficijent : koeficijenti_) {
		cout << koeficijent << "	  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
}
