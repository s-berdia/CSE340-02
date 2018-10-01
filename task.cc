//
// Created by Sandeep Balaji on 9/29/18.
//
#include <iostream>
#include "task.h"
#include "lexer.h"

void task::parse_gram(){
    LexicalAnalyzer lexer;
    Token token = lexer.GetToken();
    map<string, list<list<string>>> grams;
    while(token.token_type != DOUBLEHASH) {
        string terminal = token.lexeme;
        token = lexer.GetToken();
        if(token.token_type != ARROW){
            cout << "Error Syntax" << endl;
        }
        token = lexer.GetToken();
        list<string> terms;
        while (token.token_type != HASH){
            terms.push_back(token.lexeme);
            token = lexer.GetToken();
        }
        if(grams.find(terminal) != grams.end()){
            grams.find(terminal)->second.push_back(terms);
        }else{
            list<list<string>> tmp;
            tmp.push_back(terms);
            grams[terminal] = tmp;
        }
        token = lexer.GetToken();
    }
    setGrams(grams);
}

void task::taskone() {
    list<string> terminals;
    list<string> non_terminals;
    for (auto const& gram : getGrams()) {
        terminals.push_back(gram.first);
    }
    for (auto const& gram : getGrams()){
//        cout << gram.first << endl;
        for (auto const& g : gram.second) {
            for (auto const& l : g) {
//                cout << l << endl;
                if(find(non_terminals.begin(), non_terminals.end(), l) == non_terminals.end()
                   && find(terminals.begin(), terminals.end(), l) == terminals.end()){
                    non_terminals.push_back(l);
                }
            }
        }
    }
    setNon_terminals(non_terminals);
    setTerminals(terminals);
}

void task::tasktwo() {
    cout << "task2 2" << endl;
}

void task::taskthree() {
    cout << "task2 3" << endl;
}

void task::taskfour() {
    cout << "task2 4" << endl;
}

void task::taskfive() {
    cout << "task2 5" << endl;
}

map<string, list<list<string>>> &task::getGrams() {
    return grams;
}

void task::setGrams(map<string, list<list<string>>> &grams) {
    task::grams = grams;
}

const list<string> &task::getTerminals() const {
    return terminals;
}

void task::setTerminals(const list<string> &terminals) {
    task::terminals = terminals;
}

const list<string> &task::getNon_terminals() const {
    return non_terminals;
}

void task::setNon_terminals(const list<string> &non_terminals) {
    task::non_terminals = non_terminals;
}
