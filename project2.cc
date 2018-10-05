/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "task.h"
#include <algorithm>

using namespace std;

int main (int argc, char* argv[])
{
    int task;
    class task t;
    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }
    t.parse_gram();
    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
    t.taskone();
    t.tasktwo();
    t.taskthree();
    t.taskfour();
    t.taskfive();

    // TODO: Read the input grammar at this point from standard input

    /*
       Hint: You can modify and use the lexer from previous project
       to read the input. Note that there are only 4 token types needed
       for reading the input in this project.

       WARNING: You will need to modify lexer.cc and lexer.h to only
       support the tokens needed for this project if you are going to
       use the lexer.
     */


    switch (task) {
        case 1:{
            // TODO: perform task 1.
            for (auto const& l : t.sortThem(t.getNon_terminals())) {
                cout << l << " ";
            }
            for (auto const& l : t.sortThem(t.getTerminals())) {
                cout << l << " ";
            }
            break;
        }
        case 2:{
            // TODO: perform task 2.
            list<string> useless = t.getUselessSymbols();
            map<string, list<list<string>>> grams = t.getGrams();
            list<string> non_terminals = t.getNon_terminals();
            if (find(useless.begin(), useless.end(), t.sortThem(non_terminals).front()) != useless.end()){
                break;
            }
            for (auto const& l : t.sortThem(non_terminals)) {
                if (find(useless.begin(), useless.end(), l) != useless.end()){
                    continue;
                }
                for (auto const& i : grams[l]){
                    bool use = true;
                    for (auto const& k : i){
                        if (find(useless.begin(), useless.end(), k) != useless.end()){
                            use = false;
                        }
                    }
                    if (use){
                        cout << l << " ->" ;
                        if (i.empty()){
                            cout << " #";
                        }
                        for (auto const& k : i){
                            cout << " " << k;
                        }
                        cout << endl;
                    }
                }
            }
            break;
        }
        case 3:{
            // TODO: perform task 3.
            map<string, list<string>> first = t.getFirst();
            for (auto const &i : t.sortThem(t.getNon_terminals())){
                cout << "FIRST(" << i << ") = {";
                int k = 0;
                for (auto const &j: t.sortThem(first[i])){
                    cout << " " << j;
                    k++;
                    if(k < first[i].size()){
                        cout << ",";
                    }
                }
                cout << " }" << endl;
            }
            break;
        }
        case 4:{
            // TODO: perform task 4.
            map<string, list<string>> follow = t.getFollow();
            for (auto const &i : t.sortThem(t.getNon_terminals())){
                cout << "FOLLOW(" << i << ") = {";
                int k = 0;
                for (auto const &j: t.sortThem(follow[i])){
                    cout << " " << j;
                    k++;
                    if(k < follow[i].size()){
                        cout << ",";
                    }
                }
                cout << " }" << endl;
            }
            break;
        }
        case 5:
            // TODO: perform task 5.
            cout << t.getParser() << endl;
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}
