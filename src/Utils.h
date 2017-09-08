#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <random>

#include <SDL2/SDL.h>
#include <noise/noise.h>

#include "Components/BaseComponent.h"

using namespace std;

const SDL_Color white = { 255, 255, 255, 255 };
const SDL_Color black = { 0, 0, 0, 255 };
const SDL_Color red = { 255, 0, 0, 255 };

struct NoiseModule {
    noise::module::Perlin noiseModule;

    float GetNoise2D(float x, float y) {
        return (float) noiseModule.GetValue(x, y, 1.0);
    }
};

void logSDLError(ostream &os, const string &msg);

vector<string> getKeysFromMap(map<string, BaseComponent*>);

float smoothGradient(float val, float a, float b);

int distanceSquared(int x1, int y1, int x2, int y2);

float getRand01();
float getRand(float maxNum);


struct Vector2 {
    float x, y;

    Vector2(float x=0, float y=0) 
        : x(x), y(y)
    {
    }

    // addop. doesn't modify object. therefore const.
    Vector2 operator+(const Vector2& a) const {
        return Vector2(x+a.x, y+a.y);
    }

    Vector2 operator-(const Vector2& a) const {
        return Vector2(x-a.x, y-a.y);
    }

    float lengthSquared() const{
        return pow(x, 2.0f) + pow(y, 2.0f);
    }

    float length() const{
        return sqrt(lengthSquared());
    }

    Vector2 normalize() const {
        float l = length();
        return Vector2(x / l, y / l);

    }

    float distance(const Vector2& a) const{
        Vector2 diff = Vector2(x-a.x, y-a.y);
        return diff.length();
    }

};

struct Circle {
    int x, y;
    int r;

    bool CheckPoint(int x2, int y2) {
        int distanceSqr = distanceSquared(x, y, x2, y2);
        return distanceSqr < (r * r);
    }

    float DistanceFromCenter(int x2, int y2) {
        return sqrt(distanceSquared(x, y, x2, y2));
    }

    Vector2 GetRandomPoint() {
        float t = 2 * M_PI * getRand(r);
        float u = getRand(r) + getRand(r);
        float rand_r = u > 1 ?  2-u : u;
        return Vector2(x + rand_r*cos(t), y + rand_r*sin(t));
    }

    void DrawCircle(SDL_Renderer* ren, SDL_Color color) {

        int left = x - r;
        int right = x + r;
        int top = y - r;
        int bottom = y + r;
        SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);

        for (int i = left; i < right; i++) {
            for (int j = top; j < bottom; j++) {
                if (CheckPoint(i, j))
                    SDL_RenderDrawPoint(ren, i, j);
            }
        }
    }
};
