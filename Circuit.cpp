//
// Created by ukio on 31.12.2020.
//
#include "include/Circuit.h"
#include "include/Triangle.h"

void CircuitIndexed::createVertexStruct() {
    vertexes.reserve(circuitLength * 2 + 1);
    vertexes.clear();
    for (int i = 0; i < circuitLength - 2; i+=2) {
        double x_start = container[i];
        double y_start = container[i + 1];

        double x_end = container[i + 2];
        double y_end = container[i + 3];

        vertexes.emplace_back(sf::Vector2f(x_start, y_start), color);
        vertexes.emplace_back(sf::Vector2f(x_end, y_end), color);
    }
    vertexes.emplace_back(sf::Vector2f(container[circuitLength - 2],
                                       container[circuitLength - 1]), color);
    vertexes.emplace_back(sf::Vector2f(container[0],container[1]), color);
}

bool CircuitIndexed::isConvex() {
    for (int i = 0; i < circuitLength - 1; i+=2)
    {
        int point_a_index = (i != 0) ? (i - 2) : (container.size() - 2);
        int point_b_index = (i == circuitLength - 2) ? 0 : i + 2;
        Point vector_a(container[point_a_index],
                       container[point_a_index + 1]);
        Point origin(container[i], container[i + 1]);
        Point vector_b(container[point_b_index], container[point_b_index + 1]);

        vector_a = vector_a - origin;
        vector_b = vector_b - origin;

        if(vector_b.cross(vector_a) < 0) {
            color = {255, 0, 0};
            return false;
        }
    }
    color = {255, 255, 255};
    return true;
}

void CircuitIndexed::draw(sf::RenderWindow & window) {
    window.draw(vertexes.data() ,vertexes.size(), sf::LineStrip);
}

CircuitIndexed::CircuitIndexed(std::vector<double> &points, int size)  : container(points), circuitLength(size) {
    createVertexStruct();
}

CircuitIndexed::CircuitIndexed(std::vector<double> &points) : container(points), circuitLength(points.size()) {
    createVertexStruct();
}
