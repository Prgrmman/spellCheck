#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include "libs.hpp"

static std::vector<std::unordered_map<std::string,std::string> > dictionary;
static Text reference;
static int maxlen;

void createDict(std::string filename){
    std::string currWord;
    std::list<std::string>::iterator it;
    int currlen, i;

    std::list<std::string> words = getWords(filename);
    Text text(words);
    reference = text;

    maxlen=0;
    for(it = words.begin(); it != words.end(); it++){
        if((*it).length() > maxlen){
            maxlen = (*it).length();
        }
    }

    for(i=0; i<maxlen; i++){
        std::unordered_map<std::string,std::string> temp;
        dictionary.push_back(temp);
    }

    for(it = words.begin(); it != words.end(); it++){
        dictionary.at((*it).length()-1).insert(make_pair((*it), (*it)));
    }
}

bool findWord(std::string word){
    if(word.length() <= maxlen){
        std::unordered_map<std::string,std::string>::iterator it;
        if ((it = dictionary.at(word.length()-1).find(word)) != dictionary.at(word.length()-1).end()){
            return true;
        }
    }
    return false;
}

std::list<std::string> withinTwoEdits(std::string word){
    int i, numRowStart, numRowEnd;
    std::list<std::string> candidates;
    int wordLength = word.length();
    bool found = findWord(word);
    if(found){
        candidates.push_back(word);
        return candidates;
    }
    else{
        //Design chiace here
        if(wordLength <= 2){
            numRowStart = 1;
            numRowEnd = wordLength+2;
        }
        else if(wordLength >= maxlen-1){
            numRowStart = wordLength-2;
            numRowEnd = maxlen;
        }
        else{
            numRowStart = wordLength-2;
            numRowEnd = wordLength+2;
        }
        for(i=numRowStart; i<numRowEnd; i++){
            if(dictionary.at(i-1).size() != 0){
                for(auto it : dictionary.at(i-1)){
                    if(editDistance(word,it.first) <= 2){
                        candidates.push_back(it.first);
                    }
                }
            }
        }
        return candidates;
    }
}
/*
 * Dear Casey,
 *      I think we need to make a small change here. We need to give
 *      words with the smaller edit distance a higher weight.
 *      One possible suggestion:
 *      -> if the word has and edit distance of 2, divide
 *          it's proportion by 2
 */

std::string findCorrection(std::string word){
    std::string correction;
    std::list<std::string> candidates;
    std::list<std::string>::iterator it;
    if(word.length() <= maxlen+2){
        candidates = withinTwoEdits(word);
        if(candidates.size() == 0){
            return "not found";
        }
        correction = candidates.front();
        for(it=candidates.begin(); it != candidates.end(); it++){
            if(reference.getProportion(*it) > reference.getProportion(correction)){
                correction = *it;
            }
        }
        return correction;
    }
    return "Not found";
}
