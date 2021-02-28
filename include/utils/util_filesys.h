#ifndef UTIL_FILESYS_H_INCLUDED
#define UTIL_FILESYS_H_INCLUDED

#include <iostream>
#include <glob.h>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool file_exists(string path);
bool is_directory(string pathname);
bool is_file(string pathname);
unsigned long get_file_size(const char * filepath);
unsigned long get_file_time_last_modified(const char *filepath);
unsigned long get_file_time_create(const char *filepath);

vector<string> directory_glob(const string& pat);

std::string get_file_contents(const char *filename);

const char *humanSize(uint64_t bytes);

#endif // UTIL_FILESYS_H_INCLUDED
