#include<stdio.h>
#include<stdlib.h>
#include<string.h>


class A {
int a;
   int  sum(int x, int y, int z) {
      return(x+ y +z);
   }
};

class B {
   float a, b, c;
   void seta(float value) {
      a = value;
   }
   void setb(float value) {
      b = value;
   }
   void setc(float value) {
      c = value;
   }
   float geta() {
      return(a);
   }
   float getb() {
      return(b);
   }
   float getc() {
      return(c);
   }
};



int main(int argc, char *argv[]) {
class A myA;
int total;
int a, b, c;
class B myB;
float val;

   a = 1;
   b = 2;
   c = 3;

   total = myA.sum(a, b, c);
   printf("output shoudl be 6: %d\n", total);

   val =1.5;
   myB.seta(val);
   printf("output should be 1.50000: %f\n", myB.geta());

}

