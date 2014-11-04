// -*- C++ -*-
/*!
 * @file  sensor.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "sensor.h"
#include <iostream>
#include <fstream>

using namespace std;

// Module specification
// <rtc-template block="module_spec">
static const char* sensor_spec[] =
  {
    "implementation_id", "sensor",
    "type_name",         "sensor",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

int receive(char *adcval);
int Datacheck(char *dt);

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
sensor::sensor(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_soundOut("sound", m_sound),
    m_infraredOut("infrared", m_infrared)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
sensor::~sensor()
{
}



RTC::ReturnCode_t sensor::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("sound", m_soundOut);
  addOutPort("infrared", m_infraredOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sensor::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t sensor::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sensor::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t sensor::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sensor::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sensor::onExecute(RTC::UniqueId ec_id)
{
	int id;
	ifstream ifs;

	/*風検知用ADC*/
	ifs.open("/sys/class/hwmon/hwmon0/device/in2_input",ifstream::in);
	char adcval[256];
	if(ifs.fail())
	{
		cout << "失敗" << endl;
	}
	while(ifs.getline(adcval,256))
	{
		m_sound.data = (long)adcval;
		m_soundOut.write();
	}


	/*赤外線用ADC*/
	ifs.open("/sys/class/hwmon/hwmon0/device/in3_input",ifstream::in);
	char adcval0[256];
	if(ifs.fail())
	{
		cout << "失敗" << endl;
	}
	ifs.getline(adcval0,256);
	id = receive(adcval0);
	m_infrared.data = (long)id;
	m_infraredOut.write();

	ifs.open("/sys/class/hwmon/hwmon0/device/in4_input",ifstream::in);
	char adcval1[256];
	if(ifs.fail())
	{
		cout << "失敗" << endl;
	}
	ifs.getline(adcval1,256);
	id = receive(adcval1);
	m_infrared.data = (long)id;
	m_infraredOut.write();


	ifs.open("/sys/class/hwmon/hwmon0/device/in5_input",ifstream::in);
	char adcval2[256];
	if(ifs.fail())
	{
		cout << "失敗" << endl;
	}
	ifs.getline(adcval2,256);
	id = receive(adcval2);
	m_infrared.data = (long)id;
	m_infraredOut.write();


	ifs.open("/sys/class/hwmon/hwmon0/device/in6_input",ifstream::in);
	char adcval3[256];
	if(ifs.fail())
	{
		cout << "失敗" << endl;
	}
	ifs.getline(adcval3,256);
	id = receive(adcval3);
	m_infrared.data = (long)id;
	m_infraredOut.write();

	ifs.close();

  return RTC::RTC_OK;
}

int Datacheck(char *dt)
{
	int a,b,i;
	a = 0;
	//キーデータ1のチェック
	a = 0;
	for(i = 0; i < 8; i++)
	{
		if(*dt++ == 0x31)
		{
			a = a | (1 << i);
		}
	}
	//キーデータ2のチェック(反転データ)
	b = 0;
	for(i = 0; i < 8; i++)
	{
		if(*dt++ == 0x30)
		{
			b = b | (1 << i);
		}
	}

	if(a != b)
	{
		return 0;
	}

	return a;
}

int receive(char *adcval)
{
	char irbit[16];
	unsigned long t;
	int ans;
	int i;


	ans = 0;
	t = 0;

	if(*adcval <= 12500)
	{
		t = 0;
		while (*adcval <= 12500) {
			sleep(1000);
			t++;
		}
	}
	if(t>3000){
		i = 0;
		while(*adcval > 12500);
		while(1)
		{
			while(*adcval <= 12500);
			t = 0;
			while(*adcval > 12500)
			{
				sleep(1000);
				t++;
			}
			if(t >= 50)
			{
				irbit[i] = (char)0x31; //ON
			}
			else
			{
				irbit[i] = (char)0x30; //OFF
			}
			i++;
			if(i == 16) break;
		}
		if(i == 16)
		{
			ans == Datacheck(irbit);
		}
	}
	return (ans);
}

/*
RTC::ReturnCode_t sensor::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sensor::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sensor::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sensor::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sensor::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void sensorInit(RTC::Manager* manager)
  {
    coil::Properties profile(sensor_spec);
    manager->registerFactory(profile,
                             RTC::Create<sensor>,
                             RTC::Delete<sensor>);
  }
  
};


