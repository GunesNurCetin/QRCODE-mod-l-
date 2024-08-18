String inputString = "";      // Tarayıcıdan gelen veriyi saklamak için değişken
String DataScanner = "";      // Veriyi işlemek için kullanılan değişken
bool stringComplete = false;  // Verinin tam olarak alınıp alınmadığını kontrol eden değişken

void setup() {
    pinMode(8, OUTPUT); // Tarayıcıyı çalıştırmak için kullanılan port
    // Seri haberleşmeyi başlat:
    Serial.begin(9600);
    while (!Serial) {
        ; // Seri portun bağlanmasını bekle. Sadece yerel USB portu için gerekli
    }
    // 200 karakterlik bir mesaj saklamak için değişkeni tanımla
    inputString.reserve(200);
}

void loop() {
    digitalWrite(8, HIGH);   // Yüksek lojik değeri gönder
    delay(200);              // 200 milisaniye bekle
    digitalWrite(8, LOW);    // Düşük lojik değeri gönder, bu bir anahtara basmak gibi tarayıcıyı çalıştırır
    delay(200);              // 200 milisaniye bekle
  
    // Tarayıcıdan veri alınıp alınmadığını kontrol et
    if (stringComplete) {
        
        if (DataScanner == "8859411300023\r\n") // Veri belirlenenle eşleşirse "OK" mesajını göster
        {
            Serial.println("OK");
            delay(1000); 
        }   
        else Serial.println("No Data"); // Veri eşleşmezse "No Data" mesajını göster
            
        // Yeni veri için değişkenleri temizle
        inputString = "";
        DataScanner = "";
        stringComplete = false;
    }
}

/*
  SerialEvent, donanım seri portunun RX hattına yeni veri geldiğinde gerçekleşir.
  Bu rutin, loop() her çalıştığında araya girer, bu nedenle loop içindeki delay
  komutu yanıt süresini geciktirebilir. Birden fazla bayt veri mevcut olabilir.
*/

void serialEvent() {
    while (Serial.available()) {
        // Yeni baytı al:
        char inChar = (char)Serial.read();
        // inputString'e ekle:
        inputString += inChar;
        // Okunan her karakteri anında ekrana yazdır:
        Serial.print(inChar);  
        // Gelen karakter yeni bir satırsa, ana döngünün bu veriyle ilgili bir şey yapması için bir bayrak ayarla:
        if (inChar == '\n') {
            stringComplete = true;
            DataScanner = String(inputString);
        }
    }
}
