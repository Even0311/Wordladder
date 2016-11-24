//
// Created by Haoran Zhi on 16/8/11.
//

#include <iostream>
#include "genlib.h"
#include "lexicon.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <set>
#include <string>

//This assignment is completed by Muzi Song(z5033171).

//The map is used to store the word and level
std::unordered_map<std::string,int> wordLevel;
//The queue is used to store words level by levey to perform a BFS search
std::queue<std::string> BFSqueue;
//The map is used to store all the path go to the current word , which is as the map key
std::unordered_map<std::string,std::set<std::vector<std::string>>> wordPath;

//The main bredth First Search procedure
void breadFirstSearch(std::string start,std::string end){
    Lexicon Lex("EnglishWords.dat");
    //These two variable to control to find all the shortest path ,
    //Once find one solution, if the level exceed the shortest one , break
    //Then complete searching the same level for all the possible solution path , then break
    int shortestLevel=0;
    int findFlag=0;
    BFSqueue.push(start);
    wordLevel[start]=1;
    std::vector<std::string> a {start};
    wordPath[start].insert(a);
    //pop continuely from the queue to perform the BFS
    while(!BFSqueue.empty()){
        std::string word=BFSqueue.front();
        BFSqueue.pop();
        int level=wordLevel[word];
        //find a longer path compared with the shortest one , just break
        if((findFlag==1) && (level>shortestLevel)){
            break;
        }
        //find one solution
        if(word==end){
            shortestLevel=wordLevel[word];
            findFlag=1;
        }
        //change every char of one word to construct all the one hop away word
        //and construct the valid word path by using the previous word path
        int b = word.length();
        for (int i = 0;i<b;i++){
            for(int j = 'a';j<'z'+1;j++){
                std::string temp=word;
                char m = (char) j;
                temp.replace(i,1,1,m);
                if(temp == word ||!Lex.containsWord(temp)){
                    continue;
                }
                if(wordPath.count(temp)==0) {
                    wordLevel[temp]=level+1;
                    std::set<std::vector<std::string>> allPath=wordPath[word];
                    for(auto it2=allPath.begin();it2!=allPath.end();++it2){
                        std::vector<std::string> newPath=*it2;
                        newPath.push_back(temp);
                        wordPath[temp].insert(newPath);
                    }
                    BFSqueue.push(temp);
                }else{
                    if(wordLevel[temp]==level+1){
                        std::set<std::vector<std::string>> allPath=wordPath[word];
                        for(std::set<std::vector<std::string>>::iterator it2=allPath.begin();it2!=allPath.end();++it2){
                            std::vector<std::string> newPath=*it2;
                            newPath.push_back(temp);
                            wordPath[temp].insert(newPath);
                        }
                        BFSqueue.push(temp);
                    }else{
                        continue;
                    }
                }
            }
        }
    }
    //print all the shortest solution path
    if(shortestLevel!=0) {
        cout<<"Found ladder: ";

        for (std::set<std::vector<std::string>>::iterator it3 = wordPath[end].begin(); it3 != wordPath[end].end(); ++it3){
            std::vector<std::string> pathList=*it3;
            for(std::vector<std::string>::iterator it4=pathList.begin();it4<pathList.end();++it4){
                cout << *it4<<" ";
            }
            cout<<endl;
        }
    }

    else if(shortestLevel==0){
        cout <<"No ladder found."<<endl;
    }
}


int main() {
    std::string start;
    std::string end;
    cout<<"Enter start word (RETURN to quit): ";
    cin >>start;
    std::transform(start.begin(), start.end(), start.begin(), ::tolower);
    cout<<"Enter destination word: ";
    cin >>end;
    std::transform(end.begin(), end.end(), end.begin(), ::tolower);
    breadFirstSearch(start,end);
    return 0;
}
