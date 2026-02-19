#include <iostream>

using namespace std;

class Base {
public:
    // Конструктор
    Base() {
        cout << "Base constructor" << endl;
    }

    // Обычный деструктор Base
    ~Base() {
        cout << "Base destructor" << endl;
    }

    // Виртуальный метод
    virtual void virtualMethod() {
        cout << "Base::virtualMethod()" << endl;
    }

    // Обычный метод
    void nonVirtualMethod() {
        cout << "Base::nonVirtualMethod()" << endl;
    }
};

class Derived : public Base {
public:
    // Конструктор
    Derived() {
        cout << "Derived constructor" << endl;
    }

    // Деструктор Derived
    ~Derived() {
        cout << "Derived destructor" << endl;
    }

    // Переопределение виртуального метода
    void virtualMethod() override {
        cout << "Derived::virtualMehod()" << endl;
    }

    // Перекрытие обычного метода
    void nonVirtualMethod() {
        cout << "Derived::nonVirtualMethod()" << endl;
    }
};

class Base2 {
public:
    // Base2 конструктор
    Base2() {
        cout << "Base2 constructor" << endl;
    }

    // Виртуальный деструктор Base2
    virtual ~Base2() {
        cout << "virtual Base2 destructor" << endl;
    }
};

class Derived2 : public Base2 {
public:
    // Derived2 конструктор
    Derived2() {
        cout << "Derived2 constructor" << endl;
    }

    // Derived2 деструктор
    ~Derived2() {
        cout << "Derived2 destructor" << endl;
    }
};


int main() {
    cout << "Создание объекта Derived" << endl;
    Derived derived;

    cout << endl << "=== Вызов через указатель на Base ===" << endl << endl;
    Base* baseptr = &derived;
    baseptr->virtualMethod(); // Вызовется виртуальный метод Derived
    baseptr->nonVirtualMethod(); // Вызовется обычный метод Base

    cout << endl << "=== Вызов через указатель на Derived ===" << endl << endl;
    Derived* derivedptr = &derived;
    derivedptr->virtualMethod(); // Вызовется метод Derived
    derivedptr->nonVirtualMethod(); // Вызовется метод Derived

    cout << endl << "=== Демонстрация виртуального деструктора ===" << endl << endl;
    Base2* ptr2 = new Derived2();
    delete ptr2; // Сработают оба деструктора: сначала Derived2, потом Base2

    cout << endl << "=== Демонстрация обычного деструктора ===" << endl << endl;
    Base* ptr = new Derived();
    delete ptr; // Срабатывает только базовый деструктор

    cout << endl << "=== Автоматическое удаление статического объекта в конце программы ===" << endl << endl;
}