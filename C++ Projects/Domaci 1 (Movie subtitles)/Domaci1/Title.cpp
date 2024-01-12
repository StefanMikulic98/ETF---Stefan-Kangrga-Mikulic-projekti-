#include "Title.h"
#include <iostream>
using namespace std;

Title::Title() {			
	this->title = "";
	this->size = 0;
}

Title::Title(string name)
{
	this->title = name;
	this->size = 0;
}

void Title::setSize(int size) {
	this->size = size;
}

void Title::setName(string title){
	this->title = title;
}

int Title::getSize()
{
	return this->size;
}

string Title::getName()
{
	return this->title;
}

