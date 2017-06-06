/*You have to construct a car. Step by Step. Kata by Kata.
First you have to implement the engine and the fuel tank.

The default fuel level of a car is 20 liters.
The maximum size of the tank is 60 liters.
Of course every car's life begins with an engine not running. ;-)

Every call of a method from the car correlates to 1 second.

The fuel consumption in running idle is 0.0003 liter/second.
For convenience the start of the engine consumes nothing and we don't care, if the engine is warm or cold.

The fuel tank is on reserve, if the level is under 5 liters.
The fuel tank display shows the level as rounded for 2 decimal places.
Internally an accuracy up to 10 decimal places should be more than enough.
In difference to most real cars, the fuel tank display is always showing its information, also when the the engine is not running.

And consider the locigal things about fuel and engine... ;-)

In all tests only the whole car will be tested. Feel free to write your own tests for the other classes. 

Under the text you will find the code of the interfaces. 

Have fun coding it and please don't forget to vote and rank this kata! :-) 


This kata is part of a series of katas for constructing a car:

Constructing a car #1 - Engine and Fuel Tank
Constructing a car #2 - Driving
Constructing a car #3 - On-Board Computer

The next parts will be coming soon... */

class ICar{
public:
    virtual void EngineStart() = 0;
    virtual void EngineStop() = 0;
    virtual void Refuel(double liters) = 0;
    virtual void RunningIdle() = 0;
protected:
    bool engineIsRunning = false;
};

class IEngine{
public:
    virtual void Consume(double liters) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
protected:
    bool isRunning = false;
};

class IFuelTank{
public:
    virtual void Consume(double liters) = 0;
    virtual void Refuel(double liters) = 0;
protected:
    double fillLevel = 0.0;
    bool isOnReserve = false;
    bool isComplete = false;
};


class IFuelTankDisplay{
protected:
    double fillLevel = 0.0;
    bool isOnReserve = false;
    bool isComplete = false;
};

// start of unique code
#include <memory>
#include <cmath>
class Car; class Engine; class FuelTank; class FuelTankDisplay;
class Engine : public IEngine{	
public:
	Engine(FuelTank* _fuelTank): fuelTank(_fuelTank){}
    void Consume(double liters) override;
    void Start() override;
    void Stop() override;
    bool getIsRunning()const {return isRunning;}
private:	
	FuelTank* fuelTank;
};

class FuelTank : public IFuelTank{
friend class FuelTankDisplay;
friend class Engine;
public:
	FuelTank(Car* _car): car(_car){}
    void Consume(double liters) override;
    void Refuel(double liters) override;  
private:
	constexpr static double capacity = 60.0; 
	Car* car; 
};

class FuelTankDisplay : public IFuelTankDisplay{
public:
	FuelTankDisplay(FuelTank* _fuelTank): fuelTank(_fuelTank){}
	double getFillLevel() const{ return std::round(100*fuelTank->fillLevel)/100;}
	double getIsOnReserve() const{ return fuelTank->isOnReserve;}
	double getIsComplete() const{ return fuelTank->isComplete;}
private:
	FuelTank* fuelTank;
};

class Car : public ICar{
	friend class Engine;
	friend class FuelTank;
	friend class FuelTankDisplay;
public:
	Car(double liters = 20);
	void EngineStart() override;
    void EngineStop() override;
    void Refuel(double liters) override;
    void RunningIdle() override;   
    bool getEngineIsRunning() const;
    std::shared_ptr<FuelTankDisplay> fuelTankDisplay;
private:
	std::shared_ptr<Engine> engine;
	std::shared_ptr<FuelTank> fuelTank;
	constexpr static double idleRate = 0.0003;

};
void Engine::Consume(double liters){fuelTank->Consume(liters);}
void Engine::Start(){
	if (fuelTank->fillLevel)
		isRunning = true;
}
void Engine::Stop(){ isRunning = false;}
void FuelTank::Consume(double liters){
	if (liters <= 0) return;
	isComplete = false;
	if (fillLevel <= liters){ 
		fillLevel = 0.0;
		if (car->getEngineIsRunning()) 
			car->EngineStop();
	}
	else fillLevel = std::round(100000*(fillLevel-liters))/100000;
	if (fillLevel <= 5.0) isOnReserve = true;
}
void FuelTank::Refuel(double liters){
	if (liters < 0) return;
	if (fillLevel + liters >= capacity){
		fillLevel = capacity;
		isComplete = true;
	}
	else fillLevel = std::round(100000*(fillLevel+liters))/100000;
	if (fillLevel <= 5) isOnReserve = true;
}
Car::Car(double liters){
	fuelTank = std::make_shared<FuelTank>(this);
	fuelTankDisplay = std::make_shared<FuelTankDisplay>(fuelTank.get());
	engine = std::make_shared<Engine>(fuelTank.get());
	Refuel(liters);
}
void Car::EngineStart(){
	engine->Start();
	engineIsRunning = engine->getIsRunning();
}
void Car::EngineStop(){
	engine->Stop();
	engineIsRunning = false;
}
void Car::Refuel(double liters){fuelTank->Refuel(liters);}
void Car::RunningIdle(){
	if (engineIsRunning) 
		engine->Consume(idleRate);
}
bool Car::getEngineIsRunning() const {return engineIsRunning;}

#include <iostream>
int main(){
	Car car(60);    
}
