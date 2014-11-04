// -*- C++ -*-
/*!
 * @file  getinfo.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "getinfo.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

FILE *fp;

using namespace std;

// Module specification
// <rtc-template block="module_spec">
static const char* getinfo_spec[] =
  {
    "implementation_id", "getinfo",
    "type_name",         "getinfo",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.id", "0",
    // Widget
    "conf.__widget__.id", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
getinfo::getinfo(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_soundIn("sound", m_sound),
    m_infraredIn("infrared", m_infrared),
    m_networkIn("network", m_network),
    m_otherdataIn("otherdata", m_otherdata),
    m_mydataOut("mydata", m_mydata),
    m_ledOut("led", m_led)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
getinfo::~getinfo()
{
}



RTC::ReturnCode_t getinfo::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("sound", m_soundIn);
  addInPort("infrared", m_infraredIn);
  addInPort("network", m_networkIn);
  addInPort("otherdata", m_otherdataIn);
  
  // Set OutPort buffer
  addOutPort("mydata", m_mydataOut);
  addOutPort("led", m_ledOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("id", m_id, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t getinfo::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t getinfo::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t getinfo::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t getinfo::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t getinfo::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t getinfo::onExecute(RTC::UniqueId ec_id)
{

	int snd_data;
	int inf_data;
	int ntk_data;
	int otr_data;
	int data;
	int sleep;

		/*調光LED用PWM*/
		if(m_soundIn.isNew())
		{
			m_soundIn.read();
			snd_data = m_sound.data;
			/*センサーデータより、調光変化を行う*/
			if(1500 < snd_data || snd_data < 2000)
			{
				sleep = 1000;
			}
			else if(2000 < snd_data || snd_data < 2500)
			{
				sleep = 5000;
			}
			m_led.data = sleep;
			m_ledOut.write();

		}

		/*まわりのキャンドルの情報を取得し、LEDのsleepを変化させる*/
		if(m_otherdataIn.isNew())
		{
			m_otherdataIn.read();
			otr_data = m_otherdata.data;

			sleep = otr_data ;

			m_led.data = sleep;
			m_ledOut.write();

		}

		/*センサ情報又は無線情報からつなぎの変更*/
		/*m_id = 0のときセンサ情報を基にポート間の繋がりを変更する*/
		if(m_id == 0)
		{
			if(m_infraredIn.isNew())
			{
				m_infraredIn.read();
				inf_data = m_infrared.data;
				if(inf_data == 1)
				{
					string com = "~/workspace/ledcon/shells";
					string comInit = "_1";
					com += "test01";
					com	+= comInit;
					int txt;
					txt = system(com.c_str());
					/*pwmデータの送信*/
					m_mydata.data = sleep;
					m_mydataOut.write();

				}
				else if(inf_data == 2)
				{
					string com = "~/workspace/ledcon/shells";
					string comInit = "_2";
					com += "test01";
					com	+= comInit;
					int txt;
					txt = system(com.c_str());
					m_mydata.data = sleep;
					m_mydataOut.write();

				}
				else if(inf_data == 3)
				{
					string com = "~/workspace/ledcon/shells";
					string comInit = "_3";
					com += "test01";
					com	+= comInit;
					int txt;
					txt = system(com.c_str());
					m_mydata.data = sleep;
					m_mydataOut.write();


				}
			}
		}
		/*m_id = 1のとき無線情報を基にポート間の繋がりを変更する*/
		if(m_id == 1)
		{
			if(m_networkIn.isNew())
			{
				m_networkIn.read();
				ntk_data = m_network.data;
				if(ntk_data == 1)
				{
					string com = "~/workspace/ledcon/shells";
					string comInit = "_1";
					com += "test01";
					com	+= comInit;
					int txt;
					txt = system(com.c_str());
					m_mydata.data = sleep;
					m_mydataOut.write();

				}
				else if(ntk_data == 2)
				{
					string com = "~/workspace/ledcon/shells";
					string comInit = "_2";
					com += "test01";
					com	+= comInit;
					int txt;
					txt = system(com.c_str());
					m_mydata.data = sleep;
					m_mydataOut.write();


				}
				else if(ntk_data == 3)
				{
					string com = "~/workspace/ledcon/shells";
					string comInit = "_3";
					com += "test01";
					com	+= comInit;
					int txt;
					txt = system(com.c_str());
					m_mydata.data = sleep;
					m_mydataOut.write();
				}

			}
		}


		/*赤外線LED用PWM*/
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(3200);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(10);
		//信号生成
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);

		//信号の反転データ生成
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		usleep(5);

		pclose(fp);

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t getinfo::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t getinfo::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t getinfo::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t getinfo::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t getinfo::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void getinfoInit(RTC::Manager* manager)
  {
    coil::Properties profile(getinfo_spec);
    manager->registerFactory(profile,
                             RTC::Create<getinfo>,
                             RTC::Delete<getinfo>);
  }
  
};


