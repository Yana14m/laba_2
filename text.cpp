#include "text.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>
using namespace std;

bool isVowel(char c) {
    c=static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}

void processText(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Ошибка: файл не найден!");
    }
    string line, word;
    bool found = false;
    cout << "Подходящие слова:\n";

    while (getline(file, line)) {
        istringstream stream(line);
        while (stream >> word) {
            while (!word.empty() && (word.back() == '.' || word.back() == ',' ||  word.back() == '!' || word.back() == '?')) {
                word.pop_back();
            }

            if (!word.empty() && isVowel(word.front()) && isVowel(word.back())) {
                cout << word << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout<<"В файле нет подходящих слов!\n";
    }
    file.close();
}