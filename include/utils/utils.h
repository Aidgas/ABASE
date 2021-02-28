#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <algorithm>
#include <vector>
#include <time.h>
#include <string>
#include <string.h>
#include <unistd.h>

#define EPSILON 0.0001

using namespace std;


clock_t get_time_in_milliseconds();

template <typename T>
void remove_duplicates(std::vector<T>& vec);

void _cleanup(char** pointer);

string getPathAppBin(char *argv0);


/// @brief      Equal: returns true if `a` is approximately == `b`, and false otherwise
bool is_float_eq(float a, float b, float epsilon);
bool is_double_eq(double a, double b, double epsilon);

/// @brief      Not Equal: returns true if `a` is definitely != `b`, and false otherwise
bool is_float_ne(float a, float b, float epsilon);
bool is_double_ne(double a, double b, double epsilon);

/// @brief      Less Than: returns true if `a` is definitively < `b`, and false otherwise
bool is_float_lt(float a, float b, float epsilon);
bool is_double_lt(double a, double b, double epsilon);

/// @brief      Less Than or Equal: returns true if `a` is definitively <= `b`, and false otherwise
bool is_float_le(float a, float b, float epsilon);
bool is_double_le(double a, double b, double epsilon);

/// @brief      Greater Than: returns true if `a` is definitively > `b`, and false otherwise
bool is_float_gt(float a, float b, float epsilon);
bool is_double_gt(double a, double b, double epsilon);

/// @brief      Greater Than or Equal: returns true if `a` is definitively >= `b`, and false
///             otherwise
bool is_float_ge(float a, float b, float epsilon);
bool is_double_ge(double a, double b, double epsilon);

#endif // UTILS_H_INCLUDED
