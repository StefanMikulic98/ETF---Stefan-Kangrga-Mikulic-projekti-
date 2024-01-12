#include "Section.h"

Section::Section(int count, Time* starttime, Time* endtime, Title* title)
{
	this->count = count;
	this->starttime = starttime;
	this->endtime = endtime;
	this->title = title;
}

Section::~Section() {
	delete this->starttime;
	delete this->endtime;
	delete this->title;
}

void Section::setNumber(int count)
{
	this->count = count;
}

Time* Section::getStarttime()
{
	return starttime;
}

Time* Section::getEndtime()
{
	return endtime;
}

Title* Section::getTitle()
{
	return title;
}

int Section::getNumber()
{
	return this->count;
}