#include "Linija.h"   //bitan je redosled ukljucivanja h. fajlova, pa je nemoguce u ovom slucaju uraditi alfabetskim redosledom
#include "Stajaliste.h"
#include "GradskiPrevoz.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void prihvatiGresku(string izuzetak) {
	cout << "Greska: " << izuzetak << endl;
}


// Funkcija koja poredi tacan izlaz sa ocekivanim izlazom za odgovarajucu opciju
void proveraIzlaza(const string& tekst_izlaz, const string& oznaka, const string& oznaka_1, const int& izbor) {
	
	try {
		switch (izbor) {
		case 1: {       //provera ispisa osnovnih informacija za dato stajaliste
			ifstream tacan_izlaz("stajaliste_" + oznaka + ".txt"); 
			stringstream ss_izlaz;
			ss_izlaz << tacan_izlaz.rdbuf(); tacan_izlaz.close();
			string tacan_tekst = ss_izlaz.str();

			if (tacan_tekst != "" && tacan_tekst == tekst_izlaz) {
				cout << "Generisan je fajl student_stajaliste_" + oznaka + ".txt sa osnovnim informacijama o stajalistu " + oznaka + "." << endl << endl;
			}
			else {
				throw string("Nije uspesno generian fajl za stajaliste" + oznaka + ".");
			}
			break;
		}
		case 2: {		  //provera ispisa osnovnih informacija za datu liniju
			ifstream tacan_izlaz("linija_" + oznaka + ".txt");
			stringstream ss_izlaz;
			ss_izlaz << tacan_izlaz.rdbuf(); tacan_izlaz.close();
			string tacan_tekst = ss_izlaz.str();

			if (tacan_tekst != "" && tacan_tekst == tekst_izlaz) {
				cout << "Generisan je fajl student_linija_" + oznaka + ".txt sa osnovnim informacijama o liniji " + oznaka + "." << endl << endl;
			}
			else {
				throw string("Nije uspesno generian fajl za liniju" + oznaka + ".");
			}
			break;
		}
		case 3: {		  //provera ispisa statistickih informacija za datu liniju
			ifstream tacan_izlaz("statistika_" + oznaka + ".txt");
			stringstream ss_izlaz;
			ss_izlaz << tacan_izlaz.rdbuf(); tacan_izlaz.close();
			string tacan_tekst = ss_izlaz.str();

			if (tacan_tekst != "" && tacan_tekst == tekst_izlaz) {
				cout << "Generisan je fajl student_statistika_" + oznaka + ".txt sa statistickim informacijama o liniji" + oznaka + "." << endl << endl;
			}
			else {
				throw string("Nije uspesno generian fajl za statatistiku linije" + oznaka + ".");
			}
			break;
		}
		case 4: {		//za sada samo ispisuje da je generisan fajl, bez provere!

			//ifstream tacan_izlaz("putanja_" + oznaka + "_" + oznaka_1 + ".txt");
			//stringstream ss_izlaz;
			//ss_izlaz << tacan_izlaz.rdbuf(); tacan_izlaz.close();
			//string tacan_tekst = ss_izlaz.str();

			//if (tacan_tekst != "" && tacan_tekst == tekst_izlaz) {  
			cout << "Generisan je fajl putanje od stajalista oznake " + oznaka + " do stajalista oznake " + oznaka_1 + " \n( student_putanja_" + oznaka + "_" + oznaka_1 + ")." << endl << endl;
			//}
			//else {
			//	//throw string("Nije uspesno generian fajl za pitanju stajalista od " + oznaka + "do " + oznaka_1 + ".");
			//}
			break;
		}
		}
	}
	catch (string izuzetak) {
		prihvatiGresku(izuzetak);
	}
}


int main() {
	string tekst_izlaz;
	int izbor;
	bool radi = true;

	GradskiPrevoz* gradska_mreza = new GradskiPrevoz();

	while (radi) {
		cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:\n1. Ucitavanje podataka o mrezi gradskog prevoza\n0. Kraj rada " << endl;
		cin >> izbor;

		try {
			switch (izbor) {
			case 1: {  //Ucitavanje stajalista i linije
				string putanja;

				cout << izbor << "\nMolimo Vas, unesite ime fajla sa stajalistima:" << endl;
				cin >> putanja;   // ime ulaznog fajla za stajalista

				ifstream input1(putanja + ".txt");
				stringstream ss1;
				ss1 << input1.rdbuf(); input1.close();
				string stajalista_ulaz = ss1.str();

				if (stajalista_ulaz.empty()) {
					throw string("Pogresno uneto ime fajla sa stajalistima!\n\n");
				}

				gradska_mreza->ucitajStajaliste(stajalista_ulaz);

				cout << "Molimo Vas, unesite ime fajla sa linijama gradskog prevoza:" << endl;
				cin >> putanja;   // ime ulaznog fajla za linije

				ifstream input2(putanja + ".txt");
				stringstream ss2;
				ss2 << input2.rdbuf(); input2.close();
				string linije_ulaz = ss2.str();

				if (linije_ulaz.empty()) {
					throw string("Pogresno uneto ime fajla sa linijama!\n\n");
				}

				gradska_mreza->ucitajLinije(linije_ulaz);

				cout << "Mreza gradskog prevoza je uspesno ucitana.\n\n";
				radi = false;  //zaustavlja se obilazenje prve petlje nakon uspesnog ucitavanja stajalista i linije
				break;
			}
			case 0: {  //Kraj programa
				cout << "Kraj programa" << endl;
				radi = false;
				delete gradska_mreza;
				break;
			}
			default:
				cout << "Netacan unos\n\n";
			}
		}
		catch (string izuzetak) {
			prihvatiGresku(izuzetak);
		}
	}

	if(izbor){ radi = true; }

	while (radi) {
		cout << "=======================================================" << endl;
		cout << "Molimo Vas, odaberite opciju:\n1. Prikaz informacija o stajalistu\n2. Prikaz osnovnih informacija o liniji gradskog prevoza\n3. Prikaz statistickih informacija o liniji gradskog prevoza\n4. Pronalazak putanje izmedju dva stajalista\n0. Kraj rada" << endl;
		cout << "=======================================================" << endl << endl;
		cin >> izbor;  //izbor opcija

		//try {
			switch (izbor) {

			case 1: {		//Prikaz informacija o stajalistu
				int oznaka;

				cout << "Molimo Vas, unesite oznaku stajalista cije osnovne informacije zelite da prikazete:" << endl;
				cin >> oznaka; 
				tekst_izlaz = gradska_mreza->prikazStajalista(oznaka);

				ofstream moj_izlaz("student_stajaliste_" + to_string(oznaka) + ".txt");   //formiranje izlaznog fajla 
				moj_izlaz << tekst_izlaz; moj_izlaz.close();
				proveraIzlaza(tekst_izlaz, to_string(oznaka), "", izbor);
				break;
			}
			case 2: {		//Prikaz informacija o liniji
				string oznaka;

				cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete:" << endl;
				cin >> oznaka;
				tekst_izlaz = gradska_mreza->prikazLinija(oznaka);

				ofstream moj_izlaz("student_linija_" + oznaka + ".txt");   //formiranje izlaznog fajla 
				moj_izlaz << tekst_izlaz; moj_izlaz.close();
				proveraIzlaza(tekst_izlaz, oznaka, "", izbor);
				break;
			}
			case 3: {		//Prikaz statistickih informacija o liniji
				string oznaka;
				cout << "Molimo Vas, unesite oznaku linije cije statisticke informacije zelite da prikazete:" << endl;
				cin >> oznaka;
				tekst_izlaz = gradska_mreza->prikazStatistika(oznaka);

				ofstream moj_izlaz("student_statistika_" + oznaka + ".txt");    //formiranje izlaznog fajla 
				moj_izlaz << tekst_izlaz; moj_izlaz.close();
				proveraIzlaza(tekst_izlaz, oznaka, "", izbor);
				break;
			}
			case 4: {		//Prikaz putanje izmedju zadatih stajalista
				int oznaka1, oznaka2;
				/*
				for (int i = 0; i != gradska_mreza->stajalista_.size(); i++) {
					for (int j = 0; j != gradska_mreza->stajalista_.size(); j++) {
						if (gradska_mreza->stajalista_[i] != gradska_mreza->stajalista_[j] ) {
							try {
							oznaka1 = gradska_mreza->stajalista_[i]->dohvatiSifru();
							oznaka2 = gradska_mreza->stajalista_[j]->dohvatiSifru();
							tekst_izlaz = gradska_mreza->prikazPutanje(oznaka1, oznaka2);
							
							ofstream moj_izlaz("student_putanja_" + to_string(oznaka1) + "_" + to_string(oznaka2) + ".txt");    //formiranje izlaznog fajla 
							moj_izlaz << tekst_izlaz; moj_izlaz.close();
							proveraIzlaza(tekst_izlaz, to_string(oznaka1), to_string(oznaka2), izbor);
							}
							catch (string izuzetak) {
								prihvatiGresku(izuzetak);
							}
						}
					}
				}*/
				///*
				cout << "Molimo Vas, unesite oznaku pocetnog stajalista:" << endl;
				cin >> oznaka1;
				cout << "Molimo Vas, unesite oznaku krajnjeg stajalista:" << endl;
				cin >> oznaka2;
				tekst_izlaz = gradska_mreza->prikazPutanje(oznaka1, oznaka2);
				
				ofstream moj_izlaz("student_putanja_" + to_string(oznaka1) + "_" + to_string(oznaka2) + ".txt");    //formiranje izlaznog fajla 
				moj_izlaz << tekst_izlaz; moj_izlaz.close();
				proveraIzlaza(tekst_izlaz, to_string(oznaka1), to_string(oznaka2), izbor);//*/
				break;
			}
			case 0:		//Kraj programa
				cout << "Kraj programa" << endl;
				radi = false;
				break;
				exit(-3);
			default:
				cout << "Netacan unos\n\n";

			}
		//}
		//catch (string izuzetak) {
		//	prihvatiGresku(izuzetak);
		//}
	}

delete gradska_mreza;

return 0;
}