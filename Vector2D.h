#pragma once

// Stolen from the Solidity 2D game engine

class Vector2D {
        float _x;
        float _y;
public:
        Vector2D();
        Vector2D(float x,float y);
        virtual ~Vector2D();

        float& x();
        float x() const;

        float& y();
        float y() const;

        Vector2D operator+(const Vector2D& rhs) const;
        Vector2D operator-(const Vector2D& rhs) const;

        float length() const;

        static float distance(const Vector2D& v1, const Vector2D& v2);
        static Vector2D zero();
};

