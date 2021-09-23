#include <iostream>
#include <cmath>
#include "Circle.h"

int Circle::distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

bool Circle::circleCase(int x, int y, size_t radius){
    if(distance(this->x,this->y,x,y) + this->radius <= radius){
        return true;
    }
    return false;
}

bool Circle::ellipseEquation(int x1, int y1, int x, int y, size_t radiusX, size_t radiusY){
    return (pow(x1 - x,2) / pow(radiusX,2) + pow(y1 - y,2) / pow(radiusY,2)) <= 1;
}

bool Circle::ellipseCase(int x, int y, size_t radiusX, size_t radiusY){
    if(ellipseEquation(this->x + this->radius,this->y,x,y,radiusX,radiusY)){
        if(ellipseEquation(this->x,this->y + this->radius,x,y,radiusX,radiusY)){
            if(ellipseEquation(this->x - this->radius, this->y,x,y,radiusX,radiusY)){
                if(ellipseEquation(this->x,this->y - this->radius,x,y,radiusX,radiusY)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Circle::rectangleCase(int x, int y, size_t width, size_t height){
    if(x <= this->x - radius && y <= this->y && x + width >= this->x - radius && y + height >= this->y){
        if(x <= this->x && y <= this->y - radius && x + width >= this->x && y + height >= this->y - radius){
            if(x <= this->x + radius && y <= this->y && x + width >= this->x + radius && y + height >= this->y){
                if(x <= this->x && y <= this->y + radius && x + width >= this->x && y + height >= this->y + radius){
                    return true;
                }
            }
        }
    }
    return false;
}

Circle::Circle(){
    x = 10;
    y = 10;
    radius = 10;
    name = "circle";
    colour = "red";
}

Circle::Circle(int xx, int yy,size_t otherRadius,const std::string& otherColour){
    x = xx;
    y = yy;
    radius = otherRadius;
    name = "circle";
    colour = otherColour;
}

void Circle::print()const{
    std::cout << name << " " << x << " " << y << " " << radius << " " << colour << std::endl;
}

void Circle::translate(int horizontal,int vertical){
    x = x + horizontal;
    y = y + vertical;
}

bool Circle::within(const std::string& name, int x, int y, size_t otherElem1, size_t otherElem2){
    if(name == "rectangle"){
        return rectangleCase(x,y,otherElem1,otherElem2);
    }
    if(name == "ellipse"){
        return ellipseCase(x,y,otherElem1,otherElem2);
    }
    if(name == "circle"){
        return circleCase(x,y,otherElem1);
    }
    std::cout << "Figure name : " << name << std::endl;
    std::cout << "Figure not supported" << std::endl;
    return false;
}

void Circle::serialize(std::ofstream& file){
    file << "<" << name << " "  << "cx=" << x << " " << "cy=" << y << " " << "r=" << radius << " " << "fill=" << colour << " " << "/>" << "\n";
}