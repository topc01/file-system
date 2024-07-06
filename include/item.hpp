#pragma once

#include <string>


namespace SO {

const int FILE = 0;
const int FOLDER = 1;

class Item {
private:
    std::string __name;
    int __type;
    Item *__ptrParent;
    Item *__ptrNext;
    Item *__ptrPrevious;
    Item *__ptrChild;
public:
    Item();
    Item(std::string name, int type, Item *parent);
    int getItemType();
    Item *getParent();
    Item *getNext();
    Item *getPrevious();
    Item *getChild();
    std::string getName();
    void setPrevious(Item *previous);
    void setNext(Item *next);
    void setChild(Item *child);
    virtual ~Item();
};

}
