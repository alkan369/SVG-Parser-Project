#include <iostream>
#include <cmath>
#include "Ellipse.h"

int Ellipse::distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

bool Ellipse::circleCase(int x, int y, size_t radius){
    if(distance(this->x - radiusX,this->y,x,y) <= radius){
        if(distance(this->x,this->y + radiusY,x,y) <= radius){
            if(distance(this->x + radiusX,this->y,x,y) <= radius){
                if(distance(this->x,this->y - radiusY,x,y) <= radius){
                    return true;
                }
            }
        }
    }
    return false;   
}

bool Ellipse::ellipseEquation(int x1, int y1, int x, int y, int radiusX, int radiusY){
    return (pow(x1 - x,2) / pow(radiusX,2) + pow(y1 - y,2) / pow(radiusY,2)) <= 1;
}

bool Ellipse::ellipseCase(int x, int y, size_t radiusX, size_t radiusY){
    if(ellipseEquation(this->x - this->radiusX,this->y,x,y,radiusX,radiusY)){
        if(ellipseEquation(this->x,this->y + this->radiusY,x,y,radiusX,radiusY)){
            if(ellipseEquation(this->x + this->radiusX,this->y,x,y,radiusX,radiusY)){
                if(ellipseEquation(this->x,this->y - this->radiusY,x,y,radiusX,radiusY)){
                    return true;    
                }
            }
        }
    }
    return false;
}

bool Ellipse::rectangleCase(int x, int y, size_t width, size_t height){
    if(x <= this->x - radiusX && y <= this->y && x + width >= this->x - radiusX && y + height >= this->y){
        if(x <= this->x && y <= this->y + radiusY && x + width >= this->x && y + height >= this->y + radiusY){
            if(x <= this->x + radiusX && y <= this->y && x + width >= this->x + radiusX && y + height >= this->y){
                if(x <= this->x && y <= this->y - radiusY && x + width >= this->x && y + height >= this->y - radiusY){
                    return true;
                }
            } 
        }
    }
    return false;
}

Ellipse::Ellipse(){
    x = 10;
    y = 10;
    radiusX = 10;
    radiusY = 20;
    name = "ellipse";
    colour = "red";
}

Ellipse::Ellipse(int xx, int yy, size_t otherRadiusX, size_t otherRadiusY,const std::string& otherColour){
    x = xx;
    y = yy;
    radiusX = otherRadiusX;
    radiusY = otherRadiusY;
    name = "ellipse";
    colour = otherColour;
}

void Ellipse::print()const{
    std::cout << name << " " << x << " " << y << " " << radiusX << " " << radiusY << " " << colour << std::endl;
}

void Ellipse::translate(int horizontal,int vertical){
    x = x + horizontal;
    y = y + vertical;
}

bool Ellipse::within(const std::string& name, int x, int y, size_t otherElem1, size_t otherElem2){
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

void Ellipse::serialize(std::ofstream& file){
    file << "<" << name << " " << "cx=" << x << " " << "cy=" << y << " " << "rx=" << radiusX << " " << "ry=" << radiusY << " " << "fill=" << colour << " " << "/>" << "\n";
}