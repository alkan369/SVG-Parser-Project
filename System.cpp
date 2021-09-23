#include <iostream>
#include "System.h"

void System::readCommand(const std::string& currentCommand, int& number, int& x, int& y){
    number = 0;
    int spaceCNT = 0;
    for(int i = 0; i < currentCommand.size(); i++){
        if(currentCommand[i] == ' '){
            ++spaceCNT;
            continue;
        }
        if(spaceCNT == 1 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            number = number * 10 + (currentCommand[i] - '0');
        }
        if(spaceCNT == 2 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            x = x * 10 + (currentCommand[i] - '0');
        }
        if(spaceCNT == 3 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            y = y * 10 + (currentCommand[i] - '0');
        }
    }
    if(spaceCNT < 3 && x != 0 && y == 0){
        y = x;
        x = number;
        number = -1;
    }
}

void System::figureCase(const std::string& name,const int& x, const int& y, const size_t& otherElem1, const size_t& otherElem2,const std::string& colour){
   if(name == "rectangle" || name == "rect"){
       figures.push_back(new Rectangle(x,y,otherElem1,otherElem2,colour));
       std::cout << "Added rectangle" << std::endl;
   }
   else if(name == "ellipse"){
       figures.push_back(new Ellipse(x,y,otherElem1,otherElem2,colour));
       std::cout << "Added ellipse" << std::endl;
   }
   else if(name == "circle"){
       figures.push_back(new Circle(x,y,otherElem1,colour));
       std::cout << "Added circle" << std::endl;
   }
   else{
       std::cout << "Figure type not supported" << std::endl;
   }
}

void System::readFigure(const std::string& currentCommand,std::string& name, int& x, int& y, size_t& otherElem1, size_t& otherElem2, std::string& colour){
    
    int spaceCNT = 0;     
    for(int i = 0; i < currentCommand.size(); i++){
        if(currentCommand[i] == ' '){
            ++spaceCNT;
            continue;
        }
        if(spaceCNT == 1){
            name.push_back(currentCommand[i]);
        }
        if(spaceCNT == 2 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            x = x * 10 + (currentCommand[i] - '0');
        }
        if(spaceCNT == 3 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            y = y * 10 + (currentCommand[i] - '0');
        }
        if(spaceCNT == 4 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            otherElem1 = otherElem1 * 10 + (currentCommand[i] - '0');
        }
        if(spaceCNT == 5 && currentCommand[i] >= '0' && currentCommand[i] <= '9'){
            otherElem2 = otherElem2 * 10 + (currentCommand[i] - '0');
        }
        if(spaceCNT == 6 || (name == "circle" && spaceCNT == 5)){
            colour.push_back(currentCommand[i]);
        }
    }

}

bool System::doesExist(const std::string& fileName)const{
    std::ifstream file(fileName);
    bool result = file.good();
    file.close();
    return result;
}

void System::serialize(std::ofstream& file){
    if(!file.is_open()){
        std::cout << "The file has not been opened" << std::endl;
        return;
    }
    file <<  "<?xml version=1.0 standalone=no?>" << "\n"
    "<!DOCTYPE svg PUBLIC -//W3C//DTD SVG 1.1//EN" << "\n" 
    "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd>" << "\n"
    "<svg>" << "\n";

    for(int i = 0; i < figures.size(); i++){
        figures[i]->serialize(file);
    }
    file << "</svg>" << "\n";
}

void System::deserialize(std::ifstream& file){
    if(!file.is_open()){
        std::cout << "File has not been opened" << std::endl;
        return;
    }
    std::string line;
    int lineCNT = 0;
    while (std::getline(file,line)){
        ++lineCNT;
        if(lineCNT <= 4){
            continue;
        }
        std::string name;
        int x = 0;
        int y = 0;
        size_t otherElem1 = 0;
        size_t otherElem2 = 0;
        std::string colour;
        if(line[0] == '<'){
            int spaceCNT = 0;
            int equalCNT = 0;
            for(int i = 1; i < line.size(); i++){
                if(line[i] == ' '){
                    ++spaceCNT;
                    continue;
                }
                if(spaceCNT == 0){ 
                    name.push_back(line[i]);
                }
                if(line[i] == '='){
                    ++equalCNT;
                    continue;
                }
                if((spaceCNT == 1 && equalCNT == 1 && line[i] >= '0' && line[i] <= '9')){
                    x = x * 10 + (line[i] - '0');
                }
                if(spaceCNT == 2 && equalCNT == 2 && line[i] >= '0' && line[i] <= '9'){
                    y = y * 10 + (line[i] - '0');
                }
                if(spaceCNT == 3 && equalCNT == 3 && line[i] >= '0' && line[i] <= '9'){
                    otherElem1 = otherElem1 * 10 + (line[i] - '0');
                }
                if(spaceCNT == 4 && equalCNT == 4 && line[i] >= '0' && line[i] <= '9'){
                    otherElem2 = otherElem2 * 10 + (line[i] - '0');
                }
                if((spaceCNT == 5 && equalCNT == 5) || (name == "circle" && spaceCNT == 4 && equalCNT == 4)){
                    colour.push_back(line[i]);
                }
            }
            figureCase(name,x,y,otherElem1,otherElem2,colour);
        }
    }
}

void System::checkFileStatus(std::ofstream& file){
    if(file.good()){
        std::cout << "Data has been saved successfully" << std::endl;
    }
    else{
        std::cout << "Error saving data" << std::endl;
    }
}

void System::figuresPOP(){
    for(int i = 0; i < figures.size(); i++){
        delete figures[i];
        figures[i] = nullptr;
    }
    figures.clear();
}

System::~System(){
    figuresPOP();
}

void System::open(const std::string& fileName){
    if(doesExist(fileName)){
        figuresPOP();
        std::ifstream file(fileName);
        deserialize(file);
        file.close();
        std::cout << "Data has been loaded" << std::endl;
    }
    else{
        std::ofstream file(fileName);
        file.close();
        std::cout << "File has been created" << std::endl;
    }

}

void System::close(std::fstream& file){
    file.close();
    std::cout << "File has been closed" << std::endl;
}

void System::save(const std::string& fileName){
    std::ofstream file(fileName);
    serialize(file);
    checkFileStatus(file);
    file.close();
}

void System::print(){
    for(int i = 0; i < figures.size(); i++){
        figures[i]->print();
    }
}

void System::create(const std::string& currentCommand){
    std::string name;
    int x = 0;
    int y = 0;
    size_t otherElem1 = 0;
    size_t otherElem2 = 0;
    std::string colour;

    readFigure(currentCommand,name,x,y,otherElem1,otherElem2,colour);
    std::cout << "Figure :" << " " << name << " " << x << " " << y << " " << otherElem1 << " " << otherElem2 << " " << colour << std::endl;
    figureCase(name,x,y,otherElem1,otherElem2,colour);
}

void System::erase(const std::string& currentCommand){
    int number;
    int x = 0;
    int y = 0;
    readCommand(currentCommand,number,x,y);
    if(number == -1 || number >= figures.size()){
        std::cout << "There is no figure with number " << number << std::endl;
        return;
    }
    delete figures[number];
    figures[number] = nullptr;
    figures.erase(figures.begin() + number);
}

void System::translate(const std::string& currentCommand){
    int number;
    int x = 0;
    int y = 0;
    readCommand(currentCommand,number,x,y);
    if(number == -1){
        number = figures.size();
        for(int i = 0; i < number; i++){
            figures[i]->translate(x,y);
        }
        return;
    }
    if(number >= figures.size()){
        std::cout << "There is not figure with number " << number << std::endl;
        return;
    }
    figures[number]->translate(x,y);
    std::cout  << "Translated figure with number " << number << std::endl;
}


void System::within(const std::string& currentCommand){
    std::string name;
    int x = 0;
    int y = 0;
    size_t otherElem1 = 0;
    size_t otherElem2 = 0;
    std::string colour;

    readFigure(currentCommand,name,x,y,otherElem1,otherElem2,colour);
    
    for(int i = 0; i < figures.size(); i++){
        if(figures[i]->within(name,x,y,otherElem1,otherElem2)){
            figures[i]->print();
        }
    }
}