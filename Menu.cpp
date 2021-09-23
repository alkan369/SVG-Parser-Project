#include <iostream>
#include "Menu.h"

void Menu::compare(int& choice){

    std::string keyWord;
    for(int i = 0; i <currentCommand.size(); i++){
        if(currentCommand[i] == ' '){
            break;
        }
        keyWord.push_back(currentCommand[i]);
    }

    for(int i = 0; i < commands.size(); i++){
        if(keyWord == commands[i]){
            choice = i;
        }
    }

}    

void Menu::loadCommands(){
    commands.push_back("open");//0
    commands.push_back("close");//1
    commands.push_back("save");//2
    commands.push_back("saveas");//3
    commands.push_back("help");//4
    commands.push_back("exit");//5
    commands.push_back("print");//6
    commands.push_back("create");//7
    commands.push_back("erase");//8
    commands.push_back("translate");//9
    commands.push_back("within");//10
}

void Menu::printCommands(){
    std::cout << "Supported commands : " << std::endl;
    for(int i = 0; i < commands.size(); i++){
        std::cout << commands[i] << std::endl;
    }
}

void Menu::commandCases(){
    int choice = -1;
    compare(choice);
    switch (choice)
    {
    case 0:{
        std::cout << "Open" << std::endl;
        open();
        break;
    }
    case 1:{
        std::cout << "Close" << std::endl;
        close();
        break;
    }
    case 2:{
        std::cout << "Save" << std::endl;
        save();
        break;
    }
    case 3:{
        std::cout << "SaveAs" << std::endl;
        saveas();
        break;
    }
    case 4:{
        std::cout << "Help" << std::endl;
        printCommands();
        break;
    }
    case 5:{
        std::cout << "Exitting" << std::endl;
        std::fstream file(fileName);
        file.close();
        break;
    }

    case 6: {
        std::cout << "Print" << std::endl;
        print();
        break;
    }
    case 7 : {
        std::cout << "Create" << std::endl;
        create();
        break;
    }
    case 8:{
        std::cout << "Erase" << std::endl;
        erase();
        break;
    }
    case 9:{
        std::cout << "Translate" << std::endl;
        translate();
        break;
    }
    case 10:{
        std::cout << "Within" << std::endl;
        within();
        break;
    }
    default: {
        std::cout << "Invalid command" << std::endl;
        break;
    }

    }
}

void Menu::readFileCommand(){
    bool foundSpace = false;
    for(int i = 0; i < currentCommand.size(); i++){
        if(currentCommand[i] == ' '){
            foundSpace = true;
            continue;
        }
        if(foundSpace){
            fileName.push_back(currentCommand[i]);
        }
    }
    std::cout << "File : " << fileName << std::endl;
}

void Menu::menu(){
    loadCommands();
    printCommands();

    do{
        std::cout << "Enter command : ";
        std::getline(std::cin,currentCommand);
        std::cout << currentCommand << std::endl;
        commandCases();
    }while(currentCommand != "exit");
    std::cout << "Exitted" << std::endl;
}

void Menu::open(){
    fileName.clear();
    readFileCommand();
    system.open(fileName);
}

void Menu::close(){
    std::fstream file(fileName);
    system.close(file);
}

void Menu::save(){
    system.save(fileName);
}

void Menu::saveas(){
    std::fstream file(fileName);
    file.close();
    fileName.clear();
    readFileCommand();
    system.save(fileName);
}

void Menu::print(){
    system.print();
}

void Menu::create(){
    system.create(currentCommand);
}

void Menu::erase(){
    system.erase(currentCommand);
}

void Menu::translate(){
    system.translate(currentCommand);
}

void Menu::within(){
    system.within(currentCommand);
}