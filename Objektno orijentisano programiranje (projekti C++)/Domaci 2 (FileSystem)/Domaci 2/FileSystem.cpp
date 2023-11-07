#include "FileSystem.h"
#include "FSparser.h"
#include <iostream>


FileSystem::FileSystem(){
	this->root_ = new Folder("",nullptr);
	this->cd_ = root_;
}

FileSystem::~FileSystem(){
	delete root_;
	log_file_.close();
}

//pomocna funkcija za ispisivanje poruke nakon catch()
void LogException(string ErrMsg, ofstream& log_file_) {
	log_file_ << "Error: "<< ErrMsg << endl;
}

//zadana funkcija
void FileSystem::loadHierarchy(const string& fs_filepath, const string& log_filepath) {
	string folders = fs_filepath;
	string name, extension, new_line, firstword;	
	Folder* nd = (Folder*)cd_;

	fstream inputFile(fs_filepath, ios::in);

	log_file_.open(log_filepath, ios::out);
	try {
		while (getline(inputFile, new_line))
		{
			SplitFirstWord(new_line, firstword);
			for (SplitFirstFolder(firstword, name); !firstword.empty(); SplitFirstFolder(firstword, name)) {
				if (name.empty())
					nd = (Folder*)root_;
				else {
					nd = (Folder*)(nd->getChild(name));
					if (nd == nullptr)
						throw string("Folder " + name + " not found");
				}
			}
			SplitNameExtension(name, extension);
			if (extension.empty()) {
					nd->NEW(name);
			}
			else {
					nd->NEW(name, extension, new_line);
			}
			nd = (Folder*) cd_;
		}
	}
	catch (string ErrMsg) {
		LogException(ErrMsg, log_file_);
	}
	inputFile.close();
}

//zadana funkcija
void FileSystem::execute(const string& filepath) {
	string folders = filepath;
	string next_folder, name, ext, data;
	Folder* nd = (Folder*)cd_;
	File_exe* cd;

	fstream inputFile(filepath, ios::in);
	try {
		cd = new File_exe("", nullptr, "", "");
		while (getline(inputFile, data))
		{
			cd->setData(data);
			nd=(Folder *)cd->EXE(log_file_, nd);
		}
		cd_ = nd;
		delete(cd);
	}
	catch (string ErrMsg) {
		LogException(ErrMsg, log_file_);
	}
}

//nije zadana funkcija kao prethodna, izvrsava vlastiti exe fajl, a ne eksterni
//filepath u ovoj funkciji je u internom fajl sistemu
void FileSystem::execute_local(const string& filepath) {
	string folders = filepath;
	string next_folder, name, ext;
	Folder* nd = (Folder*)cd_;
	File_exe* cd;

	try {
		for (SplitFirstFolder(folders, next_folder); !folders.empty(); SplitFirstFolder(folders, next_folder)) {
			if (next_folder.empty())
				nd = (Folder*)root_;
			else {
				nd = (Folder*)(nd->getChild(next_folder));
				if (nd == nullptr)
					throw string("Folder " + next_folder + " not found");
			}
		}
		name = next_folder;
		SplitNameExtension(name, ext);
		cd = (File_exe*)(ext.empty() ? (nd->getChild(name)) : (nd->getChild(name, ext)));
		if (cd == nullptr)
			throw string("File " + name + "." + ext + " not found");
			cd_ = cd->EXE(log_file_, (Folder*)cd_);
	}
	catch (string ErrMsg) {
		LogException(ErrMsg, log_file_);
	}
}


