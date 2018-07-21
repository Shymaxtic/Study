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

class Client {
public:
    void draw() {
#ifdef LINUX
        Widget* w =  new LinuxButton;
#else
        Widget* w = new WindowButton;
#endif
        w->draw();
        displayWindowOne();
        displayWindowTwo();
    }
    void displayWindowOne() {
#ifdef LINUX
        Widget* w[] = {new LinuxButton, new LinuxMenu};
#else
        Widget* w[] = {new WindowButton, new WindowMenu};
#endif
        w[0]->draw();
        w[1]->draw();
    }
    void displayWindowTwo() {
#ifdef LINUX
        Widget* w[] = {new LinuxMenu, new LinuxButton};
#else
        Widget* w[] = {new LinuxMenu, new LinuxButton};
#endif
        w[0]->draw();
        w[1]->draw();
    }
};

int main() {
    Client* c = new Client;
    c->draw();
}
