#pragma once    
#include "System.h"

class Menu {

    private:
    std::string fileName;
    std::string currentCommand;
    std::vector<std::string> commands;
    System system;

    void compare(int& choice);
    void loadCommands();
    void printCommands();
    void commandCases();
    void readFileCommand();

    void open();
    void close();
    void save();
    void saveas();
    void print();
    void create();
    void erase();
    void translate();
    void within();

    public:
    void menu();
};