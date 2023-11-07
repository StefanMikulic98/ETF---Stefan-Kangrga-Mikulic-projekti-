#include "GradskiPrevoz.h"

const int N = 999999;

GradskiPrevoz::GradskiPrevoz(const string& ime) : ime_(ime){}

GradskiPrevoz::~GradskiPrevoz(){
	for (Linija* linija : linije_) {
		delete linija;
	}
	linije_.clear();
	for (Stajaliste* stajaliste : stajalista_) {
		delete stajaliste;
	}
	stajalista_.clear();
}


void GradskiPrevoz::ucitajLinije(const string& linije_ulaz) {
	int poz = 0;
	int sifra_stajalista;
	string oznaka_linije;
	bool provera;

	while (poz < linije_ulaz.length()) {  //ucitava sve linije 
		oznaka_linije.clear();
		sifra_stajalista = 0;
		Linija* linija = nullptr;  //inicijalizacija pokazivaca i postavlajnje na NULLPTR, praksa na koje na fakultetu stalno naglasavaju radi pazljivog koriscenja pokazivaca

		while (poz < linije_ulaz.length() && linije_ulaz[poz] != ' ') {   //prvo se ucitava oznaka_linije 
			oznaka_linije += linije_ulaz[poz];
			poz++;
		}

		poz++;
		linija = new Linija(oznaka_linije);  //oznaka_linije ce biti dovoljno da se formira objekat klase linija

		ucitajSmerA(*linija, linije_ulaz, oznaka_linije, poz);  //ucitava smer_A novoformiranog objekta klase linije

		ucitajSmerB(*linija, linije_ulaz, oznaka_linije, poz);  //ucitava smer_B novoformiranog objekta klase linije

		linije_.push_back(linija); //Nakon ucitavanja linija se ubacuje u vektor linija "GradskogPrevoza"
	}
}

void GradskiPrevoz::ucitajStajaliste(const string& stajaliste_ulaz) {
	int poz = 0;
	int sifra_stajalista;
	string naziv_stajalista;

	while (poz < stajaliste_ulaz.length()) {   //ucitava sva stajalista 
		Stajaliste* stajaliste = nullptr;  //inicijalizacija pokazivaca i postavlajnje na NULLPTR
		naziv_stajalista.clear();  //prilikom ucitavanja novog stajalista, brise se string koji je imao naziv prethodnog stajalista
		sifra_stajalista = 0;

		while (stajaliste_ulaz[poz] != ' ') {    //prvo se ucitava sifra_stajalista 
			sifra_stajalista = 10 * sifra_stajalista + (stajaliste_ulaz[poz] - '0');
			poz++;
		}
		poz++;

		while (stajaliste_ulaz[poz] != '\n' && poz < stajaliste_ulaz.length()) {   //ucitava se naziv_stajalista    
			naziv_stajalista += stajaliste_ulaz[poz];
			poz++;
		}
		poz++;

		stajaliste = new Stajaliste(sifra_stajalista, naziv_stajalista); //formira se objekat klase Stajaliste

		stajalista_.push_back(stajaliste); // stajaliste se doda u vektor stajalista kod objekta klase "GradskiPrevoz"

	}
}

string GradskiPrevoz::prikazStajalista(const int& oznaka){ //Pravi tekst za izlaz za opciju ispisa informacija o stajalistu
	string izlaz="";

	prikazStajalistaStrategija1(izlaz, oznaka);  //Uvodim ove strategije, jer su mi rekli da predvidim novi nacin ispisa, tako da cu na odbrani lako dodati novi nacin ispisa uz pitanje koji nacin ispisa se zeli itd...
	
	return izlaz;
}

string GradskiPrevoz::prikazLinija(const string& oznaka){ //Pravi tekst za izlaz za opciju ispisa informacija o liniji
	string izlaz = "";
	
	prikazLinijaStrategija1(izlaz, oznaka);  //Uvodim ove strategije, jer su mi rekli da predvidim novi nacin ispisa, tako da cu na odbrani lako dodati novi nacin ispisa uz pitanje koji nacin ispisa se zeli itd...
	
	return izlaz;
}

string GradskiPrevoz::prikazStatistika(const string& oznaka){ //Pravi tekst za izlaz za opciju ispisa statistickih informacija o liniji, malo se zakomplikovalo jer imamo vektore rednih brojeva stajalista u vektoru stajalista "GradskiPrevoz" u smeru A i smeru B
	string izlaz = "";
	
	prikazStatistikaStrategija1(izlaz, oznaka);   //Uvodim ove strategije, jer su mi rekli da predvidim novi nacin ispisa, tako da cu na odbrani lako dodati novi nacin ispisa uz pitanje koji nacin ispisa se zeli itd...

	return izlaz;
}

string GradskiPrevoz::prikazPutanje(const int& oznaka1, const int& oznaka2){
	string izlaz = "";
	int maks_vrsta, maks_kolona = 0, pocetak = 0, kraj = 0;
	static int broj_kolona, i;
	Matrica* matrica = nullptr;
	bool putanja = false, greska = true;
	int strategija = 0;

	//prvo odredjujemo velicinu matrice na osnovu velicine vektora stajalista i linije
	maks_vrsta = linije_.size();
	for (Linija* linija : linije_) {  
		broj_kolona = linija->smer_A.size(); 
		broj_kolona += broj_kolona;
		if (broj_kolona > maks_kolona) {
			maks_kolona = broj_kolona;
		}
	}

	matrica = new Matrica(maks_vrsta, maks_kolona);
	matrica->popuniMatricu(linije_);  //popunjava matrice sa rednim brojevima stajalista za odgovarajuce linije u matrici

	for (Stajaliste* stajaliste : stajalista_) {  //odredjuje redni broj pocetnog stajalista
		if (oznaka1 == stajaliste->dohvatiSifru()) {
			greska = false;
			break;
		}
		pocetak++;
	}

	if (greska) {  //ako nije nadjeno stajaliste sa oznakom koja se trazi
		throw string("U listi stajalista gradskog prevoza ne postoji uneto stajaliste!\n\n");
	}

	for (Stajaliste* stajaliste : stajalista_) {  //odredjuje redni broj krajnjeg stajalista
		if (oznaka2 == stajaliste->dohvatiSifru()) {
			greska = false;
			break;
		}
		kraj++;
	}

	if (greska) {  //ako nije nadjeno stajaliste sa oznakom koja se trazi
		throw string("U listi stajalista gradskog prevoza ne postoji uneto stajaliste!\n\n");
	}

	matrica->potragaPutanje(pocetak, kraj);  //trazi se putanja

	strategija = matrica->putanja_[0];
	matrica->putanja_.pop_front();

	// ima dve strategije za pronalazak putanje pa samim tim i dva nacina ispisa
	if (strategija == 1) {
		izlaz.append("->" + linije_[matrica->putanja_[0]]->dohvatiOznaku() + "\n");
		for ( i = 1; i < matrica->putanja_.size(); i++) {
			if (i != 1) {  //================================================= jer ako je bus 0 i stajaliste 0, ne bi se ispisalo stajaliste!
				if (matrica->putanja_[i] != matrica->putanja_[i - 1]) {
					izlaz.append(to_string(stajalista_[matrica->putanja_[i]]->dohvatiSifru()) + " ");
				}
			}  //=================================================
			else {   //=================================================
				izlaz.append(to_string(stajalista_[matrica->putanja_[i]]->dohvatiSifru()) + " ");   //=================================================
			}   //=================================================
		}
		izlaz.pop_back();
	}

	if (strategija == 2) {
		izlaz.append("->" + linije_[matrica->putanja_[0]]->dohvatiOznaku() + "\n");
		for ( i = 1; i < matrica->putanja_.size() && matrica->putanja_[i] != N; i++) {
			if (i != 1) {  //================================================= jer ako je bus 0 i stajaliste 0, ne bi se ispisalo stajaliste!
				if (matrica->putanja_[i] != matrica->putanja_[i - 1]) {
					izlaz.append(to_string(stajalista_[matrica->putanja_[i]]->dohvatiSifru()) + " ");
				}
			}  //=================================================
			else {   //=================================================
				izlaz.append(to_string(stajalista_[matrica->putanja_[i]]->dohvatiSifru()) + " ");   //=================================================
			}
		}
		i++;
		izlaz.pop_back();
		izlaz.append("\n");
		izlaz.append("->" + linije_[matrica->putanja_[i]]->dohvatiOznaku() + "\n");
		i++;
		for ( i ; i < matrica->putanja_.size() && matrica->putanja_[i] != N; i++) {
			if (matrica->putanja_[i] != matrica->putanja_[i-1]) {
				izlaz.append(to_string(stajalista_[matrica->putanja_[i]]->dohvatiSifru()) + " ");
			}
			else {
				if (matrica->putanja_[i - 2] == N) {
					izlaz.append(to_string(stajalista_[matrica->putanja_[i]]->dohvatiSifru()) + " ");
				}
			}
		}
		izlaz.pop_back();
	}
	if (izlaz == "") {  //ako nije nadjeno stajaliste sa oznakom koja se trazi
		throw string("Ne postoji putanja izmedju dva uneta stajalista!\n\n");
	}

	return izlaz;
}

void GradskiPrevoz::prikazStajalistaStrategija1(string& izlaz, const int& oznaka){
	for (Stajaliste* stajaliste : stajalista_) {
		if (oznaka == stajaliste->dohvatiSifru()) {  //trazi stajaliste po vektoru stajalista "GradskogPrevoza" na osnovu oznake
			izlaz.append(to_string(stajaliste->dohvatiSifru()) + " " + stajaliste->dohvatiNaziv() + " [");

			for (Linija* linije_stajalista : stajaliste->linije_stajalista) { //ispisuje oznake svih linija koja prolaze kroz to stajaliste
				izlaz.append(linije_stajalista->dohvatiOznaku() + " ");
			}
			break;
		}
	}
	if (izlaz == "") {  //ako nije nadjeno stajaliste sa oznakom koja se trazi
		throw string("U listi stajalista gradskog prevoza ne postoji uneto stajaliste!\n\n");
	}
	izlaz.pop_back(); //brise poslednji razmak koji je nastao prilikom ispisivanja oznake linija
	izlaz.append("]");

}

void GradskiPrevoz::prikazLinijaStrategija1(string& izlaz, const string& oznaka){

	for (Linija* linija : linije_) {
		if (oznaka == linija->dohvatiOznaku()) {  //trazi liniju po listi linija "GradskogPrevoza" na osnovu oznake
			izlaz.append(oznaka + " " + stajalista_[linija->smer_A.front()]->dohvatiNaziv() + "->" + stajalista_[linija->smer_A.back()]->dohvatiNaziv() + "\n"); //U prvom redu mora biti ispisano oznaka linije i imena okretnice(dovoljno je naziv prvog i poslednjeg stajalista u smeru A npr)
			for (int pozicija_stajalista : linija->smer_A) {  //na osnovu pozicije stajalista u listi stajalista "GradskogPrevoza" pristupa stajalistu, smer A
				izlaz.append(to_string(stajalista_[pozicija_stajalista]->dohvatiSifru()) + " " + stajalista_[pozicija_stajalista]->dohvatiNaziv() + "\n");
			}

			for (int pozicija_stajalista : linija->smer_B) {// smer B
				izlaz.append(to_string(stajalista_[pozicija_stajalista]->dohvatiSifru()) + " " + stajalista_[pozicija_stajalista]->dohvatiNaziv() + "\n");
			}
			break;
		}
	}

	if (izlaz == "") {  //ako nije nadjeno linija sa oznakom koja se trazi
		throw string("U listi linija gradskog prevoza ne postoji uneta linija!\n\n");
	}

	izlaz.pop_back(); //brise poslednji '\n' jer na kraju ne ocekuju novi red...
}

void GradskiPrevoz::prikazStatistikaStrategija1(string& izlaz, const string& oznaka){
	vector<string> nazivi_linija;
	//vector<Linija*>::iterator polozaj;
	int brojac = 0, maks_brojac = 0;
	string maks_oznaka, pomocna_oznaka;

	for (Linija* linija : linije_) {
		if (oznaka == linija->dohvatiOznaku()) { //trazi liniju po listi linija "GradskogPrevoza" na osnovu oznake
			izlaz.append(linija->dohvatiOznaku() + "\n");
			for (int pozicija_stajalista : linija->smer_A) {  //posle nalazenje linije u vektor stringova se upisuju(nagomilaju) nazivi svih mogucih linija koja prolaze kroz stajalista u smeru A
				for (vector<Linija*>::iterator polozaj = stajalista_[pozicija_stajalista]->linije_stajalista.begin(); polozaj != stajalista_[pozicija_stajalista]->linije_stajalista.end(); polozaj++) {
					if ((*polozaj)->dohvatiOznaku() != oznaka) {
						nazivi_linija.push_back((*polozaj)->dohvatiOznaku());
					}
				}
			}
			for (int pozicija_stajalista : linija->smer_B) { // sad se u vektor stringova nagomilavaju nazivi linija koja prolaze kroz stajalista u smeru B
				for (vector<Linija*>::iterator polozaj = stajalista_[pozicija_stajalista]->linije_stajalista.begin(); polozaj != stajalista_[pozicija_stajalista]->linije_stajalista.end(); polozaj++) {
					if ((*polozaj)->dohvatiOznaku() != oznaka) {
						nazivi_linija.push_back((*polozaj)->dohvatiOznaku());
					}
				}
			}
		}
		break;
	}

	if (izlaz == "") {  //ako nije nadjeno stajaliste sa oznakom koja se trazi
		throw string("U listi stajalista gradskog prevoza ne postoji uneto stajaliste!\n\n");
	}

	sort(nazivi_linija.begin(), nazivi_linija.end()); //sortira nagomilane oznake linija, ima cak i ponavljanja oznaka istih linija, a;i cemo kasnije da prebrojavamo

	pomocna_oznaka = nazivi_linija[0];

	for (string naziv : nazivi_linija) { //Nalazenje linije sa kojom oznacena linija ima najvise zajednickih stajalista
		if (pomocna_oznaka != naziv) {
			if (brojac > maks_brojac) {
				maks_brojac = brojac;
				maks_oznaka = pomocna_oznaka;
			}
			pomocna_oznaka = naziv;
			brojac = 0;
		}
		brojac++;
	}
	if (brojac > maks_brojac) {
		maks_brojac = brojac;
		maks_oznaka = pomocna_oznaka;
	}

	size_t nova_velicina = nazivi_linija.size();

	for (size_t i = 0; i < nova_velicina; i++) {  //Uklanjanje oznaka linije koje se ponavljaju
		for (size_t j = i + 1; j < nova_velicina; j++) {
			if (nazivi_linija[i] == nazivi_linija[j]) {
				nazivi_linija.erase(nazivi_linija.begin() + j);
				nova_velicina = nazivi_linija.size();
				j--;
			}
		}
	}

	for (string naziv : nazivi_linija) { //ispis svih linija sa kojom data linija ima zajednicka stajalista
		izlaz.append(naziv + " ");
	}
	izlaz.pop_back(); //uklanja visak " " koji nam ne treba
	izlaz.append("\n" + maks_oznaka);  // ispis linija sa kojom data linija ima najvise zajednickih stajalista

}

void GradskiPrevoz::ucitajSmerA(Linija& linija, const string& linije_ulaz, const string& oznaka_linije, int& poz) {
	int sifra_stajalista;
	vector<Stajaliste*>::iterator polozaj; //redni broj stajalista ciji se objekat nalazi u listu staalista "GradskogPrevoza"
	vector<Linija*>::iterator polozaj1;
	int i;

	while (poz < linije_ulaz.length() && linije_ulaz[poz-1] != '#') {
		sifra_stajalista = 0; //mora da se resetuju sifra_stajalista i i("i" i ne mora jer ce biti ionako "pregazen") prilikom ucitavanja novog stajalista
		i = 0;

		while (linije_ulaz[poz] != ' ' && linije_ulaz[poz] != '#' && poz < linije_ulaz.length()) {
			sifra_stajalista = 10 * sifra_stajalista + (linije_ulaz[poz] - '0');
			poz++;
		}

		bool provera = false;
		for (polozaj = stajalista_.begin(); polozaj != stajalista_.end(); polozaj++) {
			if (sifra_stajalista == (*polozaj)->dohvatiSifru()) { //provera dal je stajaliste vec ucitana sa takvom sifrom i da je vec uneta u vektor stajalista u klasi "GradskiPrevoz"
				i = distance(stajalista_.begin(), polozaj); //Jedan od nacina konverzije iz iteratora u int koje sam nasao na internetu, i  dohvatam redni broj stajalista koji se nalazi u vektor stajalista gradskog prevoza
				linija.smer_A.push_back(i);  //nakon te provere u polje "smer_A" se dodaje to stajaliste jer je validno( tj. postoji)

				//posto tekuca autobuska linija prolazi kroz stajaliste XXX, sada se gleda da li je u objektu klase "stajaliste" za konkretno stajaliste XXX uneto u vektor "linije_stajalista", ako nije, ubacicemo sada
				for (Linija* linije_stajalista : (*polozaj)->linije_stajalista) {
					if (oznaka_linije == linije_stajalista->dohvatiOznaku()) {
						provera = true;
					}
				}
				if (!provera) {  //prilikom ubacivanja linije u vektor linija koja prolazi kroz stajaliste, gledacemo da bude sortirano da bi se lakse kasnije ispisivalo u ispisu linija
					for (polozaj1 = (*polozaj)->linije_stajalista.begin(); (polozaj1 != (*polozaj)->linije_stajalista.end()) && (oznaka_linije > (*polozaj1)->dohvatiOznaku()); polozaj1++) {}
					(*polozaj)->linije_stajalista.insert(polozaj1, &linija);
				}
				break;
			}
		}
		poz++;
	}
}

//Isto kao kod funkcije "ucitajSmerA", tako da nisam dodavao iste komentare, jedina je razlika sto ucitavanje stajalista ne ide do '#' nego do '\n'!
void GradskiPrevoz::ucitajSmerB(Linija& linija, const string& linije_ulaz, const string& oznaka_linije, int& poz) {
	int sifra_stajalista;
	vector<Stajaliste*>::iterator polozaj; 
	vector<Linija*>::iterator polozaj1;
	int i;

	while (poz < linije_ulaz.length() && linije_ulaz[poz-1] != '\n') {
		sifra_stajalista = 0;
		i = 0;

		while (linije_ulaz[poz] != ' ' && poz < linije_ulaz.length() && linije_ulaz[poz] != '\n') {
			sifra_stajalista = 10 * sifra_stajalista + (linije_ulaz[poz] - '0');
			poz++;
		}

		bool provera = false;
		for (polozaj = stajalista_.begin(); polozaj != stajalista_.end(); polozaj++) {
			if (sifra_stajalista == (*polozaj)->dohvatiSifru()) {
				i = distance(stajalista_.begin(), polozaj);
				linija.smer_B.push_back(i);

				for (Linija* linije_stajalista : (*polozaj)->linije_stajalista) {
					if (oznaka_linije == linije_stajalista->dohvatiOznaku()) {
						provera = true;
					}
				}
				if (!provera) { 
					for (polozaj1 = (*polozaj)->linije_stajalista.begin(); (polozaj1 != (*polozaj)->linije_stajalista.end()) && (oznaka_linije > (*polozaj1)->dohvatiOznaku()); polozaj1++) {}
					(*polozaj)->linije_stajalista.insert(polozaj1, &linija);
				}
				break;
			}
		}
		poz++;
	}
}



