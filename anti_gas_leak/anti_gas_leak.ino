//#include <LiquidCrystal_I2C.h>

//#include <LiquidCrystal.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial mySerial(9, 8);

int gasValue = A0;
int data = 0;
int relay = 6;
int buzzerPin = 7;

void setup() {
    randomSeed(analogRead(0));
    mySerial.begin(9600);
    Serial.begin(9600);
    lcd.begin(20,4); // Initialize the LCD without specifying the number of columns and rows
    lcd.backlight();
    pinMode(gasValue, INPUT);
    pinMode(relay, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    lcd.setCursor(2, 0);
    lcd.print("WELCOME TO  ");
    lcd.setCursor(2, 1);
    lcd.print("GAS DETECTION SYSTEM");
    lcd.setCursor(6, 2);
    lcd.print("DESIGN By :-");
    lcd.setCursor(6, 3);
    lcd.print("GROUP 12");
    delay(3000);
    lcd.clear();
}


void loop() {
    data = analogRead(gasValue);

    Serial.print("Gas Level: ");
    Serial.println(data);

    lcd.setCursor(2, 1);
    lcd.print("Gas Level: ");
    lcd.print(data);

    if (data > 600) {
        SendMessage();
        Serial.println("Gas detect alarm");
        lcd.setCursor(1, 0);
        lcd.print("Exhaust fan: ON");
        lcd.setCursor(2, 2);
        lcd.print("Gas Level Exceed");
        lcd.setCursor(2, 3);
        lcd.print("SMS Sent");
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(relay, HIGH);
    } else {
        Serial.println("Gas Level Low");
        lcd.setCursor(2, 3);
        lcd.print("Gas Level Normal");
        digitalWrite(buzzerPin, LOW);
        digitalWrite(relay, LOW);
    }

    delay(1000);
}

void SendMessage() {
     // Configure GSM module for text mode
    mySerial.println("AT+CMGF=1");
    delay(1000);

    // Set the recipient phone number
    mySerial.println("AT+CMGS=\"+917045442497\"\r");
    delay(1000);

    // Compose and send the SMS message
    mySerial.println("Excess Gas Detected.");
    mySerial.print("Gas Level: ");
    mySerial.println(data);

    // End the SMS transmission
    mySerial.println((char)26);
    delay(1000);
}
