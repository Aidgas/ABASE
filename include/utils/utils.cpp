#include "utils.h"


clock_t get_time_in_milliseconds()
{
    return clock() / (CLOCKS_PER_SEC / 1000);
}

template <typename T>
void remove_duplicates(std::vector<T>& vec)
{
  std::sort(vec.begin(), vec.end());
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

void _cleanup(char** pointer)
{
    if( *pointer != NULL )
    {
        //printf("free\n");
        
        free(*pointer);
        *pointer = NULL;
    }
}

string getPathAppBin(char *argv0)
{
    string result = "";
    char abs_exe_path[512] = "";
    
    char path_save[512] = "";
    char *p;
    string s;

    if(!(p = strrchr(argv0, '/'))) {
        getcwd(abs_exe_path, sizeof(abs_exe_path));
    }
    else {
        *p = '\0';
        getcwd(path_save, sizeof(path_save));
        chdir(argv0);
        getcwd(abs_exe_path, sizeof(abs_exe_path));
        chdir(path_save);
    }
    
    result.append(abs_exe_path);
    
    return result;
}


//------------------------------------------------------------------------------

/// @brief      See if two floating point numbers are approximately equal.
/// @param[in]  a        number 1
/// @param[in]  b        number 2
/// @param[in]  epsilon  A small value such that if the difference between the two numbers is
///                      smaller than this they can safely be considered to be equal.
/// @return     true if the two numbers are approximately equal, and false otherwise
bool is_float_eq(float a, float b, float epsilon) {
    return ((a - b) < epsilon) && ((b - a) < epsilon);
}
bool is_double_eq(double a, double b, double epsilon) {
    return ((a - b) < epsilon) && ((b - a) < epsilon);
}

/// @brief      See if floating point number `a` is > `b`
/// @param[in]  a        number 1
/// @param[in]  b        number 2
/// @param[in]  epsilon  a small value such that if `a` is > `b` by this amount, `a` is considered
///             to be definitively > `b`
/// @return     true if `a` is definitively > `b`, and false otherwise
bool is_float_gt(float a, float b, float epsilon) {
    return a > b + epsilon;
}
bool is_double_gt(double a, double b, double epsilon) {
    return a > b + epsilon;
}

/// @brief      See if floating point number `a` is < `b`
/// @param[in]  a        number 1
/// @param[in]  b        number 2
/// @param[in]  epsilon  a small value such that if `a` is < `b` by this amount, `a` is considered
///             to be definitively < `b`
/// @return     true if `a` is definitively < `b`, and false otherwise
bool is_float_lt(float a, float b, float epsilon) {
    return a < b - epsilon;
}
bool is_double_lt(double a, double b, double epsilon) {
    return a < b - epsilon;
}

/// @brief      Returns true if `a` is definitively >= `b`, and false otherwise
bool is_float_ge(float a, float b, float epsilon) {
    return a > b - epsilon;
}
bool is_double_ge(double a, double b, double epsilon) {
    return a > b - epsilon;
}

/// @brief      Returns true if `a` is definitively <= `b`, and false otherwise
bool is_float_le(float a, float b, float epsilon) {
    return a < b + epsilon;
}
bool is_double_le(double a, double b, double epsilon) {
    return a < b + epsilon;
}


bool is_float_ne(float a, float b, float epsilon)
{
    return !is_float_eq(a, b, epsilon);
}

bool is_double_ne(double a, double b, double epsilon)
{
    return !is_float_eq(a, b, epsilon);
}