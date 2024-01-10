#include "MarchingSquares.h"

#include "raylib.h"

MarchingSquares::MarchingSquares()
{
  const siv::PerlinNoise::seed_type seed = GetRandomValue(0, SHRT_MAX);
  this->perlin.reseed(seed);

  std::vector<std::vector<float>> field(this->row, std::vector<float>(this->col));
  this->field = field;
}

MarchingSquares::~MarchingSquares()
{
}

void MarchingSquares::update()
{
  float y = 0;
  for (int i = 0; i < this->row; i++)
  {
    y += this->increment;
    float x = 0;
    for (int j = 0; j < this->col; j++)
    {
      x += this->increment;
      float noise = (float)this->perlin.noise3D_01(x, y, GetTime());
      field[i][j] = noise;
    }
  }
}

void MarchingSquares::draw()
{
   // Draw perlin noise
   // for (int i = 0; i < this->row; i++)
   // {
   //   for (int j = 0; j < this->col; j++)
   //   {
   //     unsigned char value = field[i][j] * 255;
   //     Color color = { .r = value, .g = value, .b = value, .a = 255 };
   //     DrawRectangle(j * this->res, i * this->res, this->res, this->res, color);
   //   }
   // }

  for (int i = 0; i < this->row - 1; i++)
  {
    for (int j = 0; j < this->col - 1; j++)
    {
      float x = (float)j * this->res;
      float y = (float)i * this->res;
      Vector2 up = { x + this->res / 2 , y };
      Vector2 right = { x + this->res  , y + this->res / 2 };
      Vector2 down = { x + this->res / 2 , y + this->res };
      Vector2 left = { x , y + this->res / 2 };

      int a = (this->field[i][j] >= this->threshold) ? 1 : 0;
      int b = (this->field[i][j + 1] >= this->threshold) ? 1 : 0;
      int c = (this->field[i + 1][j + 1] >= this->threshold) ? 1 : 0;
      int d = (this->field[i + 1][j] >= this->threshold) ? 1 : 0;
      int state = getState(a, b, c, d);
      switch (state)
      {
      case 0:
        break;
      case 1:
        DrawLineEx(down, left, 2, MAROON);
        break;
      case 2:
        DrawLineEx(right, down, 2, MAROON);
        break;
      case 3:
        DrawLineEx(right, left, 2, MAROON);
        break;
      case 4:
        DrawLineEx(up, right, 2, MAROON);
        break;
      case 5:
        DrawLineEx(up, left, 2, MAROON);
        DrawLineEx(right, down, 2, MAROON);
        break;
      case 6:
        DrawLineEx(up, down, 2, MAROON);
        break;
      case 7:
        DrawLineEx(up, left, 2, MAROON);
        break;
      case 8:
        DrawLineEx(up, left, 2, MAROON);
        break;
      case 9:
        DrawLineEx(up, down, 2, MAROON);
        break;
      case 10:
        DrawLineEx(up, right, 2, MAROON);
        DrawLineEx(down, left, 2, MAROON);
        break;
      case 11:
        DrawLineEx(up, right, 2, MAROON);
        break;
      case 12:
        DrawLineEx(right, left, 2, MAROON);
        break;
      case 13:
        DrawLineEx(right, down, 2, MAROON);
        break;
      case 14:
        DrawLineEx(down, left, 2, MAROON);
        break;
      case 15:
      default:
        break;
      }
    }
  }
}

int MarchingSquares::getState(int a, int b, int c, int d)
{
  return (a << 3) + (b << 2) + (c << 1) + d;
}
