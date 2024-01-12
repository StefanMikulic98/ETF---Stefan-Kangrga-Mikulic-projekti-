#ifndef MATRICA_H
#define MATRICA_H

#include "GradskiPrevoz.h";

#include <deque>

class Matrica {

public:
	Matrica(const int& broj_redova, const int& broj_kolona);
	~Matrica();

	Matrica(const Matrica&) = delete;
	Matrica(Matrica&&) = delete;

	void popuniMatricu(vector<Linija*>& linije);  //popunjava matricu sa rednim brojevima stajalista za odgovarajuce linije
	void potragaStajalista(const int& pocetak, const int& kraj);  //trazi stajalista sa zadatim rednim brojevima u vektor stajalista gradskog prevoza u matrici
	void novaPotragaPocetnogStajalista();  //potraga za novom pozicijom pocetnog stajalista sa zadatim rednim brojem
	void novaPotragaKrajnjegStajalista();  //potraga za novom pozicijom krajnjeg stajalista sa zadatim rednim brojem
	void potragaPutanje(const int& pocetak, const int& kraj);  

	bool potragaPutanjeStrategija1();  //potraga  za putanjom od pocetnog do krajnjeg stajalista bez presedanja
	bool potragaPutanjeStrategija2();  //potraga  za putanjom od pocetnog do krajnjeg stajalista sa jednim presedanja
	bool potragaPutanjeStrategija3();

private:
	int broj_kolona_;
	int broj_redova_;
	vector <vector<int>> matrica;
	deque<int> putanja_;
	friend class GradskiPrevoz;
	
};

#endif