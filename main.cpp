#include <iostream>
#include "dictOperations/dictOperations.hpp"

using namespace std;

int main(int argc, char** argv)
{
    string correction;
	string wordToCorrect = argv[1];
	string dictName = argv[2];
	createDict(dictName);
	correction = findCorrection(wordToCorrect);
	cout << correction << endl;
	
	/*string correction;
	cout << "Testing" << endl;
    list<string> words = getWords(filename);
    Text text(words);
    cout << "freq of " << argv[1] <<" " << text.getProportion(argv[1]) << endl;
    // test edit distance
    string str1 = argv[1]; 
    string str2 = argv[2]; 
    cout << "Edit distance is " << editDistance(str1,str2) << endl;
	string dictName = argv[3];
	//cout << "Current dictionary contents:" << endl;
	createDict(dictName);
	correction = findCorrection("aaron");
	cout << correction << endl;
	correction = findCorrection("aaab");
	cout << correction << endl;*/

    return 0;
}
