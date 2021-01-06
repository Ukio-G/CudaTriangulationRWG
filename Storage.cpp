//
// Created by ukio on 04.01.2021.
//
#include "include/delaunator.hpp"
#include "include/Storage.h"

Storage::Storage(std::vector<double> circuit_set, sf::RenderWindow &window) :
points_set(circuit_set), circuit(CircuitIndexed(points_set)), window(window),
bbox(circuit, 20.0){
    mouse_handler.subscribe_move(&mouseMove);
    mouse_handler.subscribe_right_click(&mouseRightClick);
    mouseMove.action = [this](double x, double y, sf::Vector2i clickpoint) {
        movePoint(x, y, clickpoint);
        moveTransformation(x, y, clickpoint);
        rotateTransform(x, y, clickpoint);
    };
    mouseRightClick.action = [this](double x, double y, sf::Vector2i clickpoint) {
        append_point_to_set(clickpoint.x, clickpoint.y);
        triangulate();
    };
}

void Storage::triangulate() {
    delaunator::Delaunator d(points_set);
    triangles.clear();
    for (std::size_t i = 0; i < d.triangles.size(); i += 3)
        triangles.emplace_back(points_set, (int) d.triangles[i], (int) d.triangles[i + 1],
                               (int) d.triangles[i + 2]);
}

void Storage::rotateTransform(double x, double y, sf::Vector2i clickpoint) {
    if (clickMode != RotateTransformation)
        return;
    Matrix2D matrix2D;
    matrix2D.rotate(x);
    appendTransformation(*this, matrix2D);
}

void Storage::moveTransformation(double x, double y, sf::Vector2i clickpoint) {
    if (clickMode != TransformationTranslate)
        return;
    for (int i = 0; i < points_set.size() - 1; i += 2) {
        points_set[i] += x;
        points_set[i + 1] += y;
    }
    circuit.createVertexStruct();
}

void Storage::movePoint(double x, double y, sf::Vector2i clickpoint) {
    int index_point;
    if ((index_point = isIntersectSet(clickpoint.x, clickpoint.y, points_set, 15.0)) >= 0) {
        points_set[index_point] += x;
        points_set[index_point + 1] += y;
        circuit.createVertexStruct();
        triangulate();
    }
}

void Storage::append_point_to_set(double x, double y) {
    points_set.push_back(x);
    points_set.push_back(y);
}

void Storage::create_rectangle(int x, int y)
{
    rectangles.emplace_back(bbox.points, x, y, bbox.last_x_point_idx + 1);
}

void Storage::update_rectangles()
{
    rectangles.clear();
    for (int y = 0; y < bbox.last_y_point_idx; ++y) {
        for (int x = 0; x < bbox.last_x_point_idx; ++x) {
            rectangles.emplace_back(bbox.points, x, y, bbox.last_x_point_idx + 1);
            auto & r_last = rectangles.back();
            r_last.circuitIntersect(circuit);
        }
    }
    createBoundingRectangles();
}

void Storage::draw_rectangles()
{
    for (auto &rectangle : rectangles)
        rectangle.draw(window);
}

void Storage::draw_triangles() {
    for (auto &item : triangles)
        item.draw(window);
}

void Storage::draw_circuit() {
    circuit.draw(window);
}

void Storage::draw_bbox() {
    bbox.draw_big(window);
}

void Storage::draw_points() {
    bbox.draw_points(window);
}

void Storage::draw() {
    draw_triangles();
    draw_circuit();
}

void Storage::createBoundingRectangles() {
    if (boundingRectangles)
        delete boundingRectangles;

    boundingRectangles = new BoundingRectangles(circuit, bbox, *this);
    boundingRectangles->calculateInnerShape();
}
