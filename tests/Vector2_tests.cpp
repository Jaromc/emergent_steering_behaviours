#include "../Vector2.h"

int main()
{
   Vector2f a(1,2);
   Vector2f b(1,4);

   if (a.x != 1 || a.y != 2)
   {
      return 1;
   }

   if (a+b != Vector2f(2,6))
   {
      return 1;
   }

   if (a-b != Vector2f(0,-2))
   {
      return 1;
   }

   if (a*b != Vector2f(1,8))
   {
      return 1;
   }

   Vector2f a2 = a;
   Vector2f b2 = b;

   a2 += b;

   if (a2 != Vector2f(2,6))
   {
      return 1;
   }

   a2 = a;
   b2 = b;
   a2 -= b;

   if (a2 != Vector2f(0,-2))
   {
      return 1;
   }

   a2 = a;
   b2 = b;
   a2 *= b;

   if (a2 != Vector2f(1,8))
   {
      return 1;
   }

   return 0;
}