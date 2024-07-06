#include "../include/treeSO.hpp"
#include <iostream>

namespace SO {

treeSO::treeSO() :
    __root(nullptr),
    __currentFolder(nullptr),
    __directory("/")
{}

treeSO::treeSO(Item *root) :
    __root(root),
    __currentFolder(root),
    __directory(root->getName())
{}

Item *treeSO::getLast() {
    Item *last = __currentFolder->getChild();
    while (last != nullptr // if the folder has child Item
        && last->getNext() != nullptr)   // if the Items points to another Item,
        last = last->getNext();   // then it is not the last, so check next Item
    return last;
}

Item *treeSO::searchFor(std::string name, Item *base, int type=SO::FOLDER) {
    Item *current = base->getChild();
    
    while (current != nullptr  // if the folder has child Item, or if last Item is not checked
        && (current->getName() != name // and current Item name is not <name>,
        || current ->getItemType() != type)) // or current Item type is not <type>,
        current = current->getNext(); // go to next Item

    return current;
}

void treeSO::setCurrent(Item *requestedItem, std::string path) {
    if (requestedItem->getItemType() == SO::FILE)
        std::cout << "Folder not found" << std::endl;
    else {
        if (path.front() == '/') {
            __directory = path;
        }
        else if (path == "..") {
            int slash_position;
            for (slash_position = __directory.length(); __directory[slash_position] != '/' && slash_position > 1; slash_position--);
            __directory = __directory.substr(0, slash_position);
        }
        else if (path == ".") {
        }
        else {
            if (__directory != "/")
                __directory += "/";
            __directory += path;
        }
        __currentFolder = requestedItem;
    }
}

void treeSO::printContent(Item *requestedItem) {
    std::cout << __directory << "# ";
    Item *current = requestedItem->getChild();
    while (current != nullptr) {
        std::cout << current->getName() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

void treeSO::addItem(std::string name, int type) {
    Item *itemName = searchFor(name, __currentFolder, type);
    if (itemName == nullptr) {
        Item *last = getLast();
        Item *new_Item = new Item(name, type, __currentFolder);
        if (last == nullptr) {
            __currentFolder->setChild(new_Item);
        } 
        else {
            last->setNext(new_Item);
        }
    } 
    else {
        std::cout << "Item <" << name << "> already exists" << std::endl;
    }
}

void treeSO::remove(Item *requestedItem) {
    Item *previous = requestedItem->getPrevious();
    Item *next = requestedItem->getNext();
    if (previous == nullptr) {
        requestedItem->getParent()->setChild(next);
    }
    else {
        previous->setNext(next);
        next->setPrevious(previous);
    }
    delete requestedItem;
    
}

std::string treeSO::getDirectory() {
    return __directory;
}

Item *treeSO::goToPath(std::string path) {
    Item *current = __root;
    // Item *found = nullptr;
    
    std::size_t slash_position = 0, previous_end;

    if (path[0] == '/') {
        previous_end = 1;
    }
    else {
        previous_end = 0;
    }
    std::string name;
    while (slash_position != std::string::npos && path != "/") {
        slash_position = path.find('/', previous_end);
        name = path.substr(previous_end, slash_position - previous_end);

        current = searchFor(name, current);
        if (current == nullptr) 
            return nullptr;
        
        previous_end = slash_position + 1;
    }
    return current;
}

Item *treeSO::getItem(std::string path, int type) {
    if (path == ".") {
        return __currentFolder;
    }
    else if (path == "..") {
        if (__currentFolder == __root) {
            return __root;
        }
        return __currentFolder->getParent();
    }
    else if (path.front() == '/' || path.find('/') != std::string::npos) {
        return goToPath(path);
    }
    else {
        return searchFor(path, __currentFolder, type);
    }
}

void treeSO::traverse_rec(Item *base, int level) {
    if (base != nullptr) {
        std::cout << std::string(level*2, '-') << base->getName() << std::endl;
        Item *current = base->getChild();
        while (current != nullptr) {
            traverse_rec(current, level + 1);
            current = current->getNext();
        }
    }
}

void treeSO::traverse(Item *base) {
    traverse_rec(base, 1);
}

void treeSO::find_rec(Item *base, std::string name, std::string path) {
    if (base != nullptr) {
        Item *current = base->getChild();
        while (current != nullptr) {
            if (current->getName() == name) {
                std::cout << path + name << " ";
            }
            find_rec(current, name, path + current->getName() + "/");
            current = current->getNext();
        }
        
    }
}

void treeSO::find(Item *base, std::string path, std::string name) {
    std::cout << __directory << "# ";
    if (path.front() == '/') {
    }
    else if (path == "..") {
        int slash_position;
        for (slash_position = __directory.length(); __directory[slash_position] != '/' && slash_position > 1; slash_position--);
        path = __directory.substr(0, slash_position);
    }
    else if (path == ".") {
        path = __directory;
    }
    else {
        path = __directory + "/" + path;
    }
    find_rec(base, name, path);
    std::cout << std::endl;
}
}
