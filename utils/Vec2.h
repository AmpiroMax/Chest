#ifndef VEC2_H
#define VEC2_H

#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>
#include <cmath>
#include <iostream>
#include <vector>

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2() = default;
    // Constructor for float arguments
    Vec2(float xx, float yy) : x(xx), y(yy) {}

    Vec2(const std::vector<int> &v) : x(v.at(0)), y(v.at(1)) {}
    Vec2(const std::vector<float> &v) : x(v.at(0)), y(v.at(1)) {}

    // Копирующий конструктор из SFML
    Vec2(const sf::Vector2f &v) : x(v.x), y(v.y) {}
    Vec2(const sf::Vector2i &v) : x(v.x), y(v.y) {}

    // Копирующий конструктор из Box2D
    Vec2(const b2Vec2 &v) : x(v.x), y(v.y) {}

    // Преобразование к SFML
    operator sf::Vector2f() const { return sf::Vector2f(x, y); }
    // Преобразование к Box2D
    operator b2Vec2() const { return b2Vec2(x, y); }

    // Операторы и базовые методы (оставляю прежние)
    Vec2 operator+(const Vec2 &other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2 &other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
    Vec2 operator/(float s) const { return Vec2(x / s, y / s); }
    Vec2 &operator+=(const Vec2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2 &operator-=(const Vec2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vec2 &other) const { return !(*this == other); }

    float length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalized() const {
        float l = length();
        return (l > 0) ? Vec2(x / l, y / l) : Vec2();
    }

    // Output operator for Vec2 to std::cout
    friend std::ostream &operator<<(std::ostream &os, const Vec2 &v) {
        // Print coordinates in format (x, y)
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

#endif // VEC2_H
