//
// Created by ukio on 24.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_MATRIX2_H
#define IMGUI_SFML_APPLICATION_MATRIX2_H

#include <strings.h>
#include "Triangle.h"

class Matrix2D
{
public:
    double value[2][2];

    Matrix2D()
    {
//        bzero(value, 4 * sizeof(value));
    }

    void setIdentity()
    {
        value[0][0] = 1;
        value[1][1] = 1;
    }

    void rotate(double angle)
    {
        value[0][0] = std::cos(angle * 3.1415 / 180);
        value[0][1] = std::sin(angle * 3.1415 / 180);

        value[1][0] = -std::sin(angle * 3.1415 / 180);
        value[1][1] = std::cos(angle * 3.1415 / 180);
    }

    void translate(double factor_x, double factor_y)
    {
        value[0][0] = 1;
        value[0][1] = factor_x;

        value[1][0] = factor_y;
        value[1][1] = 1;
    }

    void scale(double factor_x, double factor_y)
    {
        value[0][0] = factor_x;
        value[0][1] = 0;

        value[1][0] = 0;
        value[1][1] = factor_y;
    }

    Point operator*(Point p)
    {
        double result_x = value[0][0] * p.x + value[0][1] * p.y;
        double result_y = value[1][0] * p.x + value[1][1] * p.y;

        return {result_x, result_y};
    }

};



#endif //IMGUI_SFML_APPLICATION_MATRIX2_H
