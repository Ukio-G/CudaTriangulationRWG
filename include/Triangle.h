//
// Created by ukio on 19.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_TRIANGLE_H
#define IMGUI_SFML_APPLICATION_TRIANGLE_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "include/Circuit.h"
#include <random>

using RawPointType = double;

class Point;
std::ostream & operator<<(std::ostream & out, Point &p);
void operator>>(Point &p, double * point_data);

class Point
{
public:
    Point() = default;
    Point(double x, double y) : x(x), y(y) { }
    Point(RawPointType * coordinates) : x(coordinates[0]), y(coordinates[1]) { }
    double x;
    double y;

    double distance (Point other) {
        auto dx = std::abs(x - other.x);
        auto dy = std::abs(y - other.y);
        return std::sqrt(dx*dx + dy*dy);
    }

    bool isIntersected(sf::Vector2i point,  double offset = 2.0) {
        return distance(Point(point.x, point.y)) < offset;
    }

    bool isIntersected(Point other,  double offset = 2.0) {
        return distance(other) < offset;
    }

    bool isIntersected(double xx, double yy,  double offset = 2.0) {
        return distance(Point(xx, yy)) < offset;
    }

    operator sf::Vector2f() {
        sf::Vector2f result;
        result.x = x;
        result.y = y;
        return result;
    }

    double dot(Point & other) {
        return (x * other.x + y * other.y);
    }

    double cross(Point & other)
    {
        double k = x * other.y - y * other.x;
        return k;
    }

    double angle(Point p1, Point p2)
    {
        p1 = p1 - *this;
        p2 = p2 - *this;

        double distances = p1.distance({0,0}) * p2.distance({0, 0});
        double cos = p1.dot(p2)/distances;
        return std::acos(cos) * 180.0 / 3.14159265;
    }

    Point operator-(Point & other) {
        return {x - other.x, y - other.y};
    }

    Point operator+(Point & other) {
        return {x + other.x, y + other.y};
    }

    Point to_screen_space(sf::RenderWindow & window)
    {
        return Point(x - window.getSize().x/2, (y - window.getSize().y/2) * -1);
    }
};


struct DebugDebug
{
    double x1;
    double x2;
    double y1;
    double y2;

    bool x_intersected;
    bool y_intersected;

    Point start;
    Point end;
};

inline void operator>>(Point &p, double * point_data)
{
    point_data[0] = p.x;
    point_data[1] = p.y;
}

inline Point randomPoint(RawPointType max_x = 300.0, RawPointType max_y = 300.0)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<RawPointType> x_generator(1.0, max_x);
    std::uniform_real_distribution<RawPointType> y_generator(1.0, max_y);
    return Point(x_generator(mt),y_generator(mt));
}

inline void generateRandomRawPoints(int pointsCount, std::vector<double> & container,
                                    RawPointType max_x = 300.0, RawPointType max_y = 300.0)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<RawPointType> x_generator(100.0, max_x);
    std::uniform_real_distribution<RawPointType> y_generator(100.0, max_y);
    for (int i = 0; i < pointsCount; ++i)
    {
        container.push_back(x_generator(mt));
        container.push_back(y_generator(mt));
    }
}

inline sf::CircleShape generateGraphicVertex(Point & p, sf::Color color = {255, 0 ,0})
{
    sf::CircleShape graphicObject;
    sf::Vector2f position = p;

    graphicObject.setPosition(position);
    graphicObject.setFillColor(color);
    graphicObject.setRadius(3.0f);

    return graphicObject;
}

inline std::vector<sf::CircleShape> generateGraphicVertexes(std::vector<Point> & points)
{
    std::vector<sf::CircleShape> result;
    result.reserve(points.size());
    for (auto & object : points)
        result.push_back(generateGraphicVertex(object));
    return std::move(result);
}

class TriangleIndex
{
public:
    int p1;
    int p2;
    int p3;
    std::vector<double> & container;
    TriangleIndex (std::vector<double> & points, int p1, int p2, int p3) : p1(p1), p2(p2), p3(p3), container(points)
    {
    }

    void draw(sf::RenderWindow& window) {
        sf::Vertex vertices[4] =
        {
                sf::Vertex(sf::Vector2f (container[2 * p1], container[2 * p1+ 1]), sf::Color(0, 127, 127)),
                sf::Vertex(sf::Vector2f (container[2 * p2], container[2 * p2+ 1]), sf::Color(0, 127, 127)),
                sf::Vertex(sf::Vector2f (container[2 * p3], container[2 * p3+ 1]), sf::Color(0, 127, 127)),
                sf::Vertex(sf::Vector2f (container[2 * p1], container[2 * p1+ 1]), sf::Color(0, 127, 127))
        };
        window.draw(vertices,4,sf::LineStrip);
    }
};

class Triangle
{
public:
    Triangle (std::vector<Point> points) : vertexes_graphic(generateGraphicVertexes(points)), vertexes_points(points) { }
    Triangle (RawPointType * coordinates)
    {
        vertexes_points = {Point(coordinates), Point(coordinates + 2), Point(coordinates + 4)};
        vertexes_graphic = generateGraphicVertexes(vertexes_points);
    }
    std::vector<sf::CircleShape> vertexes_graphic;
    std::vector<Point> vertexes_points;

    void draw(sf::RenderWindow & window) {
        sf::Vertex vertices[vertexes_graphic.size() + 1];
        int i = 0;
        for (auto &vertexesGraphic : vertexes_graphic) {
            window.draw(vertexesGraphic);
            vertices[i].position = {vertexesGraphic.getPosition().x + vertexesGraphic.getRadius() / 2,
                                    vertexesGraphic.getPosition().y + vertexesGraphic.getRadius() / 2};
            vertices[i++].color = {255, 0, 0};
        }
        vertices[i].position = {vertexes_graphic[0].getPosition().x + vertexes_graphic[0].getRadius() / 2,
                                vertexes_graphic[0].getPosition().y + vertexes_graphic[0].getRadius() / 2};
        vertices[i].color = {255, 0, 0};
        window.draw(vertices,vertexes_graphic.size() + 1,sf::LineStrip);
    }

    float sign (Point p1, Point p2, Point p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }

    bool PointInTriangle (Point pt)
    {
        float d1, d2, d3;
        bool has_neg, has_pos;
        Point v1 = vertexes_points[0];
        Point v2 = vertexes_points[1];
        Point v3 = vertexes_points[2];
        d1 = sign(pt, v1, v2);
        d2 = sign(pt, v2, v3);
        d3 = sign(pt, v3, v1);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }
};

#endif //IMGUI_SFML_APPLICATION_TRIANGLE_H

