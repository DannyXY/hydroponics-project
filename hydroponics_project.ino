#define BLYNK_TEMPLATE_ID "TMPL2fzESvGbc"

#define BLYNK_TEMPLATE_NAME "Final Year Project"



// HEADER FILES

#include <stdio.h>

#include <stdlib.h>

#include <WiFi.h>

#include <HTTPClient.h>

#include <WebServer.h>

#include <BlynkSimpleEsp32.h>

// #include <LiquidCrystal_I2C.h>

#include <DHT.h>

#include <ArduinoJson.h>

#include <ESP_Google_Sheet_Client.h>

#include <time.h>

#include <HardwareSerial.h>

#include <NewPing.h>



// TIME SERVER CREDENTIALS

const char* ntpServer = "pool.ntp.org";

const long gmtOffset_sec = 19800;

const int daylightOffset_sec = 0;



// WiFi credentials

char ssid[] = "Dannys Galaxy S20+";

char pass[] = "dannyxyzzzzzy";







// Blynk Auth Token

char auth[] = "h52gXXf2EfLc6vMbE_U3qPuj322diOQ8";



byte values[11];

HardwareSerial UARTSerial1(0);



char numberArray[20];



// GSHEET Config Details

#define PROJECT_ID "hydroponics-systems-log"

#define CLIENT_EMAIL "esp32-testing-logs@hydroponics-systems-log.iam.gserviceaccount.com"

#define USER_EMAIL "hydropnicsproject@gmail.com"

const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCfYQJ+i/ghcWcH\nDd/BjZY8r85noKqU+AOYbZCxKa7ZUHrjCSz9qrPPlInq4Qkp8GuFQ8aEAuQh+kGZ\nF6vkYuahrT49BmAgGBer5PHPILjcqlEx1L78qeibuedAlFDcpx4dPKAJDvy3MWz4\ncvtsXQyqc7gskQXUl0ZOIqfYVE4vG48LRtBh5fuVv77zrIkhDrqBlpI2NjvLo1ok\ntHQ5Rp3ejTMX8fBAuKTmsau0zvPaqG4GPNyR6rKuPT/G39g3UT89QNBpWQ3gygtq\n+VvgM+ba3hIwQnyA/oNuHHLe/Aa5Qe82/IE7akdGfU+i/cDpXULFjBVuV99hJkKl\n2I/A0AbLAgMBAAECggEAOJXUsOE5A4ajsZl3a9y9DmbMvXYJmkJD5IZh7MSD05wD\nRUAovRcyJ+zw2ndzLXSyd+oMPSpZnMahK51/5eJHR/eeNURiNILZRKpQP926RH4j\nvbFu7X3VnBRwyjjeTLj4tCCmIRE1IEVoDv2jzmFq8cmMBianD0d2Kp+bP+8OoyJy\nHRw9OcWSXkwJ73ZM1z4s2RgEqdbIvIsk9wkFheNEz+fUxJXktoiVFyJ21nc8OJ3u\n7jS4KVuxXLPFe4jtRtPaNU5y2zVin1HnR9GfJd/AzB0+v84GWOdcoVuXvG5rRQEn\nJwIqhMr54ymcHHcev6RtkCEzHnCvXcC1wdz8DgKHoQKBgQDTj9LATkx0UCJM/8f8\nITuqnYh+NrkZ39T/Bt8fvXzOHuMp3IJEe709U2zjsqFRgDUaIr5FYLcB5YWrHgDi\nI4TKr76jQwzBxeEMYOra+xROD3wSDGftbXdOyRNJylAgKj5XBTLKeOwlVMyu7vn1\nYLUFLpE1AtGytD/Ga7GV8wdFRwKBgQDA2zDhJBKB539XKCD4wp5tJ2EPRMPTl7TQ\na56IYdB4nr0KXy+q7bhWz5weCScipBkGvUxwOK9eqLXL2sAlY8AfExzHKaPa3MOE\nGnZJtp45pgpvbVcUnHcU3L+nTFGvgoLHU4c+XNwP68EYVzVblrSBfUrZYe6tBcws\nXdt6t5NEXQKBgQC4usfShUv68BHTXDC6diZMZzvMwWnFLw4kFVL0uxdkP9IpNlNF\nCysFhnf5Jnv311QG2zl7COUjsc+SyCMLUupbtTNoCV71QByvG11XEo/7TUgP1mdV\nCRV5ZNgDwbVPMLO4dmCQLSA9xJrpUOBPoz7NJIlEWY7TVNKvJlAtV8UMdwKBgHVp\nPLHkvyu9H2aVdLVd7wuvLMUZ7Uq1koxM6MBJJJ06rwZQevnKLi8TyAz1L5FEbEQR\nHSc5K3MqrTtFmzNoLj/858lMzYfiXVngrmEkP+IC91ltLNXMiCb4Wenladm7UBk/\n/hd2ezdqJS3HciGnd49aEyaTG7bUz7+3CHcGqi61AoGAUmFGuQ619DQF3fMwn7tF\nFTACTFdRliDHTuhdl8rJ9NV13ySTVCB5c0uf0KZIW8pmfvYINcDMGjkV7DLUzMmZ\ngfI4Nmmc62pcbwUKUpX21oOGXi5+SIMwgUHNLENZEPYvkY/dEu7YE/lXMcJ3d2Nk\nWZU+1hR3BfYsebYYgiSF8AI=\n-----END PRIVATE KEY-----\n";





// I2C LCD settings

#define LCD_ADDRESS 0x27  // Change this to your LCD's I2C address

#define LCD_COLUMNS 20

#define LCD_ROWS 4



// SENSOR PIN SELECTIONS

#define MOISTSENSORPIN1 2

#define MOISTSENSORPIN2 4

#define ECHOPIN1 12

// #define ECHOPIN2 27

#define TRIGPIN1 14

// #define TRIGPIN2 26

#define DHTPIN 32

#define DHTTYPE DHT22



// ACTUATOR PIN SELECTION

#define NUTRIENT_PIN_1 34

#define WATER_PIN_1 36

// #define NUTRIENT_PIN_2 20

// #define WATER_PIN_2 23

// #define LIGHT_PIN 9

// #define FAN_ACTUATOR 10



/**

  PINS 21 and 22 should be ignored since they're SCL and SDA pins for the I2C

**/

// NPK SENSOR PIN DEFINITION

#define DI 13

#define DE 14

#define RE 15

#define RO 16



#define MAX_DISTANCE 15

#define MIN_DISTANCE 2



#define BUZZER 20



bool isWLConnected;



// Initialize I2C LCD

// LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);



// Initialize sensors

DHT dht(DHTPIN, DHTTYPE);



WebServer server(80);



// INITIALIZE ULTRASONIC SENSORS

NewPing nutrientLevelSensor(TRIGPIN1, ECHOPIN1, MAX_DISTANCE);

// NewPing waterLevelSensor(TRIGPIN2, ECHOPIN2, MAX_DISTANCE);



// VARIABLES FOR STORING SENSOR READINGS

float NPKValue = 100;

byte nitrogenVal = 0;

byte potassiumVal = 0;

byte phosphorusVal = 0;

float waterTemp = 21.4;

float soilMoisture1 = 2032;

float soilMoisture2 = 1293;

float airTemp = 27.4;

float airHumidity = 122;

long waterLevel = 30;

long nutrientLevel = 30;

// SET DEFAULT MODE

int modeSelect = 0;

bool spreadsheetCreated = true;



// @dev: Only set to true when sensors are interfaced

bool isOperational = false;



const byte nitro[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0a };

const byte phos[] = { 0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xd5, 0xca };

const byte pota[] = { 0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xca };



// Modes configuration

struct Mode {

  const char* name;

  float minNPKValue;

  float maxNPKValue;

  float waterTempMin;

  float waterTempMax;

  float minSoilMoisture;

  float maxSoilMoisture;

  float minNutrientLevel;

  float minWaterLevel;

};



Mode modes[] = {

  { "Vegetative", 5.5, 6.5, 21, 28, 2400, 1200, 8, 20 },

  { "Flowering", 5.8, 6.2, 1.4, 2.2, 20, 24, 6, 18 },

  // Add more modes as needed

};



// Define Token status callback

void tokenStatusCallback(TokenInfo info);





void setup() {

  // Initialize Serial Monitor

  Serial.begin(115200);

  // UARTSerial1.begin(115200, SERIAL_8N1, 1, 3);



  Serial.println("\nInitialized");



  // Initialize WiFi

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {

    isWLConnected = false;

  }

  isWLConnected = true;

  Serial.println("WiFi connected");

  Serial.println("IP Address: ");

  Serial.println(WiFi.localIP());



  server.on("/", handleRoot);

  server.on("/data", handleData);

  server.on("/cropMode", handleCropMode);

  server.begin();



  // // Initialize LCD

  // lcd.init();

  // lcd.noBacklight();

  // lcd.setCursor(0, 0);

  // lcd.print("Wowzer, i work?");



  // Initialize Actuator Pins

  pinMode(NUTRIENT_PIN_1, OUTPUT);

  pinMode(WATER_PIN_1, OUTPUT);

  // pinMode(NUTRIENT_PIN_2, OUTPUT);

  // pinMode(WATER_PIN_2, OUTPUT);

  // pinMode(LIGHT_PIN, OUTPUT);

  // pinMode(FAN_ACTUATOR, OUTPUT);

  pinMode(RE, OUTPUT);

  pinMode(DE, OUTPUT);



  // digitalWrite(LIGHT_PIN, HIGH);

  // digitalWrite(FAN_ACTUATOR, HIGH);



  // SET TOKEN CALLBACK

  GSheet.setTokenCallback(tokenStatusCallback);



  // SET AUTH PREREFRESH

  GSheet.setPrerefreshSeconds(10 * 60);



  // BEGIN THE ACCESS TOKEN GENERATION

  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  dht.begin();

  Blynk.begin(auth, ssid, pass);

}



void connectWifi() {

  if (WiFi.status() != WL_CONNECTED) {

    WiFi.begin(ssid, pass);

    isWLConnected = false;

  } else {

    isWLConnected = true;

    Serial.println("WiFi connected");

  }

}



void handleCropMode() {

  if (server.hasArg("mode")) {

    modeSelect = server.arg("mode").toInt();

  }

  server.send(200, "text/plain", "OK");

}



long readMoistureSensor(int ANALOG_PIN) {

  pinMode(ANALOG_PIN, INPUT);

  long moisture = analogRead(ANALOG_PIN);

  return moisture;

}



void updateBlynkVariables() {

  Serial.print("Nutrient Level in cm : ");

  Serial.println(nutrientLevel);

  Blynk.virtualWrite(V0, airTemp);

  Serial.print("AirTemp Level in cm : ");

  Serial.println(airTemp);

  Blynk.virtualWrite(V1, soilMoisture2);

  Serial.print("Moisture Level in cm : ");

  Serial.println(soilMoisture2);

  Blynk.virtualWrite(V2, nutrientLevel);

  Blynk.virtualWrite(V3, modeSelect);

}



void handleRoot() {

  String html = R"rawliteral(

<!DOCTYPE html>

<html lang="en">

<head>

    <meta charset="UTF-8">

    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>ESP32 Monitor</title>

    <style>

        * {

            margin: 0;

            padding: 0;

            box-sizing: border-box;

        }

        body {

            font-family: Arial, sans-serif;

            line-height: 1.6;

            background-color: #f5f5f5;

            color: #333;

            display: flex;

            flex-direction: column;

            min-height: 100vh;

        }

        header {

            background: #4CAF50;

            color: #fff;

            padding: 1rem;

            text-align: center;

        }

        main {

            flex: 1;

            display: flex;

            flex-direction: column;

            justify-content: center;

            align-items: center;

            padding: 2rem;

        }

        .card-container {

            display: flex;

            gap: 2rem;

        }

        .card {

            background: #fff;

            border-radius: 8px;

            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);

            padding: 2rem;

            text-align: center;

            max-width: 400px;

            width: 100%;

            border: 2px solid #8D6E63;

        }

        .card h2 {

            margin-bottom: 1rem;

            color: #4CAF50;

        }

        p {

            margin: 0.5rem 0;

        }

        select {

            padding: 0.5rem;

            border: 1px solid #ccc;

            border-radius: 4px;

            font-size: 1rem;

            margin: 1rem 0;

        }

        footer {

            background: #8D6E63;

            color: #fff;

            text-align: center;

            padding: 1rem;

        }

        button {

            background: #4CAF50;

            border: none;

            color: #fff;

            padding: 0.5rem 1rem;

            font-size: 1rem;

            border-radius: 4px;

            cursor: pointer;

            transition: background 0.3s ease;

            margin: 0.5rem;

        }

        button.active {

            background: #388E3C;

        }

        button:hover {

            background: #388E3C;

        }

    </style>

</head>

<body>

    <header>

        <h1>ESP32 Sensor Dashboard</h1>

    </header>

    <main>

        

            <button id="topButton" class="active" onclick="showTop()">Top Layer</button>

            <button id="bottomButton" onclick="showBottom()">Bottom Layer</button>

        </div>

        <div class="card-container">

            <section class="card" id="topLayer">

                <h2>Top Layer Sensor Readings</h2>

                <p>Temperature: <span id='temperatureTop'></span> ï¿½C</p>

                <p>Humidity: <span id='humidityTop'></span> </p>

                <p>Nutrient Level: <span id='nutrientLevelTop'></span> %</p>

                <p>Water Level: <span id='waterLevelTop'></span> %</p>

                <p>Nitrogen Level: <span id='nitrogenLevelTop'></span> mg/kg</p>

                <p>Soil Moisture: <span id='soilMoistureTop'></span></p>

            </section>

            <section class="card" id="bottomLayer" style="display: none;">

                <h2>Bottom Layer Sensor Readings</h2>

                <p>Temperature: <span id='temperatureBottom'></span> ï¿½C</p>

                <p>Humidity: <span id='humidityBottom'></span> </p>

                <p>Nutrient Level: <span id='nutrientLevelBottom'></span> </p>

                <p>Water Level: <span id='waterLevelBottom'></span> %</p>

                <p>Nitrogen Level: <span id='nitrogenLevelBottom'></span> mg/kg</p>

                <p>Soil Moisture: <span id='soilMoistureBottom'></span></p>

            </section>

        </div>

        <h2>Crop Mode</h2>

        <select id="cropMode" onchange="setCropMode()">

            <option value="Vegetative">Vegetative</option>

            <option value="Flowering">Flowering</option>

            <option value="Grain">Grain</option>

        </select>

    </main>

    <footer>

        <p>Â© 2024 ESP32 Sensor Dashboard. All rights reserved.</p>

    </footer>

    <script>

        function setCropMode() {

            const mode = document.getElementById('cropMode').value;

            fetch('/cropMode?mode=' + mode);

        }



        function showTop() {

            document.getElementById('topLayer').style.display = 'block';

            document.getElementById('bottomLayer').style.display = 'none';

            document.getElementById('topButton').classList.add('active');

            document.getElementById('bottomButton').classList.remove('active');

        }



        function showBottom() {

            document.getElementById('topLayer').style.display = 'none';

            document.getElementById('bottomLayer').style.display = 'block';

            document.getElementById('topButton').classList.remove('active');

            document.getElementById('bottomButton').classList.add('active');

        }



        setInterval(function() {

            fetch('/data').then(response => response.json()).then(data => {

                document.getElementById('temperatureTop').innerText = data.temperatureTop;

                document.getElementById('humidityTop').innerText = data.humidityTop;

                document.getElementById('nutrientLevelTop').innerText = data.nutrientLevelTop;

                document.getElementById('waterLevelTop').innerText = data.waterLevelTop;

                document.getElementById('nitrogenLevelTop').innerText = data.nitrogenLevelTop;

                document.getElementById('soilMoistureTop').innerText = data.soilMoistureTop;

                document.getElementById('temperatureBottom').innerText = data.temperatureBottom;

                document.getElementById('humidityBottom').innerText = data.humidityBottom;

                document.getElementById('nutrientLevelBottom').innerText = data.nutrientLevelBottom;

                document.getElementById('waterLevelBottom').innerText = data.waterLevelBottom;

                document.getElementById('nitrogenLevelBottom').innerText = data.nitrogenLevelBottom;

                document.getElementById('soilMoistureBottom').innerText = data.soilMoistureBottom;

                document.getElementById('cropMode').value = data.modeSelect;

            });

        }, 1000);

    </script>

</body>

</html>

)rawliteral";

  server.send(200, "text/html", html);

}



BLYNK_WRITE(V3) {

  modeSelect = param.asInt();          // Update the mode based on Blynk button selection

  Blynk.virtualWrite(V3, modeSelect);  // Upload the current mode to Blynk

  Serial.println(modeSelect);

}



void handleData() {

  String json = "{";

  json += "\"temperatureTop\": 27.4 ,";

  json += "\"humidityTop\": 122 ,";

  json += "\"nutrientLevelTop\": " + String(nutrientLevel) + ",";

  json += "\"waterLevelTop\": " + String(waterLevel) + ",";

  json += "\"nitrogenLevelTop\": " + String(nitrogenVal) + ",";

  json += "\"phosphorusLevelTop\": " + String(phosphorusVal) + ",";

  json += "\"potassiumLevelTop\": " + String(potassiumVal) + ",";

  json += "\"soilMoistureTop\": 1140,";

  json += "\"soilMoistureBottom\": 1350,";

  json += "\"modeSelect\":" + String(modeSelect) + "," ;

  json += "\"temperatureBottom\": 28.4 ,";

  json += "\"humidityBottom\": 129 ,";

  json += "\"nutrientLevelBottom\": " + String(nutrientLevel) + ",";

  json += "\"waterLevelBottom\": " + String(waterLevel) + ",";

  json += "\"nitrogenLevelBottom\": " + String(nitrogenVal) + ",";

  json += "\"phosphorusLevelBottom\": " + String(phosphorusVal) + ",";

  json += "\"potassiumLevelBottom\": " + String(potassiumVal);

  json += "}";



  server.send(200, "application/json", json);

}



void loop() {

  Blynk.run();

  int level;

  /** 

    READING  AND UPDATING SENSOR VALUES

  **/

  // READ NUTRIENT AND WATER LEVEL

  Serial.println("WiFi connected");

  Serial.println("IP Address: ");

  Serial.println(WiFi.localIP());

  level = nutrientLevelSensor.ping_cm();

  if(level >= MIN_DISTANCE && level <= MAX_DISTANCE) {

    nutrientLevel = 100.0 * (MAX_DISTANCE - level) / (MAX_DISTANCE - MIN_DISTANCE);

  }

  // level = waterLevelSensor.ping_cm();

  // if(level >= MIN_DISTANCE && level <= MAX_DISTANCE) {

  //   waterLevel = 100.0 * (MAX_DISTANCE - level) / (MAX_DISTANCE - MIN_DISTANCE);

  // }

  

  Serial.print("NUTRIENT LEVEL");

  Serial.print(nutrientLevel);

  Serial.println("%");

  Serial.print("WATER LEVEL");

  Serial.print(waterLevel);

  Serial.println("%");



  // READ MOISTURE SENSOR VALUES

  soilMoisture1 = readMoistureSensor(MOISTSENSORPIN1);

  soilMoisture2 = readMoistureSensor(MOISTSENSORPIN2);



  // READ DHT SENSOR VALUES

  float temp = dht.readTemperature();

  if (isnan(temp)) {

    temp = 0;

    Serial.print("Failed To Read Temperature");

  }

  airTemp = temp;

  float humidity = dht.readHumidity();

  if (isnan(humidity)) {

    humidity = 0;

    Serial.print("Failed To Read Humidity");

  }

  airHumidity = humidity;



  // // READ NPK SENSORS

  // nitrogenVal = readNPKValue(nitro);

  // phosphorusVal = readNPKValue(phos);

  // potassiumVal = readNPKValue(pota);

  /** 

  TODO: @dev @feature

  **/





  // // GOOGLE SHEETS SETUP

  bool ready = GSheet.ready();



  String spreadsheetId, spreadsheetURL;

  if (!spreadsheetCreated) {

    FirebaseJson response;

    Serial.println("\nCREATING SPREADSHEET");

    Serial.println("------------------------------");

    FirebaseJson spreadsheet;

    spreadsheet.set("properties/title", "HYDROPONICS SYSTEM LOGGER");

    spreadsheet.set("sheets/properties/gridProperties/rowCount", 100000);

    spreadsheet.set("sheets/properties/gridProperties/columnCount", 9);



    bool success = false;



    success = GSheet.create(&response, &spreadsheet, USER_EMAIL);

    response.toString(Serial, true);

    Serial.println();

    FirebaseJson valueRange;

    if (success) {

      valueRange.add("majorDimension", "COLUMNS");

      valueRange.set("values/[1]/[0]", "Time/Date");

      valueRange.set("values/[2]/[0]", "Air Temperature");

      valueRange.set("values/[3]/[0]", "Soil Moisture 1");

      valueRange.set("values/[4]/[0]", "Soil Moisture 2");

      valueRange.set("values/[5]/[0]", "Nitrogen Value");

      valueRange.set("values/[6]/[0]", "Phosphorus Value");

      valueRange.set("values/[7]/[0]", "Potassium Value");

      valueRange.set("values/[8]/[0]", "Water Temperature");

      valueRange.set("values/[9]/[0]", "Mode Selected");



      // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append

      // GET SPREADSHEET ID FROM RESPONSE

      FirebaseJsonData result;

      response.get(result, FPSTR("spreadsheetId"));

      if (result.success)

        spreadsheetId = result.to<const char*>();

      // Append values to the spreadsheet

      bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);

      if (success) {

        response.toString(Serial, true);

        valueRange.clear();

      } else {

        Serial.println(GSheet.errorReason());

      }



      // GET SPREADSHEET URL

      result.clear();

      response.get(result, FPSTR("spreadsheetUrl"));

      if (result.success) {

        spreadsheetURL = result.to<const char*>();

        Serial.println("\nThe Spreadsheet URL IS:  ");

        Serial.println(spreadsheetURL);

      }

      spreadsheetCreated = true;

    }

  }

  FirebaseJson updateResponse;

  FirebaseJson updatedValueRange;



  struct tm timeInfo;

  char timeStringBuff[50];

  String asString;

  char buffer[40];



  Serial.println("\nUpdate spreadsheet values...");

  Serial.println("------------------------------");

  if (!getLocalTime(&timeInfo)) {

    Serial.println("Failed to obtain time");

    return;

  }



  strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeInfo);

  asString = timeStringBuff;



  updatedValueRange.add("majorDimension", "COLUMNS");

  updatedValueRange.set("values/[1]/[0]", asString);

  updatedValueRange.set("values/[2]/[0]", airTemp);

  updatedValueRange.set("values/[3]/[0]", soilMoisture1);

  updatedValueRange.set("values/[4]/[0]", soilMoisture2);

  updatedValueRange.set("values/[5]/[0]", 0);

  updatedValueRange.set("values/[6]/[0]", 0);

  updatedValueRange.set("values/[7]/[0]", 0);

  updatedValueRange.set("values/[8]/[0]", waterTemp);

  updatedValueRange.set("values/[9]/[0]", modes[modeSelect].name);



  // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append

  // Append values to the spreadsheet

  bool appendSuccess = GSheet.values.append(&updateResponse /* returned response */, "1jP59bcENNQlb_kU0ojV-iEM_uAzwaTNtZALk3c55n90" /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &updatedValueRange /* data range to append */);

  if (appendSuccess) {

    // updateResponse.toString(Serial, true);

    updatedValueRange.clear();

  } else {

    Serial.println(GSheet.errorReason());

  }

  Serial.println();

  // Serial.println(ESP.getFreeHeap());

  // CONTROL CONDITIONS



  if(isOperational) {



    Mode mode = modes[modeSelect];

    if (waterLevel < mode.minWaterLevel || nutrientLevel < mode.minNutrientLevel) {

      pinMode(BUZZER, OUTPUT);

      digitalWrite(BUZZER, HIGH);

    }



    if (soilMoisture1 < mode.minSoilMoisture) {

      pinMode(WATER_PIN_1, OUTPUT);

      digitalWrite(WATER_PIN_1, HIGH);

      delay(4000);

      digitalWrite(WATER_PIN_1, LOW);

    }

    // if (soilMoisture2 < mode.minSoilMoisture) {

    //   pinMode(WATER_PIN_2, OUTPUT);

    //   digitalWrite(WATER_PIN_2, HIGH);

    //   delay(4000);

    //   digitalWrite(WATER_PIN_2, LOW);

    // }

    // if (soilMoisture1 > mode.maxSoilMoisture || soilMoisture1 > mode.maxSoilMoisture) {

    //   pinMode(FAN_ACTUATOR, OUTPUT);

    //   digitalWrite(FAN_ACTUATOR, HIGH);

    // }



    if (NPKValue < mode.minNPKValue) {

      pinMode(NUTRIENT_PIN_1, OUTPUT);

      digitalWrite(NUTRIENT_PIN_1, HIGH);

      delay(4000);

      // digitalWrite(NUTRIENT_PIN_2, LOW);

      // pinMode(NUTRIENT_PIN_2, OUTPUT);

      // digitalWrite(NUTRIENT_PIN_2, HIGH);

      // delay(4000);

      // digitalWrite(NUTRIENT_PIN_2, LOW);

    }



    if (NPKValue > mode.maxNPKValue) {

      pinMode(WATER_PIN_1, OUTPUT);

      digitalWrite(WATER_PIN_1, HIGH);

      delay(4000);

      digitalWrite(WATER_PIN_1, LOW);

      // pinMode(WATER_PIN_2, OUTPUT);

      // digitalWrite(WATER_PIN_2, HIGH);

      // delay(4000);

      // digitalWrite(WATER_PIN_2, LOW);

    }



      /** 

      TODO: Implement BULB LED activation according to 24H time

    **/

  }



    updateBlynkVariables();

    Serial.println("Hi guys");

    // delay(15000);

    server.handleClient();



}



void tokenStatusCallback(TokenInfo info) {

  if (info.status == esp_signer_token_status_error) {

    Serial.printf("Token info: Type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());

    Serial.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());

  } else {

    Serial.printf("Token info: Type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());

  }

}



// byte readNPKValue(const byte* request) {

//   digitalWrite(DE, HIGH);

//   digitalWrite(RE, HIGH);

//   UARTSerial1.write(request, sizeof(request));

//   digitalWrite(DE, LOW);

//   digitalWrite(RE, LOW);

//   delay(10);



//   byte responseLength = UARTSerial1.available();

//     for(byte i = 0; i< 7 ; i++) {

//       values[i] = UARTSerial1.read();

//       Serial.print(values[i], HEX);

//     }

//     Serial.println();

//   return values[3] << 8 | values[4];

// }

