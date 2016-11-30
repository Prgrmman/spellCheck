#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include "../editDist/editDist.hpp"
#include "../reader/reader.hpp"
#include "../freq/freq.hpp"

static std::vector<std::unordered_map<std::string,std::string> > dictionary;
static int maxlen;

void createDict(std::string filename){
	std::string currWord;
	std::vector<std::string> words;
	int currlen;
	int i;
	
	maxlen=0;
	std::ifstream testfile(filename);
	while(testfile >> currWord){
		currlen = currWord.length();
		if(currlen > maxlen){
			maxlen = currlen;
		}
		words.push_back(currWord);
	}
	testfile.close();
	
	for(i=0; i<maxlen; i++){
		std::unordered_map<std::string,std::string> temp;
		dictionary.push_back(temp);
	}
	
	for(i=0; i<words.size(); i++){
		dictionary.at(words.at(i).length()-1).insert(make_pair(words.at(i), words.at(i)));
	}        

	/*for(i=0; i<maxlen; i++){
		if(dictionary.at(i).size() != 0){
			for(auto it : dictionary.at(i)){
					std::cout << it.first << std::endl;
			}
			std::cout << std::endl;
		}
	}*/
}

bool findWord(std::string word){
	if(word.length() <= maxlen){
		std::unordered_map<std::string,std::string>::iterator it;
		if ((it = dictionary.at(word.length()-1).find(word)) != dictionary.at(word.length()-1).end()){// if the word is not the map
			return true;
		} 
	}
    return false;
}

std::list<std::string> withinTwoEdits(std::string word){
	//if iteration of unordered maps possible, can still do this part easily
	int numRowCheck;
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
			
		}
		else if(wordLength >= maxlen-1){
			
		}
		else{
			
		}
		candidates.push_back("hi");
		return candidates;
	}
}

std::string findCorrection(std::string word){
	//std::string correction;
	std::list<std::string> candidates;
	candidates = withinTwoEdits(word);
	return candidates.front();
}
