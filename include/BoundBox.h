//
// Created by ukio on 29.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_BOUNDBOX_H
#define IMGUI_SFML_APPLICATION_BOUNDBOX_H

#include "Circuit.h"
#include "Triangle.h"

class BoundBox
{
public:
    CircuitIndexed *BigBound = nullptr;
    CircuitIndexed *MinBound = nullptr;
    CircuitIndexed & circuit;
    std::vector<double> min_bound_points;
    std::vector<double> big_bound_points;
    std::vector<sf::Vertex> points_to_draw;
    int last_x_point_idx;
    int last_y_point_idx;
    std::vector<double> points;
    float step;
    double min_bound_width;
    double min_bound_height;

    BoundBox(CircuitIndexed & circuit, float step);

    void recreate();

    void createMinBound();
    void createBigBound();

    void draw_min(sf::RenderWindow & window);
    void draw_big(sf::RenderWindow & window);
    void draw_points(sf::RenderWindow & window);

    std::vector<int> getRectangleIndexes(int i, int j);

    ~BoundBox();

    void updateStep(float new_step);
};

#endif //IMGUI_SFML_APPLICATION_BOUNDBOX_H
