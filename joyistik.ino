// Joystick Pinleri
const int pinX = A0; 
const int pinY = A1; 
const int pinButon = 2; 

void setup() {
  // Saniyede 9600 bit hızında seri iletişimi başlat
  Serial.begin(9600);
  
  // Buton pini için Arduino'nun içindeki pull-up direncini kullan
  pinMode(pinButon, INPUT_PULLUP); 
}

void loop() {
  // Eksen değerlerini oku (0 ile 1023 arasında)
  int xDegeri = analogRead(pinX); 
  int yDegeri = analogRead(pinY); 
  
  // Buton durumunu oku (Basılı: 0, Serbest: 1)
  int butonDurumu = digitalRead(pinButon); 

  // Değerleri Seri Monitör'e yan yana yazdır
  Serial.print("X: "); 
  Serial.print(xDegeri);
  
  Serial.print(" | Y: "); 
  Serial.print(yDegeri);
  
  Serial.print(" | Buton: "); 
  // Butona basıldığında GND'ye çekildiği için LOW (0) değeri okunur
  if (butonDurumu == LOW) {
    Serial.println("BASILI (0)");
  } else {
    Serial.println("SERBEST (1)");
  }

  
  delay(100); 
}