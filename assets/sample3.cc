#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double vald;
float  valf;
char   valc;
class D myD;

struct mystruct {
   float f;
   double d;
   long l;
   short s;
   int i;
   char c;
};

	/* function prototype */
float total (float,float) ;
float product(float , float  ) ;

	/* class with overloaded methods */
class A {
int a, aa;
int aaa;
	/* add parameters */
   void add(int a, int aa) {
      printf("%d\n", a+ aa);
   }
	// add class variables
   void add() {
      printf("%d\n", a + aa);
   }
};

	// simple function outside of a class
float product(float a, float b) {
   return( a*b );
}


	/* class with no methods */
class B {
long b;
short c;
};

	/* class with no variables */
class C{
   void add(int a, int b) {
      printf("%d\n", a+b);
   }
	// create a class inside the method
   void makeObject() {
      int a, b;
      class B myB1;
         a = 7;
         myB1.b = 3;
         myB1.c = 10;
         printf("output should be 20: %d", a + (int)myB1.b +myB1.c);

		/* call the method inside the class */
         ptintf("output should be 3: ");
         a = 1; b = 2;
         add(a, b);}};

class D
{
int a,b, c;
   void seta(int val ) {
      a = val;
   }
   void setb(int val ){
      b = val;
   }
   void setc (int val) {
      c = val;
   }
   int geta() {
      return(a);
   }
   int getb (){
      return( b);
   }
   int getc () {
      return( c );
   }
   void math() {
   int result;
      result = a + b* c /a;
   }
};

class
E {
   float
      abc = 1.2;

   struct mystruct *  method()
   {
   struct mystruct *ptr;
      int z = 3;
      z++;
      printf("output should be 4 1.200000 : %d %f\n", z, abc);

      ptr = malloc(sizeof(struct mystruct));
      return(ptr);
   };
   void string1(char str[]) {
      printf("output should be abcd: %s\n", str);
   }
   void string2(char *str) {
      printf("output should be efgh: %s\n", str);
   }
};


int main(int argc, char *argv[]) {
class A myA;
class B myB1,myB2, myB3;
class B myC;
int x, y;
char str[50];
struct mystruct *sptr;
char *name;
class E myE;

   printf("Hello \" there\n");
   strcpy(str, "A string containing the word class may be tricky");

   sptr = malloc(sizeof(struct mystruct));

   name = malloc(sizeof(char)*100);

   myA.a = 5;
   myA.a = 10;
   printf("output should be 15: ");
   myA.add();

   x = 4;
   y = 5;
   printf("output should be 9: ");
   myA.add(x, y);

   myB3.b = 10;
   myB3.c = 11;
   printf("output should be 10, 11: %ld %d", myB3.b, myB3.c);
   myC.makeObject() ;

	// comment with a keyword in it class A nota {
   x = 11;
   myD.seta(x);
   printf("output should be 11: %d\n", myD.geta());

   free(sptr);
   sptr = myE.method();
   strcpy(str, "abcd");
   myE.string1(str);
   strcpy(str, "efgh");
   myE.string2(str);
}


float total(float a, float b){
   return(a +b );
}

