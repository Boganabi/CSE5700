#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

// Define token types
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUM,
    OPERATOR,
    WHITESPACE,
    ERROR
};

// Token structure to hold token type and lexeme
struct Token {
    TokenType type;
    string lexeme;
};

// vector to relate enumeration to string value
const vector<string> enumtostring = {"Keyword", "Identifier", "Num", "Operator", "Whitespace"}; 

// Function to tokenize input code
vector<Token> tokenize(const string& code) {
    vector<Token> tokens;
    cout << code << endl;
    // use regex to sift through input text
    regex keyword_regex("\\b(while|if|else|return|break|continue|int|float|void)\\b");
    regex identifier_regex("[a-zA-Z_][a-zA-Z0-9_]*");
    regex number_regex("\\b\\d+(\\.\\d+)?([eE][+-]?\\d+)?\\b");
    regex operator_regex("[-+*/()<>=!{}]+");
    regex whitespace_regex("[ ]+");
    // regex error_regex("\\s+");

    smatch match;
    string remaining_code = code;

    while (regex_search(remaining_code, match, keyword_regex) ||
           regex_search(remaining_code, match, identifier_regex) ||
           regex_search(remaining_code, match, number_regex) ||
           regex_search(remaining_code, match, operator_regex) ||
           regex_search(remaining_code, match, whitespace_regex)/* ||
           regex_search(remaining_code, match, error_regex)*/) {
        TokenType token_type;
        if (match.prefix().length() > 0) {
            tokens.push_back({WHITESPACE, match.prefix()});
        }
        if (regex_search(remaining_code, match, keyword_regex)) {
            token_type = KEYWORD;
        } 
        else if (regex_search(remaining_code, match, identifier_regex)) {
            token_type = IDENTIFIER;
        } 
        else if (regex_search(remaining_code, match, number_regex)) {
            token_type = NUM;
        } 
        else if (regex_search(remaining_code, match, operator_regex)) {
            token_type = OPERATOR;
        } 
        else if (regex_search(remaining_code, match, whitespace_regex)) {
            token_type = WHITESPACE;
        }
        // else if (regex_search(remaining_code, match, error_regex)) {
        //     token_type = ERROR;
        // }
        else{
            token_type = ERROR;
        }

        // insert match into list
        if(token_type != WHITESPACE) { tokens.push_back({token_type, match.str()}); }
        remaining_code = match.suffix();
    }

    return tokens;
}

int main() {
    // Read input code from a file
    ifstream file("input.cpp");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // Read the entire file into a string
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Tokenize the input code
    vector<Token> tokens = tokenize(code);

    // Print tokens
    cout << "Class : Lexeme" << endl;
    for (const auto& token : tokens) {
        if(token.type != OPERATOR){
            cout << enumtostring[token.type] << " : " << token.lexeme << endl;
        }
        else{
            cout << token.lexeme << " : " << token.lexeme << endl;
        }
    }

    return 0;
}