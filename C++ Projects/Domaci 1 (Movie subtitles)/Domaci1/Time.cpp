#include "Time.h"

Time::Time(){
	this->H = this->M = this->MS = this->S = 0;
}

Time::Time(int H, int M, int S, int MS){
	this->setTime(H, M, S, MS);
}

void Time::setTime(int H, int M, int S, int MS) {
	this->H = H >= H_MIN && H <= H_MAX ? H : H_MIN;
	this->M = M >= M_MIN && M <= M_MAX ? M : M_MIN;
	this->S = S >= S_MIN && S <= S_MAX ? S : S_MIN;
	this->MS = MS >= MS_MIN && MS <= MS_MAX ? MS : MS_MIN;
}

void Time::shiftFor(int ms, int& H, int& M, int& S, int& MS){
	int Timecurrent = 0;
	H = this->getHours();
	M = this->getMinutes();
	S = this->getSeconds();
	MS = this->getMiliseconds();

	Timecurrent = (H * 60 * 60 * 1000) + (M * 60 * 1000) + (S * 1000) + MS;
	Timecurrent += ms;
	
	H =(Timecurrent / (1000 * 60 * 60)) % 100;
	M = (Timecurrent / (1000 * 60)) % 60;
	S = (Timecurrent / 1000) % 60;
	MS = Timecurrent % 1000;

	this->setTime(H, M, S, MS);	
}

void Time::shiftBack(int ms, int& H, int& M, int& S, int& MS){
	int Timecurrent = 0;
	H = this->getHours();
	M = this->getMinutes();
	S = this->getSeconds();
	MS = this->getMiliseconds();

	Timecurrent = (H * 60 * 60 * 1000) + (M * 60 * 1000) + (S * 1000) + MS;
	Timecurrent -= ms;
	if (Timecurrent > 0) {
		H = (Timecurrent / (1000 * 60 * 60)) % 24;
		M = (Timecurrent / (1000 * 60)) % 60;
		S = (Timecurrent / 1000) % 60;
		MS = Timecurrent % 1000;

		this->setTime(H, M, S, MS);
	}
}

int Time::getHours(){
	return this->H;
}

int Time::getMinutes(){
	return this->M;
}

int Time::getSeconds(){
	return this->S;
}

int Time::getMiliseconds(){
	return this->MS;
}
