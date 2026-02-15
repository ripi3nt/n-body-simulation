#pragma once

struct Vec2 {
  float x;
  float y;

  Vec2& operator+=(const Vec2& vec2) {
    x += vec2.x; 
    y += vec2.y; 
    return *this;
  }

  Vec2& operator-=(const Vec2& vec2) {
    x -= vec2.x; 
    y -= vec2.y; 
    return *this;
  }

  Vec2 operator-(const Vec2& vec) {
    return {x - vec.x, y - vec.y};
  }

  Vec2 operator+(const Vec2& vec) {

    return {vec.x + x, vec.y + y};
  }

  Vec2 operator=(const Vec2& vec) {
    return {vec.x, vec.y};
  }

  Vec2 operator*(float s) {
    return { x * s, y * s};
  }

  Vec2 operator/(float s) {
    return { x / s, y / s};
  }
};


