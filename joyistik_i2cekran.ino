#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ekran nesnesi (16 sütun, 2 satır)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Joystick Pinleri
const int pinX = A0;
const int pinY = A1;

// Ekranda hareket edecek metin
String metin = "ARDUINO";
int metinUzunlugu = 7; // "ARDUINO" kelimesinin harf sayısı

// Metnin başlangıç koordinatları
int xKonumu = 0; // 0'dan başlar (Sol)
int yKonumu = 0; // 0. satır (Üst)

// Önceki konum (Ekranı sadece hareket olduğunda güncellemek için)
int eskiX = -1;
int eskiY = -1;

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  int xDegeri = analogRead(pinX); // 0 - 1023
  int yDegeri = analogRead(pinY); // 0 - 1023
  
  // 1. Y Ekseni Kontrolü (Yukarı / Aşağı)
  // 400 ve 600 değerleri ölü bölgedir. Çubuk ortadayken (512) işlem yapılmaz.
  // Bunun sebei oluşabilecek elektriksel gürültüden kaynaklıdır.
  // Sensörler her ölçüm sırasında belli bir hata payına sahiptir.
  if (yDegeri < 400) {
    yKonumu = 0; // Üst satıra geç
  } else if (yDegeri > 600) {
    yKonumu = 1; // Alt satıra geç
  }

  // 2. X Ekseni Kontrolü (Sağ / Sol)
  if (xDegeri < 400) {
    xKonumu--; // Sola kaydır
  } else if (xDegeri > 600) {
    xKonumu++; // Sağa kaydır
  }

  // 3. Ekran Sınırlarını Koruma
  // Metnin sol taraftan dışarı çıkmasını engelle
  if (xKonumu < 0) {
    xKonumu = 0;
  }
  // Metnin sağ taraftan dışarı çıkmasını engelle (16 sütun - metin uzunluğu)
  if (xKonumu > (16 - metinUzunlugu)) {
    xKonumu = 16 - metinUzunlugu;
  }

  // 4. Ekranı Güncelleme
  // Sadece eğer x veya y konumu değiştiyse ekranı sil ve yeniden yaz
  if (xKonumu != eskiX || yKonumu != eskiY) {
    lcd.clear();                 // Ekranı temizle
    lcd.setCursor(xKonumu, yKonumu); // İmleci yeni konuma al
    lcd.print(metin);            
    
    // Yeni konumu eski konum olarak kaydet
    eskiX = xKonumu;
    eskiY = yKonumu;
  }

  delay(150); 
}