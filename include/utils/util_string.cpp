#include "util_string.h"

std::string string_format(const std::string &fmt, ...)
{
    int size = 100;
    std::string str;
    va_list ap;
    while (1)
    {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size)
        {
            str.resize(n);
            //printf("\nresize %d\n", n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

string string_replace( string src, string const& target, string const& repl)
{
    // handle error situations/trivial cases

    if (target.length() == 0) {
        // searching for a match to the empty string will result in
        //  an infinite loop
        //  it might make sense to throw an exception for this case
        return src;
    }

    if (src.length() == 0) {
        return src;  // nothing to match against
    }

    size_t idx = 0;

    for (;;) {
        idx = src.find( target, idx);
        if (idx == string::npos)  break;

        src.replace( idx, target.length(), repl);
        idx += repl.length();
    }

    return src;
}

/*
vector<string> string_split(string text, char sep)
{
  unsigned int start = 0, end = 0;
  vector<string> result;

  while ((end = text.find(sep, start)) != string::npos)
  {
    result.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  result.push_back(text.substr(start));

  return result;
}*/

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> string_split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

std::string truncate(std::string str, size_t width, bool show_ellipsis)
{
    if (str.length() > width)
        if (show_ellipsis)
            return str.substr(0, width) + "...";
        else
            return str.substr(0, width);
    return str;
}


bool is_number(const std::string& s)
{
    return( strspn( s.c_str(), "-.0123456789" ) == s.size() );
}

///-----------------------------------------------------------------------------
void *reallocf(void* ptr, size_t size)
{
    void *newptr = realloc(ptr, size);
    if (NULL == newptr && ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }

    return newptr;
}
/// ----------------------------------------------------------------------------
vector<string> _str_split(char *_str, char delimeter, int limit)
{
    int i = 0, len_str = strlen(_str);
    int _len_tmp_str = 0;
    char *_tmp_str = NULL;
    vector<string> result;

    /// parse _str
    for(i=0; i < len_str; i++)
    {
        if(
               (_str[i] == delimeter)
            && (
                    (limit == 0)
                 || (limit > 0 && limit > result.size() + 1)
                )
          )
        {
            // reset tmp str
            if(_tmp_str != NULL)
            {
                result.push_back(_tmp_str);
            }

            _len_tmp_str = 0;
        }
        else
        {
            _len_tmp_str += 1;
            _tmp_str = (char *)reallocf(_tmp_str, _len_tmp_str+1);

            _tmp_str[_len_tmp_str-1] = _str[i];
            _tmp_str[_len_tmp_str]   = '\0';
        }
    }

    if( _len_tmp_str > 0 )
    {
        //printf("++ %s;\n", _tmp_str);
        result.push_back(_tmp_str);
    }

    free(_tmp_str);

    return result;
}

char* trim(char * s) 
{
    int l = strlen(s);

    while(isspace(s[l - 1])) --l;
    while(* s && isspace(* s)) ++s, --l;

    return strndup(s, l);
}

char* trim_space(char *str)
{
    char *end;
    /* skip leading whitespace */
    while (isspace(*str)) {
        str = str + 1;
    }
    /* remove trailing whitespace */
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end = end - 1;
    }
    /* write null character */
    *(end+1) = '\0';
    return str;
}

int* findSubString(
            char* str
          , char* search
          , int offset
          , bool ignore_case
          , bool skip_string_blocks
      )
{
    int len_str      = strlen(str);
    int len_pattent  = strlen(search);
    bool find        = false;
    
    for(int i = offset; i < len_str; i++)
    {
        if(    skip_string_blocks 
            && _skipStringBlock(str, len_str, &i) )
        {
            continue;
        }
        
        find = true;
        
        for(int j = 0, k = i; j < len_pattent && k < len_str; j++, k++)
        {
            if( ignore_case )
            {
                if( toupper(str[k]) != toupper(search[j]) )
                {
                    find = false;
                    break;
                }
            }
            else
            {
                if( str[k] != search[j] )
                {
                    find = false;
                    break;
                }
            }
        }
        
        if( find )
        {
            int *result = new int[2];
            result[0] = i;
            result[1] = i + len_pattent;
            return result;
        }
    }
    
    return NULL;
}

FindSubString* findSubString(
            char* str
          , vector<string> search
          , int offset
          , bool ignore_case
          , bool skip_string_blocks
      )
{
    int len_str      = strlen(str), len_pattent;
    bool find        = false;
    
    for(int i = offset; i < len_str; i++)
    {
        if(    skip_string_blocks 
            && _skipStringBlock(str, len_str, &i) )
        {
            continue;
        }
        
        for(int tt = 0; tt < search.size(); tt++)
        {
            len_pattent  = strlen(search[tt].c_str());
            find = true;

            for(int j = 0, k = i; j < len_pattent && k < len_str; j++, k++)
            {
                if( ignore_case )
                {
                    if( toupper(str[k]) != toupper(search[tt][j]) )
                    {
                        find = false;
                        break;
                    }
                }
                else
                {
                    if( str[k] != search[tt][j] )
                    {
                        find = false;
                        break;
                    }
                }
            }

            if( find )
            {
                FindSubString* result = new FindSubString();
                result->start         = i;
                result->end           = i + len_pattent;
                result->find_token    = search[tt];
                
                return result;
            }
        }
    }
    
    return NULL;
}

SplitByWordList* splitByWordList(
            char* str
          , vector<string> search
          , int offset
          , bool ignore_case
          , bool skip_string_blocks
      )
{
    SplitByWordList* r = new SplitByWordList();
    
    int save_i, cmpare;
    int len_str      = strlen(str), len_pattent;
    bool find        = false;
    string _value    = "";
    
    for(int i = offset; i < len_str; i++)
    {
        save_i = i;
        
        if(    skip_string_blocks 
            && _skipStringBlock(str, len_str, &save_i) )
        {
            _value.append(str, i, save_i - i + 1);
            
            i = save_i;
            continue;
        }
        
        find = false;
        
        for(int tt = 0; (i == 0 || isspace(str[i - 1]) ) && tt < search.size(); tt++)
        {
            len_pattent  = strlen(search[tt].c_str());
            find = false;
            cmpare = 0;

            for(int j = 0, k = i; j < len_pattent && k < len_str; j++, k++)
            {
                if( ignore_case )
                {
                    if( toupper(str[k]) != toupper(search[tt][j]) )
                    {
                        find = false;
                        break;
                    }
                    else
                    {
                        find = true;
                        cmpare += 1;
                    }
                }
                else
                {
                    if( str[k] != search[tt][j] )
                    {
                        find = false;
                        break;
                    }
                    else
                    {
                        find = true;
                        cmpare += 1;
                    }
                }
            }
            
            if( cmpare != len_pattent )
            {
                find = false;
            }

            if( find && isspace(str[i + len_pattent]) )
            {
                if( r->count > 0 )
                {
                    r->result[ r->count - 1 ]->value = trim(_value);
                }
                
                _value = "";
                
                SubStringInfo* item = new SubStringInfo();
                item->start         = i;
                item->end           = i + len_pattent;
                item->find_token    = search[tt];
                
                r->result.push_back(item);
                r->count  = r->result.size();
                
                i += len_pattent;
                
                break;
            }
        }
        
        if( ! find )
        {
            _value += str[i];
        }
    }
    
    if( r->count > 0 )
    {
        r->result[ r->count - 1 ]->value = trim(_value);
    }
    
    return r;
}

bool skipBrackets(char* src, int len_src, int *offset)
{
    int count_opened = 0, count_closed = 0;
    //int start_index = 0;
    int end_index = 0;
    
    for(int i = *offset; i < len_src; i++)
    {
        _skipSpace(src, len_src, &i);
        
        if( src[i] == '(' )
        {
            _skipSpace(src, len_src, &i);
            
            count_opened += 1;
            //start_index = i;
            
            for(int j = i + 1; j < len_src; j++)
            {
                _skipSpace(src, len_src, &j);
                
                if( _skipStringBlock(src, len_src, &j) )
                {
                    continue;
                }
                else if( src[j] == '(' )
                {
                    count_opened += 1;
                }
                else if( src[j] == ')' )
                {
                    count_closed += 1;
                    
                    if( count_opened == count_closed )
                    {
                        end_index = j;
                        break;
                    }
                }
                
                *offset = j + 1;
                end_index = j;
            }
            
            break;
        }
        else if( src[i] == '{' )
        {
            _skipSpace(src, len_src, &i);
            
            count_opened += 1;
            //start_index = i;
            
            for(int j = i + 1; j < len_src; j++)
            {
                _skipSpace(src, len_src, &j);
                
                if( _skipStringBlock(src, len_src, &j) )
                {
                    continue;
                }
                else if( src[j] == '{' )
                {
                    count_opened += 1;
                }
                else if( src[j] == '}' )
                {
                    count_closed += 1;
                    
                    if( count_opened == count_closed )
                    {
                        end_index = j;
                        break;
                    }
                }
                
                *offset = j + 1;
                end_index = j;
            }
            
            break;
        }
    }
    
    return false;
}

bool _skipStringBlock(char *src, int len_src, int *offset, bool single_guote)
{
    int j = *offset;
    
    if(
            ( j == 0 && src[j] == '"' )
         || ( j > 0  && src[j] == '"' && src[j-1] != '\\' )
      )
    {
        //skip quotes
        for(int k = j + 1; k < len_src; k++)
        {
            j = k;
            *offset = k;

            if( 
                    ( j == 0 && src[j] == '"' )
                 || ( j > 0 && src[j] == '"' && src[j-1] != '\\' )
              )
            {
                return true;
            }
        }
    }
    else if(
                single_guote
            &&  (
                    ( j == 0 && src[j] == '\'' )
                 || ( j > 0  && src[j] == '\'' && src[j-1] != '\\' )
            )
        )
    {
        //skip quotes
        for(int k = j + 1; k < len_src; k++)
        {
            j = k;
            *offset = k;

            if(
                    ( j == 0 && src[j] == '\'' )
                 || ( j > 0 && src[j] == '\'' && src[j-1] != '\\' )
              )
            {
                return true;
            }
        }
    }
    
    return false;
}

char* _getStringCurlyBrackets(char* src, int len_src, int offset, int *offset_save)
{
    char* result = NULL;
    int k = 0;
    
    for(int i = offset; i < len_src; i++)
    {
        _skipSpace(src, len_src, &i);
        
        if( src[i] == '{' )
        {
            _skipSpace(src, len_src, &i);
            
            for(int j = i + 1; j < len_src; j++)
            {
                if( src[j] == '}' )
                {
                    *offset_save = j + 1;
                    break;
                }
                else
                {
                    if( k == 0 )
                    {
                        result = (char *) malloc( 2 );
                        result[ k ]      = src[j];
                        result[ k + 1 ]  = '\0';
                    }
                    else
                    {
                        result = (char *) reallocf( result,  k + 2 );
                        result[ k ]      = src[j];
                        result[ k + 1 ]  = '\0';
                    }

                    //printf("strlen(result): %d %d %d %s\n", strlen(result), k, j, result );

                    *offset_save = j + 1;
                    k += 1;
                }
            }
            
            break;
        }
    }
    
    return result;
}

// поиск конца скобок, пропуская строки, и внутренние внутренние скобки
char* _getStringCurlyBrackets2(char* src, int len_src, int offset, int *offset_save, bool return_result)
{
    char* result = NULL;
    int count_opened = 0, count_closed = 0;
    int start_index = 0;
    int end_index = 0;
    
    for(int i = offset; i < len_src; i++)
    {
        _skipSpace(src, len_src, &i);
        
        if( src[i] == '(' )
        {
            _skipSpace(src, len_src, &i);
            
            count_opened += 1;
            start_index = i;
            
            for(int j = i + 1; j < len_src; j++)
            {
                _skipSpace(src, len_src, &j);
                
                if( _skipStringBlock(src, len_src, &j) )
                {
                    continue;
                }
                else if( src[j] == '(' )
                {
                    count_opened += 1;
                }
                else if( src[j] == ')' )
                {
                    count_closed += 1;
                    
                    *offset_save = j + 1;
                    
                    if( count_opened == count_closed )
                    {
                        end_index = j;
                        break;
                    }
                }
                
                end_index = j;
            }
            
            break;
        }
    }
    
    if( end_index - start_index > 0 )
    {
        int l = end_index - start_index - 1;
        
        result = (char *) calloc( l + 1, 1 );
        strncpy(result, src + start_index + 1, l);
        
        printf("line: %d %d |%s|\n", __LINE__, l, result);
    }
    
    return result;
}

// параметры по запятой
vector<string> _splitParametersByChar(char *src, int len_src, char ch)
{
    vector<string> result;
    int start = 0;
    
    for(int j = 0; j < len_src; j++)
    {
        _skipSpace(src, len_src, &j);
        
        if( src[j] == '(' )
        {
            _getStringCurlyBrackets2(src, len_src, j, &j);
        }
        
        if( _skipStringBlock(src, len_src, &j) )
        {
            continue;
        }
        else if( src[j] == ch )
        {
            if( j - start > 0 )
            {
                int l = j - start;

                char *tmp = (char *) calloc( l + 1, 1 );
                tmp[l] = '\0';
                strncpy(tmp, src + start, l );

                printf("line: %d l=%d start=%d |%s|\n", __LINE__, l, start, tmp);
                
                result.push_back(tmp);
                
                free(tmp);
            }
            
            start = j + 1;
        }
        
    }
    
    if( len_src - start > 0 )
    {
        int l = len_src - start;

        char *tmp = (char *) calloc( l + 1, 1 );
        strncpy(tmp, src + start, l );

        printf("line: %d %d |%s|\n", __LINE__, l, tmp);

        result.push_back(tmp);

        free(tmp);
    }
    
    return result;
}

char* _getStringQuoted(char* src, int len_src, int offset, int *offset_save, bool signle_quote)
{
    char* result = NULL;
    int k = 0;
    
    for(int i = offset; i < len_src; i++)
    {
        _skipSpace(src, len_src, &i);
        
        if( src[i] == '"' )
        {
            for(int j = i + 1; j < len_src; j++)
            {
                if(
                        ( j == 0 && src[j] == '"' )
                     || ( j > 0 && src[j] == '"' && src[j-1] != '\\' )
                )
                //if( src[j] == '"' )
                {
                    *offset_save = j + 1;
                    break;
                }
                else
                {
                        if( k == 0 )
                        {
                            result = (char *) malloc( 2 );
                            result[ k ]      = src[j];
                            result[ k + 1 ]  = '\0';
                        }
                        else
                        {
                            result = (char *)  reallocf( result,  k + 2 );
                            result[ k ]      = src[j];
                            result[ k + 1 ]  = '\0';
                        }
                        
                        //printf("strlen(result): %d %d %d %s\n", strlen(result), k, j, result );
        
                        *offset_save = j + 1;
                        k += 1;
                }
            }
            
            break;
        }
        else if( signle_quote && src[i] == '\'' )
        {
            for(int j = i + 1; j < len_src; j++)
            {
                if(
                        ( j == 0 && src[j] == '\'' )
                     || ( j > 0 && src[j] == '\'' && src[j-1] != '\\' )
                )
                //if( src[j] == '"' )
                {
                    *offset_save = j + 1;
                    break;
                }
                else
                {
                        if( k == 0 )
                        {
                            result = (char *) malloc( 2 );
                            result[ k ]      = src[j];
                            result[ k + 1 ]  = '\0';
                        }
                        else
                        {
                            result = (char *)  reallocf( result,  k + 2 );
                            result[ k ]      = src[j];
                            result[ k + 1 ]  = '\0';
                        }
                        
                        //printf("strlen(result): %d %d %d %s\n", strlen(result), k, j, result );
        
                        *offset_save = j + 1;
                        k += 1;
                }
            }
            
            break;
        }
    }
    
    return result;
}

/*
 *  return next not space position
*/
bool _skipSpace(char* src, int len_src, int *offset)
{
    for(int i = *offset; i < len_src; i++)
    {
        if( ! isspace(src[i]) )
        {
            *offset = i;
            return true;
        }
    }
    
    return false;
}

/*
 * return string (offset --> [stop_chars])
 */
char* _getWord(char* src, int len_src, int offset, char* stop_chars, int *offset_save )
{
    char* result = NULL;
    int i, j, k = 0, len_stop_chars = strlen( stop_chars );
    
    _skipSpace(src, len_src, &offset);
    
    for(i = offset; i < len_src; i++)
    {
        for(j = 0; j < len_stop_chars; j++)
        {
            if( src[i] == stop_chars[j] )
            {
                return result;
            }
        }
        
        if( k == 0 )
        {
            result = (char *) malloc( 2 );
            result[ k ]      = src[i];
            result[ k + 1 ]  = '\0';
        }
        else
        {
            result = (char *) reallocf( result,  k + 2 );
            result[ k ]      = src[i];
            result[ k + 1 ]  = '\0';
        }
        
        //printf("strlen(result): %d %d\n", strlen(result), k );
        
        *offset_save = i + 1;
        k += 1;
    }
    
    return result;
}

char* _getWordStopSpace(char* src, int len_src, int offset, int *offset_save )
{
    char* result = NULL;
    int i, j, k = 0;
    
    _skipSpace(src, len_src, &offset);
    
    for(i = offset; i < len_src; i++)
    {
        if( isspace(src[i]) )
        {
            return result;
        }
        
        if( k == 0 )
        {
            result = (char *) malloc( 2 );
            result[ k ]      = src[i];
            result[ k + 1 ]  = '\0';
        }
        else
        {
            result = (char *) reallocf( result,  k + 2 );
            result[ k ]      = src[i];
            result[ k + 1 ]  = '\0';
        }
        
        //printf("strlen(result): %d %d\n", strlen(result), k );
        
        *offset_save = i + 1;
        k += 1;
    }
    
    return result;
}

/*
 * Get a substring of `str` from `start` to `end`
 */
char *substr(const char *str, int start, int end) 
{
    if (0 > start) 
        return NULL;
    
    int len = strlen(str);
    // -1 == length of string
    if (-1 == end) end = len;
    
    if (end <= start) 
        return NULL;
    
    int diff = end - start;
    if (len == diff) 
        return strdup(str);
    
    if (len < start) 
        return NULL;
    
    if (len + 1 < end) 
        return NULL;

    char *res = (char *) malloc(sizeof(char) * diff + 1);
    
    if (NULL == res) 
        return NULL;
    
    memset(res, '\0', diff + 1);
    strncpy(res, str + start, diff);
    return res;
}

bool icasecmp(const string& l, const string& r)
{
    return l.size() == r.size()
        && equal(l.cbegin(), l.cend(), r.cbegin(),
            [](string::value_type l1, string::value_type r1)
                { return toupper(l1) == toupper(r1); });
}

bool icasecmp(const wstring& l, const wstring& r)
{
    return l.size() == r.size()
        && equal(l.cbegin(), l.cend(), r.cbegin(),
            [](wstring::value_type l1, wstring::value_type r1)
                { return towupper(l1) == towupper(r1); });
}


///--------------------------------------------------------------------------------------------
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

void build_decoding_table() {

    decoding_table = (char *)malloc(256);

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}

void base64_cleanup() {
    free(decoding_table);
}

char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length) {

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char*)malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (unsigned int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}

unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length) {

    if (decoding_table == NULL) build_decoding_table();

    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    unsigned char *decoded_data = (unsigned char *)malloc(*output_length);
    if (decoded_data == NULL) return NULL;

    for (unsigned int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return decoded_data;
}

vector<string> getListWords(string where)
{
    int len   = where.length();
    char* str = (char*) where.c_str();
    vector<string> list;

    for(int i = 0; i < len; i++)
    {
        _skipSpace(str, len, &i);
        if( _skipStringBlock(str, len, &i) )
        {
            continue;
        }

        int save_offset;
        char* w = _getWord(str, len, i, "!@#$%^&*()-_+[]{}/=*~`\\\'\"<>?,| \t\n\r\f\v", &save_offset);

        if( w != NULL )
        {
            if( ! isdigit(w[0]) )
            {
                list.push_back( w );
                printf("w: %s\n", w);
            }

            free(w);

            i = save_offset - 1;
        }
    }

    std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());

    return list;
}