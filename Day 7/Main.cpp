#include <bits/stdc++.h>
using namespace std;
enum Sensors
{
	TemperatureSensor = 0,
	LDRSensor,
	IRSensor,

};
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
		if (!status)
			cout << "The door is CLOSED" << endl;
		if (status)
			cout << "The door is OPEN." << endl;
	}
};

class ClientApplication
{
public:
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
					cout << deviceNames[sen[i].name] << " : CLOSED" << endl;
				else if (deviceNames[sen[i].name] == "Light")
					cout << deviceNames[sen[i].name] << " : OFF" << endl;
				else
					cout << deviceNames[sen[i].name] << " : ON" << endl;
			}
			else
			{
				if (deviceNames[sen[i].name] == "Door")
					cout << deviceNames[sen[i].name] << " : OPEN" << endl;
				else if (deviceNames[sen[i].name] == "Light")
					cout << deviceNames[sen[i].name] << " : ON" << endl;
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
	ClientApplication client = ClientApplication();
	TempSensor tempsen1(0);
	LDRsensor ldr(INT_MAX);
	MotionSensor irsen(INT_MAX);
	Fan f1(false, 0);
	Light l1(false, INT_MAX);
	Door d1(false, INT_MAX);

	vector<Sensor> sensorsAvailable;
	sensorsAvailable.push_back(tempsen1);
	sensorsAvailable.push_back(ldr);
	sensorsAvailable.push_back(irsen);

	client.connectDevices(sensorsAvailable);
	client.report(sensorsAvailable);
	cout << "\n"
		 << endl;

	// Setting Thresholds:
	int fanThreshold = 25;
	f1.Listener(fanThreshold, [fanThreshold, &f1](int temperature)
				{
			if(temperature>=fanThreshold){
					sensorThreshold[0]=fanThreshold;
					f1.setStatus(true);
			} });
	int lightThreshold = 200;
	l1.Listener(lightThreshold, [&](int intensity)
				{
			if(intensity<=lightThreshold){
				sensorThreshold[1] = lightThreshold;
				l1.setStatus(true);
			} });
	int doorThreshold = 3;
	d1.Listener(doorThreshold, [doorThreshold, &d1](int distance)
				{
			if (distance <= doorThreshold)
			{
				sensorThreshold[2] = doorThreshold;
				d1.setStatus(true);
	} });

	// Interface
	while (1)
	{
		int input;
		cout << "1. Increase Value" << endl;
		cout << "2. Decrease Value" << endl;
		cout << "3. Connect Device" << endl;
		cout << "4. Disconnect Device" << endl;
		cout << "5. Change Settings" << endl;
		cin >> input;
		if (input == 1 || input == 2)
		{
			cout << "Please Select the sensor" << endl;
			int input2;
			cout << "1.Temperature Sensor" << endl;
			cout << "2.LDR Sensor" << endl;
			cout << "3.Motion Sensor" << endl;
			cin >> input2;
			cout << "Please Enter the value" << endl;
			int val;
			cin >> val;
			if (input2 == 1)
			{
				f1.increaseTemp(val);
				f1.fanStatus();
			}
			else if (input2 == 2)
			{
				l1.increaseIntensity(val);
				l1.lightStatus();
			}
			else if (input2 == 3)
			{
				d1.changeDistance(val);
				d1.doorStatus();
			}
			else
			{
				cout << "Invalid input" << endl;
			}
		}
		else if (input == 3)
		{
			client.connectDevices(sensorsAvailable);
		}
		else if (input == 4)
		{
			client.disconnectDevices(sensorsAvailable);
		}
		else if (input == 5)
		{
			cout << "Please Select the sensor" << endl;
			int input2;
			cout << "1.Temperature Sensor" << endl;
			cout << "2.LDR Sensor" << endl;
			cout << "3.Motion Sensor" << endl;
			cin >> input2;
			cout << "Please Enter the new threshold value" << endl;
			int val;
			cin >> val;
			if (input2 == 1)
			{
				f1.Listener(val, [&](int temperature)
							{
			if(temperature>=val){
				sensorThreshold[0] = val;
				f1.setStatus(true);
			} });
			}
			else if (input2 == 2)
			{
				l1.Listener(val, [&](int intensity)
							{
			if(intensity<=val){
				sensorThreshold[1] = val;
				l1.setStatus(true);
			} });
			}
			else if (input2 == 3)
			{
				d1.Listener(val, [&](int distance)
							{
			if (distance <= val)
			{
				sensorThreshold[2] = val;
				d1.setStatus(true);
	} });
			}
			else
			{
				cout << "Invalid input" << endl;
			}
		}
		else
		{
			cout << "Invalid Input" << endl;
		}
	}

	return 0;
}