  const int motorA1  = 5;// L298N'in IN3 Girişi
  const int motorA2  = 6;  // L298N'in IN1 Girişi
  const int motorB1  = 10; // L298N'in IN2 Girişideğişkeni
  const int motorB2  = 9;  // L298N'in IN4 Girişi
  const int trigPinon = 3;
  const int echoPinon = 2;
  const int trigPinarka = 11;
  const int echoPinarka = 12; 
  const int buzzer = 4;
  long frontduration;
  int frontdistance;
  long behindduration;
  int behinddistance;
  int rascontrolc;
  int rascontrolq;
    // Pinlerimizi belirleyelim
  int referencelength;
  int arkasayar;
  int onsayar;
    int i=0; //Döngüler için atanan rastgele bir değişken
    int j=0; //Döngüler için atanan rastgele bir değişken
    int state; //Bluetooth cihazından gelecek sinyalin 
    int vSpeed=255;     // Standart Hız, 0-255 arası bir değer alabilir
   
void setup() { 
    pinMode(buzzer, OUTPUT); 
    pinMode(trigPinon, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPinon, INPUT); // Sets the echoPin as an Input
    pinMode(trigPinarka, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPinarka, INPUT); // Sets the echoPin as an Input
   pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);    
    Serial.begin(9600); 
}
 
void loop() 
{

// Code for Front Ultrasonic sensor
if(arkasayar<5)
{
  arkasayar++;
 digitalWrite(trigPinarka, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPinarka, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinon, LOW);
 behindduration = pulseIn(echoPinarka, HIGH);
 behinddistance= behindduration*0.034/2;
 behinddistance = behinddistance % 1000;
 if(behinddistance < 30)
 {
   tone(buzzer, 1000); // Send 1KHz sound signal...
   delay(20);
   noTone(buzzer);     // Stop sound...
  } 
 if(arkasayar = 5 )
 {
  arkasayar= 0;
  }
  }

  if(onsayar<5)
  {
    onsayar++; 
  // Clears the trigPin
 digitalWrite(trigPinon, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPinon, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinon, LOW);
 frontduration = pulseIn(echoPinon, HIGH);
 frontdistance= frontduration*0.034/2;
 frontdistance = frontdistance % 1000;
 if(frontdistance < 30)
 {
   tone(buzzer, 1000); // Send 1KHz sound signal...
   delay(20);
   noTone(buzzer);     // Stop sound...
  }
 if(onsayar = 5)
 {
  onsayar = 0 ;
  }
    }


  /*Bluetooth bağlantısı koptuğunda veya kesildiğinde arabayı durdur.
 (Aktif etmek için alt satırın "//" larını kaldırın.)*/
//     if(digitalRead(BTState)==LOW) { state='S'; }

  //Gelen veriyi 'state' değişkenine kaydet
    
    if(Serial.available() > 0){     
      state =Serial.read();  
      Serial.write(state);  
    }
 

    if(state == 'Q')
       rascontrolq = state ;

    if (state == '0'){
      vSpeed=150;}
    else if (state == '1'){
      vSpeed=150;}
    else if (state == '2'){
      vSpeed=150;}
    else if (state == '3'){
      vSpeed=150;}
    else if (state == '4'){
      vSpeed=150;}
    else if (state == '5'){
      vSpeed=250;}
    else if (state == '6'){
      vSpeed=250;}
    else if (state == '7'){
      vSpeed=250;}
    else if (state == '8'){
      vSpeed=250;}
    else if (state == '9'){
      vSpeed=250;}
      
  /***********************İleri****************************/
  //Gelen veri 'F' ise araba ileri gider.
    if (state == 'F') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
    }
  /**********************İleri Sol************************/
  //Gelen veri 'G' ise araba ileri sol(çapraz) gider.
    else if (state == 'G') {
      analogWrite(motorA1,vSpeed ); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 100);    analogWrite(motorB2, 0); 
    }
  /**********************İleri Sağ************************/
  //Gelen veri 'I' ise araba ileri sağ(çapraz) gider.
    else if (state == 'I') {
        analogWrite(motorA1, 100); analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
      
    }
  /***********************Geri****************************/
  //Gelen veri 'B' ise araba geri gider.
    else if (state == 'B') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, vSpeed); 
    }
  /**********************Geri Sol************************/
  //Gelen veri 'H' ise araba geri sol(çapraz) gider
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 100); 
        analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  /**********************Geri Sağ************************/
  //Gelen veri 'J' ise araba geri sağ(çapraz) gider
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 100); 
    }
  /***************************Sol*****************************/
  //Gelen veri 'L' ise araba sola gider.
    else if (state == 'L') {
      analogWrite(motorA1, vSpeed);   analogWrite(motorA2, 150); 
        analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
    }
  /***************************Sağ*****************************/
  //Gelen veri 'R' ise araba sağa gider
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);   analogWrite(motorB2, 150);     
    }
  
  /************************Stop*****************************/
  //Gelen veri 'S' ise arabayı durdur.
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }
 
    while(rascontrolq == 'Q')
    {
      state = Serial.read();

          if (state == '0'){
      vSpeed=150;}
    else if (state == '1'){
      vSpeed=150;}
    else if (state == '2'){
      vSpeed=150;}
    else if (state == '3'){
      vSpeed=150;}
    else if (state == '4'){
      vSpeed=150;}
    else if (state == '5'){
      vSpeed=250;}
    else if (state == '6'){
      vSpeed=250;}
    else if (state == '7'){
      vSpeed=250;}
    else if (state == '8'){
      vSpeed=250;}
    else if (state == '9'){
      vSpeed=250;}
      
  /***********************İleri****************************/
  //Gelen veri 'F' ise araba ileri gider.
    if (state == 'F') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
    }
  /**********************İleri Sol************************/
  //Gelen veri 'G' ise araba ileri sol(çapraz) gider.
    else if (state == 'G') {
      analogWrite(motorA1,vSpeed ); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 100);    analogWrite(motorB2, 0); 
    }
  /**********************İleri Sağ************************/
  //Gelen veri 'I' ise araba ileri sağ(çapraz) gider.
    else if (state == 'I') {
        analogWrite(motorA1, 100); analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
      
    }
  /***********************Geri****************************/
  //Gelen veri 'B' ise araba geri gider.
    else if (state == 'B') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, vSpeed); 
    }
  /**********************Geri Sol************************/
  //Gelen veri 'H' ise araba geri sol(çapraz) gider
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 100); 
        analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  /**********************Geri Sağ************************/
  //Gelen veri 'J' ise araba geri sağ(çapraz) gider
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 100); 
    }
  /***************************Sol*****************************/
  //Gelen veri 'L' ise araba sola gider.
    else if (state == 'L') {
      analogWrite(motorA1, vSpeed);   analogWrite(motorA2, 150); 
        analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
    }
  /***************************Sağ*****************************/
  //Gelen veri 'R' ise araba sağa gider
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);   analogWrite(motorB2, 150);     
    }
  
  /************************Stop*****************************/
  //Gelen veri 'S' ise arabayı durdur.
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    } 

      if(state == 'C')
      rascontrolq = state ;
      break;
      }

}
