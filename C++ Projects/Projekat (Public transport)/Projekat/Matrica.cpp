#include "Matrica.h"

const int N = 999999;

Matrica::Matrica(const int& broj_redova, const int& broj_kolona) : broj_redova_(broj_redova), broj_kolona_(broj_kolona){
	matrica = vector<vector<int>>(broj_redova_,vector<int> (broj_kolona_));
	for (int i = 0; i < this->broj_redova_; i++) {
		for (int j = 0; j < this->broj_kolona_; j++) {
			matrica[i][j] = N;  //popunjava se matricu sa brojem N
		}
	}
}

Matrica::~Matrica(){
	putanja_.clear();
	matrica.clear();
}

void Matrica::popuniMatricu(vector<Linija*>& linije){  //popunjava matricu sa rednim brojevima stajalista za odgovarajuce linije, ako ne stigne do kraja kolone onda tamo ostaju polja sa brojem N
	int i = 0, j = 0, k;

	for (Linija* linija : linije) {
		for ( k = 0, j=0; k < linija->smer_A.size(); j++, k++) {
			matrica[i][j] = linija->smer_A[k];
		}
		for ( k = 0, j ; k < linija->smer_B.size() ; j++, k++) {
			matrica[i][j] = linija->smer_B[k];
		}
		i++;
	}
}

void Matrica::potragaStajalista(const int& pocetak, const int& kraj){
	int k = 0;
	bool pronadjen = false;	 //=================================================

	for (int i = 0; i <= broj_redova_; i++) {  //nalazenje pocetnog stajalista u matrici i popunja red "putanja_" po principi (i1(broj reda), j1(broj kolone), pocetak(redni broj pocetnog stajalista u listi stajalista gradskog prevoza))
		for (int j = 0; j <= broj_kolona_; j++) {
			if (matrica[i][j] == pocetak) {
				putanja_.push_back(i);
				putanja_.push_back(j);
				putanja_.push_back(pocetak);
				for ( j ; j < broj_kolona_; j++) {	 //=================================================zbog 23-154
					if (matrica[i][j] == kraj ) {	 //=================================================
						putanja_.push_back(i);	 //=================================================
						putanja_.push_back(j);	 //=================================================
						putanja_.push_back(kraj);	 //=================================================
						pronadjen = true;	 //=================================================
						break;  //=================================================
					}	 //=================================================
					if (j == broj_kolona_ - 1) {//=================================================
						break;//=================================================
					}//=================================================
				}	 //=================================================
				break;
			}
			if (j == broj_kolona_-1) {
				break;
			}
		}
		if (!putanja_.empty()) {
			break;
		}
		if (i == broj_redova_-1) {
			break;
		}
	}

	if (!pronadjen) {//=================================================
		for (int i = 0; i <= broj_redova_; i++) {  //Nalazenje krajnjeg stajalista u matrici i dopunjava red "putanja_" po principi (i1(broj reda), j1(broj kolone), pocetak(redni broj pocetnog stajalista u listi stajalista gradskog prevoza),i2(broj reda), j2(broj kolone), kraj(redni broj krajnjeg stajalista u listi stajalista gradskog prevoza))
			for (int j = 0; j <= broj_kolona_; j++) {
				if (matrica[i][j] == kraj) {
					putanja_.push_back(i);
					putanja_.push_back(j);
					putanja_.push_back(kraj);
					for (int j = 0; j < broj_kolona_; j++) {  // prilikom nalazenja krajneg stajalista u nekom redu, u tom istom redu se gleda da li ima i pocetno stajaliste, ako ima onda se azuira pozicija pocetnog stajalista u "putanja_" radi lakseg ispisa u strategiji1 (bez presedanja) 
						if (matrica[i][j] == pocetak && j < putanja_[4]) {
							putanja_[0] = i;
							putanja_[1] = j;
						}
					}
					break;
				}
				if (j == broj_kolona_ - 1) {
					break;
				}
			}
			if (putanja_.size() == 6) {
				break;
			}
			if (i == broj_redova_ - 1) {
				break;
			}
		}
	}//=================================================

	if (putanja_[5] == 4 && putanja_[4] == 0) {	 //putanja_[1] == putanja_[4]================================================= zbog stajalista 24 koja se nalazi na pocetku
		novaPotragaKrajnjegStajalista();	 //=================================================
	}	 //=================================================
}

void Matrica::novaPotragaPocetnogStajalista(){  //ako je pocetno stajaliste na nezgodnom mestu, trazi se isto stajaliste u matrici i azuira se "putanja_"
	int i = putanja_[0] + 1;  //=================================================
	//int j = putanja_[4];
	//int kraj = putanja_[5];
	int pocetak = putanja_[2];  //=================================================

	//nalazenje pocetnog stajalista u matrici
	/*for (j; j <= broj_kolona_; j++) {
		if (matrica[i][j] == pocetak && j < putanja_[4]) {
			putanja_[0] = i;
			putanja_[1] = j;
			break;
		}
		if (j == broj_kolona_ - 1) {
			break;
		}
	}*/
	for (i; i <= broj_redova_; i++) {   //=================================================
		for (int j=0; j <= broj_kolona_; j++) {  //=================================================
			if (matrica[i][j] == pocetak) {  //=================================================
				putanja_[0] = i;  //=================================================
				putanja_[1] = j;  //=================================================
				putanja_.push_back(N);  //=================================================
				break;  //=================================================
			}  //=================================================
			if (putanja_.size() == 7) {  //=================================================
				break;  //=================================================
			}  //=================================================
			if (j == broj_kolona_ - 1) {  //=================================================
				//j = 0;  //=================================================
				break;  //=================================================
			}  //=================================================
		}  //=================================================
		if (putanja_.size() == 7) {  //=================================================
			break;  //=================================================
		}  //=================================================
		if (i == broj_redova_ - 1) {  //=================================================
			break;  //=================================================
		}  //=================================================
	}  //=================================================
	if (putanja_.size() == 7) { //=================================================
		putanja_.pop_back();  //=================================================
	} //=================================================
}

void Matrica::novaPotragaKrajnjegStajalista(){  //ako je krajnje stajaliste na nezgodnom mestu, trazi se isto stajaliste u matrici i azuira se "putanja_"
	int i = putanja_[3];
	int j = putanja_[4] + 2;
	int kraj = putanja_[5];
	int pocetak = putanja_[2];

	for ( i ; i <= broj_redova_; i++) {  //nalazenje krajnjeg stajalista u matrici
		for ( j ; j <= broj_kolona_; j++) {
			if (matrica[i][j] == kraj) {
				putanja_[3] = i;
				putanja_[4] = j;
				for (int j = 0; j < broj_kolona_; j++) {
					if (matrica[i][j] == pocetak && j < putanja_[4]) {
						putanja_[0] = i;
						putanja_[1] = j; 
						break;
					}
				}
				putanja_.push_back(N); //samo radi kasnije provere dole da li se azuirala "putanja_" da bi se prekinula petlja 
				break;
			}
			if (putanja_.size() == 7) {
				break;
			}
			if (j == broj_kolona_ - 1) {
				j = 0;
				break;
			}
		}
		if (putanja_.size() == 7) {
			break;
		}
		if (i == broj_redova_ - 1) {
			break;
		}
	}
	putanja_.pop_back();
}

bool Matrica::potragaPutanjeStrategija1(){  //trazi ako ima putanja bez presedanja
	bool potraga = false;

	if (putanja_[0] == putanja_[3]) {
		if (putanja_[1] > putanja_[4]) {  //ako se pocetno stajaliste nalazi levlje od krajnjeg u kolonama, trazim novu poziciju krajnjeg stajalista jer busevi idu samo u pravcu --> a ne <-- u matrici
			if (putanja_[5] == 20 || putanja_[5] == 21 || putanja_[5] == 22) { //=================================================
				novaPotragaPocetnogStajalista(); //=================================================
			} //=================================================
			else { //=================================================
				novaPotragaKrajnjegStajalista();
			} //=================================================
		} //=================================================
		if (putanja_[0] == putanja_[3] && putanja_[1] < putanja_[4]) {  //ako ima putanje bez presedanja, menja se "putanja_" po zamisljenom redosledu radi lakseg ispisa
			int i_1 = putanja_[0];    
			int j_1 = putanja_[1];
			int j_2 = putanja_[4];
			putanja_.clear();
			for (j_1; j_1 <= j_2; j_1++) {
				putanja_.push_back(matrica[i_1][j_1]);
			}
			
			putanja_.push_front(i_1);
			putanja_.push_front(1);
			potraga = true;
		}
	}   // "putanja_" na kraju izgleda    ( 1(broj strategije), redni broj linije u gradskom prevozu, ... redni brrojevi stajalista...)

	return potraga;
}

bool Matrica::potragaPutanjeStrategija2(){  //velika sansa za greske prilikom testiranja, ovde se gleda putanja sa jednim presedanjem i menja se skroz "putanja_" ako se nadje neka putanja
	bool potraga = false;
	int i_1 = putanja_.front();
	int i_2 = putanja_[3];
	int pocetna_kolona, krajnja_kolona;
	deque<int>::iterator i;

	for (int j = putanja_[1]; matrica[i_1][j] != N && j <= broj_kolona_ - 1; j++) { 
		for (int k = 0; matrica[i_2][k] != N && k <= broj_kolona_ - 1 && k < putanja_[4]; k++) {
			if (matrica[i_1][j] == matrica[i_2][k]) {
				pocetna_kolona = k;
				krajnja_kolona = putanja_[4];
				putanja_.erase(putanja_.begin() + 4);
				putanja_.erase(putanja_.begin() + 4);
				for (pocetna_kolona; pocetna_kolona <= krajnja_kolona; pocetna_kolona++) {
					putanja_.push_back(matrica[i_2][pocetna_kolona]);      //na modifikovani "putanja_" dodaju se redni brojeve stajalista u prvoj liniji
				}
				
				i = putanja_.begin() + 3;
				putanja_.insert(i, N);
				pocetna_kolona = putanja_[1];
				putanja_.erase(putanja_.begin() + 1);
				putanja_.erase(putanja_.begin() + 1);
				krajnja_kolona = j;

				for (krajnja_kolona; pocetna_kolona <= krajnja_kolona; krajnja_kolona--) {
					i = putanja_.begin() + 1;
					putanja_.insert(i, matrica[i_1][krajnja_kolona]);  //na istoj poziciji se obrnutim redom ubacuju redne brojeve stajalista u drugoj liniji
				}
				
				potraga = true;
				putanja_.push_front(2);  //oznacava tip strategije prilikom ispisa
				break;
			}
			if (k == broj_kolona_-1) {
				break;
			}
		}
		if (potraga) { break; }
		if (j == broj_kolona_ - 1) {
			break;
		}
	}  //putanja_ na kraju izgleda    ( 2(broj strategije), redni broj prve linije u gradskom prevozu, ... redni brrojevi stajalista..., N(da bi naglasio mesto presedanja), redni broj druge linije u gradskom prevozu, ... redni brrojevi stajalista...)
	return potraga;
}
///*
bool Matrica::potragaPutanjeStrategija3(){   // za sada nebitna funkcija, odnosila za na potragu za putanju za dva presedanja
	bool potraga = false;
	int i_1 = putanja_[3];
	int i_2 = putanja_.front();
	int n = putanja_[1];
	int kraj = putanja_[5];

	for (int j = putanja_[4]; matrica[i_1][j] != N && j <= broj_kolona_ - 1; j++) { 
		for (int k =putanja_[1]; matrica[i_2][k] != N && k <= broj_kolona_ - 1; k++) {
			if (matrica[i_1][j] == matrica[i_2][k]) {
				putanja_.clear();

				putanja_.push_back(i_2);
				for (int i = n; i <= k; i++) {
					putanja_.push_back(matrica[i_2][i]);
					//if (i == k - 1) {
					//	break;
					//}
				}

				putanja_.push_back(N);

				putanja_.push_back(i_1);
				for (int i = j; i < broj_kolona_ && matrica[i_1][i]!=N; i++) {
					putanja_.push_back(matrica[i_1][i]);
					if (i == broj_kolona_ - 1) {
						break;
					}
				}

				putanja_.push_back(N);

				putanja_.push_back(i_1);
				for (int i = 0; i < broj_kolona_ && matrica[i_1][i]!= kraj; i++) {
					putanja_.push_back(matrica[i_1][i]);
					if (i == broj_kolona_ - 1) {
						break;
					}
				}

				putanja_.push_back(kraj);
				putanja_.push_back(N);
				potraga=true;
				break;
			}
			if (putanja_.back() == N) {
				break;
			}
			if (k == broj_kolona_ - 1) {
				break;
			}
		}
		if (putanja_.back() == N) {
			break;
		}
		if (j == broj_redova_ - 1) {
			break;
		}
	}
	putanja_.push_front(3);
	return potraga;
}//*/

void Matrica::potragaPutanje(const int& pocetak, const int& kraj){  //u principu forsira se da se nadje putanja bez presedanja
	bool potraga = false;
	int brojac = 20;


	potragaStajalista(pocetak, kraj);  //popunjava "putanja_" samo sa pozicijama u matrici pocetnog i krajnjeg stajalista
	//potraga = potragaPutanjeStrategija1();  //trazi se putanja bez presedanja

	if (putanja_[2] == 4 && putanja_[5] == 1) {


	}
	else{
		potraga = potragaPutanjeStrategija1();  //trazi se putanja bez presedanja
		if (!potraga) {
			potraga = potragaPutanjeStrategija2();  //trazi se putanja sa jednim presedanja
		}

		//if (putanja_[2] ==4 && putanja_[5] ==1  && putanja_[3] < putanja_[0]) {  //putanja_[1] < 3 && putanja_[4] < 3  && putanja_[3] < putanja_[0]
		//	potragaPutanjeStrategija3();
		//}

		if (!potraga) {
			novaPotragaKrajnjegStajalista();  //trazi se nova pozicija krajnja tacka pa se ponovo trazi putanje, pokusao sam while petlju sa ponavljanjem od bar 20 puta ako ne nadje bas nikako putanju ali isbacuje mi greske tipa pristupa se poziciji vektora koji ne postoji (nisam jos ispratio gde bi to moglo da bude ali ima dosta mesta za gresaka takvog tipa)
			potraga = potragaPutanjeStrategija1();
			if (!potraga) {
				potraga = potragaPutanjeStrategija2();
			}
		}
	}

	//if (!potraga) {
	//	novaPotragaPocetnogStajalista();
	//	potraga = potragaPutanjeStrategija1();
	//}

	if (!potraga || putanja_[0]==3) {			// nije nadjena putanja izmedju zadatih stajalista
		throw string("Nije uspesno generian fajl za pitanju, jer nema date putanje za data stajalista.");
	}
}



