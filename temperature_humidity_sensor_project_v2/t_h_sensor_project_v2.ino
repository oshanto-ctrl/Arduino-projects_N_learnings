// Include necessary libraries
#include "DHT.h"

// Set Digital pin connected to DHT seonsor
#define DHTPIN 2 


// DHT22 (AOSONG AM2302) 
#define DHTTYPE DHT22 

/* 
Initializing the DHT sensor with DHTPIN, DHTTYPE
two parameters.
*/

DHT dht(DHTPIN, DHTTYPE);

// Initialize some variables for temperature
float initial_temp = 0.0;




// setup() function
void setup(){
  Serial.begin(9600);
  Serial.println(F("Temperatue & Humidity Tracking"));

  // Begin DHT
  dht.begin();

  // Initial temprature reading
  initial_temp = getTemp("c");


} // setup function ends


// loop() function
void loop(){
 /*
  // Wait 1000 m.s = 1 sec between measurements.
  delay(4000);
  */
  // get current temperature in celcius
  float temp_celcius = getTemp("c");

  // get current temperature in fahrenheit
  float temp_fahren = getTemp("f");

  // get humidity in air
  float humidity = getTemp("h");

  // get heat index in celcius
  float hic = getTemp("hic");

  // get heat index in fahrenheit
  float hif = getTemp("hif");

  // Some calcualtion on temperature (celcius)
  
  float temp_change = temp_celcius - initial_temp; // store previous encountered temperature
  

  // Printing th eoutput in serial monitor
  Serial.print("==========================================\n");

  if(temp_change > 1.0){
    Serial.println("Temperature Rising Indicated!!!\n");
  }else if(temp_change < -2.0){
    Serial.println("Temperature Falling!!!\n");
  }else{
    Serial.println("");
  }
  // Printing Temperature
  Serial.print(F("Temparature Now: "));
  Serial.print(temp_celcius);
  Serial.print(F("°C"));
  Serial.print("    ");
  Serial.print(temp_fahren);
  Serial.print(F("°F"));

  // Printing Humidity
  Serial.print("\nHumidity: ");
  Serial.print(humidity);
  Serial.print(F("%"));

  // Print Heat Index
  Serial.print("\nHeat Index: ");
  Serial.print(hic);
  Serial.print(F("°C  "));
  Serial.print(hif);
  Serial.println(F("°F"));


// Wait 1000 m.s = 1 sec between measurements.
// Delay n seconds before next reading 
  delay(4000);
  
} // Loop function ends


// Custom function for getting temperature
float getTemp(String request){
    // Reading of temperature or humidity takes about 250 miliseconds.

  // read humidity
  float humidity = dht.readHumidity();

  // read temperature as celcius (as default)
  float temp_celcius = dht.readTemperature();

  // read temperature as fahrenheit
  // set parameter (isFahrenheit = true)
  float temp_fahren = dht.readTemperature(true);

  // Check the failure of reading from sensor;
  // to return and check again for the reading.
  if (isnan(humidity) || isnan(temp_celcius) || isnan(temp_fahren)){
    Serial.println(F("Unable read temperature and humidity!\nTrying again..."));
    return;
  }

  // Computing the heat index in Fahrenheit (the default)
  float heat_index_fahren = dht.computeHeatIndex(temp_fahren, humidity);

  // Computing head index in celcius
  // set parameter isFahrenheit = false
  float heat_index_celcius = dht.computeHeatIndex(temp_celcius, humidity, false);

  // Respond to requests
  if(request == "c"){
    return temp_celcius; // return temperature in celcius
  }else if(request == "f"){
    return temp_fahren; // return temperature in fahrenheit
  }else if(request == "h"){
    return humidity;  // return humidity in air
  }else if(request == "hic"){
    return heat_index_celcius; // return heat index in celcius
  }else if(request == "hif"){
    return heat_index_fahren; // return heat index in fahrenheit
  }else{
    return 0.00; // Return no response if no request.
  }



} // getTemp function ends

