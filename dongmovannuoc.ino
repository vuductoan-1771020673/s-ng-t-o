#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Khai báo chân
const int waterPin = 3;    // DOUT cảm biến nước
const int ledPin = 13;     // LED
const int servoPin = 9;    // Signal servo

Servo myServo;             // Đối tượng servo
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Địa chỉ I2C (kiểm tra nếu khác)

void setup() {
  Serial.begin(9600);          // Serial Monitor
  pinMode(waterPin, INPUT);    // Cảm biến INPUT
  pinMode(ledPin, OUTPUT);     // LED OUTPUT
  myServo.attach(servoPin);    // Gắn servo
  myServo.write(0);            // Góc ban đầu 0°
  lcd.init();                  // Khởi tạo LCD
  lcd.backlight();             // Bật đèn nền
  lcd.setCursor(0, 0);         // Dòng 1
  lcd.print("He thong nuoc:");
  Serial.println("Dự án sẵn sàng!");
}

void loop() {
  int waterValue = digitalRead(waterPin);  // Đọc DOUT (LOW: có nước)

  if (waterValue == LOW) {  // Mức nước cao
    digitalWrite(ledPin, HIGH);  // Bật LED
    myServo.write(90);           // Quay servo 90°
    lcd.setCursor(0, 1);         // Dòng 2
    lcd.print("Muc cao - Mo van");
    Serial.println("Muc cao - Mo van!");
  } else {                  // Mức nước thấp
    digitalWrite(ledPin, LOW);   // Tắt LED
    myServo.write(0);            // Về 0°
    lcd.setCursor(0, 1);
    lcd.print("Muc thap - Dong ");
    Serial.println("Muc thap - Dong van");
  }

  delay(500);  // Đợi 0.5 giây
}