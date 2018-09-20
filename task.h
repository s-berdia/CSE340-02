//
// Created by Sandeep Balaji on 9/17/18.
//

#ifndef LEXER_PASRSER_TASK_H
#define LEXER_PASRSER_TASK_H
#endif //LEXER_PASRSER_TASK_H
#include <list>

using namespace std;

struct Gram{
    string id;
    list<list<Gram *> > grams;
};

struct gram_list{
    string id;
    Gram * gram;
    gram_list(string i, Gram * g){
        id =i;
        gram = g;
    }
};

class Task {
private:
    Gram * start = NULL;
    list<gram_list> listgram;

public:
    void taskone();
    void tasktwo();
    void taskthree();
    void taskfour();
    void taskfive();
    Gram * parse_gram();
    Gram *getStart() const;
    void setStart(Gram *start);
};