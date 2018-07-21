#include <iostream>
using namespace std;
enum class Option {Full, Trial};
class Screen {
public:
    virtual void display() = 0;
};
class OperatingSystem {
public:
    virtual void run() = 0;
};
class Camera {
public:
    virtual void process() = 0;
};
/************************************************************/
class SmartPhone {
public:
    void turnOn() {
        cout << "Smartphone\n";
        if(this->screen) this->screen->display();
        if(this->os) this->os->run();
        if(this->camera) this->camera->process();
    }
    void setScreen(Screen* scr) {
        this->screen = scr;
    }
    void setOperatingSystem(OperatingSystem* os) {
        this->os = os;
    }
    void setCamera(Camera* camera) {
        this->camera = camera;
    }

private:
    Screen* screen = NULL;
    OperatingSystem* os = NULL;
    Camera* camera = NULL;
};

class SmartPhoneBuilder {
public:
    virtual void buildScreen() = 0;
    virtual void buildCamera() = 0;
    virtual void buildOperatingSystem() = 0;
};
/************************************************************/
class OLEDScreen : public Screen {
public:
    void display() {
        cout << "OLED screen\n";
    }
};
class LCDScreen : public Screen {
public:
    void display() {
        cout << "LCD screen\n";
    }
};
/************************************************************/
class iOS : public OperatingSystem {
public:
    void run() {
        cout << "iOS - Apple\n";
    }
};
class Android : public OperatingSystem {
public:
    void run() {
        cout << "Android - Google\n";
    }
};
/************************************************************/
class HQCamera : public Camera {
public:
    void process() {
        cout << "High Quality Camera\n";
    }
};
class LQCamera : public Camera {
public:
    void process() {
        cout << "Low Quality Camera\n";
    }
};
/************************************************************/
class TypeAPhoneBuilder : public SmartPhoneBuilder {
public:
    TypeAPhoneBuilder() {
        this->smartphone = new SmartPhone;
    }
    void buildOperatingSystem() {
        OperatingSystem* os = new iOS;
        this->smartphone->setOperatingSystem(os);
    }
    void buildCamera() {
        Camera* camera = new HQCamera;
        this->smartphone->setCamera(camera);
    }
    void buildScreen() {
        Screen* screen = new OLEDScreen;
        this->smartphone->setScreen(screen);
    }
    SmartPhone* getSmartphone() {
        return this->smartphone;
    }
private:
    SmartPhone* smartphone;

};
class TypeBPhoneBuilder : public SmartPhoneBuilder {
public:
    TypeBPhoneBuilder() {
        this->smartphone = new SmartPhone;
    }
    void buildOperatingSystem() {
        OperatingSystem* os = new Android;
        this->smartphone->setOperatingSystem(os);
    }
    void buildCamera() {
        Camera* camera = new HQCamera;
        this->smartphone->setCamera(camera);
    }
    void buildScreen() {
        Screen* screen = new LCDScreen;
        this->smartphone->setScreen(screen);
    }
    SmartPhone* getSmartphone() {
        return this->smartphone;
    }
private:
    SmartPhone* smartphone;
};
class TypeCPhoneBuilder : public SmartPhoneBuilder {
public:
    TypeCPhoneBuilder() {
        this->smartphone = new SmartPhone;
    }
    void buildOperatingSystem() {
        OperatingSystem* os = new Android;
        this->smartphone->setOperatingSystem(os);
    }
    void buildCamera() {
        Camera* camera = new LQCamera;
        this->smartphone->setCamera(camera);
    }
    void buildScreen() {
        Screen* screen = new LCDScreen;
        this->smartphone->setScreen(screen);
    }
    SmartPhone* getSmartphone() {
        return this->smartphone;
    }
private:
    SmartPhone* smartphone;
};
/************************************************************/
class Director {
public:
    Director() {}
    Director(SmartPhoneBuilder* builder) {
        this->builder = builder;
    }
    void setBuilder(SmartPhoneBuilder* b) {
        this->builder = b;
    }

    void CreatePhone(Option option) {
        if(option == Option::Full) {
            this->builder->buildOperatingSystem();
            this->builder->buildCamera();
            this->builder->buildScreen();
        }else if(option == Option::Trial) {
            this->builder->buildOperatingSystem();
            this->builder->buildScreen();
        }
    }
private:
    SmartPhoneBuilder* builder;
};
int main() {
    TypeAPhoneBuilder Abuilder;
    TypeBPhoneBuilder Bbuilder;
    Director director;
    director.setBuilder(&Abuilder);
    director.CreatePhone(Option::Trial);
    Abuilder.getSmartphone()->turnOn();
}
