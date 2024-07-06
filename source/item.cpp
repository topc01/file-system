#include "../include/item.hpp"
#include <iostream>

namespace SO
{

Item::Item() : 
    __name(""),
    __type(SO::FOLDER),
    __ptrParent(nullptr),
    __ptrNext(nullptr),
    __ptrPrevious(nullptr),
    __ptrChild(nullptr)
{}

Item::Item(std::string name, int type, Item *parent) : 
    __name(name),
    __type(type),
    __ptrParent(parent),
    __ptrNext(nullptr),
    __ptrPrevious(nullptr),
    __ptrChild(nullptr)
{}

int Item::getItemType() {
    return __type;
}

Item *Item::getParent() {
    return __ptrParent;
}

Item *Item::getNext() {
    return __ptrNext;
}

Item *Item::getPrevious() {
    return __ptrPrevious;
}

Item *Item::getChild() {
    return __ptrChild;
}

std::string Item::getName() {
    return __name;
}

void Item::setPrevious(Item *previous) {
    __ptrPrevious = previous;
}

void Item::setNext(Item *next) {
    next->setPrevious(this);
    // next->__ptrPrevious = this;
    __ptrNext = next;
}

void Item::setChild(Item *child) {
    if (__type == SO::FOLDER) {
        __ptrChild = child;
    }
    else {
        std::cout << "Cant set child in a file" << std::endl;
    }
}

Item::~Item() {
    Item *current = __ptrChild;
    while (current != nullptr) {
        delete current;
        current = __ptrNext;
    }
    delete this;
}

}