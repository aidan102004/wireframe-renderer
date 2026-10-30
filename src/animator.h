#pragma once

#include "point.h"
#include <cmath>

class Animator {
public:
    Point rotate_y(float angle, float x, float y, float z) {
        float c = std::cos(angle), s = std::sin(angle);
        float xp = z * s - x * c;
        float zp = z * c + x * s;
        return {xp, y, zp};
    }

    Point rotate_x(float angle, float x, float y, float z) {
        float c = std::cos(angle), s = std::sin(angle);
        float yp = y * c - z * s;
        float zp = y * s + z * c;
        return {x, yp, zp};
    }

    Point rotate_z(float angle, float x, float y, float z) {
        float c = std::cos(angle), s = std::sin(angle);
        float xp = x * c - y * s;
        float yp = x * s + y * c;
        return {xp, yp, z};
    }
};