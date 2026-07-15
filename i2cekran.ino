#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// İlk parametre I2C adresi (genellikle 0x27 veya 0x3F'dir).
// İkinci parametre sütun sayısı (16), üçüncü parametre satır sayısı (2).
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  // 1. Ekranı Başlatma
  lcd.init();       // Ekranı başlat (Eski kütüphanelerde lcd.begin() olabilir)
  lcd.backlight();  // Arka plan ışığını (LED'i) yak
  
  // 2. Ekrana Yazı Yazma
  // setCursor(sütun, satır) -> Saymaya 0'dan başlar!
  
  lcd.setCursor(0, 0);           // İmleci 1. satırın başına (0, 0) konumlandır
  lcd.print("Merhaba Arduino!"); // 1. satıra yazdır
  
  lcd.setCursor(0, 1);           // İmleci 2. satırın başına (0, 1) konumlandır
  lcd.print("Sistem Hazir...");  // 2. satıra yazdır
}

void loop() {
  
}