#ifndef SIMPLE_TPL_H_INCLUDED
#define SIMPLE_TPL_H_INCLUDED

/**
 * V 1.2
 */

#include <iostream>
#include <map>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "util_string.h"
#include "util_filesys.h"

using namespace std;

typedef map<string, string> TplMap;
typedef map<string, string>::iterator TplMap_Iter;

string tpl_file(string filename, TplMap map_data);


#endif // SIMPLE_TPL_H_INCLUDED
