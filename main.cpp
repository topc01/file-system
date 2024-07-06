#include <iostream>
#include <string>

#include "include/item.hpp"
#include "include/treeSO.hpp"


int main(int argc, char **argv) {
    
    std::cout << std::endl << "$TreeSO" << std::endl;
    std::cout << "¡Bienvenido a TreeSO!" << std::endl;
    std::cout << "¡Autores: Vicente Cuevas y Tomas Pfingsthorn!" << std::endl;

    SO::Item *root = new SO::Item("/", SO::FOLDER, nullptr);
    SO::treeSO *treeSO = new SO::treeSO(root);
    SO::Item *requestedItem = nullptr;

    std::string directory;
    std::string command;
    std::string arg1;
    std::string arg2;

    while (true) {
        directory = treeSO->getDirectory();
        std::cout << directory << "# ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }
        else {
            std::cin >> arg1;

            if (command == "mkdir") {
                if (arg1.front() == '/') {
                    std::cout << "Cant take path as parameter" << std::endl;
                    continue;
                }
                treeSO->addItem(arg1, SO::FOLDER);
            } 

            else if (command == "mkfile") {
                if (arg1.front() == '/') {
                    std::cout << "Cant take path as parameter" << std::endl;
                    continue;
                }
                treeSO->addItem(arg1, SO::FILE);
            } 

            else {
                requestedItem = treeSO->getItem(arg1);
                if (requestedItem == nullptr) {
                    std::cout << "Item not found" << std::endl;
                    continue;
                }

                if (command == "cd") {
                    treeSO->setCurrent(requestedItem, arg1);
                } 

                else if (command == "ls") {
                    treeSO->printContent(requestedItem);
                } 

                else if (command == "rm") {
                    treeSO->remove(treeSO->getItem(arg1, SO::FILE));
                    treeSO->remove(treeSO->getItem(arg1, SO::FOLDER));
                } 

                else if (command == "tree") {
                    treeSO->traverse(requestedItem);
                } 

                else if (command == "find") {
                    std::cin >> arg2;
                    treeSO->find(requestedItem, arg1, arg2);
                } 
                
                else {
                    std::cout << "Command not found: " << command << std::endl;
                }
            }
        } 
        
    }
    std::cout << std::endl;
    return 0;
}