#define countPin 2
#define dirPin 3
#define resetCounterPin 5
#define BACK 0
#define FORWARD 1

bool DIRECTION = BACK;

int forCounter = 0; //counter for measuring length
int backCounter = 0;

const int ledPin = 13; // blinking led pin
bool ledState = 0;
unsigned long previousMillis = 0;
const int blinkONInterval = 100;
const int blinkOFFInterval = 2000;

void setup(){
	Serial.begin(115200);
	pinMode(ledPin, OUTPUT);

	pinMode(countPin, INPUT);
	pinMode(dirPin, INPUT);
	attachInterrupt(countPin, countTeeth, RISING);
	// attachInterrupt(dirPin, chkDirection, FALLING);
}

void loop(){
	blink();
}
// counts the teeth in only one direction
// if the wheel goes into the other direction, it counts the backward
// steps but not the forward.... so it should maintain the right position
void countTeeth (){
	if (chkDirection()) {
		if(backCounter > 0) { // TODO one step is counted TWO times....need to fix
			backCounter--;
		} else {
			forCounter++;
		}
	} else {
		backCounter++;
	}
	Serial.print(backCounter);
  Serial.print(" : ");
  Serial.println(forCounter);
}

bool chkDirection (){
	if (digitalRead(dirPin)==DIRECTION) {
		return FORWARD;
	} else {
		return BACK;
	}
}

void blink(){
	unsigned long currentMillis = millis();

	if(ledState == 0) {
		if (currentMillis - previousMillis >= blinkOFFInterval) {
			previousMillis = currentMillis;
			ledState = 1;
		}
	} else {
		if(currentMillis - previousMillis >= blinkONInterval) {
			previousMillis = currentMillis;
			ledState = 0;
		}
	}

	// set the LED with the ledState of the variable:
	digitalWrite(ledPin, ledState);

}
