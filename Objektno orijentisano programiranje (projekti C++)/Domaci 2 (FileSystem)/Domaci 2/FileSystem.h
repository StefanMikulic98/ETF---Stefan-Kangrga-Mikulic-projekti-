#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "FSnode.h"
#include <fstream>
#include <string>
using namespace std;

class FileSystem {
public:
	FileSystem();
	~FileSystem();

	void loadHierarchy(const string& fs_filepath, const string& log_filepath);
	void execute(const string& filepath);
	void execute_local(const string& filepath);

private:
	class FSnode* root_;
	class FSnode* cd_;
	ofstream log_file_;
};

#endif