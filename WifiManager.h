#ifndef WifiManager_h
#define WifiManager_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WifiManager
{
public:
  WifiManager(char* _ssid, 
              char* _password, 
              char* _apssid, 
              char* _appaassword, 
              int _ConnectionAttemptsBeforeLocalAP = 3,
              int _MSBetweenConnectionAttempts = 5000);

  void PrintWifiDetails();

  void EnableLocalAP();

  void DisableLocalAP();

  bool ConnectedToWifi();

  void ConnectToWifi();

  void EnsureConnected();

  void Start();

  bool WaitForConnection(int timeoutms);
  
  bool LocalAPEnabled;
  int ConnectionAttempts;
  int ConnectionAttemptsBeforeLocalAP;

  int MSBetweenConnectionAttempts;

protected:

  long lastConnectAttempt;
  
  char* ssid;
  char* password;
  char* apssid;
  char* appaassword;
};

#endif