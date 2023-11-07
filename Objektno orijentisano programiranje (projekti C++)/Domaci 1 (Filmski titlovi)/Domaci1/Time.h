#ifndef TIME_H
#define TIME_H

#define H_MIN 0
#define H_MAX 99
#define M_MIN 0
#define M_MAX 59
#define S_MIN 0
#define S_MAX 59
#define MS_MIN 0
#define MS_MAX 999

class Time {

public:
	Time();
	Time(int H, int M, int S, int MS);
	
	void setTime(int H, int M, int S, int MS);

	void shiftFor(int ms, int& H, int& M, int& S, int& MS);
	void shiftBack(int ms, int& H, int& M, int& S, int& MS);
	
	int getHours();
	int getMinutes();
	int getSeconds();
	int getMiliseconds();


private:
	int H, M, S, MS;
};

#endif
