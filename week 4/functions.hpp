#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>


void char_file_to_vector(std::vector<char> & v){
    std::ifstream input("bible.txt");
    char c;
    while(input.get(c)){
        v.push_back(c);
    }
    input.close();

}

void print_number_char_vec(const std::vector<char> & v){
    std::cout << "number of chars in vector is: " << v.size() << std::endl;
}


void print_number_lines_vec(const std::vector<char> & v){
    int n_lines = std::count(v.begin(), v.end(), '\n');
    std::cout << "number of lines in vector is: " << n_lines << std::endl;

}


void print_number_alfabet_letters_vec(const std::vector<char> & v){
    int n_letters = std::count_if(v.begin(), v.end(), isalpha);
    std::cout << "number of alfabet letters in vector is: " << n_letters << std::endl;

}


void char_vec_to_lower_case(std::vector<char> & v){
    std::transform(v.begin(), v.end(), v.begin(), [](char c){return std::tolower(c);});
}


std::map<char, int> count_every_letter(const std::vector<char> & v){
    std::map<char, int> letter_dict = {};
    std::string alphabet = "abcdefghijklmnopqrstuwvxyz";
    for(char c : alphabet){
        int n = std::count(v.begin(), v.end(), c);
        letter_dict[c] = n;
    }
    return letter_dict;
}

void print_letters_aplhabet_order(std::map<char, int> dict){
    std::string alphabet = "abcdefghijklmnopqrstuwvxyz";
    std::cout << "in order of the alphabet:" << std::endl;
    for(char c : alphabet){
        int n = dict[c];
        std::cout << "letter:  " << c << " appeared:  " << n << "  times" << std::endl;
    }
    std::cout << std::endl;

}


void print_letters_common_order(std::map<char, int> dict){
    std::map<int, char> map = {};
    std::vector<int> order = {};
    std::string alphabet = "abcdefghijklmnopqrstuwvxyz";
    std::cout << "in order of least common to most common:" << std::endl;
    for(char c : alphabet){
        int n = dict[c];
        map[n] = c;
        order.push_back(n);
    }
    std::sort(order.begin(), order.end());
    for(int n : order){
        char c = map[n];
        std::cout << "letter:  " << c << " appeared:  " << n << "  times" << std::endl;
    }
    std::cout << std::endl;
}


void print_common_words(){
    std::map<std::string, int> word_count;
    std::ifstream input("bible.txt");
    while(!input.eof()){
        std::string temp;
        std::string word;
        input >> temp;
        if(!temp.empty()){
            for(char c : temp){
                if( isalpha(c) ){
                    word = word + c;
                }
            }
            std::transform(word.begin(), word.end(), word.begin(), [](char c){return std::tolower(c);});
            if(!word.empty()){
                auto o = word_count.find(word);
                if(o == word_count.end()){
                    word_count[word] = 1;
                }
                else{
                    o->second++;
                }
            }
        }
    }
    std::map<std::string, int> ss;
    for(unsigned int i = 0; i < 10; i++){
        int most = 0;
        std::string s;
        for(auto it = word_count.begin(); it != word_count.end(); ++it){
            if(it->second > most){
                most = it->second;
                s = it->first;
            }
        }
        ss[s] = most;
        word_count[s] = 0;
    }
    std::vector<int> order;
    std::vector<std::string> words;
    for(auto const& [key, val] : ss){
        order.push_back(val);
        words.push_back(key);
    }

    std::cout << "top 10 most common words:" << std::endl;
    for(unsigned int i = 0; i < 10; i++){
        int index = std::max_element(order.begin(),order.end()) - order.begin();
        int n = order[index];
        std::string s = words[index];
        order.erase(order.begin() + index);
        words.erase(words.begin() + index);
        std::cout << "the word:  " << s << "  appeared:  " << n << "  times" << std::endl;
    }

}


#endif // FUNCTIONS_HPP
