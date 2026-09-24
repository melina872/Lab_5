#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

//Variables
const int chipSelect = 10;
File dataFile;

//Potentiometer variables
const int potPin = A0;
int sensorValue = 0;

int position = 0;
void setup() {
    Serial.begin(9600);
    Serial.println("Program Started");
    Serial.println("Initializing SD card...");
    SD.begin(chipSelect);

    //Chip verification
    if (SD.begin(chipSelect)) {
        Serial.println("SD Card Found");
    }
    else{
        Serial.println("SD Card Not Found");
    }

    //Potentiometer setup
    sensorValue = analogRead(potPin);

    Serial.print("Value= ");
    Serial.println(sensorValue);

    delay(500);

    //CSV header creation
    dataFile = SD.open("sensor.csv", FILE_WRITE);
    if(dataFile){
        dataFile.println("Time,Value");
        dataFile.close();
    }
    else {
        Serial.println("File not found");
    }

}
 
void loop() {
    Serial.println(position);
    delay(1000);

    // // Creating the first file
    // dataFile = SD.open("hello.txt", FILE_WRITE);
    // dataFile.println("Hello Dawson");
    // dataFile.close();

    // //Creating a file to log potentiometer values
    // dataFile = SD.open("sensor.txt", FILE_WRITE);
    // dataFile.println(sensorValue);
    // dataFile.close();

    //Creating a CSV file and log in the information
    sensorValue = analogRead(potPin);
    unsigned long timeSeconds = millis() / 1000;

    Serial.print("Value = ");
    Serial.println(sensorValue);
    Serial.print("Time = ");
    Serial.println(timeSeconds);

    dataFile = SD.open("sensor.csv", FILE_WRITE);
    if(dataFile){
        dataFile.print(timeSeconds);
        dataFile.print(",");
        dataFile.println(sensorValue);
        dataFile.close();
    }
    else {
        Serial.println("File not found");
    }
  
    delay(1000);
}