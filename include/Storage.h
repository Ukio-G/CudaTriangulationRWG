//
// Created by ukio on 25.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_STORAGE_H
#define IMGUI_SFML_APPLICATION_STORAGE_H

#include <vector>
#include "Triangle.h"
#include "Circuit.h"
#include "AppendModes.h"
#include "Matrix2.h"
#include "BoundBox.h"
#include "Rectangle.h"
#include "BoundingRectangles.h"

extern MouseMoveEvent mouse_handler;

class Storage;
void appendTransformation(Storage & s, Matrix2D & transformation);

class Storage {
public:
    std::vector<double> points_set;
    std::vector<TriangleIndex> triangles;
    std::vector<RectangleIndexed> rectangles;
    CircuitIndexed circuit;
    BoundBox bbox;
    BoundingRectangles *boundingRectangles = nullptr;
    sf::RenderWindow &window;
    MouseSubscriber mouseMove;
    MouseSubscriber mouseRightClick;
    ClickModes clickMode = MovePoint;
    Storage() = default;
    Storage(std::vector<double> circuit_set, sf::RenderWindow &window);
    void triangulate();
    void rotateTransform(double x, double y, sf::Vector2i clickpoint);
    void moveTransformation(double x, double y, sf::Vector2i clickpoint);
    void movePoint(double x, double y, sf::Vector2i clickpoint);

    void append_point_to_set(double x, double y);
    void create_rectangle(int x, int y);
    void createBoundingRectangles();
    void update_rectangles();
    void draw_rectangles();
    void draw_triangles();
    void draw_circuit();
    void draw_bbox();

    void draw_points();

    void draw();
};

#endif //IMGUI_SFML_APPLICATION_STORAGE_H
