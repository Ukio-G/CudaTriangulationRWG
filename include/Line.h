//
// Created by ukio on 31.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_LINE_H
#define IMGUI_SFML_APPLICATION_LINE_H

#include "Triangle.h"
#include "Circuit.h"

class Line {
public:
    enum ClickMode {MovePoints, TranslateLine};
    ClickMode cm = MovePoints;
    Line(std::vector<double> points);

    std::vector<double> circuit_points;
    CircuitIndexed *circuit = nullptr;
    Point start;
    Point end;
    MouseSubscriber subscriber;
    Line(Point start, Point end);

    void updateCircuit();

    void updatePointsVector();

    void draw(sf::RenderWindow &window);

    void mouseMove(double x, double y, sf::Vector2i clickPosition);
};


#endif //IMGUI_SFML_APPLICATION_LINE_H
