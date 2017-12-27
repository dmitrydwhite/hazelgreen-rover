#include <SoftwareSerial.h>

SoftwareSerial ublxGPS(1, 8);

bool first_loop_exec;
bool message_started = false;
char GPS_info_char;
char GPS_info_buffer[128];
int received_char;


void setup() {
  // Open serial communications and wait for Serial port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Connected to Dmitry & Alex's awesome GPS!");

  // Open serial communications with the GPS device:
  ublxGPS.begin(9600);

  // Use the native method to allow an interrupt on Pin 1 (== interrupt vector 0, first arg passed) when we get a CHANGE event on that pin.
  attachInterrupt(0, messageFromGPS, CHANGE);
  first_loop_exec = true;
}

void loop() {
  // Code in this if block initializes the GPS unit
  if (first_loop_exec == true){
    delay(2000);
    ublxGPS.println(F("$PUBX,40,RMC,0,0,0,0*47")); //RMC OFF
    delay(100);
    ublxGPS.println(F("$PUBX,40,VTG,0,0,0,0*5E")); //VTG OFF
    delay(100);
    ublxGPS.println(F("$PUBX,40,GGA,0,0,0,0*5A")); //CGA OFF
    delay(100);
    ublxGPS.println(F("$PUBX,40,GSA,0,0,0,0*4E")); //GSA OFF
    delay(100);
    ublxGPS.println(F("$PUBX,40,GSV,0,0,0,0*59")); //GSV OFF
    delay(100);
    ublxGPS.println(F("$PUBX,40,GLL,0,0,0,0*5C")); //GLL OFF
    delay(1000);
    first_loop_exec = false;
    Serial.println("Handshake and Configuration Done.");
  }

  // Only request info from the GPS unit if we're not in the midst of receiving data from it
  if (message_started == false) {
    Serial.println("Asking GPS for data");
    ublxGPS.println("$PUBX,00*33"); // This is the message to send to the GPS requesting position info.
  }

  // Our request interval is 5 seconds.
  delay(5000);
}

void messageFromGPS() {
  // MANAGES THE CHARACTERS RECEIVED BY GPS
  while (ublxGPS.available()) {
    GPS_info_char=ublxGPS.read();
    
    if (GPS_info_char == '$'){ // start of message
      Serial.print("Received from GPS:");
      message_started=true;
      received_char=0;
    } else if (GPS_info_char == '*'){ // end of message
      Serial.println("Determining Sector:");
      
      for (int i=0; i<received_char; i++){
        Serial.write(GPS_info_buffer[i]); // writes the message to the PC once it has been completely received
      }

      Serial.println();
      message_started=false; // ready for the new message
    } else if (message_started==true) { // the message is already started and I got a new character
      Serial.print(GPS_info_char);
      if (received_char<=128){ // to avoid buffer overflow
        GPS_info_buffer[received_char]=GPS_info_char;
        received_char++;
      }else{ // resets everything (overflow happened)
        Serial.println("We had an overflow");
        message_started=false;
        received_char=0;
      }
    }
  }
}

