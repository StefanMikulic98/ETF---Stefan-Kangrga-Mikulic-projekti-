#ifndef TITLE_H
#define TITLE_H

#include <string>
using namespace std;

class Title {

public:
	Title();
	Title(string name);

	void setSize(int size);
	void setName(string title);

	int getSize();
	string getName();
	
private:
	string title;
	int size;
};
#endif