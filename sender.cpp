#define laserpin 2

int incomingByte = 0;
int sendInterval = 50;


void setup()
{

  pinMode(laserpin,OUTPUT);
  digitalWrite(laserpin,HIGH);
  delay(1000);
  digitalWrite(laserpin,LOW);
  Serial.begin(115200);
}

void loop() {
  int phrase[8];
  // check if data is available
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    for (int i = 7; i >= 0;i--){

        phrase[i] = bitRead(incomingByte,i);

    }
    // prints the received data
    
    Serial.print("Phrase:");
    for (int i = 7; i >= 0; i--) {
      Serial.print(String(phrase[i]));
    }
    Serial.println("");


    // Send a signal to start listening
    Serial.println("Sending start signal...");
    digitalWrite(laserpin,HIGH);
    delay(10);
    digitalWrite(laserpin,LOW);
    delay(80);
    // Send data through laser.
    for (int i = 7; i>= 0; i--) {
      if (phrase[i] == 1) digitalWrite(laserpin,HIGH);
      else digitalWrite(laserpin,LOW);
      delay(sendInterval);
      digitalWrite(laserpin,LOW);
    }
    delay(1000);
  }
}
    
