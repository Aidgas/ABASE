#ifndef UTIL_STRING_H_INCLUDED
#define UTIL_STRING_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;


struct FindSubString
{
    int start, end;
    string find_token;
};

struct SubStringInfo
{
    int start, end;
    string find_token, value;
    
    SubStringInfo()
    {
        start = end = 0;
        find_token = "";
        value = "";
    }
};

/**
    Когда realloc() возвращает NULL, вы теряете вашу ссылку на предыдущее выделение памяти.
    FreeBSD предоставляет удобную функцию, reallocf(), которая эквивалентна следующей.
*/
void *reallocf(void* ptr, size_t size);

/**
    Возвращает массив строк.
    В случае ошибки возвращает NULL
    Внимание! после использован его надо освободить
*/
vector<string> _str_split(char *_str, char delimeter, int limit);

char* trim(char *str);
char* trim_space(char *str);

char* trim2(char *str, const char *seps);

std::string string_format(const std::string &fmt, ...);
string string_replace( string src, string const& target, string const& repl);

vector<string> string_split(const string &s, char delim);

static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

std::string truncate(std::string str, size_t width, bool show_ellipsis=true);

/**
 * 
 * @param str
 * @param search
 * @param offset
 * @param ignore_case
 * @param skip_string_blocks
 * @return [start_pos, end_pos]
 */
int* findSubString(
            char* str
          , char* search
          , int offset = 0
          , bool ignore_case = true
          , bool skip_string_blocks = true
      );

FindSubString* findSubString(
            char* str
          , vector<string> search
          , int offset = 0
          , bool ignore_case = true
          , bool skip_string_blocks = true
      );



char* _getWord(char* src, int len_src, int offset, char* stop_chars, int *offset_save );
char* _getWordStopSpace(char* src, int len_src, int offset, int *offset_save );
bool _skipSpace(char* src, int len_src, int *offset);
char* _getStringQuoted(char* src, int len_src, int offset, int *offset_save, bool signle_quote = true);
vector<string> _splitParametersByChar(char *src, int len_src, char ch = ',');
char* _getStringCurlyBrackets2(char* src, int len_src, int offset, int *offset_save, bool return_result = true);
char* _getStringCurlyBrackets(char* src, int len_src, int offset, int *offset_save);
bool _skipStringBlock(char *str, int len_src, int *offset, bool single_guote = true);
char *substr(const char *str, int start, int end);

bool icasecmp(const string& l, const string& r);
bool icasecmp(const wstring& l, const wstring& r);


void build_decoding_table();
void base64_cleanup();
char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);
unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);

string strLimitLien(string &s, int limit);
vector<string> getListWords(string where);

struct SplitByWordList
{
    vector<SubStringInfo*> result;
    int count;
    
    bool isToken(string name, int index)
    {
        if( index < 0 || index >= count )
        {
            return false;
        }
        
        for(int i = 0; i < count; i++)
        {
            if( i == index && icasecmp(name, result[i]->find_token) )
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool isTokenExist(string name)
    {
        for(int i = 0; i < count; i++)
        {
            if( icasecmp(name, result[i]->find_token) )
            {
                return true;
            }
        }
        
        return false;
    }
    
    SubStringInfo* getByToken(string name)
    {
        for(int i = 0; i < count; i++)
        {
            if( icasecmp(name, result[i]->find_token) )
            {
                return result[i];
            }
        }
        
        return NULL;
    }
    
    SplitByWordList()
    {
        count = 0;
    }
    
    ~SplitByWordList()
    {
        for(int i = 0; i < count; i++)
        {
            delete result[i];
        }
    }
};

SplitByWordList* splitByWordList(
            char* str
          , vector<string> search
          , int offset = 0
          , bool ignore_case = true
          , bool skip_string_blocks = true
      );

#endif // UTIL_STRING_H_INCLUDED
