#ifndef GRADSKIPREVOZ_H
#define GRADSKIPREVOZ_H

#include "Linija.h"
#include "Stajaliste.h"
#include "Matrica.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

class GradskiPrevoz {

public:
	GradskiPrevoz(const string& ime= "gradska mreza"); 
	~GradskiPrevoz();

	GradskiPrevoz(const GradskiPrevoz&) = delete;
	GradskiPrevoz(GradskiPrevoz&&) = delete;

	void ucitajLinije(const string& linije_ulaz); 
	void ucitajStajaliste(const string& stajaliste_ulaz);
	string prikazStajalista(const int& oznaka);		//ispis 1.
	string prikazLinija(const string& oznaka);		//ispis 2.
	string prikazStatistika(const string& oznaka);	 //ispis 3.
	string prikazPutanje(const int& oznaka1, const int& oznaka2);	//ispis 4.

	void prikazStajalistaStrategija1(string& izlaz, const int& oznaka);  //strategije uvede radi lakseg uvodjenja novih nacina ispisa stajalista i linije (modifikacije)
	void prikazLinijaStrategija1(string& izlaz, const string& oznaka);
	void prikazStatistikaStrategija1(string& izlaz, const string& oznaka);
	
	void ucitajSmerA(Linija& linija, const string& linije_ulaz, const string& oznaka_linije, int& poz);
	void ucitajSmerB(Linija& linija, const string& linije_ulaz, const string& oznaka_linije, int& poz); 

	vector<Stajaliste*> stajalista_;
private:
	string ime_;
	//vector<Stajaliste*> stajalista_;  //vector svih stajalista koje se ucitaju sa ulaza
	vector<Linija*> linije_;  // lista svih linija koje se ucitaju sa ulaza

};
#endif