#pragma once
#include "DrawPrimitivesUtil.h"
#include "../ImGUI/imgui.h"

float Wedge(const float* a, const float* b)
{   // a[2], b[2]
  return a[0] * b[1] - a[1] * b[0];
}

typedef ImVec2 fPoint;

float sign(fPoint p1, fPoint p2, fPoint p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(fPoint pt, ColoredTri triangle)
{
  fPoint v1 = triangle.p0;
  fPoint v2 = triangle.p1;
  fPoint v3 = triangle.p2;
  float d1, d2, d3;
  bool has_neg, has_pos;

  d1 = sign(pt, v1, v2);
  d2 = sign(pt, v2, v3);
  d3 = sign(pt, v3, v1);

  has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
  has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

  return !(has_neg && has_pos);
}

// GET IF TARGET IS INSIDE TRIANGLE
bool IsInside(Tri triangle, ImVec2 mouseTarget)
{

  float faceVertices[][3] = {
    {triangle.p0.x, triangle.p1.x, triangle.p2.x},
    {triangle.p0.y, triangle.p1.y, triangle.p2.y}
  };
  float target[2] = { mouseTarget.x, mouseTarget.y };
  float v1[2] = { faceVertices[0][0], faceVertices[1][0] };
  float v2[2] = { faceVertices[0][1], faceVertices[1][1] };
  float v3[2] = { faceVertices[0][2], faceVertices[1][2] };
  float x1[2] = { v2[0] - v1[0], v2[1] - v1[1] };
  float x2[2] = { v3[0] - v2[0], v3[1] - v2[1] };
  float x3[2] = { v1[0] - v3[0], v1[1] - v3[1] };
  float y1[2] = { target[0] - v1[0], target[1] - v1[1] };
  float y2[2] = { target[0] - v2[0], target[1] - v2[1] };
  float y3[2] = { target[0] - v3[0], target[1] - v3[1] };
  float w1 = Wedge(x1, y1);
  float w2 = Wedge(x2, y2);
  float w3 = Wedge(x3, y3);

  return (w1 >= 0.0f) && (w2 >= 0.0f) && (w3 >= 0.0f);
}