//
// Created by ukio on 31.12.2020.
//

#include <iostream>
#include "include/BoundBox.h"

BoundBox::BoundBox(CircuitIndexed & circuit, float step) : circuit(circuit), step(step)
{
    createMinBound();
    createBigBound();
}

void BoundBox::updateStep(float new_step)
{
    if (step != new_step)
    {
        step = new_step;
        recreate();
    }
}

void BoundBox::recreate()
{
    points_to_draw.clear();
    points.clear();
    createMinBound();
    createBigBound();
}

void BoundBox::createMinBound()
{
    Point Pmin = Point(circuit.container[0], circuit.container[1]);
    Point Pmax = Point(circuit.container[0], circuit.container[1]);

    for(int i = 0; i < circuit.container.size(); i++)
    {
        if (i % 2 == 0) // X coord
        {
            if (circuit.container[i] > Pmax.x)
                Pmax.x = circuit.container[i];
            if (circuit.container[i] < Pmin.x)
                Pmin.x = circuit.container[i];
        }
        else // Y coord
        {
            if (circuit.container[i] > Pmax.y)
                Pmax.y = circuit.container[i];
            if (circuit.container[i] < Pmin.y)
                Pmin.y = circuit.container[i];
        }
    }

    min_bound_points = std::vector<double>({
                                                   Pmin.x, Pmin.y,
                                                   Pmax.x, Pmin.y,
                                                   Pmax.x, Pmax.y,
                                                   Pmin.x, Pmax.y
                                           });

    min_bound_width = Pmax.x - Pmin.x;
    min_bound_height = Pmax.y - Pmin.y;
    if (MinBound != nullptr)
        delete MinBound;
    MinBound = new CircuitIndexed(min_bound_points);
}

void BoundBox::createBigBound()
{
    last_x_point_idx = (min_bound_width / step) + 1;
    last_y_point_idx = (min_bound_height / step) + 1;

    double big_bound_width = (double)last_x_point_idx * step;
    double big_bound_height = (double)last_y_point_idx * step;

    double offset_left = (big_bound_width - min_bound_width) / 2;
    double offset_height = (big_bound_height - min_bound_height) / 2;

    auto pminx = min_bound_points[0];
    auto pminy = min_bound_points[1];
    auto pmaxx = min_bound_points[2];
    auto pmaxy = min_bound_points[5];

    big_bound_points = std::vector<double>({
                                                   pminx - offset_left, pminy - offset_height,
                                                   pmaxx + offset_left, pminy - offset_height,
                                                   pmaxx + offset_left, pmaxy + offset_height,
                                                   pminx - offset_left, pmaxy + offset_height,
                                           });
    pminx = pminx - offset_left;
    pminy = pminy - offset_height;
    for(int y = 0; y <= last_y_point_idx; y++)
        for(int x = 0; x <= last_x_point_idx; x++) {
            points.push_back(pminx + step * x);
            points.push_back(pminy + step * y);
            points_to_draw.emplace_back(sf::Vector2f(pminx + step * x, pminy + step * y));
        }
    if (BigBound != nullptr)
        delete BigBound;
    BigBound = new CircuitIndexed(big_bound_points);
    BigBound->color = {0,255,0};
    BigBound->createVertexStruct();
}

void BoundBox::draw_min(sf::RenderWindow & window)
{
    MinBound->draw(window);
}

void BoundBox::draw_big(sf::RenderWindow & window)
{
    BigBound->draw(window);
}

void BoundBox::draw_points(sf::RenderWindow & window)
{
    window.draw(points_to_draw.data(), points_to_draw.size(), sf::Points);
}

BoundBox::~BoundBox()
{
    delete BigBound;
    delete MinBound;
}

std::vector<int> BoundBox::getRectangleIndexes(int i, int j) {
    
    return std::vector<int>();
}
