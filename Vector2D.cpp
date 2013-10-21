#include "Vector2D.h"
#include <cmath>

// Stolen from the Solidity 2D game engine

Vector2D::Vector2D():
        _x(.0f),
        _y(.0f)
{}

Vector2D::Vector2D(float x, float y):
        _x(x),
        _y(y)
{
}

float Vector2D::x() const{
        return _x;
}

float Vector2D::y() const{
        return _y;
}

float& Vector2D::x() {
        return _x;
}

float& Vector2D::y() {
        return _y;
}


Vector2D Vector2D::operator+(const Vector2D& rhs) const{
        Vector2D vector;
        vector.x()=this->_x+rhs.x();
        vector.y()=this->_y+rhs.y();
        return vector;
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const{
        Vector2D vector;
        vector.x()=this->_x-rhs.x();
        vector.y()=this->_y-rhs.y();
        return vector;
}

float Vector2D::length() const{
        return sqrt(pow(_x,2.0f)+pow(_y,2.0f));
}

float Vector2D::distance(const Vector2D& v1, const Vector2D& v2){
        return (v2-v1).length();
}

Vector2D Vector2D::zero(){
        return Vector2D(0.0f,0.0f);
}

Vector2D::~Vector2D() {
}


