//
// Created by ukio on 22.12.2020.
//

#ifndef IMGUI_SFML_APPLICATION_MOUSE_H
#define IMGUI_SFML_APPLICATION_MOUSE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window.hpp>
#include <functional>


class MouseMoveEvent;
class MouseSubscriber;

int isIntersectSet(double x, double y, std::vector<double> & points, double offset = 5.0);

class MouseMoveEvent
{
public:
    std::vector<MouseSubscriber*>    listeners_move;
    std::vector<MouseSubscriber*>    listeners_right_click;
    bool leftKeyPressed = false;
    bool rightKeyPressed = false;
    sf::Vector2i prev_position = {0,0};
    void subscribe_move(MouseSubscriber * subscriber);
    void subscribe_right_click(MouseSubscriber *subscriber);
    void unsubscribe(MouseSubscriber * subscriber);
    void handle(sf::Event &event, sf::RenderWindow &window);
};

class MouseSubscriber
{
public:
    std::function<void(double, double, sf::Vector2i)> action;
    MouseMoveEvent * handler = nullptr;
    void notify(double x, double y, sf::Vector2i mouse_position);
    ~MouseSubscriber();

    void notify(sf::Event &event);
};

#endif //IMGUI_SFML_APPLICATION_MOUSE_H
