#include <iostream>
#include "dictOperations/dictOperations.hpp"

using namespace std;

int main(int argc, char** argv)
{
    string dictName = argv[1];
    createDict(dictName);
    string correction, word;
    while(true){
        cout << "Word: ";
        cin >> word;
        correction = findCorrection(word);
        cout << correction << endl;
    }
    return 0;
}
