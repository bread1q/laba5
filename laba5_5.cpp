#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    // Конструктор по умолчанию
    Base() {
        cout << "Base() конструктор" << endl;
    }
    
    // Конструктор от указателя
    Base(Base* obj) {
        cout << "Base(Base*) конструктор" << endl;
    }
    
    // Конструктор копирования
    Base(Base& obj) {
        cout << "Base(Base&) конструктор копирования" << endl;
    }
    
    virtual ~Base() {
        cout << "~Base() деструктор" << endl;
    }
    
    virtual void classname() {
        cout << "Base" << endl;
    }
};

class Desc : public Base {
public:
    Desc() {
        cout << "Desc() конструктор" << endl;
    }
    
    Desc(Desc* obj) {
        cout << "Desc(Desc*) конструктор" << endl;
    }
    
    Desc(Desc& obj) {
        cout << "Desc(Desc&) конструктор копирования" << endl;
    }
    
    ~Desc() override {
        cout << "~Desc() деструктор" << endl;
    }
    
    void classname() override {
        cout << "Desc" << endl;
    }
    
    void descOnly() {
        cout << "Метод только Desc" << endl;
    }
};

// Функции для передачи параметров
void func1(Base obj) {
    cout << "func1 приняла объект по значению" << endl;
    obj.classname();
    // Нельзя привести obj к Desc - это копия, отрезанная до Base
}

void func2(Base* obj) {
    cout << "func2 приняла указатель" << endl;
    if (obj) {
        obj->classname();
        // Можно попробовать привести
        Desc* d = dynamic_cast<Desc*>(obj);
        if (d) {
            cout << "Это оказался Desc, вызываем descOnly: " << endl;
            d->descOnly();
        }
    }
}

void func3(Base& obj) {
    cout << "func3 приняла ссылку" << endl;
    obj.classname();
    
    Desc* d = dynamic_cast<Desc*>(&obj);
    if (d) {
        cout << "Это оказался Desc, вызываем descOnly: " << endl;
        d->descOnly();
    }
}

int main() {
    cout << endl << "=== Создание объектов ===" << endl << endl;
    Base b;
    Desc d;
    
    cout << endl << "=== Передача Base в функции ===" << endl << endl;
    cout << "-- Вызов func1(b) --" << endl;
    func1(b);
    
    cout << endl << "-- Вызов func2(&b) --" << endl;
    func2(&b);
    
    cout << endl << "-- Вызов func3(b) --" << endl;
    func3(b);

    cout << endl << "=== Передача Desc в функции ===" << endl << endl;
    cout << "-- Вызов func1(d) --" << endl;
    func1(d);
    
    cout << endl << "-- Вызов func2(&d) --" << endl;
    func2(&d);
    
    cout << endl << "-- Вызов func3(d) --" << endl;
    func3(d);

    cout << endl << "=== Создание указателей ===" << endl << endl;
    Base* pb = new Base();
    Desc* pd = new Desc();

    cout << endl << "=== Передача Base в функции ===" << endl << endl;
    cout << "-- Вызов func1(*pb) --" << endl;
    func1(*pb);
    
    cout << endl << "-- Вызов func2(pb) --" << endl;
    func2(pb);
    
    cout << endl << "-- Вызов func3(*pb) --" << endl;
    func3(*pb);

    cout << endl << "=== Передача Desc в функции ===" << endl << endl;
    cout << "-- Вызов func1(*pd) --" << endl;
    func1(*pd);
    
    cout << endl << "-- Вызов func2(pd) --" << endl;
    func2(pd);
    
    cout << endl << "-- Вызов func3(*pd) --" << endl;
    func3(*pd);

    cout << endl << "=== Уничтожение объектов ===" << endl;
}