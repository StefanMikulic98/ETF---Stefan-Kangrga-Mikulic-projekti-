#include "SubtitleEditor.h"
#include <iostream>
using namespace std;

SubtitleEditor::SubtitleEditor() {
	this->first = this->last = this->current = this->current1 = this->last1 = nullptr;
	this->sfirst = this->slast = this->scurrent = nullptr;
}

SubtitleEditor::~SubtitleEditor() {
	while (this->first != nullptr) {
		listOfSection* old = this->first;
		this->first = this->first->next;
		delete old->section;
		delete old;
	}
	this->first = this->last = this->current = this->current1 = this->last1 = nullptr;
}

int SubtitleEditor::loadSubtitles(string subtitles)
{
	bool i = true;
	int pos = 0;
	int enumber = 0;
	while (pos < subtitles.length()) {
		Section* section = nullptr;
		string greska = "";
		int size = 0;
		size_t text_size = 0;
		int H = 0; int M = 0; int S = 0; int MS = 0;
		int number = 0;
		while ( pos < subtitles.length() && subtitles[pos] != '\n') {
			if (subtitles[pos] >= '9' && subtitles[pos] <= '0') {
				i = false;
				pos++;
				break;
			}
			else {
				number = 10 * number + (subtitles[pos] - '0');
				pos++;
			}
		}
		pos++;

		while ( pos < subtitles.length() && subtitles[pos] != '\n' && subtitles[pos] != '-') {
			H = readHours(subtitles, pos);
			M = readMinutesSeconds(subtitles, pos);
			S = readMinutesSeconds(subtitles, pos);
			MS = readMiliseconds(subtitles, pos);
		}
		if (checkError(H, M, S, MS) == 1) {
			i = false;
		}
		Time* starttime = new Time(H, M, S, MS);

		for (; pos < subtitles.length() && (subtitles[pos] == '-' || subtitles[pos] == '>' || subtitles[pos] == ' '); pos++);
		while (pos < subtitles.length() && subtitles[pos] != '\n' && subtitles[pos] <= '9' && subtitles[pos] >= '0') {
			H = readHours(subtitles, pos);
			M = readMinutesSeconds(subtitles, pos);
			S = readMinutesSeconds(subtitles, pos);
			MS = readMiliseconds(subtitles, pos);
		}
		if (checkError(H, M, S, MS) == 1) {
			i = false;
		}
		Time* endtime = new Time(H, M, S, MS);

		string text = readTitle(subtitles, pos);
		if (greska == text) {
			i = false;
		}

		int erows = checkEmptyRows(subtitles, pos);
		if (erows == 1) {
			i = false;
		}
		else text += "\n\n";

		Title* title = new Title(text);

		if (i) {
			section = new Section(number, starttime, endtime, title);

			listOfSection* element = new listOfSection();
			element->section = section;
			element->next = nullptr;
			element->prev = nullptr;

			if (!this->first) {
				this->first = this->last = this->current = element;
			}
			else {
				element->prev = this->last;
				this->last->next = element;
				this->last = element;
			}
			
			text_size = text.length();
			size = static_cast<int>(text_size);
			element->section->getTitle()->setSize(size);
			
		}
		else {
			enumber = number;
			break;
		}
	}
	if (i) {
		return -1;
	}
	else return enumber;
}

string SubtitleEditor::saveSubtitles()
{
	string title="";
	int i = 0;
	int H = 0;	int M = 0;	int S = 0;	int MS = 0;

	this->current = this->first;
	while (this->current != nullptr) {
		title.append(to_string(this->current->section->getNumber()));
		title.append("\n");
		H = this->current->section->getStarttime()->getHours();
		M = this->current->section->getStarttime()->getMinutes();
		S = this->current->section->getStarttime()->getSeconds();
		MS = this->current->section->getStarttime()->getMiliseconds();

		title.append(saveNumber(H, title));
		title.append(":");
		title.append(saveNumber(M, title));
		title.append(":");
		title.append(saveNumber(S, title));
		title.append(",");
		title.append(saveMNumber(MS, title));

		title.append(" --> ");

		H = this->current->section->getEndtime()->getHours();
		M = this->current->section->getEndtime()->getMinutes();
		S = this->current->section->getEndtime()->getSeconds();
		MS = this->current->section->getEndtime()->getMiliseconds();

		title.append(saveNumber(H, title));
		title.append(":");
		title.append(saveNumber(M, title));
		title.append(":");
		title.append(saveNumber(S, title));
		title.append(",");
		title.append(saveMNumber(MS, title));

		title.append("\n");
		title += this->current->section->getTitle()->getName(); 

		this->current = this->current->next;

	}
	return title;
}

void SubtitleEditor::insertSubtitle(int start, int length, string text) {
	Section* section = nullptr;
	int H = 0; int M = 0; int S = 0; int MS = 0; int number = 1; int i = 0; bool find = true;

	addTime(start, H, M, S, MS);
	Time* starttime = new Time(H, M, S, MS);
	addTime(length, H, M, S, MS);
	Time* endtime = new Time(H, M, S, MS);

	text += "\n";
	Title* title = new Title(text);

	section = new Section(number, starttime, endtime, title);		

	listOfSection* element = new listOfSection();
	element->section = section;
	element->next = nullptr;
	element->prev = nullptr;

	this->current = this->first;

	while (find) {
		i = checkTime(start);		
		if (i) {
			if (this->current->prev != nullptr) {			
				element->next = this->current;
				element->prev = this->current->prev;
				this->current->prev->next = element;
				this->current->prev = element;
				element->section->setNumber(number);
				find = false;
				
				i = this->current->section->getNumber();
				i += 1;
				this->current->section->setNumber(i);
			}
			else {
				element->next = this->current;
				this->current->prev = element;
				find = false;
			}
		}
		number++;
		this->current = this->current->next;
	}
	
	while (this->current) {			
		i = this->current->section->getNumber();
		i += 1;
		this->current->section->setNumber(i);
		this->current = this->current->next;
	}

	if (!this->first) {
		this->first = this->last = this->current = element;
	}
}

void SubtitleEditor::deleteSubtitles() {
	
	int start = 0;
	int end = 0;
	int i = 0;
	int count = 0;

	this->current = this->first;
	this->scurrent = this->sfirst;

	if (this->sfirst) {
		while (this->scurrent != nullptr) {

			i = 1;
			start = this->scurrent->start;
			end = this->scurrent->end;
			findstart(i, start);

			i = 1;
			findend(i, end);

			this->current = this->last1->next;
			while (this->current1 != this->current) {
				listOfSection* old = this->current1;
				this->current1 = this->current1->next;

				old->next->prev = old->prev;
				old->prev->next = old->next;
				delete old->section;
				delete old;
				count++;				
			}

			while (this->current) {
				i = this->current->section->getNumber();
				i -= count;
				this->current->section->setNumber(i);

				this->current = this->current->next;
			}			
			this->scurrent = this->scurrent->next;
		}
	}
	deselect();
}

void SubtitleEditor::addToSelection(int start, int end){
	int i = 0;
	if (start > end) {
		cout << "Nevalidan unos";
	}
	else {
		i = this->last->section->getNumber();
		if (start <= 0) { start = 1; }
		if (end > i) { end = i; }

		this->scurrent = this->sfirst;
		while (1) {
			if (!this->sfirst) {   
				Selection* element = new Selection();
				element->start = start;
				element->end = end;
				element->next = nullptr;
				element->prev = nullptr;
				this->sfirst = this->slast = this->scurrent = element;
				break;
			}
			if (this->sfirst->start > start && this->sfirst->start >end) {
				Selection* element = new Selection();
				element->start = start;
				element->end = end;
				element->next = this->sfirst;
				this->sfirst->prev = element;
				element->prev = nullptr;
				this->sfirst = element; 
				this->scurrent = this->sfirst;  
				break;
			}
			if (this->slast->end < end && this->slast->end < start) {	
				Selection* element = new Selection();
				element->start = start;
				element->end = end;
				element->next = nullptr;
				this->slast->next = element;
				element->prev = this->slast;
				this->slast = element; 
				this->scurrent = this->sfirst;	
				break;
			}
			if (this->scurrent->end < start && this->scurrent->next->start > end) { 
				Selection* element = new Selection();
				element->start = start;
				element->end = end;
				element->prev = this->scurrent;
				element->next = this->scurrent->next;
				this->scurrent->next->prev = element;
				this->scurrent->next = element;
				this->scurrent = this->sfirst;
				break;
			}
			if (this->scurrent->start < start && this->scurrent->end > end) { break; } 
			if (this->scurrent->start < start && this->scurrent->end > start && this->scurrent->end < end ){    
				if (this->scurrent->next != nullptr) {
					if (this->scurrent->next->start > end) {
						this->scurrent->end = end;
						break;
					}
				}
				else {
					this->scurrent->end = end;
					break;
				}
			}
			if (this->scurrent->start < end && this->scurrent->end > end && this->scurrent->start > start ){    
				if (this->scurrent->prev != nullptr) {
					if (this->scurrent->prev->end < start) {
						this->scurrent->start = start;
						break;
					}
				}
				else {
					this->scurrent->start = start;
					break;
				}
			}
			while (1) {
				if (this->scurrent->start >= start && this->scurrent->end <= end) {
					Selection* old = this->scurrent;
					if (this->scurrent->next != nullptr) {		
						this->scurrent->next->prev = this->scurrent->prev;	
						this->scurrent = this->scurrent->next;
						delete old;
					}
					else {
						this->sfirst = this->slast = this->scurrent = nullptr;
						delete old;
						break;
					}
				}
				else {
					break;
				}
			}
			if (this->scurrent != nullptr){
				if (this->scurrent->next != nullptr) {
					this->scurrent = this->scurrent->next;
				}
			}
		}
	}
}

void SubtitleEditor::deselect(){
	while (this->sfirst != nullptr) {
		Selection* old = this->sfirst;
		this->sfirst = this->sfirst->next;
		delete old;
	}
	this->sfirst = this->slast = this->scurrent = nullptr;
}

void SubtitleEditor::boldText(int start, int end) {
	bool status = true;
	int i = 0;
	int pos = 0;
	int pos1 = 0;
	int pos2 = 0;
	int size = 0;
	int startSelection = 0;
	int endSelection = 0;
	int checkstart = 0;
	int checkend = 0;
	int check = 0;

	string startb = "<b>";
	string endb = "</b>";
	string text = "";

	if (this->sfirst != nullptr) {
		if (start <= end) {
			this->current = this->first;
			this->scurrent = this->sfirst;

			while (this->scurrent != nullptr) {
				i = 1;
				startSelection = this->scurrent->start;
				endSelection = this->scurrent->end;
				findstart(i, startSelection);

				i = 1;
				findend(i, endSelection);

				this->current = this->last1->next;
				while (this->current1 != this->current) {	
					size = this->current1->section->getTitle()->getSize();
					if (start < 0) {
						checkstart = 0;
					}
					else checkstart = start;

					if (end > size) {
						checkend = size;
					}
					else checkend = end;

					text = this->current1->section->getTitle()->getName();

					pos1 = 0;
					pos2 = 0;
					pos = 0;
					check = checkend - 2;
					for (; pos <= check; pos++) {
						if (text[pos] == '<') {
							if ((text[pos + 1] == 'i' || text[pos + 1] == 'b' || text[pos + 1] == 'u') && text[pos + 2] == '>') {
								pos1 = pos;
								pos += 2;
							}

							if (text[pos + 1] == '/' && (text[pos + 2] == 'i' || text[pos + 1] == 'b' || text[pos + 1] == 'u') && text[pos + 3] == '>') {
								pos2 = pos;
								pos += 3;
							}
						}
						if (!((pos1 < start && pos2 < start) || (pos1 > end && pos2 > end)) && (pos1 != 0 && pos2 != 0)) {
							status = false;
							break;
						}
						if ((pos1 < start && pos2 < start) && (pos1 != 0 && pos2 != 0)) {
							checkstart += 7;
							checkend += 7;
						}
					}
					if (status) {
						text.insert(checkstart, startb);
						text.insert(checkend + 1, endb);
						size += 7;
						this->current1->section->getTitle()->setSize(size);
						this->current1->section->getTitle()->setName(text);
					}
					else {
						cout << "Doslo je do preklapanja stilova." << endl;
						break;
					}

					this->current1 = this->current1->next;
				}
				if (!status) {
					break;
				}
				this->scurrent = this->scurrent->next;
			}
		}
	}
}

void SubtitleEditor::italicText(int start, int end){
	bool status = true;
	int i = 0;
	int pos = 0;
	int pos1 = 0;
	int pos2 = 0;
	int size = 0;
	int startSelection = 0;
	int endSelection = 0;
	int checkstart = 0;
	int checkend = 0;
	int check = 0;

	string starti = "<i>";
	string endi = "</i>";
	string text = "";

	if (this->sfirst != nullptr) {
		if (start <= end) {
			this->current = this->first;
			this->scurrent = this->sfirst;

			while (this->scurrent != nullptr) {
				i = 1;
				startSelection = this->scurrent->start;
				endSelection = this->scurrent->end;
				findstart(i, startSelection);

				i = 1;
				findend(i, endSelection);

				this->current = this->last1->next;
				while (this->current1 != this->current) {	
					size = this->current1->section->getTitle()->getSize();
					if (start < 0) {
						checkstart = 0;
					}
					else checkstart = start;

					if (end > size) {
						checkend = size;
					}
					else checkend = end;

					text = this->current1->section->getTitle()->getName();

					pos1 = 0;
					pos2 = 0;
					pos = 0;
					check = checkend - 2;
					for (; pos <= check; pos++) {
						if (text[pos] == '<') {
							if ((text[pos + 1] == 'i' || text[pos + 1] == 'b' || text[pos + 1] == 'u') && text[pos + 2] == '>') {
								pos1 = pos;
								pos += 2;
							}

							if (text[pos + 1] == '/' && (text[pos + 2] == 'i' || text[pos + 1] == 'b' || text[pos + 1] == 'u') && text[pos + 3] == '>') {
								pos2 = pos;
								pos += 3;
							}
						}
						if (!((pos1 < start && pos2 < start) || (pos1 > end&& pos2 > end)) && (pos1 != 0 && pos2 != 0)) {
							status = false;
							break;
						}
						if ((pos1 < start && pos2 < start) && (pos1 != 0 && pos2 != 0)) {
							checkstart += 7;
							checkend += 7;
						}
					}
					if (status) {
						text.insert(checkstart, starti);
						text.insert(checkend + 1, endi);
						size += 7;
						this->current1->section->getTitle()->setSize(size);
						this->current1->section->getTitle()->setName(text);
					}
					else {
						cout << "Doslo je do preklapanja stilova." << endl;
						break;
					}

					this->current1 = this->current1->next;
				}
				if (!status) {
					break;
				}
				this->scurrent = this->scurrent->next;
			}
		}
	}
}

void SubtitleEditor::underlineText(int start, int end){
	bool status = true;
	int i = 0;
	int pos = 0;
	int pos1 = 0;
	int pos2 = 0;
	int size = 0;
	int startSelection = 0;
	int endSelection = 0;
	int checkstart = 0;
	int checkend = 0;
	int check = 0;

	string startu = "<u>";
	string endu = "</u>";
	string text = "";

	if (this->sfirst != nullptr) {
		if (start <= end) {
			this->current = this->first;
			this->scurrent = this->sfirst;

			while (this->scurrent != nullptr) {
				i = 1;
				startSelection = this->scurrent->start;
				endSelection = this->scurrent->end;
				findstart(i, startSelection);

				i = 1;
				findend(i, endSelection);

				this->current = this->last1->next;
				while (this->current1 != this->current) {	
					size = this->current1->section->getTitle()->getSize();
					if (start < 0) {
						checkstart = 0;
					}
					else checkstart = start;

					if (end > size) {
						checkend = size;
					}
					else checkend = end;

					text = this->current1->section->getTitle()->getName();

					pos1 = 0;
					pos2 = 0;
					pos = 0;
					check = checkend - 2;
					for (; pos <= check; pos++) {
						if (text[pos] == '<') {
							if ((text[pos + 1] == 'i' || text[pos + 1] == 'b' || text[pos + 1] == 'u') && text[pos + 2] == '>') {
								pos1 = pos;
								pos += 2;
							}

							if (text[pos + 1] == '/' && (text[pos + 2] == 'i' || text[pos + 1] == 'b' || text[pos + 1] == 'u') && text[pos + 3] == '>') {
								pos2 = pos;
								pos += 3;
							}
						}
						if (!((pos1 < start && pos2 < start) || (pos1 > end&& pos2 > end)) && (pos1 != 0 && pos2 != 0)) {
							status = false;
							break;
						}
						if ((pos1 < start && pos2 < start) && (pos1 != 0 && pos2 != 0)) {
							checkstart += 7;
							checkend += 7;
						}
					}
					if (status) {
						text.insert(checkstart, startu);
						text.insert(checkend + 1, endu);
						size += 7;
						this->current1->section->getTitle()->setSize(size);
						this->current1->section->getTitle()->setName(text);
					}
					else {
						cout << "Doslo je do preklapanja stilova." << endl;
					}

					this->current1 = this->current1->next;
				}
				if (!status) {
					break;
				}
				this->scurrent = this->scurrent->next;
			}
		}
	}
}

void SubtitleEditor::removeStyle(){
	int i = 0;
	int size = 0;
	int startSelection = 0;
	int endSelection = 0;

	string text = "";

	if (this->sfirst != nullptr) {
		this->scurrent = this->sfirst;
		while (this->scurrent != nullptr) {
			i = 1;
			startSelection = this->scurrent->start;
			endSelection = this->scurrent->end;
			findstart(i, startSelection);

			i = 1;
			findend(i, endSelection);

			this->current = this->last1->next;
			while (this->current1 != this->current) {
				text = this->current1->section->getTitle()->getName();
				size = this->current1->section->getTitle()->getSize();

				int pos = 0;
				for (pos; pos < size; pos++) {
					if (text[pos] == '<' && (text[pos + 1] == 'i' || text[pos + 1] == 'u' || text[pos + 2] == 'b')) {
						text.erase(text.begin() + pos, text.begin() + (pos + 3));    
						pos=0;
						size -= 3;
						this->current1->section->getTitle()->setSize(size);
						this->current1->section->getTitle()->setName(text);
					}
					if (text[pos] == '<' && (text[pos + 1] == '/' && (text[pos + 2] == 'i' || text[pos + 2] == 'u' || text[pos + 2] == 'b'))) {
						text.erase(text.begin() + pos , text.begin() + (pos + 4));
						pos =0;
						size -= 4;
						this->current1->section->getTitle()->setSize(size);
						this->current1->section->getTitle()->setName(text);
					}
				}

				this->current1 = this->current1->next;
			}
			this->scurrent = this->scurrent->next;
		}
	}	
}

void SubtitleEditor::shiftForward(int ms) {
	int start = 0;
	int end = 0;
	int i = 0;

	this->current = this->first;
	this->scurrent = this->sfirst;

	if (this->sfirst) {   
		while (this->scurrent != this->slast) {
			i = 1;
			start = this->scurrent->start;
			end = this->scurrent->end;			
			findstart(i, start);

			i = 1;			
			findend(i, end);
			
			this->current = this->current1;
			while (this->current != this->last1->next) {
				int H = 0; int M = 0; int S = 0; int MS = 0;

				this->current->section->getStarttime()->shiftFor(ms, H, M, S, MS);
				this->current->section->getEndtime()->shiftFor(ms, H, M, S, MS);

				this->current = this->current->next;
			}
			this->scurrent = this->scurrent->next;
		}
	}
	else {					
		while (this->current != nullptr) {		
			int H = 0; int M = 0; int S = 0; int MS = 0;

			this->current->section->getStarttime()->shiftFor(ms, H, M, S, MS);
			this->current->section->getEndtime()->shiftFor(ms, H, M, S, MS);

			this->current = this->current->next;
		}
	}
}

void SubtitleEditor::shiftBackward(int ms){
	
	int start = 0;
	int end = 0;
	int i = 0;

	this->current = this->first;
	this->scurrent = this->sfirst;

	if (this->sfirst) {  
		while (this->scurrent != this->slast) {
			i = 1;
			start = this->scurrent->start;
			end = this->scurrent->end;
			findstart(i, start);

			i = 1;
			findend(i, end);

			this->current = this->current1;
			while (this->current != this->last1->next) {
				int H = 0; int M = 0; int S = 0; int MS = 0;

				this->current->section->getStarttime()->shiftBack(ms, H, M, S, MS);
				this->current->section->getEndtime()->shiftBack(ms, H, M, S, MS);

				this->current = this->current->next;
			}
			this->scurrent = this->scurrent->next;
		}
	}
	else {				
		while (this->current != nullptr) {
			int H = 0; int M = 0; int S = 0; int MS = 0;

			this->current->section->getStarttime()->shiftBack(ms, H, M, S, MS);
			this->current->section->getEndtime()->shiftBack(ms, H, M, S, MS);

			this->current = this->current->next;
		}
	}
}

void SubtitleEditor::merge(string subtitles) {
	int i = 0;
	int size = 0;

	size = this->last->section->getNumber();
	this->current = this->last;

	i = loadSubtitles(subtitles);

	if (i == -1) {
		this->current = this->current->next;
		while (this->current) {
			size++;
			this->current->section->setNumber(size);
			this->current = this->current->next;
		}
	}
}

void SubtitleEditor::fixLongLines(int max){
	int start = 0;
	int end = 0;
	int i = 0;
	string text = "";
	int size = 0;
	int character = 0;

	this->current = this->first;
	this->scurrent = this->sfirst;

	if (this->sfirst != nullptr) {  
		while (this->scurrent != nullptr) {
			i = 1;
			start = this->scurrent->start;
			end = this->scurrent->end;
			findstart(i, start);

			i = 1;
			findend(i, end);

			this->current = this->current1;
			while (this->current != this->last1->next) {
				int pos = 0;
				text = this->current->section->getTitle()->getName();
				size = this->current->section->getTitle()->getSize();
				character = 0;

				if (size > max) {
					for (; pos < size; pos++) {
						if (character % max == 0 && character != 0 && pos != 0) {
							while (text[pos] != ' ') {
								pos--;
							}
							text.erase(text.begin() + pos);
							size = this->current->section->getTitle()->getSize();
							text.insert(text.begin() + pos, '\n');
							size = this->current->section->getTitle()->getSize();
							this->current->section->getTitle()->setName(text);
							character = 0;

						}

						if (text[pos] != ' ') {
							character += 1;
						}
						if (text[pos] == '\n' && text[pos + 1] == '\n') {
							break;
						}
						if (text[pos] == '\n') {
							character = 0;
						}
					}
					this->current = this->current->next;
				}
				else {
					this->current = this->current->next;
					break;
				}
			}
			this->scurrent = this->scurrent->next;
		}
	}
	else {				
		while (this->current != nullptr) {
			int pos = 0;
			text = this->current->section->getTitle()->getName();
			size = this->current->section->getTitle()->getSize();
			character = 0;

			if (size > max) {
				for (; pos < size; pos++) {
					if (character % max == 0 && character != 0 && pos != 0) {
						while (text[pos] != ' ') {
							pos--;
						}
						text.erase(text.begin() + pos);
						size = this->current->section->getTitle()->getSize();
						text.insert(text.begin() + pos, '\n');
						size = this->current->section->getTitle()->getSize();
						this->current->section->getTitle()->setName(text);
						character = 0;

					}

					if (text[pos] != ' ') {
						character += 1;
					}
					if (text[pos] == '\n' && text[pos + 1] == '\n') {
						break;
					}
					if (text[pos] == '\n') {
						character = 0;
					}
				}
				this->current = this->current->next;
			}
			else {
				this->current = this->current->next;
			}
			
		}
	}
}

void SubtitleEditor::fixLongTime(int ms){
	int start = 0;
	int end = 0;
	int i = 0;
	int j = 1;
	int z = 0;
	int s = 0;
	string text = "";
	string newtext = "";
	int size = 0;
	int number = 0;

	this->current = this->first;
	this->scurrent = this->sfirst;

	if (this->sfirst) {
		while (this->scurrent != nullptr) {
			i = 1;
			start = this->scurrent->start;
			end = this->scurrent->end;
			findstart(i, start);

			i = 1;
			findend(i, end);

			this->current = this->current1;
			while (this->current != this->last1->next) {
				int H = 0; int M = 0; int S = 0; int MS = 0;
				int TimeBegin = 0;
				int TimeEnd = 0;
				int sum = 0;
				newtext = "";

				H = this->current->section->getEndtime()->getHours();
				M = this->current->section->getEndtime()->getMinutes();
				S = this->current->section->getEndtime()->getSeconds();
				MS = this->current->section->getEndtime()->getMiliseconds();

				TimeEnd = (H * 60 * 60 * 1000) + (M * 60 * 1000) + (S * 1000) + MS;

				H = this->current->section->getStarttime()->getHours();
				M = this->current->section->getStarttime()->getMinutes();
				S = this->current->section->getStarttime()->getSeconds();
				MS = this->current->section->getStarttime()->getMiliseconds();

				TimeBegin = (H * 60 * 60 * 1000) + (M * 60 * 1000) + (S * 1000) + MS;
				sum = TimeEnd - TimeBegin;
				
				j = 1;

				if (sum > ms) {
					j = (sum + ms - 1) / ms;

					/*z = sum;
					while (z > ms) {
						z = sum;
						z /= j;
						j++;
					}
					j--;*/

					sum /= j;
					TimeBegin += sum;

					MS = (TimeBegin % 1000);
					if (MS >= 1000) {
						S = ((TimeBegin / 1000) % 60); + 1;
						MS -= 1000;
					}
					else {
						S = ((TimeBegin / 1000) % 60);
					}

					if (S >= 60) {
						M = ((TimeBegin / (1000 * 60)) % 60) + 1;
						S -= 60;
					}
					else {
						M = ((TimeBegin / (1000 * 60)) % 60);
					}

					if (M >= 60) {
						H = ((TimeBegin / (1000 * 60 * 60)) % 24) + 1;
						M -= 60;
					}
					else {
						H = ((TimeBegin / (1000 * 60 * 60)) % 24);
					}

					text = this->current->section->getTitle()->getName();
					size = this->current->section->getTitle()->getSize();
					number = this->current->section->getNumber();

					this->current->section->getEndtime()->setTime(H, M, S, MS);
					
					s = size % j;
					size /= j;
					size -= s;
					size -= 1;
					j--;
					z = 0;

					for (; z <= size; z++) {
						newtext += text[z];						
					}

					newtext += '\n';
					this->current->section->getTitle()->setName(newtext);
					this->current->section->getTitle()->setSize(size);
					i = size;

					for (; j >= 1; j--) {

						Section* section = nullptr;

						number++;

						Time* starttime = new Time(H, M, S, MS);
						TimeBegin += sum;

						MS = (TimeBegin % 1000);
						if (MS >= 1000) {
							S = ((TimeBegin / 1000) % 60); +1;
							MS -= 1000;
						}
						else {
							S = ((TimeBegin / 1000) % 60);
						}

						if (S >= 60) {
							M = ((TimeBegin / (1000 * 60)) % 60) + 1;
							S -= 60;
						}
						else {
							M = ((TimeBegin / (1000 * 60)) % 60);
						}

						if (M >= 60) {
							H = ((TimeBegin / (1000 * 60 * 60)) % 24) + 1;
							M -= 60;
						}
						else {
							H = ((TimeBegin / (1000 * 60 * 60)) % 24);
						}


						Time* endtime = new Time(H, M, S, MS);

						newtext = "";
						size += i;
						size += 4;
						while (z <= size) {
							newtext += text[z];
							z++;
						}

						
						Title* title = new Title(newtext);

						section = new Section(number, starttime, endtime, title);

						listOfSection* element = new listOfSection();
						element->section = section;
						element->next = this->current->next;
						element->prev = this->current;

						this->current->next->prev = element;
						this->current->next = element;
						this->current = element;
						this->current->section->getTitle()->setSize(size);

						j--;
					}
					this->current1 = this->current->next;
					while (this->current1) {			
						i = this->current1->section->getNumber();
						i += 1;
						this->current1->section->setNumber(i);
						this->current1 = this->current1->next;
					}
				}
				this->current = this->current->next;
			}			
			this->scurrent = this->scurrent->next;
		}
	} 
	else {
		while (this->current) {
			int H = 0; int M = 0; int S = 0; int MS = 0;
			int TimeBegin = 0;
			int TimeEnd = 0;
			int sum = 0;
			newtext = "";

		
			H = this->current->section->getEndtime()->getHours();
			M = this->current->section->getEndtime()->getMinutes();
			S = this->current->section->getEndtime()->getSeconds();
			MS = this->current->section->getEndtime()->getMiliseconds();

			TimeEnd = (H * 60 * 60 * 1000) + (M * 60 * 1000) + (S * 1000) + MS;

			H = this->current->section->getStarttime()->getHours();
			M = this->current->section->getStarttime()->getMinutes();
			S = this->current->section->getStarttime()->getSeconds();
			MS = this->current->section->getStarttime()->getMiliseconds();

			TimeBegin = (H * 60 * 60 * 1000) + (M * 60 * 1000) + (S * 1000) + MS;

			sum = TimeEnd - TimeBegin;
			j = 1;

			if (sum > ms) {
				j = (sum + ms - 1) / ms;
				/*z = sum;
				while (z >= ms) {
					z = sum;
					z /= j;
					j++;
				}
				j--;*/

				sum /= j;
				TimeBegin += sum;
				
				MS = (TimeBegin % 1000);
				if (MS >= 1000) {
					S = ((TimeBegin / 1000) % 60); +1;
					MS -= 1000;
				}
				else {
					S = ((TimeBegin / 1000) % 60);
				}

				if (S >= 60) {
					M = ((TimeBegin / (1000 * 60)) % 60) + 1;
					S -= 60;
				}
				else {
					M = ((TimeBegin / (1000 * 60)) % 60);
				}

				if (M >= 60) {
					H = ((TimeBegin / (1000 * 60 * 60)) % 24) + 1;
					M -= 60;
				}
				else {
					H = ((TimeBegin / (1000 * 60 * 60)) % 24);
				}


				text = this->current->section->getTitle()->getName();
				size = this->current->section->getTitle()->getSize();
				number = this->current->section->getNumber();
				this->current->section->getEndtime()->setTime(H, M, S, MS);
				
				s = size % j;
				size /= j;
				size -= s;
				size -= 1;
				j--;
				z = 0;

				for (; z <= size; z++) {
					newtext += text[z];
				}

				newtext += '\n';
				this->current->section->getTitle()->setName(newtext);
				this->current->section->getTitle()->setSize(size);

				i = size;

				for (; j >= 1; j--) {

					Section* section = nullptr;

					number++;

					Time* starttime = new Time(H, M, S, MS);
					TimeBegin += sum;

					MS = (TimeBegin % 1000);
					if (MS >= 1000) {
						S = ((TimeBegin / 1000) % 60) +1;
						MS -= 1000;
					}
					else {
						S = ((TimeBegin / 1000) % 60);
					}

					if (S >= 60) {
						M = ((TimeBegin / (1000 * 60)) % 60) + 1;
						S -= 60;
					}
					else {
						M = ((TimeBegin / (1000 * 60)) % 60);
					}

					if (M >= 60) {
						H = ((TimeBegin / (1000 * 60 * 60)) % 24) + 1;
						M -= 60;
					}
					else {
						H = ((TimeBegin / (1000 * 60 * 60)) % 24);
					}

					Time* endtime = new Time(H, M, S, MS);

					newtext = "";
					size += i;
					size += 4;

					while (z <= size) {
						newtext += text[z];
						z++;
					}
					Title* title = new Title(newtext);

					section = new Section(number, starttime, endtime, title);

					listOfSection* element = new listOfSection();
					element->section = section;
					element->next = this->current->next;
					element->prev = this->current;

					this->current->next->prev = element;
					this->current->next = element;
					this->current = element;
					
				}
				this->current1 = this->current;
				while (this->current1) {			
					i = this->current1->section->getNumber();
					i += 1;
					this->current1->section->setNumber(i);
					this->current1 = this->current1->next;
				}
			}
		this->current = this->current->next;
		}	
	}
}

int SubtitleEditor::readHours(string subtitles, int& pos) {
	int hms = 0;
	for (; pos < subtitles.length() && subtitles[pos] != ':' && subtitles[pos] != ','; pos++) {
		if (subtitles[pos] >= '9' && subtitles[pos] <= '0') { break; }  //Greska?
		else {
			hms = 10 * hms + (subtitles[pos] - '0');
		}
	}
	pos++;
	if (hms >= 0 && hms < 100) {
		return hms;
	}
	else return -1;
}

int SubtitleEditor::readMinutesSeconds(string subtitles, int& pos){
	int hms = 0;
	for (; pos < subtitles.length() && subtitles[pos] != ':' && subtitles[pos] != ','; pos++) {
		if (subtitles[pos] >= '9' && subtitles[pos] <= '0') { break; } 
		else {
			hms = 10 * hms + (subtitles[pos] - '0');
		}
	}
	pos++;
	if (hms >= 0 && hms < 60) {
		return hms;
	}
	else return -1;
}

int SubtitleEditor::checkEmptyRows(string subtitles, int& pos) {
	int newrow = 0;
	while (pos < subtitles.length() && subtitles[pos] == '\n') {
		if (subtitles[pos] == '\n') { newrow += 1; }
		pos++;
	}
	if (newrow==2) {
		return -1;
	}
	else return 1;
}

string SubtitleEditor::saveNumber(int time, string title){
	string text = "";
	if (time < 10) {
		text.append("0");
		text.append(to_string(time));
	}
	else text.append(to_string(time));

	return text;
}

string SubtitleEditor::saveMNumber(int time, string title){
	string text = "";
	if (time < 10) {
		text.append("00");
		text.append(to_string(time));
	}
	else if (time < 100) {
		text.append("0");
		text.append(to_string(time));
	}
	else text.append(to_string(time));

	return text;
}

void SubtitleEditor::addTime(int ms, int& H, int& M, int& S, int& MS) {
	ms += MS + (S * 1000) + (M * 60 * 1000) + (H * 60 * 60 * 1000);
	MS = ms % 1000;
	ms /= 1000;
	S = ms % 60;
	ms /= 60;
	M = ms % 60;
	ms /= 60;
	H = ms % 60;


	/*int i = this->current->section->getStarttime()->checkMilisekunds(ms);
	if (i != 1) {
		H += ((ms / (1000 * 60 * 60)) % 24);
		M += ((ms / (1000 * 60)) % 60);
		S += ((ms / 1000) % 60);
		MS += (ms % 1000);
	}
	else MS += ms;*/
}

int SubtitleEditor::checkTime(int start){
	int H1 = 0; int M1 = 0; int S1 = 0; int MS1 = 0; int Timecurrent = 0;
	H1 = this->current->section->getStarttime()->getHours();
	M1 = this->current->section->getStarttime()->getMinutes();
	S1 = this->current->section->getStarttime()->getSeconds();
	MS1 = this->current->section->getStarttime()->getMiliseconds();

	Timecurrent = (H1 * 60 * 60 * 1000) + (M1 * 60 * 1000) + (S1 * 1000) + MS1;

	if (Timecurrent >= start) {
		return 1;
	}
	else return 0;
}

void SubtitleEditor::findstart(int indicator, int start){
	this->current1 = this->first;
	while (start != indicator) {		
		this->current1 = this->current1->next;
		indicator = this->current1->section->getNumber();
	}
}

void SubtitleEditor::findend(int indicator, int end){
	this->last1 = this->first;
	while (end != indicator) {		
		this->last1 = this->last1->next;
		indicator = this->last1->section->getNumber();
	}

}

void SubtitleEditor::undo(){
}

int SubtitleEditor::readMiliseconds(string subtitles, int& pos) {
	int number = 0;
	for (; pos < subtitles.length() && subtitles[pos] != '\n' && subtitles[pos] != ' '; pos++) {
		number = 10 * number + (subtitles[pos] - '0');
	}
	pos++;
	if (number >= 0 && number < 1000) {
		return number;
	}
	else return -1;
}

int SubtitleEditor::checkError(int H, int M, int S, int MS)
{
	if (H == -1 || M == -1 || S == -1 || MS == -1) {
		return  1;
	}
	else return 0;
}

string SubtitleEditor::readTitle(string subtitles, int& pos)   
{
	int newrow = 0;
	string greska = "";
	string text = "";
	for (; pos < subtitles.length(); pos++) {
		if (subtitles[pos] == '\n' && subtitles[pos + 1] == '\n') { break; }
		text += subtitles[pos];
		if (subtitles[pos] == '\n') { newrow += 1; }
	}
	if (newrow >= 8) {
		return greska;
	}
	else return text;
}
