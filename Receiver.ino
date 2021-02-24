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
//  // initialize the LCD
// Serial.begin(9600);
// 
//  lcd.begin();
//
//  // Turn on the blacklight and print a message.
//  lcd.backlight();
//  //lcd.print("Hello, world!");
//
//  radio.begin();
//  radio.openReadingPipe(1,addresses[0]);
//  
//  radio.openWritingPipe(addresses[1]);
//  radio.setPALevel(RF24_PA_MAX);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setChannel(110);
//}
//
//void loop()
//{ lcd.clear();
//
//
//   delay(5);
//   radio.startListening();
//  
//   if(radio.available()){
//   lcd.print("available");
//   radio.read(&receiver,sizeof(receiver));
//   lcd.print(receiver[0]);
//
//   
//  delay(500);
//  radio.stopListening();
//  input[0]=1;
//  lcd.print(input[0]);
//  radio.write(&input,sizeof(input));
//
//
//
//   
//  }
//}

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <DHT11.h>
#include <Wire.h>
//#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature[2];

RF24 radio(3,4);
//const uint64_t pipe = 0xE8E8F0F0E1LL;
const byte address[6]="00001";
void setup(void) {
Serial.begin(115200);
lcd.begin();
lcd.backlight();
lcd.clear();
radio.begin();
radio.openReadingPipe(1, address);
radio.startListening();
radio.setChannel(110);
radio.setDataRate( RF24_250KBPS );
lcd.print("Hum & temp");
delay(1000);
lcd.clear();
lcd.print("Starting.....");
radio.setPALevel(RF24_PA_MAX);
delay(1000);
}

void loop(void)
{
  delay(5);
if (radio.available() )
{
bool done = false;
while (!done)
{
done=true;
radio.read(temperature, sizeof(temperature));

delay(500);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temp");
lcd.setCursor(0, 1);
lcd.print("Humidity");
lcd.setCursor(9, 0);
lcd.print(temperature[0]);
lcd.print(" C");
lcd.setCursor(9, 1);
lcd.print(temperature[1]);
lcd.print(" %");
delay(1000);
}
}
else
{
  lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Not available");
lcd.setCursor(0,1);
lcd.print(radio.available());
delay(1000);
}
}
