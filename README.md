# Switch
ESP8266 wifi manager

Manages connecting to a wifi network

If a connection attempt fails more than _ConnectionAttemptsBeforeLocalAP times then a local access point is started to enable code to be updated via web update

## ESP8266 Examples

### Connect to access point and on failure start a local access point

```Arduino
char* ssid = "SSID";
char* password = "password";
char* LocalAPssid = "ESP8266";
char* LocalAPPassword = "password";

WifiManager wifiManager = WifiManager(ssid, password, LocalAPssid, LocalAPPassword);

void setup(void){
    wifiManager.Start();
}

void loop(void){
    wifiManager.EnsureConnected();
}
```

### Wait for wifi connection with timeout

```Arduino
char* ssid = "SSID";
char* password = "password";
char* LocalAPssid = "ESP8266";
char* LocalAPPassword = "password";

WifiManager wifiManager = WifiManager(ssid, password, LocalAPssid, LocalAPPassword);

void setup(void){
    wifiManager.Start();
}

void loop(void){
    bool connected = wifiManager.WaitForConnection(10000);
}
```