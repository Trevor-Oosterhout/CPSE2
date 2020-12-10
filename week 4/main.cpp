#include "functions.hpp"
#include <vector>
#include <iostream>
#include <functional>
#include <map>


int main() {
    std::map<char, int> dict = {};
    std::vector<char> v = {};
    char_file_to_vector(v);
    print_number_char_vec(v);
    print_number_lines_vec(v);
    print_number_alfabet_letters_vec(v);
    char_vec_to_lower_case(v);
    dict = count_every_letter(v);
    print_letters_aplhabet_order(dict);
    print_letters_common_order(dict);
    print_common_words();

}
