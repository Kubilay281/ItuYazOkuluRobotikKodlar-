// Joystick Pin Tanımlamaları
const int pinX = A0; 
const int pinY = A1; 
const int pinButon = 2; 

// LED Pin Tanımlamaları
const int ledX = 3;     // X ekseni için PWM pini
const int ledY = 5;     // Y ekseni için PWM pini
const int ledButon = 7; // Sadece Aç/Kapa (Dijital)

void setup() {
  // Seri iletişimi başlatıyoruz (Ctrl+Shift+M ile monitörü açabilirsiniz)
  Serial.begin(9600);
  
  // Joystick buton pini için dahili pull-up direncini aktifleştiriyoruz
  // Bu sayede dışarıdan direnç bağlamamıza gerek kalmaz.
  pinMode(pinButon, INPUT_PULLUP); 
  
  // LED pinlerini çıkış olarak ayarlıyoruz
  pinMode(ledX, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledButon, OUTPUT);
}

void loop() {
  // 1. Joystick Değerlerini Oku
  int xDegeri = analogRead(pinX); // 0 - 1023 arası değer okur
  int yDegeri = analogRead(pinY); // 0 - 1023 arası değer okur
  
  // INPUT_PULLUP kullandığımız için butona BASILDIĞINDA 0 (LOW), BASILMADIĞINDA 1 (HIGH) okunur
  int butonDurumu = digitalRead(pinButon); 

  // 2. LED Parlaklıklarını Ayarla
  
  // 'map' komutu ile bu iki aralığı birbirine oranlıyoruz.
  int xParlaklik = map(xDegeri, 0, 1023, 0, 255);
  int yParlaklik = map(yDegeri, 0, 1023, 0, 255);

  analogWrite(ledX, xParlaklik);
  analogWrite(ledY, yParlaklik);

  // 3. Buton LED'ini Kontrol Et
  if (butonDurumu == LOW) {       
    digitalWrite(ledButon, HIGH); // Butona basıldı, LED'i YAK
  } else {
    digitalWrite(ledButon, LOW);  // Buton serbest, LED'i SÖNDÜR
  }

  // 4. Seri Monitöre Değerleri Yazdır
  Serial.print("X Degeri: "); 
  Serial.print(xDegeri);
  Serial.print(" | Y Degeri: "); 
  Serial.print(yDegeri);
  Serial.print(" | Buton: "); 
  
  if (butonDurumu == LOW) {
    Serial.println("BASILI");
  } else {
    Serial.println("SERBEST");
  }


  delay(100); 
}