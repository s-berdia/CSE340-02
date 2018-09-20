/*
 * Copyright (C) Sandeep Balaji, 2017
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "task.h"
#include "lexer.h"

using namespace std;

Gram * Task::parse_gram(){
    LexicalAnalyzer lexer;
    Token token = lexer.GetToken();
    Gram * fin = new Gram();
    while(token.token_type != DOUBLEHASH) {
        Gram * g = new Gram();
        fin = g;
        if(Task::start != NULL){
            start = g;
        }
        if(token.token_type == ID){
            g->id = token.lexeme;
            listgram.push_back(gram_list(token.lexeme, g));
            cout << token.lexeme << endl;
        }
        else if(token.token_type == ARROW) {
            cout << "->" << endl;
            token = lexer.GetToken();
            list<list<Gram *> > gl;
            while (token.token_type != HASH){
                list<Gram *> gs;
                while (token.token_type != OR) {
                    if(token.token_type == HASH){
                        lexer.UngetToken(token);
                        break;
                    }
                    Gram * g1 = new Gram();
                    g1->id = token.lexeme;
                    listgram.push_back(gram_list(token.lexeme, g1));
                    cout << token.lexeme << endl;
                    gs.push_back(g1);
                    token = lexer.GetToken();
                    cout << token.token_type << endl;
                }
                token = lexer.GetToken();
                cout << token.token_type << endl;
                gl.push_back(gs);
            }
            g->grams = gl;
        }
        token = lexer.GetToken();
    }
    return fin;
}

void Task::taskone() {
    cout << "Task 1" << endl;
}

void Task::tasktwo() {
    cout << "Task 2" << endl;
}

void Task::taskthree() {
    cout << "Task 3" << endl;
}

void Task::taskfour() {
    cout << "Task 4" << endl;
}

void Task::taskfive() {
    cout << "Task 5" << endl;
}

Gram *Task::getStart() const {
    return start;
}

void Task::setStart(Gram *start) {
    Task::start = start;
}
