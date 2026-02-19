#include <iostream>

using namespace std;

class Base {
public:
    // обычный метод
    void method() {
        cout << "Base::method()" << endl;
    }
};

class Derived : public Base {
public:
    // перекрываемый метод
    void method() {
        cout << "Derived::method()" << endl;
    }
};

int main() {
    cout << endl << "=== Демонстрация перекрываемого и наследуемого методов ===" << endl << endl;
    Base* baseptr = new Derived();
    Derived* derivedptr = new Derived();

    cout << "Вызов через указатель на Base: " << endl;
    baseptr->method(); // Вызовется Base::method() - наследуемый метод

    cout << "Вызов через указатель на Derived: " << endl;
    derivedptr->method(); // Вызовется Derived::method() - перекрытый метод
}