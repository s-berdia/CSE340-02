//
// Created by Sandeep Balaji on 9/29/18.
//
#include <iostream>
#include "task.h"
#include "lexer.h"
#include <algorithm>
#include <set>

void task::parse_gram(){
    LexicalAnalyzer lexer;
    Token token = lexer.GetToken();
    map<string, list<list<string>>> grams;
    list<string> orderedGrams;
    map<string, int> orders;
    int order = 1;
    while(token.token_type != DOUBLEHASH) {
        string gram = token.lexeme;
        if(orders.find(token.lexeme) == orders.end()){
            orders[token.lexeme] = order;
            order++;
        }
        string terminal = token.lexeme;
        token = lexer.GetToken();
        if(token.token_type != ARROW){
            cout << "Error Syntax" << endl;
        }
        token = lexer.GetToken();
        list<string> terms;
        while (token.token_type != HASH){
            terms.push_back(token.lexeme);
            gram += " " + token.lexeme + " ";
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
        orderedGrams.push_back(gram);
        token = lexer.GetToken();
    }
    setOrderedGrams(orderedGrams);
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
    map <string, bool> generatingSymbols;
    map <string, bool> fooSymbols;
    map <string, bool> reachableSymbols;
    list<string> uselessSymbols;
    for (auto const &i: getNon_terminals()){
        generatingSymbols[i] = false;
        reachableSymbols[i] = false;
    }
    generatingSymbols["#"] = true;
    for (auto const &i: getTerminals()){
        generatingSymbols[i] = true;
        reachableSymbols[i] = false;
    }
    while(!compare_map1(generatingSymbols, fooSymbols)){
        fooSymbols = generatingSymbols;
        for (auto const &i: getGrams()){
            for (auto const &j: i.second){
                bool gen = true;
                for (auto const &k: j){
                    if (!generatingSymbols[k]){
                        gen = false;
                    }
                }
                if(gen){
                    generatingSymbols[i.first] = true;
                    break;
                }
            }
        }
    }
    reachableSymbols[sortThem(getNon_terminals()).front()] = true;
    map<string, list<list<string>>> grams = getGrams();
    for (auto const &i: sortThem(getNon_terminals())){
        for (auto const &j: grams[i]){
            bool reach = true;
            for (auto const &k: j){
                if (!generatingSymbols[k]){
                    reach = false;
                }
            }
            if (reachableSymbols[i] && generatingSymbols[i] && reach){
                for (auto const &k: j){
                    reachableSymbols[k] = true;
                }
            }
        }
    }
    for (auto const &i: getNon_terminals()){
        if (!(generatingSymbols[i] && reachableSymbols[i])){
            uselessSymbols.push_back(i);
        }
    }
    for (auto const &i: getTerminals()){
        if (!(generatingSymbols[i] && reachableSymbols[i])){
            uselessSymbols.push_back(i);
        }
    }
    setUselessSymbols(uselessSymbols);
}

void task::taskthree() {
    map<string, list<string>> first;
    first["#"] = {"#"};
    for (auto const &i: getTerminals()){
        first.insert(pair<string, list<string>> (i, {i}));
    }
    for (auto const &i: getNon_terminals()){
        first.insert(pair<string, list<string>> (i, {}));
    }
    map<string, list<string>> foo;
    while (!compare_map(first, foo)){
        foo = first;
        for (auto const &i: getGrams()){
            for (auto const &j: i.second){
                if(j.empty()){
                    if(find(first[i.first].begin(), first[i.first].end(), "#") == first[i.first].end()) {
                        // cout << "4:" << i.first << "->" << "#" << endl;
                        first[i.first].push_back("#");
                    }
                    continue;
                }
                if(find(getNon_terminals().begin(), getNon_terminals().end(), j.front()) != getNon_terminals().end()){
                    list <string> temp = first[j.front()];
                    temp.remove("#");
                    for (auto const &m: temp){
                        if(find(first[i.first].begin(), first[i.first].end(), m) == first[i.first].end()){
                            first[i.first].push_back(m);
                           // cout << "1:" << i.first << "->" << m << endl;
                        }
                    }
                }
                else{
                    if (!j.empty()){
                        if(find(first[i.first].begin(), first[i.first].end(), j.front()) == first[i.first].end()) {
                            first[i.first].push_back(j.front());
                           // cout << "3:" << i.first << "->" << j.front() << endl;
                        }
                    }
                }
                bool epsilon = false;
                list<string>::iterator it;
                for(auto it = j.begin(); it != j.end(); it++){
                    if(find(first[it->c_str()].begin(), first[it->c_str()].end(), "#") != first[it->c_str()].end()){
                        //Add next of (&k +1) to first[i.first]
                        if (next(it) != j.end()) {
                            list<string> foo = first[next(it)->c_str()];
                            foo.remove("#");
                            for (auto const &m: foo) {
                                if (find(first[i.first].begin(), first[i.first].end(), m) == first[i.first].end()) {
                                    first[i.first].push_back(m);
                                    // cout << "2:" << i.first << "->" << m << endl;
                                }
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
    }
    setFirst(first);
}

void task::taskfour() {
    map<string, list<string>> follow;
    map<string, list<string>> first = getFirst();
    map<string, list<string>> foo;
    follow[sortThem(getNon_terminals()).front()] = {"$"};
    while (!compare_map(follow, foo)){
        foo = follow;
        for (auto const &i : getGrams()){
            for (auto const &j: i.second){
                list<string>::reverse_iterator it;
                bool eplison = true;
                for (auto it = j.rbegin(); it != j.rend(); it++){
                    if (eplison){
                        if (find(getNon_terminals().begin(), getNon_terminals().end(), it->c_str()) != getNon_terminals().end()){
                            eplison = false;
                            list <string> temp = follow[i.first];
                            temp.remove("#");
                            for (auto const &m: temp){
                                if(find(follow[it->c_str()].begin(), follow[it->c_str()].end(), m) == follow[it->c_str()].end()){
                                    follow[it->c_str()].push_back(m);
                                }
                            }
                        }
                    }
                    if (find(first[it->c_str()].begin(), first[it->c_str()].end(), "#") != first[it->c_str()].end()){
                        eplison = true;
                    }
                    else{
                        break;
                    }
                }
                list<string>::iterator it1;
                list<string>::iterator it2;
                for (auto it1 = j.begin(); it1 != j.end(); it1++){
                    if (find(getNon_terminals().begin(), getNon_terminals().end(), it1->c_str()) == getNon_terminals().end()){
                        continue;
                    }
                    bool epl = true;
                    for (auto it2 = next(it1); it2 != j.end(); it2++){
                        if (!epl){
                            break;
                        }
                        list <string> temp = first[it2->c_str()];
                        temp.remove("#");
                        for (auto const &m: temp){
                            if(find(follow[it1->c_str()].begin(), follow[it1->c_str()].end(), m) == follow[it1->c_str()].end()){
                                follow[it1->c_str()].push_back(m);
                            }
                        }
                        epl = false;
                        if (find(first[it2->c_str()].begin(), first[it2->c_str()].end(), "#") != first[it2->c_str()].end()){
                            epl = true;
                        }
                    }
                }
            }
        }
    }
    setFollow(follow);
}

void task::taskfive() {
    if (!getUselessSymbols().empty()){
        setParser("NO");
        return;
    }
    map<string, list<string>> first = getFirst();
    map<string, list<string>> follow = getFollow();
    for (auto const &h: getGrams()){
        int size = 0;
        set<string> temp;
        if (h.second.size() > 1){
            for (auto const &j: h.second){
                bool epsilon = false;
                for(auto const &k: j){
                    list<string> foo = first[k];
                    foo.remove("#");
                    for (auto const &m: foo) {
                        temp.insert(m);
                        size++;
                    }
                    if(find(first[k].begin(), first[k].end(), "#") != first[k].end()){
                        epsilon = true;
                    }
                    else{
                        epsilon = false;
                        break;
                    }
                }
                if (j.empty()){
                    temp.insert("#");
                    size++;
                }
                if (epsilon){
                    temp.insert("#");
                    size++;
                }
            }
            if(size != temp.size()){
                setParser("NO");
                return;
            }
        }
    }
    for (auto const &h: first){
        if (find(h.second.begin(), h.second.end(), "#") != h.second.end()){
            bool intersect = true;
            for (auto const &l: first[h.first]){
                for (auto const &k: follow[h.first]){
                    if (l == k){
                        intersect = false;
                    }
                }
            }
            if (!intersect){
                setParser("NO");
                return;
            }
        }
    }
    setParser("YES");
}

bool reachable_set(list<list<string>> grams, map <string, bool> reachableSymbols){
    for (auto const &a: grams){
        for (auto const &b: a){
            if (!reachableSymbols[b]){
                return false;
            }
        }
    }
    return true;
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

bool task::compare_map(map<string, list<string>> first, map<string, list<string>> second){
    if (first.size() != second.size()){
        return false;
    }
    for (auto const &t: first){
        if (!compare_list(second[t.first], t.second)){
            return false;
        }
    }
    return true;
}

bool task::compare_map1(map<string, bool> first, map<string, bool> second){
    if (first.size() != second.size()){
        return false;
    }
    for (auto const &t: first){
        if (second[t.first] != t.second){
            return false;
        }
    }
    return true;
}

bool task::compare_list(list<string> first, list<string> second){
    if (first.size() != second.size()){
        return false;
    }
    first = sortThem(first);
    second = sortThem(second);
    list<string>::iterator it1;
    list<string>::iterator it2 = second.begin();
    for (it1 = first.begin(); it1 != first.end(); it1++){
        if (*it1 != *it2){
            cout << *it1 << *it2 << endl;
            return false;
        }
        it2++;
    }
    return true;
}

const list<string> &task::getUselessSymbols() const{
    return uselessSymbols;
}
void task::setUselessSymbols(const list<string> &uselessSymbols){
    task::uselessSymbols = uselessSymbols;
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

void task::setFollow(const map<string, list<string>> &follow) {
    task::follow = follow;
}

const map<string, list<string>> &task::getFollow() const {
    return follow;
}

const map<string, int> &task::getOrders() const {
    return orders;
}

void task::setOrders(const map<string, int> &orders) {
    task::orders = orders;
}

const string &task::getParser() const{
    return parser;
}

void task::setParser(const string &parser){
    task::parser = parser;
}

const list<string> &task::getOrderedGrams() const{
    return task::orderedGrams;
}

void task::setOrderedGrams(const list<string> &orderedGrams){
    task::orderedGrams = orderedGrams;
}

list<string> task::splitString(string str){
    list<string> splits;
    size_t current, previous = 0;
    current = str.find(" ");
    while (current != std::string::npos) {
        splits.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(" ", previous);
    }
    splits.push_back(str.substr(previous, current - previous));
    return splits;
}
