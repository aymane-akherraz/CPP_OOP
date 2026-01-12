#include <iostream>
#include <sstream>

using namespace std;

class FarmAnimal {
public:
	FarmAnimal(double weight);
	virtual double getWaterConsumption() = 0;
protected:
	double weight;
	double water_consumption;
};

FarmAnimal::FarmAnimal(double weight)
{
	this->weight = weight;
}

class Cow : public FarmAnimal
{
public:
	Cow(double weight);
	double getWaterConsumption() override;
};

class Sheep : public FarmAnimal
{
public:
	Sheep(double weight);
	double getWaterConsumption() override;
};

class Horse : public FarmAnimal
{
public:
	Horse(double weight);
	double getWaterConsumption() override;
};

Cow::Cow(double weight) : FarmAnimal(weight) {}

Sheep::Sheep(double weight) : FarmAnimal(weight) {}

Horse::Horse(double weight) : FarmAnimal(weight) {}

double Cow::getWaterConsumption()
{
	return ((weight / 100) * 8.6);
}

double Sheep::getWaterConsumption()
{
    return ((weight / 10) * 1.1);
}

double Horse::getWaterConsumption()
{
    return ((weight / 100) * 6.8);
}

class ConsumptionAccumulator
{
public:
	ConsumptionAccumulator();
	double getTotalConsumption();
	void addConsumption(FarmAnimal &animal);
private:
	double total_consumption;
};

ConsumptionAccumulator::ConsumptionAccumulator() :
  total_consumption(0)
{
}

double ConsumptionAccumulator::getTotalConsumption()
{
  return total_consumption;
}

void ConsumptionAccumulator::addConsumption(FarmAnimal &animal)
{
  total_consumption += animal.getWaterConsumption();
}

int show_usage()
{
	cout << "Input format: [animal] [weight]" << endl;
	return 0;
}

int main()
{
	double weight;
	string line, animal;
	stringstream iss;
	ConsumptionAccumulator accumulator;

	getline(cin, line);
	while (!line.empty())
	{
		iss.str(line);
		iss >> animal;
		if (!iss.fail())
		{
			iss >> weight;
			if (iss.fail())
				return show_usage();
			iss >> ws;
			if (!iss.eof())
				return show_usage();
			iss.clear();
		}
		else
			return show_usage();
		if (animal.compare("sheep") == 0)
		{
			Sheep animal = Sheep(weight);
			accumulator.addConsumption(animal);
		}
		else if (animal.compare("cow") == 0)
		{
			Cow animal = Cow(weight);
            accumulator.addConsumption(animal);
		}
		else if (animal.compare("horse") == 0)
        {
			Horse animal = Horse(weight);
            accumulator.addConsumption(animal);
        }
		getline(cin, line);
	}
	cout << "Total consumption: " << accumulator.getTotalConsumption() << endl;
	return 0;
}
