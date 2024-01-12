#include "LexicalAnalyzer.h"



LexicalAnalyzer::LexicalAnalyzer(const string& inputString) {
    this->inputString = inputString + "$";
    this->position = 0;
}



Token LexicalAnalyzer::getToken() {
    Token token;
    int state = 0;
    if (!this->hasNext()) {
        return token;
    }
    
    for (;this->hasNext(); this->position++) {
        char symbol = inputString[this->position];
        if (this->isSubtractionOperator(symbol)) {
            token.name = TokenName::ADDSUB;
            token.lexem = symbol;
            this->position++;
            return token;
        }

        int nextState = this->getNextState(state, symbol);
        if (nextState == -1) {
            if (symbolStack.empty()) {
                exit(1);
            }
            
            return this->createToken(state);
        }

        symbolStack.push(symbol);

        state = nextState;
    }

    this->position++;
    return this->createToken(position);
}


bool LexicalAnalyzer::hasNext() {
    return this->position < this->inputString.length();
}
int LexicalAnalyzer::getNextState(int state, char symbol) {
    return this->transitionTable.at(state).find(symbol)->second;
}


Token LexicalAnalyzer::createToken(int state) {
    Token token;

    if (this->finalStates.find(state) == this->finalStates.end()) {
        exit(1);

    }
    token.name = this->finalStates.find(state)->second;
    token.lexem = this->getLexeme();
    if (token.name == TokenName::ID && 
        this->keywords.find(token.lexem) != this->keywords.end()) {
       
        token.name = this->keywords.find(token.lexem)->second;

    }
    return token;
}


string LexicalAnalyzer::getLexeme() {
    string lexeme;

    while (!this->symbolStack.empty()) {
        lexeme += symbolStack.top();
        symbolStack.pop();
    }
    reverse(lexeme.begin(), lexeme.end());
    return lexeme;
}













bool LexicalAnalyzer::isSubtractionOperator(char symbol) {
    if (symbol != '-') {
        return false;
    }
    if (this->position == 0) {
        return false;
    }

    int previousPosition = this->position - 1;
    char previousSymbol = this->inputString[previousPosition];

    while (isspace(previousSymbol) && previousPosition >= 0) {
        previousSymbol = this->inputString[--previousPosition];
    }

    if (isalnum(previousSymbol)) {
        return true;
    }
    return false;
}