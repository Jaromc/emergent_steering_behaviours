#pragma once

#include <math.h>

template<class T>
class Vector2
{
   public:
      Vector2():x(0), y(0){}
      Vector2(T _x, T _y):x(_x), y(_y){}

      float dot(const Vector2<T> &b) const
      {
         return (x * b.x) + (y * b.y);
      }

      float length() const
      {
         return sqrt((x * x) + (y * y));
      }

      float lengthSq() const
      {
         return (x * x) + (y * y);
      }

      Vector2<T> getNormalise() const
      {
         Vector2<T> n;

         float len = length();
         if (len == 0)
            return n;

         n.x = x / len;
         n.y = y / len;
         return n;
      }

      Vector2<T> operator+(const Vector2<T> &b)const
      {
         return Vector2<T>(x + b.x,y + b.y);
      }

		Vector2<T> operator-(const Vector2<T> &b)const
      {
         return Vector2<T>(x - b.x, y - b.y);
      }

		bool operator==(const Vector2<T> &b)const
      {
         return ((x == b.x) && (y == b.y));
      }

      bool operator!=(const Vector2<T> &b)const
      {
         return ((x != b.x) || (y != b.y));
      }

		Vector2<T> operator*(const Vector2<T> &b)const
      {
         return Vector2<T>(x*b.x, y*b.y);
      }

      Vector2<T> operator-()const
      {
         return Vector2<T>(-x, -y);
      }

      Vector2<T>& operator+=(const Vector2<T> &b)
      {
         x += b.x;
         y += b.y;
         return *this;
      }

		Vector2<T>& operator-=(const Vector2<T> &b)
      {
         x -= b.x;
         y -= b.y;
         return *this;
      }

      Vector2<T>& operator*=(const Vector2<T> &b)
      {
         x *= b.x;
         y *= b.y;
         return *this;
      }

      Vector2<T>& operator/=(float f)
      {
         x /= f;
         y /= f;
         return *this;
      }

      Vector2<T>& operator*=(float f)
      {
         x *= f;
         y *= f;
         return *this;
      }


		Vector2<T> operator*(float f) const
      {
         Vector2<T> v = *this;
         v.x *= f;
         v.y *= f;
         return v;
      }

      Vector2<T> operator/(float f) const
      {
         Vector2<T> v = *this;
         v.x /= f;
         v.y /= f;
         return v;
      }

   T x;
   T y;
};

typedef Vector2<float> Vector2f;
