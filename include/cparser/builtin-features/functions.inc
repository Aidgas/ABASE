#include <string.h>
#include <cmath>
#include <sys/time.h>
#include <unistd.h>
#include <algorithm>
#include <functional>
#include <vector>

#include "../../ah_api.h"
#include "../../nrex/nrex.hpp"
#include "../../cpppath.h"
#include "../../utils/util_filesys.h"

extern "C"
{
    #include "../../utils/buf.h"
}

using namespace std;

namespace builtin_functions {

    /* * * * * Built-in Functions: * * * * */
    packToken exit(TokenMap scope) {
        
        throw std::runtime_error("exit");
        
        return packToken::None();
    }

    packToken default_print(TokenMap scope) {
        // Get the argument list:
        TokenList list = scope["args"].asList();

        bool first = true;
        for (packToken item : list.list()) {
            if (first) {
                first = false;
            } else {
                std::cout << " ";
            }

            if (item->type == STR) {
                std::cout << item.asString();
            } else {
                std::cout << item.str();
            }
        }

        std::cout << std::endl;

        return packToken::None();
    }

    packToken default_sum(TokenMap scope) {
        // Get the arguments:
        TokenList list = scope["args"].asList();

        if (list.list().size() == 1 && list.list().front()->type == LIST) {
            list = list.list().front().asList();
        }

        double sum = 0;
        for (packToken num : list.list()) {
            sum += num.asDouble();
        }

        return sum;
    }
    
    packToken default_maxDigitInList(TokenMap scope) {
        // Get the arguments:
        TokenList list = scope["args"].asList();

        if (list.list().size() == 1 && list.list().front()->type == LIST) {
            list = list.list().front().asList();
        }

        bool init = false;
        double result = 0, v;
        for (packToken num : list.list()) {
            
            v = num.asDouble();
            
            if( ! init ) 
            { 
                result = v;
                init = true;
            }
            else if( result < v )
            {
                result = v;
            }
        }

        return result;
    }
    
    packToken default_minDigitInList(TokenMap scope) {
        // Get the arguments:
        TokenList list = scope["args"].asList();

        if (list.list().size() == 1 && list.list().front()->type == LIST) {
            list = list.list().front().asList();
        }

        bool init = false;
        double result = 0, v;
        for (packToken num : list.list()) {
            
            v = num.asDouble();
            
            if( ! init ) 
            { 
                result = v;
                init = true;
            }
            else if( result > v )
            {
                result = v;
            }
            
        }

        return result;
    }

    packToken default_eval(TokenMap scope) {
        std::string code = scope["value"].asString();
        // Evaluate it as a calculator expression:
        return calculator::calculate(code.c_str(), scope);
    }

    packToken default_float(TokenMap scope) {
        packToken tok = scope["value"];
        if (tok->type & NUM) return tok.asDouble();

        // Convert it to double:
        char* rest;
        const std::string& str = tok.asString();
        errno = 0;
        double ret = strtod(str.c_str(), &rest);

        if (str == rest) {
            throw std::runtime_error("Could not convert \"" + str + "\" to float!");
        } else if (errno) {
            std::range_error("Value too big or too small to fit a Double!");
        }
        return ret;
    }

    packToken default_int(TokenMap scope) {
        packToken tok = scope["value"];
        if (tok->type & NUM) return tok.asInt();

        // Convert it to double:
        char* rest;
        const std::string& str = tok.asString();
        errno = 0;
        int64_t ret = strtol(str.c_str(), &rest, 10);

        if (str == rest) {
            throw std::runtime_error("Could not convert \"" + str + "\" to integer!");
        } else if (errno) {
            std::range_error("Value too big or too small to fit an Integer!");
        }
        return ret;
    }

    packToken default_str(TokenMap scope) {
        // Return its string representation:
        packToken tok = scope["value"];
        if (tok->type == STR) return tok;
        return tok.str();
    }
    
    packToken default_version(TokenMap scope) {
        
        packToken tok( AHTables::getVersion() );
        
        return tok.str();
    }

    packToken default_type(TokenMap scope) {
        packToken tok = scope["value"];
        packToken* p_type;

        switch (tok->type) {
            case NONE: return "none";
            case VAR: return "variable";
            case REAL: return "real";
            case INT: return "integer";
            case BOOL: return "boolean";
            case STR: return "string";
            case FUNC: return "function";
            case IT: return "iterable";
            case TUPLE: return "tuple";
            case STUPLE: return "argument tuple";
            case LIST: return "list";
            case MAP:
                p_type = tok.asMap().find("__type__");
                if (p_type && (*p_type)->type == STR) {
                    return *p_type;
                } else {
                    return "map";
                }
            default: return "unknown_type";
        }
    }

    packToken default_sqrt(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return sqrt(number);
    }
    
    packToken default_cbrt(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return cbrt(number);
    }
    
    packToken default_hypot(TokenMap scope) {
        // Get a single argument:
        double x = scope["x"].asDouble();
        double y = scope["y"].asDouble();

        return hypot(x, y);
    }
    
    packToken default_max(TokenMap scope) {
        // Get a single argument:
        double x = scope["x"].asDouble();
        double y = scope["y"].asDouble();

        return max(x, y);
    }
    
    packToken default_min(TokenMap scope) {
        // Get a single argument:
        double x = scope["x"].asDouble();
        double y = scope["y"].asDouble();

        return min(x, y);
    }
    
    packToken default_fmod(TokenMap scope) {
        // Get a single argument:
        double numer = scope["numer"].asDouble();
        double denom = scope["denom"].asDouble();

        return fmod(numer, denom);
    }

    packToken default_sin(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return sin(number);
    }

    packToken default_sinh(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return sinh(number);
    }
    
    packToken default_asin(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return asin(number);
    }
    
    packToken default_asinh(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return asinh(number);
    }

    packToken default_cos(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return cos(number);
    }

    packToken default_cosh(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return cosh(number);
    }
    
    packToken default_acos(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return acos(number);
    }
    
    packToken default_acosh(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return acosh(number);
    }

    packToken default_tan(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return tan(number);
    }

    packToken default_tanh(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return tanh(number);
    }

    packToken default_atanh(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return atanh(number);
    }

    packToken default_atan(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return atan(number);
    }

    packToken default_exp(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return exp(number);
    }
    
    packToken default_exp2(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return exp2(number);
    }
    
    packToken default_expm1(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return expm1(number);
    }
    
    packToken default_log(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return log(number);
    }
    
    packToken default_log2(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return log2(number);
    }
    
    packToken default_log10(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return log10(number);
    }
    
    packToken default_log1p(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return log1p(number);
    }
    
    packToken default_logb(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return logb(number);
    }
    
    packToken default_floor(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return floor(number);
    }
    
    packToken default_ceil(TokenMap scope) {
        // Get a single argument:
        double number = scope["value"].asDouble();

        return ceil(number);
    }
    
    packToken default_trunc(TokenMap scope) {
        // Get a single argument:
        double number = scope["value"].asDouble();

        return trunc(number);
    }
    
    packToken default_round(TokenMap scope) {
        // Get a single argument:
        double number = scope["value"].asDouble();

        return round(number);
    }
    
    packToken default_rint(TokenMap scope) {
        // Get a single argument:
        double number = scope["value"].asDouble();

        return rint(number);
    }

    packToken default_abs(TokenMap scope) {
        // Get a single argument:
        double number = scope["num"].asDouble();

        return std::abs(number);
    }

    const args_t pow_args = {"number", "exp"};

    packToken default_pow(TokenMap scope) {
        // Get two arguments:
        double number = scope["number"].asDouble();
        double exp    = scope["exp"].asDouble();

        return pow(number, exp);
    }
    
    packToken default_atan2(TokenMap scope) {
        // Get a single argument:
        double y = scope["y"].asDouble();
        double x = scope["x"].asDouble();

        return atan2(y, x);
    }
    
    inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    // trim from end
    inline std::string &rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
    }

    // trim from both ends
    inline std::string &trim(std::string &s) {
            return ltrim(rtrim(s));
    }
    
    packToken default_trim(TokenMap scope) {
        
        string v = scope["value"].asString();
        
        return trim(v);
    }
    
    packToken default_ltrim(TokenMap scope) {
        
        string v = scope["value"].asString();
        
        return ltrim(v);
    }
    packToken default_rtrim(TokenMap scope) {
        
        string v = scope["value"].asString();
        
        return rtrim(v);
    }
    
    packToken default_time(TokenMap scope) {
        // Get a single argument:

        return time(NULL);
    }
    
    /// в микросекундах
    packToken get_timestamp(TokenMap scope)
    {
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        return currentTime.tv_sec * (uint64_t)1000000 + currentTime.tv_usec;
    }

    /// в милисекундах
    packToken get_time_in_ms(TokenMap scope)
    {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        return tp.tv_sec * 1000 + tp.tv_usec / 1000;
    }
    
    packToken genarateText(TokenMap scope)
    {
        int len      = scope["len"].asInt();
        string chars = scope["chars"].asString();
        
        int let_chars = chars.length();
        int index  = 0;
        string result = "";

        if(len == 0)
        { return result; }

        srand(time(NULL));
        
        for(unsigned int i = 0; i < len; i++)
        {
            index = (int)floor( let_chars * (double)rand()/RAND_MAX );
            result += chars[ index ];
        }

        return result;
    }
    
    packToken genarateAZ09Text(TokenMap scope)
    {
        int len     = scope["len"].asInt();
        
        char salt[] = "zaqwsxcderfvbgtyhnmjuiklop0123456789";
        int index  = 0;
        string result = "";

        if(len == 0)
        { return result; }

        srand(time(NULL));
        
        for(unsigned int i = 0; i < len; i++)
        {
            index = (int)floor( 35 * (double)rand()/RAND_MAX );
            result += salt[ index ];
        }

        return result;
    }
    
    packToken genUuid(TokenMap scope)
    {
        srand (clock());
        string GUID;
        int t = 0;
        char *szTemp = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
        char *szHex  = "0123456789ABCDEF";
        char *szHex2 = "FEDCBA9876543210";
        int nLen = strlen(szTemp);

        for (t=0; t < nLen; t++)
        {
            int r = rand() % 15;
            char c = szTemp[t];

            switch(c)
            {
                case 'x' : { c = szHex[r]; } break;
                case 'y' : { c = szHex2[r]; } break;
                default: break;
            }

            GUID += c;
        }

        return GUID;
    }
    
    /* * * * * default constructor functions * * * * */

    packToken default_list(TokenMap scope) {
        // Get the arguments:
        TokenList list = scope["args"].asList();

        // If the only argument is iterable:
        if (list.list().size() == 1 && list.list()[0]->type & IT) {
            TokenList new_list;
            Iterator* it = static_cast<Iterable*> (list.list()[0].token())->getIterator();

            packToken* next = it->next();
            while (next) {
                new_list.list().push_back(*next);
                next = it->next();
            }

            delete it;
            return new_list;
        } else {
            return list;
        }
    }

    packToken default_map(TokenMap scope) {
        return scope["kwargs"];
    }

    /* * * * * Object inheritance tools: * * * * */

    packToken default_extend(TokenMap scope) {
        packToken tok = scope["value"];

        if (tok->type == MAP) {
            return tok.asMap().getChild();
        } else {
            throw std::runtime_error(tok.str() + " is not extensible!");
        }
    }
    
    packToken string_lower(TokenMap scope) {
        std::string str = scope["value"].asString();
        std::string out;
        for (char c : str) {
            out.push_back(tolower(c));
        }
        return out;
    }

    packToken string_upper(TokenMap scope) {
        std::string str = scope["value"].asString();
        std::string out;
        for (char c : str) {
            out.push_back(toupper(c));
        }
        return out;
    }
    
    packToken string_len(TokenMap scope) {
        std::string str = scope["value"].asString();
        return static_cast<int64_t> (str.size());
    }

    packToken string_split(TokenMap scope) {
        TokenList list;
        std::string str = scope["value"].asString();
        std::string split_chars = scope["chars"].asString();

        // Split the string:
        size_t start = 0;
        size_t i = str.find(split_chars, 0);
        size_t size = split_chars.size();
        while (i < str.size()) {
            // Add a new item:
            list.push(std::string(str, start, i - start));
            // Resume search:
            start = i + size;
            i = str.find(split_chars, start);
        }

        // Add a new item:
        list.push(std::string(str, start, str.size() - start));

        return list;
    }
    
    packToken string_limit(TokenMap scope) {
        std::string str  = scope["value"].asString();
        int limit        = scope["limit"].asInt();
        
        return truncate(str, limit, false);
    }
    
    
    packToken file_exist(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return cpppath::exists(value);
    }
    
    packToken default_is_dir(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return is_directory(value);
    }
    
    packToken default_humanSize(TokenMap scope) {
        int64_t value = scope["value"].asInt();
        
        return humanSize(value);
    }
    
    packToken default_is_file(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return is_file(value);
    }
    
    packToken default_file_size(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return get_file_size(value.c_str());
    }
    
    packToken default_get_file_contents(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return get_file_contents(value.c_str());
    }
    
    packToken filename(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return cpppath::filename(value);
    }
    
    packToken file_ext(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return cpppath::ext(value);
    }
    
    packToken file_sep(TokenMap scope) {
        return cpppath::sep();
    }
    
    packToken curdir(TokenMap scope) {
        return cpppath::curdir();
    }
    
    packToken normpath(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return cpppath::normpath(value);
    }
    
    packToken dirname(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return cpppath::dirname(value);
    }
    
    packToken filebase(TokenMap scope) {
        std::string value = scope["value"].asString();
        
        return cpppath::filebase(value);
    }
    
    packToken file_open(TokenMap scope) {
        std::string path = scope["path"].asString();
        packToken p_mode = *scope.find("mode");
        std::string mode;

        if (p_mode->type == NONE) {
          mode = "r";
        } else {
          mode = p_mode.asString();
        }
        
        printf("mode.c_str(): %s\n", mode.c_str());
        
        FILE* file = fopen(path.c_str(), mode.c_str());
        
        return packToken(file);
    }
    
    packToken file_close(TokenMap scope) {
        
        FILE* file = scope["file"].asFILE();
        
        fclose(file);
        
        return packToken::None();
    }
    
    packToken file_write_text(TokenMap scope) {
        std::string text = scope["text"].asString();
        
        FILE* file = scope["file"].asFILE();
        
        return fwrite(text.c_str(), 1, text.length(), file);
    }
    
    packToken file_read_line(TokenMap scope) {
        FILE* file = scope["file"].asFILE();
        
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        string result;
        
        if((read = getline(&line, &len, file)) != -1)
        {
            result.append(line);
        }
        else
        {
            return packToken::None();
        }
        
        if (line)
        {
            free(line);
        }
        
        return result;
    }
    
    packToken createFileAndPutText(TokenMap scope) {
        
        std::string path = scope["path"].asString();
        std::string text = scope["text"].asString();
        
        FILE* file = fopen(path.c_str(), "w");
        fwrite(text.c_str(), 1, text.length(), file);
        fclose(file);
        
        return packToken::None();
    }
    
    packToken createBuffer(TokenMap scope) {
        struct buf* b = scope["buffer"].asBuffer();
        
        buf_free(b);
        
        return packToken::None();
    }
    
    packToken freeBuffer(TokenMap scope) {
        struct buf* b = (struct buf*) buf_new();
        
        return packToken(b);
    }
    
    packToken regex_compile(TokenMap scope) {
        std::string pattern = scope["value"].asString();
        
        //printf("-1------------\n");
        
        nrex* regex = new nrex();
        regex->compile(pattern.c_str());
        
        return packToken(regex);
    }
    
    packToken regex_clean(TokenMap scope) {
        
        nrex* regex = scope["regex"].asRegEx();
        delete regex;
        
        return packToken::None();
    }
    
    packToken regex_match(TokenMap scope) {
        
        //printf("-2------------\n");
        
        nrex* regex = scope["regex"].asRegEx();
        
        std::string str = scope["value"].asString();
        
        nrex_result captures[regex->capture_size()];
        if( regex->match((const nrex_char*) str.c_str(), captures) )
        {
            //printf("ok match %d\n", regex->capture_size());
            
            TokenList list;
            
            for(int i = 0; i < regex->capture_size(); i++)
            {
                TokenList list2;
                list2.list().push_back( packToken(captures[i].start) );
                list2.list().push_back( packToken(captures[i].length) );
                
                list.list().push_back( packToken(list2) );
            }
            
            return list;
        }
        
        //printf("no match\n");
        
        return packToken::None();
    }
    
    // Example of replacement function for packToken::str():

    std::string packToken_str(const TokenBase* base, uint32_t nest) {
        const Function* func;

        // Find the TokenMap with the type specific functions
        // for the type of the base token:
        const TokenMap* typeFuncs;
        if (base->type == MAP) {
            typeFuncs = static_cast<const TokenMap*> (base);
        } else {
            typeFuncs = &calculator::type_attribute_map()[base->type];
        }

        // Check if this type has a custom stringify function:
        const packToken* p_func = typeFuncs->find("__str__");
        if (p_func && (*p_func)->type == FUNC) {
            // Return the result of this function passing the
            // nesting level as first (and only) argument:
            func = p_func->asFunc();
            packToken _this = packToken(base->clone());
            TokenList args;
            args.push(static_cast<int64_t> (nest));
            return Function::call(_this, func, &args, TokenMap()).asString();
        }

        // Return "" to ask for the normal `packToken::str()`
        // function to complete the job.
        return "";
    }
    
    /* * * * * LIST Type built-in functions * * * * */

    packToken list_push(TokenMap scope) {
        packToken* list = scope.find("value");
        packToken* token = scope.find("item");

        // If "this" is not a list it will throw here:
        list->asList().list().push_back(*token);

        return *list;
    }

    packToken list_pop(TokenMap scope) {
        TokenList list = scope.find("value")->asList();
        packToken* token = scope.find("pos");

        int64_t pos;

        if ((*token)->type & NUM) {
            pos = token->asInt();

            // So that pop(-1) is the same as pop(last_idx):
            if (pos < 0) pos = list.list().size() - pos;
        } else {
            pos = list.list().size() - 1;
        }

        packToken result = list.list()[pos];

        // Erase the item from the list:
        // Note that this operation is optimal if pos == list.size()-1
        list.list().erase(list.list().begin() + pos);

        return result;
    }

    packToken list_len(TokenMap scope) {
        TokenList list = scope.find("value")->asList();
        return list.list().size();
    }

    packToken list_join(TokenMap scope) {
        TokenList list = scope["value"].asList();
        std::string chars = scope["chars"].asString();
        std::stringstream result;

        std::vector<packToken>::const_iterator it = list.list().begin();
        result << it->asString();
        for (++it; it != list.list().end(); ++it) {
            result << chars << it->asString();
        }

        return result.str();
    }
    
    /* * * * * MAP Type built-in functions * * * * */

    packToken map_pop(TokenMap scope) {
        TokenMap map    = scope["value"].asMap();
        std::string key = scope["key"].asString();

        // Check if the item is available and remove it:
        if (map.map().count(key)) {
            packToken value = map[key];
            map.erase(key);
            return value;
        }

        // If not available return the default value or None
        packToken* def = scope.find("default");
        if (def) {
            return *def;
        } else {
            return packToken::None();
        }
    }

    packToken map_len(TokenMap scope) {
        TokenMap map = scope.find("value")->asMap();
        return map.map().size();
    }

    packToken default_instanceof(TokenMap scope) {
        TokenMap _super = scope["value"].asMap();
        TokenMap* _this = scope["value"].asMap().parent();

        TokenMap* parent = _this;
        while (parent) {
            if ((*parent) == _super) {
                return true;
            }

            parent = parent->parent();
        }

        return false;
    }

    struct Startup {

        Startup() {
            TokenMap& global = TokenMap::default_global();

            global["print"]           = CppFunction(&default_print, "print");
            global["sum"]             = CppFunction(&default_sum, "sum");
            global["sqrt"]            = CppFunction(&default_sqrt, {"num"}, "sqrt");
            global["cbrt"]            = CppFunction(&default_cbrt, {"num"}, "cbrt");
            global["hypot"]           = CppFunction(&default_hypot, {"x", "y"}, "hypot");
            global["max"]             = CppFunction(&default_max, {"x", "y"}, "max");
            global["min"]             = CppFunction(&default_min, {"x", "y"}, "min");
            global["maxDigitInList"]  = CppFunction(&default_maxDigitInList, "maxDigitInList");
            global["minDigitInList"]  = CppFunction(&default_minDigitInList, "minDigitInList");
            global["fmod"]            = CppFunction(&default_fmod, {"numer", "denom"}, "fmod");
            global["sin"]             = CppFunction(&default_sin, {"num"}, "sin");
            global["sinh"]            = CppFunction(&default_sinh, {"num"}, "sinh");
            global["asinh"]           = CppFunction(&default_asinh, {"num"}, "asinh");
            global["asin"]            = CppFunction(&default_asin, {"num"}, "asin");
            global["cos"]             = CppFunction(&default_cos, {"num"}, "cos");
            global["cosh"]            = CppFunction(&default_cosh, {"num"}, "cosh");
            global["acos"]            = CppFunction(&default_acos, {"num"}, "acos");
            global["acosh"]           = CppFunction(&default_acosh, {"num"}, "acosh");
            global["tan"]        = CppFunction(&default_tan, {"num"}, "tan");
            global["tanh"]       = CppFunction(&default_tanh, {"num"}, "tanh");
            global["atanh"]      = CppFunction(&default_atanh, {"num"}, "atanh");
            global["atan"]       = CppFunction(&default_atan, {"num"}, "atan");
            global["atan2"]      = CppFunction(&default_atan2, {"y", "x"}, "atan2");
            global["exp"]        = CppFunction(&default_exp, {"num"}, "exp");
            global["exp2"]       = CppFunction(&default_exp2, {"num"}, "exp2");
            global["expm1"]      = CppFunction(&default_expm1, {"num"}, "expm1");
            global["log"]        = CppFunction(&default_log, {"num"}, "log");
            global["log2"]       = CppFunction(&default_log2, {"num"}, "log2");
            global["log10"]      = CppFunction(&default_log10, {"num"}, "log10");
            global["log1p"]      = CppFunction(&default_log1p, {"num"}, "log1p");
            global["logb"]       = CppFunction(&default_logb, {"num"}, "logb");
            global["floor"]      = CppFunction(&default_floor, {"num"}, "floor");
            global["abs"]        = CppFunction(&default_abs, {"num"}, "abs");
            global["pow"]        = CppFunction(&default_pow, pow_args, "pow");
            global["float"]      = CppFunction(&default_float, {"value"}, "float");
            global["trunc"]      = CppFunction(&default_trunc, {"value"}, "trunc");
            global["round"]      = CppFunction(&default_round, {"value"}, "round");
            global["rint"]       = CppFunction(&default_rint, {"value"}, "rint");
            global["ceil"]       = CppFunction(&default_ceil, {"value"}, "ceil");
            global["real"]       = CppFunction(&default_float, {"value"}, "real");
            global["int"]        = CppFunction(&default_int, {"value"}, "int");
            global["str"]        = CppFunction(&default_str, {"value"}, "str");
            global["eval"]       = CppFunction(&default_eval, {"value"}, "eval");
            global["type"]       = CppFunction(&default_type, {"value"}, "type");
            global["extend"]     = CppFunction(&default_extend, {"value"}, "extend");
            
            global["time"]              = CppFunction(&default_time, "time");
            global["getTimestamp"]      = CppFunction(&get_timestamp, "getTimestamp");
            global["getTimeInMs"]       = CppFunction(&get_time_in_ms, "getTimeInMs");
            global["genarateText"]      = CppFunction(&genarateText, {"len", "chars"}, "genarateText");
            global["genarateAZ09Text"]  = CppFunction(&genarateAZ09Text, {"len"}, "genarateAZ09Text");
            global["genUuid"]           = CppFunction(&genUuid, "genUuid");

            global["trim"]     = CppFunction(&default_trim, {"value"}, "trim");
            global["ltrim"]    = CppFunction(&default_ltrim, {"value"}, "ltrim");
            global["rtrim"]    = CppFunction(&default_rtrim, {"value"}, "rtrim");
            
            global["lower"]    = CppFunction(&string_lower, {"value"}, "lower");
            global["upper"]    = CppFunction(&string_upper, {"value"}, "upper");
            global["strlen"]   = CppFunction(&string_len, {"value"} , "strlen");
            global["split"]    = CppFunction(&string_split, {"value", "chars"} , "split");
            global["string_limit"]    = CppFunction(&string_limit, {"value", "limit"} , "string_limit");
            
            global["regexCompile"]  = CppFunction(&regex_compile, {"value"} , "regexCompile");
            global["regexMatch"]    = CppFunction(&regex_match, {"regex", "value"} , "regexMatch");
            global["regexClean"]    = CppFunction(&regex_clean, {"regex"} , "regexClean");
            
            // Default constructors:
            global["list"]       = CppFunction(&default_list, "list");
            global["map"]        = CppFunction(&default_map, "map");
            
            global["listPush"]   = CppFunction(list_push, {"value", "item"}, "push");
            global["listPop"]    = CppFunction(list_pop, {"value"}, "pop");
            global["listLen"]    = CppFunction(list_len, {"value"}, "listLen");
            global["listJoin"]   = CppFunction(list_join, {"value", "chars"}, "join");
            
            global["mapPop"]     = CppFunction(map_pop, {"value", "key", "default"}, "pop");
            global["mapLen"]     = CppFunction(map_len, {"value"}, "len");
            
            global["filename"]   = CppFunction(filename, {"value"}, "filename");
            global["file_ext"]   = CppFunction(file_ext, {"value"}, "file_ext");
            global["file_sep"]   = CppFunction(file_sep, "file_sep");
            global["curdir"]     = CppFunction(curdir, "curdir");
            global["normpath"]   = CppFunction(normpath, {"value"}, "normpath");
            global["dirname"]    = CppFunction(dirname, {"value"}, "dirname");
            global["filebase"]   = CppFunction(filebase, {"value"}, "filebase");
            global["file_exist"] = CppFunction(file_exist, {"value"}, "file_exist");
            global["is_dir"]     = CppFunction(&default_is_dir, {"value"}, "is_dir");
            global["is_file"]    = CppFunction(&default_is_file, {"value"}, "is_file");
            global["humanSize"]  = CppFunction(&default_humanSize, {"value"}, "humanSize");
            global["file_size"]  = CppFunction(&default_file_size, {"value"}, "file_size");
            global["get_file_contents"]  = CppFunction(&default_get_file_contents, {"value"}, "get_file_contents");
            
            global["file_open"]             = CppFunction(file_open, {"path", "mode"}, "file_open");
            global["file_write_text"]       = CppFunction(file_write_text, {"file", "text"}, "file_write_text");
            global["file_read_line"]        = CppFunction(file_read_line, {"file"}, "file_read_line");
            global["file_close"]            = CppFunction(file_close, {"file"}, "file_close");
            global["createFileAndPutText"]  = CppFunction(createFileAndPutText, {"path", "text"}, "createFileAndPutText");
            
            global["createBuffer"] = CppFunction(createBuffer, "createBuffer");
            global["freeBuffer"]   = CppFunction(freeBuffer, {"buffer"}, "freeBuffer");
            
            global["instanceof"] = CppFunction(&default_instanceof,{"value"}, "instanceof");
            
            global["version"] = CppFunction(&default_version,{"value"}, "version");
            
            global["exit"]   = CppFunction(exit, {}, "exit");
            
            // const
            global["pi"]      = M_PI;
            global["PI"]      = M_PI;
            global["pi2"]     = M_PI_2;
            global["pi4"]     = M_PI_4;
            global["e"]       = M_E;
            global["log2e"]   = M_LOG2E;
            global["log10e"]  = M_LOG10E;
            global["ln2"]     = M_LN2;
            global["ln10"]    = M_LN10;
            global["sqrt2"]   = M_SQRT2;
            global["sqrt1_2"] = M_SQRT1_2;

            // Set the custom str function to `packToken_str()`
            packToken::str_custom() = packToken_str;
        }
    } __CPARSE_STARTUP;

} // namespace builtin_functions
