int motor_LA = 2; // Digital pin for left motor direction control
int motor_LB = 3; // Digital pin for left motor direction control
int motor_RA = 6; // Digital pin for right motor direction control
int motor_RB = 7; //Digital pin for right motor direction control
int enableL = 5; // Analog pin for left motor rate
int enableR = 7; // Analog pin for right motor rate


/**
 * Set our pins to their correct mode and function:
 */
void setup() {
	pinMode(motor_LA, OUTPUT);/*Set all of our left motor pins as outputs*/
	pinMode(motor_LB, OUTPUT);
	pinMode(enableL, OUTPUT);

	pinMode(motor_RA, OUTPUT);/*Set all of our right motor pins as outputs*/
	pinMode(motor_RB, OUTPUT);
	pinMode(enableR, OUTPUT);
}

/**
 * Runs motor one direction for 1 second at 200, pauses for 1 second,
 * runs the other direction for 1 second, pauses for 1 second.
 * This function is super awesome.
 */
void loop()
{
rover_forward();
rover_left();
rover_reverse();
rover_right();
}

void rover_forward(void) // move the rover forward for 5 seconds before stopping
{
    digitalWrite(motor_LA, HIGH); //Set the left motor to 85% of max power in
    digitalWrite(motor_LB, LOW); //forward direction. May take switching the
    analogWrite(enableL, 215); // digital pins to actually go forward

    digitalWrite(motor_RA, LOW); // Set the right motor to 85% of max power
    digtalWrite(motor_RB, HIGH);
    analogWrite(enableR, 215);

    delay(5000);
    analogWrite(enableL, 0);
    analogWrite(enableR, 0);
}

void rover_reverse(void) //drive rover in reverse for 5 seconds then stop
{

    digitalWrite(motor_LA, LOW); //Set the left motor to 85% of max power in
    digitalWrite(motor_LB, HIGH); //reverse direction. May take switching the
    analogWrite(enableL, 215); // digital pins to actually go forward

    digitalWrite(motor_RA, HIGH); // Set the right motor to 85% of max power
    digtalWrite(motor_RB, LOW);
    analogWrite(enableR, 215);

    delay(5000);
    analogWrite(enableL, 0);
    analogWrite(enableR, 0);
}
/** We are going to have to find how long
*** to run this for a certain angle.
*** then we can write a function for each
*** angle that's needed.
*/
void rover_left(void)
{
    digitalWrite(motor_LA, LOW); //Set the left motors to LOW
    digitalWrite(motor_LB, LOW);
    analogWrite(enableL, 0);

    digitalWrite(motor_RA, HIGH); // Set the right motor to 85% of max power
    digtalWrite(motor_RB, LOW); // for 1 second, this should turn the bot to the left
    analogWrite(enableR, 215);

    delay(1000);
    analogWrite(enableL, 0);
    analogWrite(enableR, 0);
}

void rover_right(void)
{
    digitalWrite(motor_LA, HIGH); //Set the right motor to 85% max power
    digitalWrite(motor_LB, LOW);  // for 1 second, this should turn the bot right
    analogWrite(enableL, 215);

    digitalWrite(motor_RA, LOW); //Set the right motors to LOW
    digtalWrite(motor_RB, LOW);
    analogWrite(enableR, 0);

    delay(1000);
    analogWrite(enableL, 0);
    analogWrite(enableR, 0);
}
