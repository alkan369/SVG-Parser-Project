#pragma once
#include <vector>
#include <fstream>
#include "Figure.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"


class System {

    private:
    std::vector<Figure*> figures;

    void readCommand(const std::string& currentCommand, int& number,int& x,int& y);
    void figureCase(const std::string& name,const int& x, const int& y, const size_t& otherElem1, const size_t& otherElem2,const std::string& colour);
    void readFigure(const std::string& currentCommand,std::string& name, int& x, int& y, size_t& otherElem1, size_t& otherElem2, std::string& colour);
    bool doesExist(const std::string& fileName)const;
    void serialize(std::ofstream& file);
    void deserialize(std::ifstream& file);
    void checkFileStatus(std::ofstream& file); 
    void figuresPOP();   
    
    public:
    ~System();
    void open(const std::string& fileName);
    void close(std::fstream& file);
    void save(const std::string& fileName); // save and saveAs
    void print();
    void create(const std::string& currentCommand);
    void erase(const std::string& currentCommand);
    void translate(const std::string& currentCommand);
    void within(const std::string& currentCommand);

};