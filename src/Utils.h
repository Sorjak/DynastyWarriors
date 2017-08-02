#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>

#include <SDL2/SDL.h>

#include "Components/BaseComponent.h"

using namespace std;

const SDL_Color white = { 255, 255, 255, 255 };
const SDL_Color black = { 0, 0, 0, 255 };
const SDL_Color red = { 255, 0, 0, 255 };


void logSDLError(ostream &os, const string &msg);

vector<string> getKeysFromMap(map<string, BaseComponent*>);

float smoothGradient(float val, float a, float b);

int distanceSquared(int x1, int y1, int x2, int y2);

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