//
// Created by ukio on 31.12.2020.
//

#include <iostream>
#include <include/Line.h>
#include "include/Triangle.h"
#include "include/Rectangle.h"
#include <SFML/Graphics/RectangleShape.hpp>

void Rectangle::createCircuit()
{
    if (circuit != nullptr)
        delete circuit;
    circuit = new CircuitIndexed(points);
    updateCircuit();
}

void Rectangle::draw(sf::RenderWindow & window)
{
    circuit->draw(window);
}

void Rectangle::updateCircuit()
{
    circuit->createVertexStruct();
}

void Rectangle::updatePoints()
{
    points.clear();
    points.reserve(8);
    points = {
            a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y
    };
}

Rectangle::Rectangle(){

}

Rectangle::Rectangle(std::vector<double> coords) : a(Point(coords[0], coords[1])), b(Point(coords[2], coords[3])),
c(Point(coords[4], coords[5])), d(Point(coords[6], coords[7]))
{  updatePoints(); }

Rectangle::Rectangle(Point a, Point b, Point c, Point d) : a(a), b(b), c(c), d(d)
{  updatePoints();  }

bool Rectangle::rectangleIntersect(Point start, Point end, DebugDebug & debug)
{
    Rectangle translated = translate({0, 0});
    Point a = {translated.a.x , translated.a.y};
    Point b = {translated.b.x , translated.b.y};
    Point c = {translated.c.x , translated.c.y};
    Point d = {translated.d.x , translated.d.y};

    start = {start.x, start.y};
    end = {end.x, end.y};

    double x1 = (((end.x - start.x) * (a.y - start.y)) / (end.y - start.y)) + start.x;
    double x2 = (((end.x - start.x) * (c.y - start.y)) / (end.y - start.y)) + start.x;

    sf::Vertex top_x_intersect({(float)x1, (float)a.y});
    sf::Vertex bottom_x_intersect({(float)x1, (float)a.y});


    bool x1_intersected = (x1 >= a.x && x1 <= b.x);
    bool x2_intersected = (x2 >= a.x && x2 <= b.x);

    double y1 = start.y + (((b.x - start.x) * (end.y - start.y))/ (end.x - start.x));
    double y2 = start.y + (((d.x - start.x) * (end.y - start.y))/ (end.x - start.x));

    bool y1_intersected = (y1 >= b.y && y1 <= c.y);
    bool y2_intersected = (y2 >= b.y && y2 <= c.y);

    double line_x_min = (start.x < end.x) ? start.x : end.x;
    double line_x_max = (start.x > end.x) ? start.x : end.x;

    double line_y_min = (start.y < end.y) ? start.y : end.y;
    double line_y_max = (start.y > end.y) ? start.y : end.y;

    bool x_into = (line_x_min < a.x && a.x < line_x_max) || (line_x_min < b.x && b.x < line_x_max);
    bool y_into = (line_y_min < a.y && a.y < line_y_max) || (line_y_min < c.y && c.y < line_y_max);
    bool result = ( x1_intersected + x2_intersected + y1_intersected + y2_intersected ) == 2;
    auto old_color = circuit->color;
    if (result)
        circuit->color = {255,255, 0};
    else
        circuit->color = {255,255, 255};
    if (old_color != circuit->color)
        updateCircuit();
    return result;
}

Rectangle Rectangle::translate(Point offset)
{
    Rectangle r(a,b,c,d);
    r.a = a - offset;
    r.b = b - offset;
    r.c = c - offset;
    r.d = d - offset;
    return r;
}

void RectangleIndexed::draw(sf::RenderWindow &window) {
//    window.draw(vertexes.data() ,vertexes.size(), sf::LineStrip);


        sf::Vector2f size = {
                (float) (std::abs(container[idx[0]] - container[idx[1]])),
                (float) (std::abs(container[idx[1] + 1] - container[idx[2] + 1]))
        };
        sf::RectangleShape rectangle(size);
        if(!intersected) {
            rectangle.setFillColor({0, 0, 0});
        } else
            rectangle.setFillColor({125, 0, 0});
        rectangle.setOutlineColor({255, 255, 255});
        rectangle.setOutlineThickness(1.0);
        rectangle.setPosition(container[idx[0]], container[idx[0] + 1]);
        window.draw(rectangle);

}

void RectangleIndexed::createVertexStruct() {
    vertexes.clear();
    vertexes.reserve(4 * 2);

    for (int i = 0; i < 4; ++i) {
        vertexes.emplace_back(sf::Vector2f(container[idx[i]], container[idx[i] + 1]), color);
        vertexes.emplace_back(sf::Vector2f(container[idx[(i + 1) % 4]], container[idx[(i + 1) % 4] + 1]), color);
    }
}

void RectangleIndexed::updateColor(sf::Color color)
{
    for (auto &item : vertexes)
        item.color = color;
}

bool RectangleIndexed::circuitIntersect(CircuitIndexed & circuit)
{
    Point start;
    Point end;
    auto & c_points = circuit.container;
    start = Point(c_points[c_points.size() - 2], c_points[c_points.size() - 1]);
    end = Point(c_points[0], c_points[1]);
    if (rectangleIntersect(start, end))
        return true;
    for(int i = 2; i < c_points.size() - 1; i += 2)
    {
        start = end;
        end = Point(c_points[i], c_points[i + 1]);
        if (rectangleIntersect(start, end))
            return true;
    }
    return false;
}

bool RectangleIndexed::rectangleIntersect(Point start, Point end) {
    Point a = {container[idx[0]] , container[idx[0] + 1]};
    Point b = {container[idx[1]] , container[idx[1] + 1]};
    Point c = {container[idx[2]] , container[idx[2] + 1]};
    Point d = {container[idx[3]] , container[idx[3] + 1]};

    start = {start.x, start.y};
    end = {end.x, end.y};

    double x1 = (((end.x - start.x) * (a.y - start.y)) / (end.y - start.y)) + start.x;
    double x2 = (((end.x - start.x) * (c.y - start.y)) / (end.y - start.y)) + start.x;

    bool x_1_intersected = (x1 >= a.x && x1 <= b.x);
    bool x_2_intersected = (x2 >= a.x && x2 <= b.x);

    double y1 = start.y + (((b.x - start.x) * (end.y - start.y))/ (end.x - start.x));
    double y2 = start.y + (((d.x - start.x) * (end.y - start.y))/ (end.x - start.x));

    bool y_1_intersected = (y1 >= b.y && y1 <= c.y);
    bool y_2_intersected = (y2 >= b.y && y2 <= c.y);

    double line_x_min = (start.x < end.x) ? start.x : end.x;
    double line_x_max = (start.x > end.x) ? start.x : end.x;

    double line_y_min = (start.y < end.y) ? start.y : end.y;
    double line_y_max = (start.y > end.y) ? start.y : end.y;

    bool x_into = (line_x_min < a.x && a.x < line_x_max) || (line_x_min < b.x && b.x < line_x_max);
    bool y_into = (line_y_min < a.y && a.y < line_y_max) || (line_y_min < c.y && c.y < line_y_max);

    bool only_x_intersection = ((x_1_intersected + x_2_intersected) == 2) && y_into;
    bool only_y_intersection = ((y_1_intersected + y_2_intersected) == 2) && x_into;
    bool x_y_intersection = (x_into && y_into) && ((x_1_intersected + x_2_intersected) && (y_1_intersected + y_2_intersected));
    bool start_inside = (a.x <= start.x && start.x <= b.x) && (a.y <= start.y && start.y <= d.y);
    bool end_inside = (a.x <= end.x && end.x <= b.x) && (a.y <= end.y && end.y <= d.y);
    bool result = only_x_intersection || only_y_intersection || x_y_intersection || start_inside || end_inside;

//    sf::Color new_color = (result) ? sf::Color(255,255, 0) : sf::Color(255,255, 255);
//    updateColor(new_color);
    intersected = result;
    return result;
}

RectangleIndexed::RectangleIndexed(std::vector<double> &container) : container(container) {
    for (int i = 0; i < 4; ++i)
        idx[i] = 2 * i;
    createVertexStruct();
}

RectangleIndexed::RectangleIndexed(std::vector<double> &container, int i1, int i2, int i3, int i4) : container(container) {
    idx[0] = i1;
    idx[1] = i2;
    idx[2] = i3;
    idx[3] = i4;
    createVertexStruct();
}

RectangleIndexed::RectangleIndexed(std::vector<double> &container, int rect_x, int rect_y, int points_in_row) :
container(container), x(rect_x), y(rect_y)
{
    int left_top_idx = rect_y * points_in_row * 2 + rect_x * 2;
    int right_top_idx = rect_y * points_in_row * 2 + rect_x * 2 + 2;
    int left_bottom_idx = (rect_y + 1) * points_in_row * 2 + rect_x * 2;
    int right_bottom_idx = (rect_y + 1) * points_in_row * 2 + rect_x * 2 + 2;

    idx[0] = left_top_idx;
    idx[1] = right_top_idx;
    idx[2] = right_bottom_idx;
    idx[3] = left_bottom_idx;

    createVertexStruct();
}
