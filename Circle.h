#pragma once    
#include "Figure.h"

class Circle : public Figure {
    
    private:

    size_t radius;
    
    int distance(int x1, int y1, int x2, int y2);
    bool circleCase(int x, int y, size_t radius);
    bool ellipseEquation(int x1, int y1, int x, int y, size_t radiusX, size_t radiusY);
    bool ellipseCase(int x, int y, size_t radiusX, size_t radiusY);
    bool rectangleCase(int x, int y, size_t width, size_t height);

    public:
    Circle();
    Circle(int x,int y, size_t radius,const std::string& colour);

    void print()const;

    void translate(int horizontal, int vertical);

    bool within(const std::string& name, int x, int y, size_t otherElem1, size_t otherElem2);

    void serialize(std::ofstream& file);
};