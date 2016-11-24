#include <iostream>
#include"lexicon.h"
#include<queue>
#include<stack>
#include<unordered_map>
#include<set>
const std::string PATH = "/Users/haoranzhi/ClionProjects/6771wl/EnglishWords.dat";

class WordLadder{
public:
    WordLadder();
    void findladder();
    void print_soluation();

public:
    std::string source;
    std::string destination;
    bool print_once;
    Lexicon english;
    unordered_map<std::string , int> depth;
    unordered_map<std::string,set<vector<std::string>>> allpath;
    queue<std::string> successors;
    set<vector<std::string>> candidate_soluation;

};

WordLadder::WordLadder():
        source{},destination{},print_once{true},
        english{PATH},depth{},allpath{},successors{},
        candidate_soluation{}
{}





void WordLadder::findladder(){
    successors.push(source);
    set<vector<std::string>> path;
    std::vector<std::string> vsource{source};
    path.insert(vsource);
    allpath[source] = path;
    depth[source] = 1;

    auto index = successors.size();
    bool most_position_is_modified{false};
    bool magic_lock{true}, flag{true};
    const unsigned int maxsize{2147483648};
    unsigned int most_long_length{0};

    while(flag && (index <= maxsize)){
        index = successors.size();
        if(successors.empty()){
            print_soluation();
            break;
        }

        else{
            std::string current_word = successors.front();
            const std::string remember_current =current_word;
            const unsigned int current_depth = depth[successors.front()] + 1;

            successors.pop();
            if(magic_lock && (!candidate_soluation.empty())){
                most_position_is_modified = true;
                magic_lock = false;
                most_long_length = current_depth;
            }

            if(most_position_is_modified && (current_depth > most_long_length)){
                flag = false;
            }

            for(auto current_char = current_word.begin(); current_char != current_word.end(); ++ current_char){
                for(char c = 'a'; c<='z'; ++ c){
                    *current_char = c;
                    if(current_word == destination){
                        auto temp = allpath[remember_current];

                        for(auto v = temp.begin(); v!= temp.end(); ++ v){

                            auto middle = *v;
                            middle.push_back(current_word);
                            candidate_soluation.insert(middle);
                            //candidate_soluation.push_back(middle);
                        }
                    }

                    else{
                        if((current_word == remember_current) || (!english.containsWord(current_word))) {
                            continue;
                        }


                        if((depth[current_word] == 0) || depth[current_word] == current_depth){
                            successors.push(current_word);
                            depth[current_word] = current_depth;
                            auto temp = allpath[remember_current];
                            for(auto v = temp.begin(); v != temp.end(); ++ v){

                                auto middle = *v;
                                middle.push_back(current_word);
                                allpath[current_word].insert(middle);
                            }
                        }
                    }
                }
                current_word = remember_current;
            }

            }


        }
    print_soluation();

}








void WordLadder::print_soluation() {
    if (print_once) {
        print_once = false;
        if (!candidate_soluation.empty()) {
            unsigned int shortest_path = candidate_soluation.begin()->size();
            std::cout << "Found ladder: ";

            for(const auto &s: candidate_soluation){
                if(shortest_path > s.size()){
                    shortest_path = s.size();
                }
            }

            for(const auto &s: candidate_soluation){
                if(s.size() == shortest_path){
                    for(const auto &v:s){
                        std::cout<<v<<" ";
                    }
                    std::cout<<'\n';
                }
            }

        }
        else {
            std::cout << "No ladder found." << '\n';
        }
    }
};
int main() {


    std::string source, destination;
    std::cout << "Enter start word (Return to quit): ";
    std::cin >> source;
    std::cout << "Enter destination word: ";
    std::cin >> destination;


    if (source.size() != destination.size()) {
        std::cout << "No ladder found." << '\n';
    }
    else {

        for (auto c = source.begin(); c != source.end(); ++c) {
            *c = tolower(*c);
        }

        for (auto c = destination.begin(); c != destination.end(); ++c) {
            *c = tolower(*c);
        }
        WordLadder wl= WordLadder();

        wl.source = source;
        wl.destination = destination;

        wl.findladder();

    }
}