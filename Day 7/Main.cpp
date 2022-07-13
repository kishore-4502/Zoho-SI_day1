#include <bits/stdc++.h>
using namespace std;
enum Sensors
{
	TemperatureSensor = 0,
	LDRSensor,
	IRSensor,

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
	int value;
	Sensors name;
	bool isConnected;

	Sensor(Sensors name, bool isConnected, int value)
	{
		this->name = name;
		this->isConnected = isConnected;
		this->value = value;
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

class TempSensor : public Sensor
{
public:
	int threshold;
	std::function<void(int)> action;

	TempSensor(int temperature) : Sensor(TemperatureSensor, false, temperature)
	{
	}
	int getTemperature()
	{
		return value;
	}

	void Listener(int threshold, const std::function<void(int)> &action)
	{
		this->action = action;
		this->threshold = threshold;
	}
	void increaseTemp(int x)
	{
		value = x;
		action(value);
	}
};

class LDRsensor : public Sensor
{
public:
	int threshold;
	std::function<void(int)> action;

	LDRsensor(int lightIntensity) : Sensor(LDRSensor, false, lightIntensity)
	{
	}
	int getLightIntensity()
	{
		return value;
	}
	void Listener(int threshold, const std::function<void(int)> &action)
	{
		this->action = action;
		this->threshold = threshold;
	}
	void increaseIntensity(int x)
	{
		value = x;
		action(value);
	}
};

class Fan : public TempSensor
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

class Light : public LDRsensor
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

class MotionSensor : public Sensor
{
public:
	int threshold;
	std::function<void(int)> action;
	MotionSensor(int distance)
		: Sensor(IRSensor, false, distance)
	{
	}
	int getDistance()
	{
		return value;
	}
	void Listener(int threshold, const std::function<void(int)> &action)
	{
		this->action = action;
		this->threshold = threshold;
	}
	void changeDistance(int dis)
	{
		this->value = dis;
		action(value);
	}
};

class Door : public MotionSensor
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
				if (deviceNames[ToDo[i].sensor] == "Door")
				{
					cout << deviceNames[ToDo[i].sensor] << " : OPEN" << endl;
				}
				else
					cout << deviceNames[ToDo[i].sensor] << " : OFF" << endl;
			}
			else
			{
				if (deviceNames[ToDo[i].sensor] == "Door")
					cout << deviceNames[ToDo[i].sensor] << " : CLOSED" << endl;
				else
					cout << deviceNames[ToDo[i].sensor] << " : ON" << endl;
			}
		}
	}
	void report(vector<Sensor> sen)
	{
		bool status[sen.size()];
		for (int i = 0; i < sen.size(); i++)
		{
			status[i] = sen[i].value > sensorThreshold[sen[i].name];
		}
		for (int i = 0; i < sen.size(); i++)
		{
			if (status[i])
			{
				if (deviceNames[sen[i].name] == "Door")
				{
					cout << deviceNames[sen[i].name] << " : CLOSED" << endl;
				}
				else
					cout << deviceNames[sen[i].name] << " : ON" << endl;
			}
			else
			{
				if (deviceNames[sen[i].name] == "Door")
					cout << deviceNames[sen[i].name] << " : OPEN" << endl;
				else
					cout << deviceNames[sen[i].name] << " : OFF" << endl;
			}
		}
	}
	void connectDevices(vector<Sensor> sen)
	{
		for (int i = 0; i < sen.size(); i++)
		{
			sen[i].connectSensor();
		}
		cout << "All sensors are connected to the devices through Client Application" << endl;
	}
	void disconnectDevices(vector<Sensor> sen)
	{
		for (int i = 0; i < sen.size(); i++)
		{
			sen[i].disconnectSensor();
		}
		cout << "\nDisconnected" << endl;
	}
};

int main()
{
	cout << "\n"
		 << endl;
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
		 << endl;
	vector<Automation> Vect;
	Automation a1(TemperatureSensor, '<', 20);
	Automation a2(LDRSensor, '<', 251);
	Automation a3(IRSensor, '=', 3);
	Vect.push_back(a1);
	Vect.push_back(a2);
	Vect.push_back(a3);
	ClientApplication client = ClientApplication();
	vector<Sensor> sensorsAvailable;
	TempSensor tempsen1(26);
	LDRsensor ldr(249);
	MotionSensor irsen(2);
	sensorsAvailable.push_back(tempsen1);
	sensorsAvailable.push_back(ldr);
	sensorsAvailable.push_back(irsen);
	// Connect Sensors
	client.connectDevices(sensorsAvailable);
	client.doAutomations(Vect);

	// Report status
	cout << "\n"
		 << "Status:" << endl;

	client.report(sensorsAvailable);
	return 0;
}