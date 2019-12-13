#define ESP32
#include <M5StickC.h>
#include <cstring>
#include <esp_task_wdt.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "screens.h"


void printCica(Screen *pScreen);
void printAxp(Screen *pScreen);

void setup()
{
  // put your setup code here, to run once:
  printf("Setup begins\r\n");

  TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed = 1;
  TIMERG0.wdt_wprotect = 0;

  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Axp.EnableCoulombcounter();

  ScreenMgr::init();
  ScreenMgr::add(new Screen(0, "Bat", 1000, &printAxp));
  ScreenMgr::add(new Screen(1, "Bluetooth", 0, &printBle));
  ScreenMgr::add(new Screen(2, "Time", 0, &printTime));

  printf("Setup completed\r\n");

  M5.Lcd.fillScreen(BLACK);
  (ScreenMgr::currentScreen()->screenProc)(ScreenMgr::currentScreen());
}

/** This is the main loop */
void loop()
{
  ScreenMgr::processUIActions();
  vTaskDelay(20);
}

void printSetup(Screen *pScreen)
{
}

void printBle(Screen *pScreen)
{
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.printf("\r\nCica mica\r\n");
  M5.Lcd.printf("Cica mica\r\n");
  M5.Lcd.printf("Cica mica\r\n");
  M5.Lcd.printf("\r\nCica mica\r\n");
  M5.Lcd.printf("Cica mica\r\n");
}

void printTime(Screen *pScreen)
{
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.printf("\r\nTime\r\n");
}

void printAxp(Screen *pScreen)
{

  double vbat = 0.0;
  int discharge, charge;
  double temp = 0.0;
  double bat_p = 0.0;
  int halSensor = 0;

  vbat = M5.Axp.GetVbatData() * 1.1 / 1000;
  charge = M5.Axp.GetIchargeData() / 2;
  discharge = M5.Axp.GetIdischargeData() / 2;
  temp = -144.7 + M5.Axp.GetTempData() * 0.1;
  bat_p = M5.Axp.GetPowerbatData() * 1.1 * 0.5 / 1000;

  //M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.printf("vbat:%.3fV\r\n", vbat);                            //battery voltage
  M5.Lcd.printf("icharge:%dmA\r\n", charge);                        //battery charging current
  M5.Lcd.printf("idischg:%dmA\r\n", discharge);                     //battery output current
  M5.Lcd.printf("temp:%.1fC\r\n", temp);                            //axp192 inside temp
  M5.Lcd.printf("pbat:%.3fmW\r\n", bat_p);                          //battery power
  M5.Lcd.printf("CoIn :%d\r\n", M5.Axp.GetCoulombchargeData());     //coulomb in current
  M5.Lcd.printf("CoOut:%d\r\n", M5.Axp.GetCoulombdischargeData());  //coulomb out current
  M5.Lcd.printf("CoD:%.2fmAh\r\n", M5.Axp.GetCoulombData());        //value of coulomb after calculate
  M5.Lcd.printf("Vin:%.3fmV\r\n", M5.Axp.GetVinData() * 1.7);       // ACIN vin voltage
  M5.Lcd.printf("Iin:%.3fmA\r\n", M5.Axp.GetIinData() * 0.625);     // ACIN vin current
  M5.Lcd.printf("Vuin:%.3fmV\r\n", M5.Axp.GetVusbinData() * 1.7);   //usb vin voltage
  M5.Lcd.printf("Iuin:%.3fmA\r\n", M5.Axp.GetIusbinData() * 0.375); // usb vin current
  halSensor = hallRead();
  M5.Lcd.printf("HAL: :%d\r\n", halSensor); //HAL sensor

  // 0x01 long press(1s), 0x02 press
  if (M5.Axp.GetBtnPress() == 0x02)
  {
    esp_restart();
  }
}

