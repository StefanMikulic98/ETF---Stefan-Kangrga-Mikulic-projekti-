#ifndef FSPARSER_H
#define FSPARSER_H

#include "FSnode.h"
#include <string>
using namespace std;

//skracuje input_string za prvu rec, vraca prvu rec u firstword
void SplitFirstWord(string& input_string, string& firstword); 

//vraca prvu liniju i oduzima je iz input_string
void SplitFirstLine(string& input_string, string& firstline);

//vraca ime prvog foldera u input_path i skracuje input_path do prvog '\\'
void SplitFirstFolder(string& input_path, string& firstfolder);

//nalazi ekstenziju, izbacuje ".ext" iz name , vraca u extension
void SplitNameExtension(string& name, string& extension);

#endif