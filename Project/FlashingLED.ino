
const int ledPin =  13;   
const int ledPin2 = 8;   
const int ledPin3 = 2;    

int ledState = LOW;            

unsigned long previousMillis = 0;        

const long interval = 50;           

void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
}

void loop() {
 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin2, ledState);
    digitalWrite(ledPin, ledState);
    digitalWrite(ledPin3, ledState);
  }
}
