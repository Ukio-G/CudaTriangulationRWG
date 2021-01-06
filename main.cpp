#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <GL/glew.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window.hpp>
#include <include/Storage.h>
#include <include/Line.h>
#include "include/Triangle.h"
#include "include/Mouse.h"
#include "include/Matrix2.h"
#include "include/MenuActions.h"
#include "include/BoundBox.h"


static bool executing = true;
void drawMenu(Storage & s);
void drawBoundBoxMenu(Storage & s);
void handleEvent(sf::Event & event, sf::RenderWindow & window);
float step_slider;
bool intersected;
Line::ClickMode clickModeLine = Line::MovePoints;
MouseMoveEvent mouse_handler;
Storage * storage;
void printMap(Storage & s);
std::vector<double> octodouble = {
        100.0, 100.0,
        200.0, 100.0,
        250.0, 200.0,
        250.0, 300.0,
        200.0, 350.0,
        150.0, 350.0,
        100.0, 300.0,
        50.0, 250.0
};

std::vector<std::pair<int, int>> intersectedIndexedRecatngle;

int main() {
    sf::ContextSettings settings;
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(false);
    ImGui::SFML::Init(window);
    // activate the window
    window.setActive(true);
    sf::Clock deltaClock;

    glewInit();

    /* Resource declaration */
    Storage s(octodouble, window);
    storage = &s;
    s.update_rectangles();
    s.createBoundingRectangles();

    step_slider = 20.0;

    while (executing) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            ImGui::SFML::ProcessEvent(event);
            handleEvent(event, window);
            mouse_handler.handle(event, window);
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        drawMenu(s);
        drawBoundBoxMenu(s);
        window.clear();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::SFML::Render(window);

        /* Draw using OpenGL or SFML start here */
//        s.draw_points();
//        s.draw_bbox();
        s.draw_rectangles();
        s.draw_circuit();
        window.display();
    }
    window.close();
    ImGui::SFML::Shutdown();
    return 0;
}

void handleEvent(sf::Event & event, sf::RenderWindow & window)
{
    if (event.type == sf::Event::Resized)
        glViewport(0, 0, event.size.width, event.size.height);
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        executing = false;
}

void appendTransformation(Storage & s, Matrix2D & transformation)
{
    for (int i = 0; i < s.points_set.size() - 1; i += 2)
    {
        Point p(s.points_set[i], s.points_set[i + 1]);
        p = transformation * p;
        p >> &s.points_set[i];
    }
    s.circuit.createVertexStruct();
}


void drawBoundBoxMenu(Storage & s)
{
    ImGui::Begin("Menu Bbox");
    ImGui::Text("last_x_point_idx %i", s.bbox.last_x_point_idx);
    ImGui::Text("last_y_point_idx %i", s.bbox.last_y_point_idx);
    ImGui::End();
};


void printMap(Storage & s)
{
    ImGui::Begin("Map boundingRectangles");
    for (int y = 0; y < s.boundingRectangles->h; ++y) {
        std::string line = "";
        for (int x = 0; x < s.boundingRectangles->w; ++x)
            line += std::to_string(s.boundingRectangles->boundingRectangleFlags[x][y]);
        ImGui::Text("%-3i%s", y, line.c_str());
    }
    ImGui::End();
}


void drawMenu(Storage & s) {
    ImGui::Begin("Menu");

    ImGui::Text("Active append mode: %s", to_string(s.clickMode).c_str());

    if (s.circuit.isConvex())
        ImGui::Text("Circuit is convex");
    else
        ImGui::Text("Circuit is not convex");

    if (intersected)
        ImGui::Text("Intersected");
    else
        ImGui::Text("Not Intersected");

    if (ImGui::Button("Append points to points_set"))
        s.clickMode = AddPoint;
    if (ImGui::Button("Move points"))
        s.clickMode = MovePoint;
    if (ImGui::Button("Move origin"))
        s.clickMode = MoveOrigin;
    if (ImGui::Button("Transformation translate"))
        s.clickMode = TransformationTranslate;
    if (ImGui::Button("Transformation rotate"))
        s.clickMode = RotateTransformation;

    if (ImGui::Button("Line move points"))
        clickModeLine = Line::ClickMode::MovePoints;
    if (ImGui::Button("Line translate"))
        clickModeLine = Line::ClickMode::TranslateLine;

    if (ImGui::Button("Flip X"))
        flipX(s);
    if (ImGui::Button("Flip Y"))
        flipY(s);
    auto prev = step_slider;
    ImGui::SliderFloat("bound step", &step_slider, 0.0f, 100.0f);
    if (prev != step_slider) {
        storage->bbox.updateStep(step_slider);
        storage->update_rectangles();
    }


    ImGui::End();
}
