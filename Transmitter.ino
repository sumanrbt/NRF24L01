//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//#include<SPI.h>
//#include<nRF24L01.h>
//#include<RF24.h>
//// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//uint32_t receiver[3];
//uint32_t input[3];
//RF24 radio(9,10);
//const byte addresses[][6]={"00001","00002"};
//void setup()
//{
//	// initialize the LCD
// Serial.begin(9600);
// 
//	lcd.begin();
//
//	// Turn on the blacklight and print a message.
//	lcd.backlight();
//	//lcd.print("Hello, world!");
//
//  radio.begin();
//  radio.openReadingPipe(1,addresses[1]);
//  radio.openWritingPipe(addresses[0]);
//  radio.setPALevel(RF24_PA_MAX);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setChannel(110);
//}
//
//void loop()
//{ lcd.clear();
//	delay(500);
//  radio.stopListening();
//  input[0]=1;
//  lcd.print(input[0]);
//  radio.write(&input,sizeof(input));
//
//
//
//   delay(5);
//   radio.startListening();
//  
//   if(radio.available()){
//    lcd.print("available");
//   radio.read(&receiver,sizeof(receiver));
//   lcd.print(receiver[0]);
//  }
//}






#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <DHT11.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//int pin = A0;
//DHT11 dht11(pin);
float temperature[2];

//double Fahrenheit(double celsius) {
//return ((double)(9 / 5) * celsius) + 32;
//}

//double Kelvin(double celsius) {
//return celsius + 273.15;
//}

RF24 radio(3
, 4);
//const uint64_t pipe = 0xE8E8F0F0E1LL;
const byte address[6]="00001";

void setup(void) {
  Serial.begin(115200);
  pinMode(A0,INPUT);
  
  lcd.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setChannel(110);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate( RF24_250KBPS );
  radio.stopListening();
  
}

void loop(void)
{
lcd.clear();
//float temp, humi;
//dht11.read(humi, temp);
temperature[0] = (analogRead(A0)/10)-11;
temperature[1] = 42 ;
radio.write(temperature, sizeof(temperature));
lcd.print("msg sent");
delay(500);
lcd.clear();
lcd.print("temp: ");
lcd.setCursor(6,0);
lcd.print(temperature[0]);
delay(1000);   
}
