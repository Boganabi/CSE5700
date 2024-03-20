#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Define token types
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUM,
    OPERATOR,
    SEPARATOR,
    ERROR
};

// Token structure to hold token type and lexeme
struct Token {
    TokenType type;
    string lexeme;
};

// vector to relate enumeration to string value
const vector<string> enumtostring = {"Keyword", "Identifier", "Num", "Operator", "Separator", "Error"}; 

// Function to tokenize input code
vector<Token> tokenize(const string& code) {
    vector<Token> tokens;
    istringstream iss(code);
    char ch;

    while (iss >> noskipws >> ch) {
        string token;
        token += ch;

        if (token == " " || token == "\t" || token == "\n" || token == "\r") {
            continue; // Skip whitespace characters
        }

        if (token == "while" || token == "if" || token == "else" ||
            token == "return" || token == "break" || token == "continue" ||
            token == "int" || token == "float" || token == "void") {
            tokens.push_back({KEYWORD, token});
        } 
        else if (isdigit(token[0])) {
            // Handle numeric constants
            while (iss >> std::noskipws >> ch && (isdigit(ch) || ch == '.' || ch == 'E')) {
                token += ch;
                if(ch == 'E'){
                    iss >> std::noskipws >> ch;
                    cout << token << endl;
                    cout << ch << endl;
                    if(ch == '-' || isdigit(ch)){
                        token += ch;
                    }
                    else{
                        // iss.putback(ch);
                        break;
                    }
                }
            }
            iss.putback(ch);
            tokens.push_back({NUM, token});
        } 
        else if (token.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789") == string::npos) {
            // Handle identifiers
            while (iss >> std::noskipws >> ch && (isalnum(ch) || ch == '_')) {
                token += ch;
            }
            iss.putback(ch);
                if (token == "while" || token == "if" || token == "else" ||
                token == "return" || token == "break" || token == "continue" ||
                token == "int" || token == "float" || token == "void" || token == "for") {
                tokens.push_back({KEYWORD, token});
            }
            else{
                tokens.push_back({IDENTIFIER, token});
            }
        } 
        else if (token == "(" || token == ")" || token == "{" || token == "}" || token == ";" ||
                   token == "+" || token == "-" || token == "*" || token == "/" || token == "<" ||
                   token == ">" || token == "<=" || token == ">=" || token == "==" || token == "!=" ||
                   token == "&&" || token == "||" || token == "!" || token == "=") {
            tokens.push_back({OPERATOR, token});
        } 
        else {
            // Handle error: unrecognized token
            // cerr << "Error: Unrecognized token: " << token << endl;
            tokens.push_back({ERROR, token});
        }
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