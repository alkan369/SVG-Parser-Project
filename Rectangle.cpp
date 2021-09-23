#include <iostream>
#include <cmath>
#include "Rectangle.h"

int Rectangle::distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

bool Rectangle::circleCase(int x, int y, size_t radius){
    if(distance(this->x,this->y,x,y) <= radius){
        if(distance(this->x + width,this->y,x,y) <= radius){
            if(distance(this->x,this->y + height,x,y) <= radius){
                if(distance(this->x + width,this->y + height,x,y) <= radius){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Rectangle::ellipseEquation(int x1, int y1, int x, int y, int radiusX, int radiusY){
    return (pow(x1 - x,2) / pow(radiusX,2) + pow(y1 - y,2) / pow(radiusY,2)) <= 1;
}

bool Rectangle::ellipseCase(int x, int y, size_t radiusX, size_t radiusY){
    if(ellipseEquation(this->x,this->y,x,y,radiusX,radiusY)){
        if(ellipseEquation(this->x + width,this->y,x,y,radiusX,radiusY)){
            if(ellipseEquation(this->x,this->y + height,x,y,radiusX,radiusY)){
                if(ellipseEquation(this->x + width,this->y + height,x,y,radiusX,radiusY)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Rectangle::rectangleCase(int x, int y, size_t width, size_t height){
    if(x <= this->x && y <= this->y){
        if(x + width >= this->x + this->width && y + height >= this->y + this->height){
            return true;
        }
    }
    return false;
}

Rectangle::Rectangle(){
    x = 10;
    y = 10;
    width = 10;
    height = 10;
    name = "rect";
    colour = "red";
}

Rectangle::Rectangle(int xx, int yy,size_t otherWidth,size_t otherHeight, const std::string& otherColour){
    x = xx;
    y = yy;
    width = otherWidth;
    height = otherHeight;
    name = "rect";
    colour = otherColour;
}

void Rectangle::print()const{
    std::cout << name << " " << x << " " << y << " " << width << " " << height << " " << colour << std::endl;
}

void Rectangle::translate(int horizontal, int vertical){
    x = x + horizontal;
    y = y + vertical;
}

bool Rectangle::within(const std::string& name, int x, int y, size_t otherElem1, size_t otherElem2){
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

void Rectangle::serialize(std::ofstream& file){
    file << "<" << name << " " << "x=" << x << " " << "y=" << y << " " << "width=" << width << " " << "height=" << height << " " << "fill=" << colour << " />" << "\n";
}