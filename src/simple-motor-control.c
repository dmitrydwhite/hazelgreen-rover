int motorA = 2; // Digital pin for direction control
int motorB = 3; // Digital pin for direction control
int enableA = 5; // Analog pin for motor rate

/**
 * Set our pins to their correct mode and function:
 */
void setup() {
	pinMode(motorA, OUTPUT);
	pinMode(motorB, OUTPUT);
	pinMode(enableA, OUTPUT);
}

/**
 * Runs motor one direction for 1 second at 200, pauses for 1 second,
 * runs the other direction for 1 second, pauses for 1 second.
 * This function is super awesome.
 */
void loop() {
	digitalWrite(motorA, LOW);
	digitalWrite(motorB, HIGH);
	analogWrite(enableA, 200);
	delay(1000);

	digitalWrite(motorA, LOW);
	digitalWrite(motorB, LOW); //Here is my change
	analogWrite(enableA, 0);
	delay(1000);

	digitalWrite(motorA, HIGH);
	digitalWrite(motorB, LOW);
	analogWrite(enableA, 200);
	delay(1000);

	digitalWrite(motorA, LOW);
	digitalWrite(motorB, LOW);
	analogWrite(enableA, 0);
	delay(1000);
}
