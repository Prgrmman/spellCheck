#include "editDist.hpp"
/**
 * Dynamic programming implementation of
 * Levenshtein distance
 **/

using namespace std;
int editDistance(string str1, string str2)
{
    str1 = " " + str1;
    str2 = " "+ str2;
    int len1 = str1.length();
    int len2 = str2.length();
    int dist[len1][len2]; // The dynamic table
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            if (min(i,j) == 0)
                dist[i][j] = max(i,j);
            else{
                int cost = 0; // replacement cost
                if(str1.at(i) != str2.at(j))
                    cost = 1;
                dist[i][j] = min(min(dist[i-1][j]+1, dist[i][j-1]+1), dist[i-1][j-1] + cost);
            }
        }
    }
    return dist[len1-1][len2-1];
}
