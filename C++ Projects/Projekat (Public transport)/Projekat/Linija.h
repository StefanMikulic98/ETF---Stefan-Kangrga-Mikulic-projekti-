#ifndef LINIJA_H
#define LINIJA_H

#include <string>
#include <vector>

using namespace std;

class Linija {

public:
	Linija(const string& oznaka_linije);
	~Linija();

	Linija(const Linija&) = delete;
	Linija(Linija&&) = delete;


	string dohvatiOznaku() const;
	
	vector<int> smer_A;  //redni brojevi stajalista kojim su uneti u vektor stajalista u klasi "GradskiPrevoz"
	vector<int> smer_B;  //redni brojevi stajalista kojim su uneti u vektor stajalista u klasi "GradskiPrevoz"

private:
	string oznaka_linije_;
	
};
#endif
