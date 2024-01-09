#include "Application.h"

#include "raylib.h"

Application::Application()
{
  InitWindow(this->width, this->height, "Marching Squares");
}

Application::~Application()
{
  CloseWindow();
}

void Application::run()
{
  while (!WindowShouldClose())
  {
    this->marchingSquares.update();

    BeginDrawing();

    ClearBackground(WHITE);
    this->marchingSquares.draw();

    EndDrawing();
  }
}
