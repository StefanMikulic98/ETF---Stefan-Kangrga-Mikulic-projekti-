#ifndef JEDNACINA_H
#define JEDNACINA_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Jednacina {
public:
	Jednacina(const string& ime = "jednacina");

	void citajJednacinu(string unos);
	void pisi() const;
	vector<double> koeficijenti_;

private:
	string ime_;
};

#endif
#pragma once
