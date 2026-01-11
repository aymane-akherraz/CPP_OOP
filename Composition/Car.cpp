#include <iostream>

#define className(x) #x
#define NUMBER_OF_WHEELS 4
#define NUMBER_OF_LIGHTS 10

using namespace std;

class Body
{
	string color;
public:
	Body(const string& color) : color(color) {}
    void print() const;
};

void Body::print() const
{
	cout << className(Body) << ": " << color << endl;
}

class Light
{
	string type;
public:
	Light() {};
	Light(const string& type) : type(type) {}
    void print() const;
};

void Light::print() const
{
	cout << className(Light) << ": " << type << endl;
}

class Chassis
{
	string type;
public:
	Chassis(const string& type) : type(type) {}
    void print() const;
};

void Chassis::print() const
{
	cout << className(Chassis) << ": " << type << endl;
}

class Wheel
{
	string size;
public:
	Wheel() {};
	Wheel(const string& size) : size(size) {}
    void print() const;
};

void Wheel::print() const
{
	cout << className(Wheel) << ": " << size << endl;
}

class Engine
{
	string type;
public:
	Engine(const string& type) : type(type) {}
    void print() const;
};

void Engine::print() const
{
	cout << className(Engine) << ": " << type << endl;
}

class Car
{
private:
	Engine car_engine;
	Wheel car_wheels[NUMBER_OF_WHEELS];
	Chassis car_chassis;
	Light car_lights[NUMBER_OF_LIGHTS];
	Body car_body;
public:
	Car(const Engine& engine, const Chassis& chassis, const Body& body, 
		Wheel wheels[NUMBER_OF_WHEELS], Light lights[NUMBER_OF_LIGHTS]);
	void print() const;
};

Car::Car(const Engine& engine, const Chassis& chassis, const Body& body,
        Wheel wheels[NUMBER_OF_WHEELS], Light lights[NUMBER_OF_LIGHTS])
		: car_engine(engine), car_chassis(chassis), car_body(body)
{
	for (int i = 0; i < NUMBER_OF_WHEELS; i++)
		car_wheels[i] = wheels[i];
	for (int i = 0; i < NUMBER_OF_LIGHTS; i++)
		car_lights[i] = lights[i];
}

void Car::print() const
{
	car_engine.print();
	for (int i = 0; i < NUMBER_OF_WHEELS; i++)
		car_wheels[i].print();
	car_chassis.print();
	for (int i = 0; i < NUMBER_OF_LIGHTS; i++)
		car_lights[i].print();
	car_body.print();
}

int main()
{
	Engine engine("1.0");;
	Chassis chassis("Normal");
	Body body("Black");
	Light lights[]={ Light("Type 1"), Light("Type 1"), 
		Light("Type 2"), Light("Type 2"), 
		Light("Type 3"), Light("Type 3"), 
		Light("Type 4"), Light("Type 4"), 
		Light("Type 5"), Light("Type 5")
	};
	Wheel wheels[] = { Wheel("16inches"), Wheel("16inches"), 
		Wheel("16inches"), Wheel("16inches") };
	Car car(engine, chassis, body, wheels, lights);
	car.print();
	return 0;
}
