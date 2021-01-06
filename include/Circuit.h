//
// Created by ukio on 21.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_CIRCUIT_H
#define IMGUI_SFML_APPLICATION_CIRCUIT_H

#include "Mouse.h"
#include "sfDistance.h"

class CircuitIndexed
{
public:
    std::vector<double> & container;
    // |__px1__|__py1__|__px2__|__py2__|__px3__|__py3__|... -//-
    std::vector<sf::Vertex> vertexes;
    int circuitLength;
    sf::Color color = {255,255,255};


    CircuitIndexed(std::vector<double> & points);
    CircuitIndexed(std::vector<double> & points, int size);

    void createVertexStruct() ;
    bool isConvex() ;
    void draw(sf::RenderWindow & window) ;
};

#endif //IMGUI_SFML_APPLICATION_CIRCUIT_H
