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
    map<string, int> orders;
    int order = 1;
    orders[token.lexeme] = order;
    order++;
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
            if(orders.find(token.lexeme) == orders.end()){
                orders[token.lexeme] = order;
                order++;
            }
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
    setOrders(orders);
    setGrams(grams);
}

void task::taskone() {
    list<string> non_terminals;
    list<string> terminals;
    for (auto const& gram : getGrams()) {
        non_terminals.push_back(gram.first);
    }
    for (auto const& gram : getGrams()){
        for (auto const& g : gram.second) {
            for (auto const& l : g) {
                if(find(non_terminals.begin(), non_terminals.end(), l) == non_terminals.end()
                   && find(terminals.begin(), terminals.end(), l) == terminals.end()){
                    terminals.push_back(l);
                }
            }
        }
    }
    setNon_terminals(non_terminals);
    setTerminals(terminals);
}

void task::tasktwo() {
//    cout << "task2" << endl;
}

void task::taskthree() {
    map<string, list<string>> first;
    first.insert(pair<string, list<string>> ("#", {"#"}));
    for (auto const &i: getTerminals()){
        first.insert(pair<string, list<string>> (i, {i}));
    }
    for (auto const &i: getNon_terminals()){
        first.insert(pair<string, list<string>> (i, {}));
    }
    for (auto const &i: getGrams()){
        for (auto const &j: i.second){
            if(j.empty()){
                if(find(first[i.first].begin(), first[i.first].end(), "#") == first[i.first].end()) {
                    first.at(i.first).push_back("#");
                }
            }
            if(find(getNon_terminals().begin(), getNon_terminals().end(), j.front()) != getNon_terminals().end()){
                list <string> temp = first.at(j.front());
                temp.remove("#");
                for (auto const &m: temp){
                    if(find(first[i.first].begin(), first[i.first].end(), m) == first[i.first].end()){
                        first[i.first].push_back(m);
//                        cout << "1:" << i.first << "->" << m << endl;
                    }
                }
            }
            else{
                if (!j.empty()){
                    if(find(first[i.first].begin(), first[i.first].end(), j.front()) == first[i.first].end()) {
                        first[i.first].push_back(j.front());
//                        cout << "3:" << i.first << "->" << j.front() << endl;
                    }
                }
            }
            bool epsilon = false;
            list<string>::iterator it;
            for(auto it = j.begin(); it != j.end(); it++){
                if(find(first.at(it->c_str()).begin(), first.at(it->c_str()).end(), "#") != first.at(it->c_str()).end()){
                    //Add next of (&k +1) to first[i.first]
                    list <string> foo = first.at(next(it)->c_str());
                    foo.remove("#");
                    for (auto const &m: foo){
                        if(find(first[i.first].begin(), first[i.first].end(), m) == first[i.first].end()){
                            first[i.first].push_back(m);
//                            cout << "2:" << i.first << "->" << m << endl;
                        }
                    }
                    epsilon = true;
                }
                else{
                    epsilon = false;
                    break;
                }
            }
            if (epsilon){
                if(find(first[i.first].begin(), first[i.first].end(), "#") == first[i.first].end()) {
                    first[i.first].push_back("#");
                }
            }
        }
    }
    setFirst(first);
}

list<string> task::sortThem(list<string> terms){
    map<string, int> ods = getOrders();
    int i, j, n = (int) terms.size(), k = 0;
    string arr[n];
    for (auto const &ar: terms){
        arr[k] = ar;
        k++;
    }
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (ods[arr[j]] > ods[arr[j+1]]) {
                arr[j].swap(arr[j+1]);
            }
        }
    }
    list<string> foo;
    for (int m = 0; m < n; m++){
        foo.push_back(arr[m]);
    }
    return foo;
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

void task::setFirst(const map<string, list<string>> &first) {
    task::first = first;
}

const map<string, list<string>> &task::getFirst() const {
    return first;
}

const map<string, int> &task::getOrders() const {
    return orders;
}

void task::setOrders(const map<string, int> &orders) {
    task::orders = orders;
}
