#pragma once
#include "DrawPrimitivesUtil.h"
#include "../ImGUI/imgui.h"

float Wedge(const float* a, const float* b)
{   // a[2], b[2]
  return a[0] * b[1] - a[1] * b[0];
}

float sign(ImVec2 p1, ImVec2 p2, ImVec2 p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(ImVec2 pt, ColoredTri triangle)
{
  ImVec2 v1 = *triangle.p0;
  ImVec2 v2 = *triangle.p1;
  ImVec2 v3 = *triangle.p2;
  float d1, d2, d3;
  bool has_neg, has_pos;

  d1 = sign(pt, v1, v2);
  d2 = sign(pt, v2, v3);
  d3 = sign(pt, v3, v1);

  has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
  has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

  return !(has_neg && has_pos);
}

bool PointInTriangle(ImVec2 pt, const float tri[][3])
{
  return PointInTriangle(pt,
    ColoredTri{
      .p0 = new ImVec2(tri[0][0],tri[1][1]),
      .p1 = new ImVec2(tri[0][1],tri[1][1]),
      .p2 = new ImVec2(tri[0][2],tri[1][2]),
    });
}