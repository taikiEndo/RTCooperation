// -*- C++ -*-
/*!
 * @file  w_lan.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "w_lan.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <ext/stdio_filebuf.h>
#include <iomanip>
#include <algorithm>

#define COMMAND "iwlist wlan0 scan"

using namespace std;

// 無線情報のクラス 
class APlist
{
  public:
    unsigned char mac[6];
    string essid;
    int signal_lv;
};

// 下記ソート関数用
bool compare_signal_level(const APlist& ap1, const APlist& ap2) {  return  ap1.signal_lv > ap2.signal_lv; }

// MACアドレス取得 
void getMac(APlist& ap,int index,string str){
  char* e;
  long preMac;
    if(index >=0 && index < 6){
    preMac = strtol(str.c_str(), &e, 16);
    if((preMac != LONG_MAX) && (preMac != LONG_MIN)){
      ap.mac[index] = (unsigned char)preMac;
    }else{
      ap.mac[index] = 0;
    }
  }
};

/*
int checkESSID(APlist& ap){
  if(ap.essid == m_ssid_conf1){ //各ledのESSID　config化予定
    return 0; 
  }
  else if(ap.essid == m_ssid_conf2){
    return 0; 
  }
  else if(ap.essid == m_ssid_conf3){
    return 0;
  }
  return -1
};
*/


// Module specification
// <rtc-template block="module_spec">
static const char* w_lan_spec[] =
  {
    "implementation_id", "w_lan",
    "type_name",         "w_lan",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "DOTS",
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
w_lan::w_lan(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_wl_infOut("wl_inf", m_wl_inf)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
w_lan::~w_lan()
{
}



RTC::ReturnCode_t w_lan::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("wl_inf", m_wl_infOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t w_lan::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t w_lan::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t w_lan::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t w_lan::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t w_lan::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t w_lan::onExecute(RTC::UniqueId ec_id)
{
  // 変数の宣言 
  string buf,buf2,buf3;
  vector<APlist> Cells;
  APlist ap;
  bool get_ap;
  string::size_type ind,ind2,ind3;
  int iMac;

  FILE *p_file; // popen用ファイルポインタ
 
  p_file=popen(COMMAND,"r"); // "iwlist wlan0 scan" の実行

  // iwlistコマンド実行用ストリーム処理
  __gnu_cxx::stdio_filebuf<char> *p_fb = new __gnu_cxx::stdio_filebuf<char>(p_file, std::ios_base::in); 
  std::istream input(static_cast<std::streambuf *>(p_fb));

  // iwlist実行結果の読み込み
  while(getline(input, buf)){
    ind = buf.find("Cell",0); // 一覧文頭の検索
    if(ind != string::npos){
      get_ap = false;

      ind = buf.find("Address",0); // MACアドレスの行を検索
      if(ind != string::npos){
        buf2 = buf.substr(ind+9);
	ind2 = 0;
	iMac = 0;
	while((ind3 = buf2.find(":",ind2)) != string::npos && iMac < 5){
          buf3 = buf2.substr(ind2,ind3-ind2);
	  getMac(ap,iMac,buf3);
	  iMac++;
	  ind2 = ind3+1;
	}
	buf3 = buf2.substr(ind2,buf2.size()-ind2);
	getMac(ap,iMac,buf3);
      }else{
        break;
      }
      while(!get_ap && getline(input, buf)){
        ind = buf.find("ESSID",0); // ESSIDの行を検索
        if(ind != string::npos){
          buf2 = buf.substr(ind+7,buf.length()-(ind+7+1));
	  ap.essid = buf2;
          //ESSIDをチェック
          if(true){//checkESSID(ap)){
            while(!get_ap && getline(input, buf)){
              ind = buf.find("Signal level",0); // Signalの行を検索
              if(ind != string::npos){
                ind2 = buf.find(" ",ind+13);
	        buf2 = buf.substr(ind+13,ind2-(ind+13));
	        ap.signal_lv = atoi(buf2.c_str());
                Cells.push_back(ap);
                get_ap = true;
              }
            }
          }else{
            break;
          }
        }
      }
    }
  }

  // 取得結果をシグナルの強い順にソートして表示
  sort(Cells.begin(), Cells.end(), compare_signal_level);
  for(unsigned int i=0; i<Cells.size();i++){
    cout << "Cell" << i << " ESSID:" << Cells[i].essid << " signal level:" << Cells[i].signal_lv << endl;
  }

  if(!Cells.empty()){ // 無線情報が取得出来ていた場合
    stringstream ss;
    for(int m =0; m<6; m++){
      ss << hex << uppercase << setw(2) << setfill('0') << (int)(Cells[0].mac[m]) ;
      if(m < 5){
        ss << ':';
      }
    }
    cout << "<<The Nearest AccessPoint>>" << endl;
    cout << "MAC-ADDRESS:" << ss.str() << " ESSID:" << Cells[0].essid << " signal level:" << Cells[0].signal_lv<< endl;
    cout << endl;

    m_wl_inf.data=Cells[0].essid.c_str();
    m_wl_infOut.write();
    Cells.clear();
  }

  usleep(5000000); //情報取得周期 5s
  
  pclose(p_file);
 
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t w_lan::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t w_lan::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t w_lan::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t w_lan::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t w_lan::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void w_lanInit(RTC::Manager* manager)
  {
    coil::Properties profile(w_lan_spec);
    manager->registerFactory(profile,
                             RTC::Create<w_lan>,
                             RTC::Delete<w_lan>);
  }
  
};


