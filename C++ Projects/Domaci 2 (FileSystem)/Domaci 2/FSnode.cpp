#include "FSnode.h"
#include <iostream>

FSnode::FSnode(const string& name,FSnode* parent){
	name_ = string(name);
	parent_ = parent;
}

FSnode::~FSnode(){	
}

//FSnode metode su ili zajednicki podskup ili "default" exception za klase koje je ne podrzavaju
void FSnode::LS( ofstream& log_file_){
	log_file_ << LS_PREFIX << name_;
}

void FSnode::LS(ofstream& log_file_, const string& prefix) {
	log_file_ << prefix << LS_PREFIX << name_;
}

FSnode* FSnode::CD(const string& name){	
	throw string("NOT_DIRECTORY");
}

void FSnode::NEW(const string& name){
	throw string("Parent folder of " + name + " does not exist!");
}

void FSnode::NEW(const string& name, const string& extension, const string& data){
	throw string("Parent folder of " + name + "." + extension + " does not exist!");
}

void FSnode::DEL(const string& name) {
	throw string(name + ": cannot delete");   
}

void FSnode::DEL(const string& name, const string& extension) {
	throw string(name + "." + extension + ": cannot delete");   
}

FSnode* FSnode::EXE(ofstream& log_file_, Folder* cdir){
	throw string("Not executable!");
}

FSnode* FSnode::getParent() const{
	return parent_;
}

FSnode* FSnode::getChild(const string& name) {
	return nullptr;
}

FSnode* FSnode::getChild(const string& name, const string& extension) {
	return nullptr;
}

string FSnode::getExtension() const {
	return "";
}

string FSnode::getName() const {
  return name_; 
}

//Nadogradnja FSnode metoda, specificnih za datoteke
File::File(const string& name, FSnode* parent, const string& data, const string& extension) : FSnode(name,parent){
	data_ = data;
	extension_ = extension;
}

File::~File() {
	extension_.clear();
}

void File::LS( ofstream& log_file_){
	FSnode::LS(log_file_);
	log_file_ << "." << extension_ << endl;
}

void File::LS(ofstream& log_file_, const string& prefix) {
	FSnode::LS(log_file_, prefix);
	log_file_ << "." << extension_ << endl;
}

string File::getData() const{
	return data_;
}

void File::setData(string data){
	this->data_ = data;
}

string File::getExtension() const{
	return extension_;
}

void File::setExtension(string extension){
	this->extension_ = extension;
}


Folder::Folder(const string& name, FSnode* parent): FSnode(name,parent){
	if (parent_ == nullptr) parent_ = this;
}

Folder::~Folder() {
	children_.clear();
}

//Nadogradnja FSnode metoda, specificnih za datoteke
void Folder::LS(ofstream& log_file_) {
	for (list<FSnode*>::iterator chld = children_.begin(); chld != children_.end(); chld++) {
		(*chld)->LS(log_file_,"");
	}
}

void Folder::LS(ofstream& log_file_, const string& prefix) {
	FSnode::LS(log_file_, prefix);
	log_file_ << endl;
	for (list<FSnode*>::iterator chld = children_.begin(); chld != children_.end(); chld++) {
		(*chld)->LS(log_file_, prefix+"\\"+ name_);
	}
}

void Folder::DEL(const string& name){
	list<FSnode*>::iterator chld;

	//TODO: Use getChild!!!
	for (chld = children_.begin(); chld != children_.end(); chld++) {
		if (name == (*chld)->getName() && (*chld)->getExtension().empty()) {
			children_.erase(chld);	
			return;
		}
	}
	throw string("Folder " + name + " not found.");
}

void Folder::DEL(const string& name, const string& extension){
	list<FSnode*>::iterator chld;

	//TODO: Use getChild!!!
	for (chld = children_.begin(); chld != children_.end(); chld++) {
		if (name == (*chld)->getName() && !(*chld)->getExtension().empty() && (*chld)->getExtension() == extension) {
			children_.erase(chld);
			return;
		}
	}
	throw string("File " + name + "." + extension + " not found.");
}

FSnode* Folder::CD(const string& name) {
	if (name == "..") {
		return this->getParent();
	}
	else if (name.empty()) {
		return this;  //ako je prazan onda vraca samog sebe
	}
	else {
		for (list<FSnode*>::iterator chld = children_.begin(); chld != children_.end(); chld++) {
			if (name == (*chld)->getName()) {
				return (*chld)->CD(""); //trik da se proveri da li je folder, ako nije onda se generise exception
			}
		}
		throw string("Folder not found: " + name);
	}
}

void Folder::NEW(const string& name){
	list<FSnode*>::iterator chld;

	for (chld = children_.begin(); (chld != children_.end()) && (name > (*chld)->getName()); chld++) {}
	
	if((chld != children_.end()) && ((*chld)->getName() == name) && (*chld)->getExtension().empty()) {
		throw string("Folder \'" + name +"\' exists");
	}
	//TODO: proveri da li chld == end moye da se koristi ovako, za dodavanje na kraj liste
	this->children_.insert(chld, new Folder(name, this));
}

void Folder::NEW(const string& name, const string& extension, const string& data) {     

	list<FSnode*>::iterator chld;

	for (chld = children_.begin(); (chld != children_.end()) && ((name > (*chld)->getName()) || (name == getName() && (extension > (*chld)->getExtension()))); chld++) {}

	if ((chld != children_.end()) && ((*chld)->getName() == name) && !(*chld)->getExtension().empty() && extension == (*chld)->getExtension()) {
		throw string("\'" + name + "." + extension + "\' exists");
	}
	
	if (extension == "txt") {
		this->children_.insert(chld, new File_txt(name, this, data));
	}
	else if (extension == "exe") {
		this->children_.insert(chld, new File_exe(name, this, data));
	}
	else {
		throw string("Unknown file extension: " + extension);
	}	
}

//tekst tip datoteka koja trenutno nema nikakvu nadogradnju
File_txt::File_txt(const string& name, FSnode* parent, const string& data, const string& extension) : File(name,parent,data, extension){}

//exe tip datoteka koja ima 1 nadogradnju: EXE() metodu
File_exe::File_exe(const string& name, FSnode* parent, const string& data, const string& extension) : File(name, parent, data, extension) {}

FSnode* File_exe::EXE(ofstream& log_file_, Folder* cdir){
	string code = this->data_;
	string codeline;
	string token = "";
	size_t pos;

	for (SplitFirstLine(code, codeline); !codeline.empty(); SplitFirstLine(code,codeline)) {
		SplitFirstWord(codeline, token);

		switch (token.at(0)) {
		case 'L':
			if (token != "LS") {
				throw string("Unknown command: " + token);
			}

			cdir->LS(log_file_);
			break;
		case 'C':
			if (token != "CD") {
				throw string("Unknown command: " + token);
			}
			SplitFirstWord(codeline, token);
			cdir = (Folder*)(cdir->CD(token));
			break;
		case 'N':
			if (token != "NEW") {
				throw string("Unknown command: " + token);
			}
			SplitFirstWord(codeline, token);

			pos = token.find('.');
			if (pos == string::npos) {
				cdir->NEW(token);
			}
			else {
				cdir->NEW(token.substr(0, pos), token.substr(pos + 1), codeline);
			}

			break;
		case 'D':
			if (token != "DEL") {
				throw string("Unknown command: " + token);
			}
			SplitFirstWord(codeline, token);

			pos = token.find('.');
			if (pos == string::npos) {
				cdir->DEL(token);
			}
			else {
				cdir->DEL(token.substr(0, pos), token.substr(pos + 1));
			}
			break;
		case 'E': {
				string name, extension;
				File_exe* pchild;

				if (token != "EXE") {
					throw string("Unknown command: " + token);
				}
				SplitFirstWord(codeline, name);

				SplitNameExtension(name, extension);

				pchild = (File_exe*)(cdir->getChild(name, extension));
				if (pchild != nullptr) {
					cdir = (Folder*)(pchild->EXE(log_file_, cdir));
					break;
				}
				throw string("File " + name + "." + extension + " not found.");
			}
			break;
		default:
			throw string("Unknown command: " + token);

		}
	}
	return cdir;
}


FSnode* Folder::getChild(const string& name) {
	for (list<FSnode*>::iterator chld = this->children_.begin(); chld != children_.end(); chld++) {
		if (name == (*chld)->getName() && (*chld)->getExtension().empty()) {
			return(*chld);
		}
	}
	return nullptr;
}

FSnode* Folder::getChild(const string& name, const string& extension) {
	for (list<FSnode*>::iterator chld = this->children_.begin(); chld != children_.end(); chld++) {
		if (name == (*chld)->getName() && !(*chld)->getExtension().empty() && (*chld)->getExtension() == extension) {
			return(*chld);
		}
	}
	return nullptr;
}
