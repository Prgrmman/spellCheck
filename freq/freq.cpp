#include <iterator>
#include "freq.hpp"

using namespace std;

/*
 * Implementation of Text object
 */

//Default Constructor
Text::Text(){
    size = 0;
}

// Constructor
Text::Text(const list<string>& words)
{
    size = 0;
    for(string word : words){
        insertWord(word);
    } 
}

// adds word to hash
// if word is already in hash, update it's count
void Text::insertWord(const string word)
{
    unordered_map<string,int>::iterator it;
    if ((it = count_map.find(word)) == count_map.end()){ // if the word is not the map
        words.push_back(word); // add it to the map
        count_map.insert(make_pair(word,1));
    }
    else{
        (it-> second)++;
    }
    size++;
}

// returns the proportion of a word in the text
// returns -1 if the word is not in the text
double Text::getProportion(const string& word, int dist)
{
    unordered_map<string,int>::iterator it;
    if ((it = count_map.find(word)) == count_map.end()){// if the word is not the map
        return -1;
    }
    if (dist == 0) return 1; 
    double prop = it->second / (size * dist * 1.0);
    if (dist == 1) return prop;
    else return prop / 100;

}


