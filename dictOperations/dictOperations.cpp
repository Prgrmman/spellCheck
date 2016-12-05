#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <utility>
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

std::list<std::pair<std::string, int> > withinTwoEdits(std::string word){
    int i, numRowStart, numRowEnd, editDist;
	std::pair<std::string, int> candidate;
    std::list<std::pair<std::string, int> > candidates;
    int wordLength = word.length();
    bool found = findWord(word);
    if(found){
		candidate = std::make_pair(word, 0);
        candidates.push_back(candidate);
        return candidates;
    }
    else{
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
					editDist = editDistance(word,it.first);
                    if(editDist <= 2){
						candidate = std::make_pair(it.first, editDist);
                        candidates.push_back(candidate);
                    }
                }
            }
        }
        return candidates;
    }
}

std::string findCorrection(std::string word){
	std::string correction;
    std::pair<std::string, int> correctPair;
    std::list<std::pair<std::string, int> > candidates;
    std::list<std::pair<std::string, int> >::iterator it;
    if(word.length() <= maxlen+2){
        candidates = withinTwoEdits(word);
        if(candidates.size() == 0){
            return "not found";
        }
        correctPair = candidates.front();
        for(it=candidates.begin(); it != candidates.end(); it++){
        	if(reference.getProportion((*it).first, (*it).second) > reference.getProportion(correctPair.first, correctPair.second)){
                correction = (*it).first;	
				correctPair = *it;
            }
        }
        return correction;
    }
    return "Not found";
}
