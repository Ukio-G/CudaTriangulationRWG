//
// Created by ukio on 31.12.2020.
//

#include <iostream>
#include "include/Line.h"

void Line::mouseMove(double x, double y, sf::Vector2i clickPosition)
{
    if(cm == TranslateLine) {
        start.x += x;
        start.y += y;

        end.x += x;
        end.y += y;

        updatePointsVector();
        updateCircuit();
    }
    else if (cm == MovePoints)
    {
        int index_point;
        if ((index_point = isIntersectSet(clickPosition.x, clickPosition.y, circuit_points, 15.0)) >= 0) {
            circuit_points[index_point] += x;
            circuit_points[index_point + 1] += y;
            start = {circuit_points[0], circuit_points[1]};
            end = {circuit_points[2], circuit_points[3]};
            circuit->createVertexStruct();
        }
    }
}

void Line::updateCircuit()
{
    circuit->createVertexStruct();
}

void Line::updatePointsVector()
{
    circuit_points.clear();
    circuit_points.reserve(4);
    circuit_points = {start.x, start.y, end.x, end.y};
}

void Line::draw(sf::RenderWindow & window)
{
    circuit->draw(window);
}

Line::Line(std::vector<double> points) : circuit_points(points),
                                    start(Point(points[0], points[1])),
                                    end(Point(points[2], points[3])) {
    circuit = new CircuitIndexed(circuit_points);

    subscriber.action = [this](double x, double y, sf::Vector2i position){
        mouseMove(x, y, position);
    };

}

Line::Line(Point start, Point end) : start(start), end(end)
{
    circuit_points = {start.x, start.y, end.x, end.y};
    circuit = new CircuitIndexed(circuit_points);
    subscriber.action = [this](double x, double y, sf::Vector2i position){
        mouseMove(x, y, position);
    };
}
