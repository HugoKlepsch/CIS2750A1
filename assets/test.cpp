class A {
    int a;
    int fn() {

    }
}

class B {
    int b;
    class A aObj;
    int fn() {
        class A myClass;
        myClass.a=7;
        myClass.fn();
        aObj.fn();
    }
}

int main() {
    class B newClass;
    newClass.b = 3;
    newClass.fn();
}
