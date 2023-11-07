#include "SistemJednacina.h"

#include "string"
using namespace std;

int main() {
	string nova_jednacina;
	int izbor;
	bool radi = true;

	SistemJednacina* sistem_jednacina = new SistemJednacina();

	while (radi) {
		cout << "Odaberite opciju:\n1. Unos nove jednacine\n2. Kraj unosa " << endl;
		cin >> izbor;

		try {
			switch (izbor) {
			case 1: {  //Ucitavanje nove jednacine
				string putanja;

				//cout << izbor << "\nNova jednacina => " << endl;    //////////////////////////
				//cin >> nova_jednacina;								/////////////////////////

				//sistem_jednacina->citajJednacinu(nova_jednacina);////////////////////////////////////
				sistem_jednacina->citajJednacinu("9.5i1-2.5i2-2i4=12");
				sistem_jednacina->citajJednacinu("-2.5i1+11i2-3.5i3-5i5=-16");
				sistem_jednacina->citajJednacinu("-3.5i2+15.5i3-4i5=14");
				sistem_jednacina->citajJednacinu("-2i1+7i4-3i5=10");
				sistem_jednacina->citajJednacinu("-5i2-4i3-3i4+12i5=-30");
				sistem_jednacina->pisi();
				cout << "\nZavrsen unos " << endl;
				
				break;
			}
			case 2: {  //Kraj unosa
				radi = false;
				break;
			}
			default:
				cout << "Netacan unos\n\n";
			}
		}
		catch (string izuzetak) {
			//prihvatiGresku(izuzetak);
		}
	}

	if (izbor) { radi = true; }

	while (radi) {
		cout << "=======================================================" << endl;
		cout << "Molimo Vas, odaberite nacin resavanja zadatka:\n1. Gausova metoda eliminacije sa izborom pivota\n2. Gaus-Zajdenlova metoda\n3. Prikaz prosirene matrice sistema jednacine\n4. Kraj programa\n " << endl;
		cout << "=======================================================" << endl << endl;
		cin >> izbor;  //izbor opcija

		switch (izbor) {

		case 1: {		//Gausova metoda eliminacije sa izborom pivota
			sistem_jednacina->gausMetoda();
			//sistem_jednacina->pisi();
			break;
		}
		case 2: {		//Gaus-Zajdenlova metoda
			sistem_jednacina->gausZajdelovaMetoda();
			break;
		}	
		case 3: {		//Prikaz proserene matrice koeficijenata
			sistem_jednacina->pisi();
			break;
		}
		case 4: {		//Kraj programa
			cout << "Kraj programa" << endl;
			radi = false;
			break;
		}
		default:
			cout << "Netacan unos\n\n";
		}
	}

	delete sistem_jednacina;

	return 0;
}