#pragma once
#include <string>
#include <fstream>


class Figure{
    protected:
    int x;
    int y;
    std::string name;
    std::string colour;

    public:
    virtual void print()const = 0;

    virtual void translate(int horizontal, int vertical) = 0;

    virtual bool within(const std::string& name, int x, int y, size_t otherElem1, size_t otherElem2) = 0;

    virtual void serialize(std::ofstream& file) = 0;
};