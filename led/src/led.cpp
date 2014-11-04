// -*- C++ -*-
/*!
 * @file  led.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "led.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

FILE *fp;

using namespace std;



// Module specification
// <rtc-template block="module_spec">
static const char* led_spec[] =
  {
    "implementation_id", "led",
    "type_name",         "led",
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

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
led::led(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ledIn("led", m_led)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
led::~led()
{
}



RTC::ReturnCode_t led::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("led", m_ledIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t led::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t led::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t led::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t led::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t led::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t led::onExecute(RTC::UniqueId ec_id)
{
	int led_data;

	if(m_ledIn.isNew())
	{
		m_ledIn.read();
		led_data = m_led.data;
		fp = popen("echo 1 > /sys/class/gpio/gpio168/value","r");
		sleep(led_data);
		fp = popen("echo 0 > /sys/class/gpio/gpio168/value","r");
		sleep(led_data);
	}

	pclose(fp);

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t led::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t led::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t led::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t led::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t led::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ledInit(RTC::Manager* manager)
  {
    coil::Properties profile(led_spec);
    manager->registerFactory(profile,
                             RTC::Create<led>,
                             RTC::Delete<led>);
  }
  
};


