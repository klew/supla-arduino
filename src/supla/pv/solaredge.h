/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef ARDUINO_ARCH_AVR
// Arduino Mega can't establish https connection, so it can't be supported

#ifndef __solaredge_h
#define __solaredge_h

#include <WiFiClientSecure.h>
#include <supla/sensor/electricity_meter.h>
#include <supla/clock/clock.h>

#define APIKEY_MAX_LENGTH 100
#define PARAMETER_MAX_LENGTH 20

namespace Supla {
namespace PV {
class SolarEdge : public Supla::Sensor::ElectricityMeter {
 public:
  SolarEdge(const char *apiKeyValue, const char *siteIdValue, const char *inverterSerialNumberValue, Supla::Clock *clock);
  void readValuesFromDevice();
  void iterateAlways();
  bool iterateConnected(void *srpc);
  Channel *getSecondaryChannel();

 protected:
  WiFiClientSecure pvClient;

  char buf[1024];

  unsigned _supla_int64_t totalGeneratedEnergy;
  _supla_int_t currentPower;
  unsigned _supla_int16_t currentCurrent;
  unsigned _supla_int16_t currentFreq;
  unsigned _supla_int16_t currentVoltage;
  int bytesCounter;
  int retryCounter;
  int valueToFetch;
  bool startCharFound;
  bool dataIsReady;
  bool dataFetchInProgress;
  bool headerFound;
  unsigned long connectionTimeoutMs;

  char apiKey[APIKEY_MAX_LENGTH];
  char siteId[PARAMETER_MAX_LENGTH];
  char inverterSerialNumber[PARAMETER_MAX_LENGTH];
  Supla::Clock *clock;
  Supla::Channel temperatureChannel;
};
};  // namespace PV
};  // namespace Supla

#endif
#endif
