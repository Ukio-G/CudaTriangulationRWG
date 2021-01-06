//
// Created by ukio on 22.12.2020.
//
#include <cmath>
#include "include/Mouse.h"

void MouseMoveEvent::handle(sf::Event & event, sf::RenderWindow & window)
{
    if (event.type != sf::Event::MouseButtonPressed &&
        event.type !=  sf::Event::MouseButtonReleased &&
        event.type !=  sf::Event::MouseMoved)
        return;

    sf::Vector2i event_position = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed) {
        leftKeyPressed = !leftKeyPressed && event.mouseButton.button == sf::Mouse::Left;
        rightKeyPressed = !rightKeyPressed && event.mouseButton.button == sf::Mouse::Right;
    } else if (event.type == sf::Event::MouseButtonReleased) {
        leftKeyPressed = leftKeyPressed && !(event.mouseButton.button == sf::Mouse::Left);
        rightKeyPressed = rightKeyPressed && !(event.mouseButton.button == sf::Mouse::Right);
    }

    auto dx = event_position.x - prev_position.x;
    auto dy = event_position.y - prev_position.y;

    if (event.type == sf::Event::MouseMoved && leftKeyPressed)
        for (auto &item : listeners_move)
            item->notify(dx, dy, event_position);

    if (event.type == sf::Event::MouseButtonPressed && rightKeyPressed)
        for (auto &item : listeners_right_click)
            item->notify(dx, dy, event_position);

    prev_position = event_position;
}

void MouseMoveEvent::subscribe_move(MouseSubscriber *subscriber)
{
    listeners_move.push_back(subscriber);
    subscriber->handler = this;
}

void MouseMoveEvent::subscribe_right_click(MouseSubscriber *subscriber)
{
    listeners_right_click.push_back(subscriber);
    subscriber->handler = this;
}

void MouseMoveEvent::unsubscribe(MouseSubscriber *subscriber)
{
    std::remove(listeners_move.begin(), listeners_move.end(), subscriber);
};

void MouseSubscriber::notify(double x, double y, sf::Vector2i mouse_position)
{
    action(x, y, mouse_position);
}

MouseSubscriber::~MouseSubscriber()
{
    if(handler)
        handler->unsubscribe(this);
}


int isIntersectSet(double x, double y, std::vector<double> & points, double offset)
{
    for (int i = 0; i < points.size() - 1; i+=2)
    {
        double px = points[i];
        double py = points[i + 1];

        double dx = px - x;
        double dy = py - y;

        double distance = std::sqrt(dx*dx + dy*dy);
        if (distance <= offset)
            return i;
    }
    return -1;
}
