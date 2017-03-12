#include "WifiManager.h"

WifiManager::WifiManager(char* _ssid,
                        char* _password,
                        char* _apssid,
                        char* _appaassword,
                        int _ConnectionAttemptsBeforeLocalAP,
                        int _MSBetweenConnectionAttempts)
{
  ssid = _ssid;
  password = _password;
  apssid = _apssid;

  MSBetweenConnectionAttempts = _MSBetweenConnectionAttempts;
  lastConnectAttempt = 0;
  
  ConnectionAttemptsBeforeLocalAP = _ConnectionAttemptsBeforeLocalAP;
  ConnectionAttempts = 0;
  LocalAPEnabled = false;
}

void WifiManager::PrintWifiDetails()
{
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void WifiManager::EnableLocalAP()
{

  if(LocalAPEnabled == true)
  {
    return; //Local AP already enabled
  }

  Serial.println("Enabling local AP");
  
  LocalAPEnabled = true;
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(apssid, appaassword);
}

void WifiManager::DisableLocalAP(){
  
  if(LocalAPEnabled == false)
    return;
    
  Serial.println("Disabling local AP");
  WiFi.mode(WIFI_STA);
  LocalAPEnabled = false;
}

bool WifiManager::ConnectedToWifi() {
  return WiFi.status() == WL_CONNECTED;
}

void WifiManager::ConnectToWifi() {

  //Check if already connected, if so exit
  if(ConnectedToWifi()){
    
    DisableLocalAP();
    
    if(ConnectionAttempts > 0){
      Serial.println("Wifi Connected");
      PrintWifiDetails();
    }
    
    ConnectionAttempts = 0;
    return;
  }

  Serial.println("Connecting to wifi");

  if(LocalAPEnabled == false){
    WiFi.mode(WIFI_STA);
  }
  
  Serial.println("WiFi.begin");
  WiFi.begin(ssid, password);
 
  //First connection attempt is ignored as it checks too soon after trying to connect
  ConnectionAttempts++;
  if(ConnectionAttempts > 1){
    Serial.println("wifi connection failed");
  }
  
  if(ConnectionAttempts > ConnectionAttemptsBeforeLocalAP + 1){
    Serial.println("Too many wifi connect failures, starting local AP");
    EnableLocalAP();
  }
}

void WifiManager::Start(){
  EnableLocalAP();
  ConnectToWifi();
}

void WifiManager::EnsureConnected(){

  long currentTime = millis();

  if((lastConnectAttempt + MSBetweenConnectionAttempts)> currentTime){
    lastConnectAttempt = currentTime;
    ConnectToWifi();
  }
}

bool WifiManager::WaitForConnection(int timeoutms)
{
  long startMillis = millis();
  long endMillis = startMillis + timeoutms;

  while(!ConnectedToWifi()){

    if(millis() > endMillis){
      return false;
    }
    
    ConnectToWifi();
    delay(500);
  }

  return true;
}