//
// Created by ukio on 22.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_SFDISTANCE_H
#define IMGUI_SFML_APPLICATION_SFDISTANCE_H


//#include <SFML/Graphics/CircleShape.hpp>
//#include <cmath>
//
//inline double getDistance(double x, double y, sf::CircleShape & shape1)
//{
//    double dx = std::abs(shape1.getPosition().x + shape1.getRadius() / 2 - x);
//    double dy = std::abs(shape1.getPosition().y + shape1.getRadius() / 2 - y);
//
//    return std::sqrt(dx*dx + dy*dy);
//}
//
//inline double getDistance(sf::CircleShape &shape1 , sf::CircleShape & shape2)
//{
//    double dx = std::abs(shape1.getPosition().x + shape1.getRadius() / 2 - shape2.getPosition().x + shape2.getRadius() / 2);
//    double dy = std::abs(shape1.getPosition().y + shape1.getRadius() /2  - shape2.getPosition().y + shape2.getRadius() / 2);
//
//    return std::sqrt(dx*dx + dy*dy);
//}
//
//inline double getDistance(sf::Vector2i &point , sf::CircleShape & shape1)
//{
//    double dx = std::abs(shape1.getPosition().x + shape1.getRadius() / 2 - point.x);
//    double dy = std::abs(shape1.getPosition().y + shape1.getRadius() / 2 - point.y);
//
//    return std::sqrt(dx*dx + dy*dy);
//}
//
//inline bool isIntersected(double x, double y, sf::CircleShape & shape, double offset = 2.0)
//{
//    return getDistance(x, y, shape) < offset;
//}
//
//bool isIntersected(sf::Vector2i &point, sf::CircleShape & shape, double offset = 2.0)
//{
//    return getDistance(point, shape) < offset;
//}

#endif //IMGUI_SFML_APPLICATION_SFDISTANCE_H
