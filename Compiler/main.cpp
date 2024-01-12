#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Node.h"
#include "SemanticAnalyzer.h"
using namespace std;


int main() {
    string inputString = "int add(int x, int y, int z){"
        "return x + y;"
        "}"
        "int main(int x, int y) {\n"

        "string y = \"compiler\";"
        "int x = 0;"
        "        while (x > 0 & x <100 | false) {\n"
        "            x = x + 1;\n"
        "        }\n"
        "x = add(x, y);"
        "    return 0;\n"
        "}";



    LexicalAnalyzer lexicalAnalyzer(inputString);

    while (lexicalAnalyzer.hasNext()) {
        Token token = lexicalAnalyzer.getToken();
        if (token.name != TokenName::WHITESPACE) {
            cout << "token name: " << token.name << endl;;
            cout << "lexeme: " << token.lexem << endl << endl;
        }
    }
    


    return 0;
}