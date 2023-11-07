#ifndef SUBTITLEDITOR_H
#define SUBTITLEDITOR_H

#include <string>
#include "Section.h"
using namespace std;

struct listOfSection {
	Section* section;
	listOfSection* next;
	listOfSection* prev;
};

struct Selection {
	int start, end;
	Selection* next;
	Selection* prev;
};

class SubtitleEditor {

public:
	SubtitleEditor();
	~SubtitleEditor();

	int loadSubtitles(string subtitles);
	string saveSubtitles();
	void insertSubtitle(int start, int length, string text);
	void deleteSubtitles();

	void addToSelection(int start, int end);
	void deselect();

	void boldText(int start, int end);
	void italicText(int start, int end);
	void underlineText(int start, int end);
	void removeStyle();

	void shiftForward(int ms);
	void shiftBackward(int ms);
	
	void merge(string subtitles);
	void fixLongLines(int max);
	void fixLongTime(int ms);

	int checkError(int H, int M, int S, int MS);
	string readTitle(string subtitles, int& pos);
	int readHours(string subtitles, int& pos);
	int readMinutesSeconds(string subtitles, int& pos);
	int readMiliseconds(string subtitles, int& pos);
	int checkEmptyRows(string subtitles, int& pos);
	string saveNumber(int time, string title);
	string saveMNumber(int time,string title);
	void addTime(int ms, int& H, int& M, int& S, int& MS);
	int checkTime(int start);
	void findstart(int indicator, int start);
	void findend(int indicator, int end);
	void undo();
	
private:
	listOfSection *first, *last, *current, *current1, *last1;
	Selection* sfirst, * scurrent, * slast;
};

#endif
