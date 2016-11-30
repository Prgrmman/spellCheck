#include <set>
#include <stdlib.h>
#include "reader.hpp"
#define isascii(c)  ((c & ~0x7F) == 0)
using namespace std;

/*
 * Strips string of unwanted characters
 * returns new formatted string
 * all characters returned are in lowercase
 */
static string strip_punct(const string& s, const string& chars)
{
    stringstream ss;
    for(char c: s){
        if (chars.find(c) == string::npos && isascii(c))
            ss << (char)tolower(c);
    }
    return ss.str();
}

/*
 * splits string into tokens based on delimits
 */
static list<string> split(const string& s, const string& delimits)
{
    list<string> result;
    size_t pos = 0;
    size_t npos;
    while((npos = s.find_first_of(delimits, pos)) != string::npos){
        if (npos > pos)
            result.push_back(s.substr(pos, npos - pos));
        pos = npos + 1;
    }
    if (pos < s.length())
        result.push_back(s.substr(pos, npos - pos));
    return result;
}
/*
 * Process line based on mode
 */
static list<string> processWords(const string& s)
{
    string temp = s;
    temp = strip_punct(temp, "\",.?!;:()\r_#*[]/\\");  
    return split(temp, " \n\t");
}
/*
 * returns true if word contains a digit
 */
static bool containsNumber(const string& word)
{
    for(char c: word)
        if(isdigit(c))
            return true;
    return false;
}

/*
 * returns list of words from file
 */
list<string> getWords(const string& filename)
{
    list<string> words;
    fstream file;
    file.open(filename);
    if (!file.is_open()){
        cerr << "File open error\n";
        exit(1);
    }
    string line;
    while(getline(file, line)){
        if (line.length() > 0){
            list<string> lineWords = processWords(line);
            lineWords.remove_if(containsNumber);
            words.insert(words.end(), lineWords.begin(), lineWords.end());
        }
    }
    file.close();
    return words;
}



