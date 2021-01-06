//
// Created by ukio on 04.01.2021.
//
#include <iostream>
#include "include/BoundingRectangles.h"
#include "include/Storage.h"

BoundingRectangles::BoundingRectangles(CircuitIndexed & circuitIndexed, BoundBox & boundBox, Storage & parent) :
circuit(circuitIndexed), bbox(boundBox), parent(parent)
{
    realloc(boundBox.last_x_point_idx, boundBox.last_y_point_idx);
    for (auto &item : parent.rectangles) {
        int r_x = item.x;
        int r_y = item.y;
        boundingRectangleFlags[r_x][r_y] = (int)item.intersected;
    }
}

void BoundingRectangles::print_intersected() {
    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            if (boundingRectangleFlags[x][y])
                std::cout << "has intersected rectangle at x = " << x << " and y = " << y << "\n";
};

void BoundingRectangles::deleteRectFlags()
{
    if (!boundingRectangleFlags)
        return;
    for(int i = 0; i < h; ++i)
        delete [] boundingRectangleFlags[i];
    delete [] boundingRectangleFlags;
}

void BoundingRectangles::realloc(int new_w, int new_h)
{
    w = new_w;
    h = new_h;
//    deleteRectFlags();
    std::cout << __func__ << " " << h << " " << w << "\n";
//    boundingRectangleFlags = new int*[h];
    boundingRectangleFlags = new int*[200];
    for(int i = 0; i < h; ++i)
            boundingRectangleFlags[i] = new int[200];
//        boundingRectangleFlags[i] = new int[w];
}


BoundingRectangles::~BoundingRectangles()
{
    deleteRectFlags();
}

RectangleIndexed & BoundingRectangles::getRectangleByXY(int x, int y)
{
    return parent.rectangles[y * parent.bbox.last_x_point_idx + x];
}

void BoundingRectangles::calculateInnerShape() {
    auto isHasLeft = [this](int x, int y) -> bool {
        for(int x_cnt = x; x_cnt >= 0; x_cnt--)
            if (boundingRectangleFlags[x_cnt][y])
                return true;
        return false;
    };

    auto isHasRight = [this](int x, int y) -> bool {
        for(int x_cnt = x; x_cnt <= w; x_cnt++)
            if (boundingRectangleFlags[x_cnt][y])
                return true;
        return false;
    };

    auto isHasTop = [this](int x, int y) -> bool {
        for(int y_cnt = y; y_cnt >= 0; y_cnt--)
            if (boundingRectangleFlags[x][y_cnt])
                return true;
        return false;
    };

    auto isHasBottom = [this](int x, int y) -> bool {
        for(int y_cnt = y; y_cnt <= h; y_cnt++)
            if (boundingRectangleFlags[x][y_cnt])
                return true;
        return false;
    };

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            bool hasLeft = isHasLeft(x, y);
            bool hasRight = isHasRight(x, y);
            bool hasTop = isHasTop(x, y);
            bool hasBottom = isHasBottom(x, y);
            boundingRectangleFlags[x][y] = (hasRight && hasLeft && hasTop && hasBottom) ? 1 : 0;
            if (hasRight && hasLeft && hasTop && hasBottom) {
                getRectangleByXY(x, y).intersected = true;
            }

        }
    }
}
