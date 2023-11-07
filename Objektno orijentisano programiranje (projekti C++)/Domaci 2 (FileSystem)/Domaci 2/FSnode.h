#ifndef FSNODE_H
#define FSNODE_H

#include "FileSystem.h"
#include "FSparser.h"

#include <exception>
#include <fstream>
#include <list>
#include <string>

using namespace std;

// prefix for LS output
#define LS_PREFIX "\\"

class Folder;

class FSnode {
public:
	FSnode(const string& name, FSnode* parent);
	virtual ~FSnode();

	//zadane funkcije
	virtual void LS(ofstream& log_file_);
	virtual void LS(ofstream& log_file_, const string& prefix);
	virtual FSnode* CD(const string& name);
	virtual void NEW(const string& name);
	virtual void NEW(const string& name, const string& extension, const string& data);
	virtual void DEL(const string& name);
	virtual void DEL(const string& name, const string& extension);
	virtual FSnode* EXE(ofstream& log_file_, Folder* cdir);

	//pomocne funkcije za pristup zasticenim podacima
	virtual string getExtension() const;
	string getName() const;
	FSnode* getParent() const;
	virtual FSnode* getChild(const string& name) ;
	virtual FSnode* getChild(const string& name, const string& extension);

protected:
	string name_;
	FSnode* parent_;
};

//Folder FSnode
class Folder : public FSnode {
public:
	Folder(const string& name, FSnode* parent);
	~Folder();

	//zadane funkcije
	void LS(ofstream& log_file_) override;
	void LS(ofstream& log_file_, const string& prefix) override;
	FSnode* CD(const string& name) override;
	void NEW(const string& name) override;
	void NEW(const string& name, const string& extension, const string& data) override;
	void DEL(const string& name) override;
	void DEL(const string& name, const string& extension) override;

	//pomocne funkcije za pristup zasticenim podacima
	FSnode* getChild(const string& name) override;
	FSnode* getChild(const string& name, const string& extension) override;

private:
	list<FSnode*> children_;

};

//zajednicki podskup svih vrsta fajlova
class File : public FSnode {
public:
	File(const string& name, FSnode* parent, const string& data, const string& extension);
	~File();

	void LS( ofstream& log_file_) override;
	void LS(ofstream& log_file_, const string& prefix) override;

	string getData() const;
	void setData(string data);
	string getExtension() const override;
	void setExtension(string extension);
	
protected:
	string extension_;
	string data_; 
};

//tekst datoteka
class File_txt : public  File {
public:
	File_txt(const string& name, FSnode* parent, const string& data, const string& extension = "txt");
private:
};

//exe datoteka dodaje-> EXE() metodu
class File_exe : public  File {
public:
	File_exe(const string& name, FSnode* parent, const string& data, const string& extension="exe");

	FSnode* EXE(ofstream& log_file_, Folder* cdir) override;
private:
};

#endif