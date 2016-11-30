/********************************************************************
 * --Library dictOperations--                                       *
 *  Suggested use:                                                  *
 *  --> use createDict(std::string filename) to                     *
 *      Create a dictionary of words to be used for finding words   *
 *      within 2 edit distance                                      *
 ********************************************************************/
#ifndef DICTOPERATIONS_H
#define DICTOPERATIONS_H
#include <string>

void createDict(std::string word);
std::string findCorrection(std::string word);

#endif
