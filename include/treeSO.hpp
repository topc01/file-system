#pragma once

#include "item.hpp"


namespace SO {

class treeSO {
private:
    Item *__root;
    Item *__currentFolder;
    std::string __directory;
    Item *getLast();
    Item *searchFor(std::string name, Item *base, int type);
public:
    treeSO();
    treeSO(Item *root);
    void setCurrent(Item *requestedItem, std::string path);
    void printContent(Item *requestedItem);
    void addItem(std::string name, int type);
    // void remove(std::string name);
    void remove(Item *requestedItem);
    std::string getDirectory();
    Item *goToPath(std::string path);
    Item *getItem(std::string path, int type=SO::FOLDER);
    void traverse_rec(Item *item, int level);
    void traverse(Item *item);
    void find_rec(Item *base, std::string name, std::string path);
    void find(Item *base, std::string path, std::string name);
};


}