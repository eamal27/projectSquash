// Utility Functions
/**
 * @author Elias Amal
 * @author Caleb Phillips
 * @author Michael Stergianis
 */

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Util {
public:
    /**
     * Helper function to trim whitespace from start or end of a string
     * @param str The string to be trimmer
     * @return    A trimmed version of input
     */
    static string trim(const string& str);
    static bool isFloat(const string & s);
    static bool isInteger(const string & s);
};

#endif // UTIL_H
