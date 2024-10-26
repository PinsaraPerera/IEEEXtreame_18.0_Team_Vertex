// find the maximum number of substring without getting repeated
# include <iostream>
# include <unordered_set>
# include <string>
using namespace std;

class Solution {
    void allPossibleSubstrings(string& s,int pos,int& maxCount,unordered_set<string>& uniqueSubstring){
        if(pos==s.size()){
            if(maxCount < uniqueSubstring.size())
                maxCount = uniqueSubstring.size();
            return;
        }
        string substring; //Current substring
        for(int i=pos;i<s.size();++i){
            substring.push_back(s[i]);

            //Check if current substring is unique
            if(uniqueSubstring.count(substring)==0){
                uniqueSubstring.insert(substring);
                allPossibleSubstrings(s,i+1,maxCount,uniqueSubstring);
                uniqueSubstring.erase(substring);
            }
        }
    }
public:
    int maxUniqueSplit(string s) {
        int maxCount=0;
        unordered_set<string> uniqueSubstring;
        allPossibleSubstrings(s,0,maxCount,uniqueSubstring);
        return maxCount;
    }
};