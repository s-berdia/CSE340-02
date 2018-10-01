//
// Created by Sandeep Balaji on 9/17/18.
//

#ifndef LEXER_PASRSER_TASK_H
#define LEXER_PASRSER_TASK_H
#endif //LEXER_PASRSER_TASK_H
#include <list>
#include <map>

using namespace std;

class task {
private:
    map<string, list<list<string>>> grams;
    list<string> terminals;
    list<string> non_terminals;

public:
    void taskone();
    void tasktwo();
    void taskthree();
    void taskfour();
    void taskfive();
    void parse_gram();
    map<string, list<list<string>>> &getGrams();
    void setGrams(map<string, list<list<string>>> &grams);
    const list<string> &getTerminals() const;
    void setTerminals(const list<string> &terminals);
    const list<string> &getNon_terminals() const;
    void setNon_terminals(const list<string> &non_terminals);
};