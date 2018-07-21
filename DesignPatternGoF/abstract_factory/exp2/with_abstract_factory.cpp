#include <iostream>
#define LINUX

using namespace std;

class Widget{
public:
        virtual void draw()  = 0;
};

class LinuxButton : public Widget{
public:
    void draw() {cout << "LinuxButton\n";}
};
class LinuxMenu : public Widget {
public:
    void draw() {cout << "LinuxMenu\n";}
};
/*************************************/
class WindowButton : public Widget {
public:
    void draw() {cout << "WindowButton\n";}
};
class WindowMenu : public Widget {
public:
    void draw() {cout << "WindowMenu\n";}
};

class Factory {
public:
    virtual Widget* createButton() = 0;
    virtual Widget* createMenu() = 0;
};

class LinuxFactory : public Factory {
public:
    Widget* createButton() {
        return new LinuxButton;
    }
    Widget* createMenu() {
        return new LinuxMenu;
    }
};

class WindowFactory : public Factory {
public:
    Widget* createButton() {
        return new WindowButton;
    }
    Widget* createMenu() {
        return new WindowMenu;
    }
};

class Client {
private:
    Factory* factory;
public:
    Client(Factory* f) {
        factory = f;
    }
    void draw() {
        Widget* w = factory->createButton();
        w->draw();
        displayWindowOne();
        displayWindowTwo();
    }
    void displayWindowOne() {
        Widget* w[] =  {
            factory->createButton(), factory->createMenu()
        };
        w[0]->draw();
        w[1]->draw();
    }
    void displayWindowTwo() {
        Widget* w[] =  {
            factory->createMenu(), factory->createButton()
        };
        w[0]->draw();
        w[1]->draw();
    }
};

int main() {
    Factory* factory;
#ifdef LINUX
    factory = new LinuxFactory;
#else
    factory = new WindowFactory;
#endif
    Client* c = new Client(factory);
    c->draw();
}

