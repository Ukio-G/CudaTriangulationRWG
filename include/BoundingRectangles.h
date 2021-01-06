//
// Created by ukio on 04.01.2021.
//

#ifndef IMGUI_SFML_APPLICATION_BOUNDINGRECTANGLES_H
#define IMGUI_SFML_APPLICATION_BOUNDINGRECTANGLES_H
#include "Circuit.h"
#include "BoundBox.h"
#include "Rectangle.h"

class Storage;

class BoundingRectangles
{
public:
    CircuitIndexed & circuit;
    BoundBox & bbox;
    Storage & parent;
    int ** boundingRectangleFlags = nullptr;
    int w;
    int h;

    BoundingRectangles(CircuitIndexed & circuitIndexed, BoundBox & boundBox, Storage & parent);
    ~BoundingRectangles();
    void print_intersected();
    void deleteRectFlags();
    void realloc(int new_w, int new_h);
    void calculateInnerShape();

    RectangleIndexed &getRectangleByXY(int x, int y);
};

#endif //IMGUI_SFML_APPLICATION_BOUNDINGRECTANGLES_H
