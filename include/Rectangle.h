//
// Created by ukio on 04.01.2021.
//

#ifndef IMGUI_SFML_APPLICATION_RECTANGLE_H
#define IMGUI_SFML_APPLICATION_RECTANGLE_H

#include "Triangle.h"

class RectangleIndexed
{
public:

    RectangleIndexed(std::vector<double> &container);

    RectangleIndexed(std::vector<double> &container, int rect_x, int rect_y, int points_in_row);

    RectangleIndexed(std::vector<double> &container, int i1, int i2, int i3, int i4);

    ~RectangleIndexed()
    {

    }
    std::vector<double> & container;
    std::vector<sf::Vertex> vertexes;

    int idx[4];
    int x;
    int y;
    sf::Color color = {255,255,255};

    void createVertexStruct();
    bool rectangleIntersect(Point start, Point end);
    void draw(sf::RenderWindow & window) ;

    void updateColor(sf::Color color);

    bool circuitIntersect(CircuitIndexed &circuit);

    bool intersected;
};

class Rectangle
{
public:
    Point a;
    Point b;
    Point c;
    Point d;

    std::vector<double> points;
    CircuitIndexed *circuit = nullptr;
    void updatePoints();
    void createCircuit();
    Rectangle();

    Rectangle(Point a, Point b, Point c, Point d);
    bool rectangleIntersect(Point start, Point end, DebugDebug & debug);
    Rectangle translate(Point offset);

    void updateCircuit();

    void draw(sf::RenderWindow &window);


    Rectangle(std::vector<double> coords);

    bool rectangleIntersect(Point start, Point end, sf::RenderWindow &window);
};


#endif //IMGUI_SFML_APPLICATION_RECTANGLE_H
