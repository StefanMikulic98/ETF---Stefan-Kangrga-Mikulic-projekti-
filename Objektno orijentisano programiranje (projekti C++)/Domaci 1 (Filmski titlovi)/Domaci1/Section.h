#ifndef SECTION_H
#define SECTION_H

#include "Time.h"
#include "Title.h"

class Section {

public:
	Section(int count, Time* starttime, Time* endtime, Title* title);
	~Section();

	void setNumber(int count);

	Time* getStarttime();
	Time* getEndtime();
	Title* getTitle();
	int getNumber();


private:
	int count;
	Time* starttime;
	Time* endtime;
	Title* title;
};


#endif

