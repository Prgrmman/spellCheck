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
    string word;
    while(true){
        cout << "Word: ";
        cin >> word;
        cout << endl;
        correction = findCorrection(word);
        cout << correction << endl;
        
    }
    return 0;
}
