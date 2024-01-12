#include "FSparser.h"

#include <sstream>
const string WHITESPACE = " \n\t\f\r\v";

void SplitFirstWord(string& input_string, string& firstword) {
	stringstream ss;
	size_t pos;

	// Obrisi space na pocetku (ako ima)
	pos = input_string.find_first_not_of(WHITESPACE);
	if (pos != string::npos)
		input_string = input_string.substr(pos);

	// Izdvoji prvu rec
	ss = stringstream(input_string);
	ss >> firstword;

	// Obrisi prvu rec i space pre druge reci
	input_string = input_string.substr(firstword.length());
	pos = input_string.find_first_not_of(WHITESPACE);
	if (pos != string::npos)
		input_string = input_string.substr(pos);
}

void SplitFirstLine(string& input_string, string& firstline){
	stringstream ss;
	size_t pos;

	pos = input_string.find("\\n");
	if (pos != string::npos) {
		firstline = input_string.substr(0, pos);
		input_string = input_string.substr(pos + 2);
	}
	else {
		firstline = input_string;
		input_string.clear();
	}
}

// Todo: make a common function with SplitFirstLine()
void SplitFirstFolder(string& input_path, string& firstfolder) {
	stringstream ss;
	size_t pos;

	pos = input_path.find("\\");
	if (pos != string::npos) {
		firstfolder = input_path.substr(0, pos);
		input_path = input_path.substr(pos + 1);
	}
	else {
		firstfolder = input_path;
		input_path.clear();
	}
}

void SplitNameExtension(string& name, string& extension) {
	size_t pos = name.find('.');

	if (pos != string::npos) {
		extension = name.substr(pos + 1);
		name = name.substr(0, pos);
	}
	else {
		// Nije nas briga da li je ekstenzija = exe, zato sto hvatamo gresku sa default metodama klase
		extension = "";
	}
}
