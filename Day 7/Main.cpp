#include <bits/stdc++.h>
using namespace std;
enum Sensors
{
	TempSensor = 0,
	LDRsensor,
	MotionSensor,

};
class Automation
{
public:
	Sensors sensor;
	char operation;
	int sensorValue;
	Automation(Sensors x, char y, int z)
	{
		sensor = x;
		operation = y;
		sensorValue = z;
	}
};
void doAutomations(vector<Automation> ToDo);

string deviceNames[] = {"Fan", "Light", "Door"};
string sensorNames[] = {"Temperature sensor", "LDR sensor", "Motion Sensor"};
int sensorThreshold[] = {25, 200, 3};

class Sensor
{
public:
	string name;
	bool isConnected;

	Sensor(string name, bool isConnected)
	{
		this->name = name;
		this->isConnected = isConnected;
	}
	void connectSensor()
	{
		isConnected = true;
	}
	void disconnectSensor()
	{
		isConnected = false;
	}
};
class Device
{
};

class TempSensor : public Sensor
{
public:
	int temperature;
	int threshold;
	std::function<void(int)> action;

	TempSensor(int temperature) : Sensor("Temperature Sensor", true)
	{
		this->temperature = temperature;
	}
	int getTemperature()
	{
		return temperature;
	}

	void Listener(int threshold, const std::function<void(int)> &action)
	{
		this->action = action;
		this->threshold = threshold;
	}
	void increaseTemp(int x)
	{
		temperature = x;
		action(temperature);
	}
};

class LDRsensor : public Sensor
{
public:
	int lightIntensity;
	int threshold;
	std::function<void(int)> action;

	LDRsensor(int lightIntensity) : Sensor("LDR Sensor", true)
	{
		this->lightIntensity = lightIntensity;
	}
	int getLightIntensity()
	{
		return lightIntensity;
	}
	void Listener(int threshold, const std::function<void(int)> &action)
	{
		this->action = action;
		this->threshold = threshold;
	}
	void increaseIntensity(int x)
	{
		lightIntensity = x;
		action(lightIntensity);
	}
};

class Fan : public TempSensor, Device
{
	bool status = false;

public:
	Fan(bool status, float temperature)
		: TempSensor(temperature)
	{
		this->status = status;
	}
	void setStatus(bool x)
	{
		this->status = x;
	}
	void fanStatus()
	{
		if (status)
			cout << "The fan is ON." << endl;
		else
			cout << "The fan is OFF" << endl;
	}
};

class Light : public LDRsensor, Device
{
public:
	bool status;
	Light(bool status, int lightIntensity)
		: LDRsensor(lightIntensity)
	{
		this->status = status;
	}
	void setStatus(bool x)
	{
		this->status = x;
	}
	void lightStatus()
	{
		if (status)
			cout << "The light is ON." << endl;
		else
			cout << "The light is OFF" << endl;
	}
};

class MotionSensor
{
public:
	int distance;
	int threshold;
	std::function<void(int)> action;
	MotionSensor(int distance)
	{
		this->distance = distance;
	}
	int getDistance()
	{
		return distance;
	}
	void Listener(int threshold, const std::function<void(int)> &action)
	{
		this->action = action;
		this->threshold = threshold;
	}
	void changeDistance(int dis)
	{
		this->distance = dis;
		action(distance);
	}
};

class Door : public MotionSensor, Device
{
public:
	bool status;
	Door(bool status, int distance)
		: MotionSensor(distance)
	{
		this->status = status;
	}
	void setStatus(bool x)
	{
		this->status = x;
	}
	void doorStatus()
	{
		if (status)
			cout << "The door is OPEN." << endl;
		else
			cout << "The door is CLOSED" << endl;
	}
};

class ClientApplication
{
public:
	void doAutomations(vector<Automation> ToDo)
	{
		bool status[ToDo.size()];
		for (int i = 0; i < ToDo.size(); i++)
		{
			Automation a = ToDo[i];
			int threshold = sensorThreshold[a.sensor];
			if (a.operation == '<')
			{
				status[i] = a.sensorValue < threshold;
			}
			if (a.operation == '>')
			{
				status[i] = a.sensorValue > threshold;
			}
			if (a.operation == '=')
			{
				status[i] = a.sensorValue == threshold;
			}
		}
		for (int i = 0; i < ToDo.size(); i++)
		{
			if (status[i])
			{
				cout << deviceNames[ToDo[i].sensor] << " : OFF" << endl;
			}
			else
			{
				cout << deviceNames[ToDo[i].sensor] << " : ON" << endl;
			}
		}
	}
};

int main()
{
	// For Fan(status,temperature):
	Fan f1(false, 20);
	f1.fanStatus();
	int fanThreshold = 25;
	f1.Listener(fanThreshold, [fanThreshold, &f1](int temperature)
				{
		if(temperature>=fanThreshold){
			f1.setStatus(true);
		} });
	f1.increaseTemp(26);
	f1.fanStatus();

	// For Light
	Light l1(false, 200);
	l1.lightStatus();
	int lightThreshold = 250;
	l1.Listener(lightThreshold, [&](int intensity)
				{
		if(intensity>=lightThreshold){
			l1.setStatus(true);
		} });
	l1.increaseIntensity(251);
	l1.lightStatus();

	// For Door
	Door d1(false, 10);
	d1.doorStatus();
	int doorThreshold = 3;
	d1.Listener(doorThreshold, [doorThreshold, &d1](int distance)
				{
		if (distance <= doorThreshold)
		{
			d1.setStatus(true);
} });
	d1.changeDistance(3);
	d1.doorStatus();

	// Automation

	cout << "\n"
		 << "Doing automations!"
		 << endl;
	vector<Automation> Vect;
	Automation a1(TempSensor, '<', 20);
	Automation a2(LDRsensor, '<', 251);
	Automation a3(MotionSensor, '=', 4);
	Vect.push_back(a1);
	Vect.push_back(a2);
	Vect.push_back(a3);
	ClientApplication client = ClientApplication();
	client.doAutomations(Vect);
	return 0;
}