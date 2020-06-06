#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <set>
#include <fstream>

using std::istringstream;
using std::pair;
using std::ofstream;
using std::ifstream;
using std::cin;
using std::cout;
using std::set;
using std::string;
using std::map;
auto &npos = string::npos;

void openFile(ifstream& file) {
    string name;
    cout << "Enter the name of the file (e.g. 'source.txt'):\n";
    cin >> name;
    file.open(name);
    while (file.fail()) {
        cout << "Failed to open '" << name << "'! Please check if the name is correct and enter again:\n";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> name;
        file.open(name);
    }
}

void readFile(map<string, pair<set<size_t>, size_t>>& words, set<string>& links, ifstream& file) {
    istringstream iss;
    size_t count = 0;
    string word, line;

    while (getline(file, line)) {
        count++; // line count
        iss.str(line);
        while (iss >> word) {
            if (word.find("http://") != npos || word.find("https://") != npos || word.find("www.") != npos) {
                links.insert(word);
            } else {
                // https://stackoverflow.com/questions/6319872/how-to-strip-all-non-alphanumeric-characters-from-a-string-in-c
                word.erase(std::remove_if(word.begin(), word.end(), [](char character) { return !isalpha(character); } ), word.end());
                if (!word.empty()) {   // if the word contains any letters
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower); // transform to lowercase
                    words[word].first.insert(count);// capture the line number (std::set - no duplicates)
                    words[word].second++; // frequency++
                }
            }
        }
        iss.clear();
    }
}

void printResults(map<string, pair<set<size_t>, size_t>>& words, set<string>& links) {
    ofstream file ("results.txt");
    file << std::left << std::setw(18) << "Word" << std::setw(14)
         << "Repeats" << std::setw(15) << "In lines" << "\n";
    file << "---------------------------------------------------------------------------------------";
    for (const auto& word : words)
        if (word.second.second >= 2) {
            file << "\n" << std::setw(18) << word.first
                 << std::setw(14) << word.second.second;
            unsigned int i = 0;
            for (auto lineNumber : word.second.first) {// list the line numbers
                if (i > 12) {
                    i = 0;
                    file << std::endl << std::left << std::setw(32) << " ";
                } else {
                    i++;
                }
                file << std::left << std::setw(4) << lineNumber;
            }
        }

    file << "\n\nURL:\n";
    file << std::endl;
    for (const string& url : links)
        file << url << std::endl;
    file.close();
}

int main() {
    ifstream file;
    set<string> links;
    map<string, pair<set<size_t>, size_t>> words;
    // first = word string
    // second.first = line numbers
    // second.second = times repeated
    cout << "Hello! I am WordCounter - I will count the words and find URLs in your .txt file.\n"
            "For accurate results, please make sure the ending of the URL is followed by a space.\n";
    openFile(file);
    readFile(words, links, file);
    file.close();
    printResults(words, links);
    cout << "Success! To view the results, open the file 'results.txt'.";
    return 0;
}