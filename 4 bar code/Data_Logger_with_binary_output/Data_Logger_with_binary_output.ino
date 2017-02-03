
const int chipSelect = 53;
/*

 * SD card attached to SPI bus as follows:
 ** MOSI - pin 51 (interconnected to pin 11)
 ** MISO - pin 50 (interconnected to pin 12)
 ** CLK - pin 52 (interconnected to pin 13)
 ** CS - pin 53 (leave unconnected)
 
 This code was created 3/20/13
 by Benjamin Brandwin
 
 This code is designed to work with an arduino mega 2560 micro-controller and a 16 bit binary counter. The counter
 has been built to output two 8 bit binary numbers to the arduino mega's 'A' and 'C' port registers. The counter 
 counts pulses from an external source (in our case gamma-gamma coincidences) and the arduino counts time intervals.
 Once the desired (user selected) time interval has been reached, the arduino records the current value at the 
 port registers and recods the count and the time in milliseconds to a text file on an external SD memory card.
 The circuit board also contains two buttons. One of these is a save switch which MUST BE PRESSED before the unit 
 is turned off in order to preserve data. A Serial output, as well as a vibration feedback confirms that the save 
 has occured. A second button works as a test button. When the external output is removed, the test button should 
 advance the count by one (although there will be some bounce as no debounce has been built in). All together 
 there are 6 + 16 connections.  6 make up the control scheme, and 16 for the binary input. 
 The remaining 6 are: 5V, Gnd, Test Signal, Clear, Save, and vibration feedback.
 
 */
 
#include <SdFat.h>
SdFat sd;
SdFile myFile;


const int testPin = 42;  //test signal  
const int clearPin = 43;  //clear signal
const int switchPin = 7; //save button
const int beep = 6; // beep feedback
const char* file_name = "dat1.txt"; // enter desired file name "HERE.txt"

long interval = 1000; // counting interval in milliseconds
unsigned long previousMillis = 0; // holds previous time a count was saved

unsigned long currentMillis = 0; //holds current time value.


int lastSwitchState = LOW;  // switching varibale for saving


long time; // holds current time of save
int minute; // holds integer minute value
int second; //holds integer second value left over after minute
int mils; // hols integer millisecond value left over after seconds

long ones; //holds first binary number
long Two56; // holds second binary number (mulitiplied by 256)
long num; // holds total binary number

int i = 0; // counting interval

void setup() {
  
   DDRA = B00000000; // Initialize port A (pins 22 - 29) as inputs
   DDRC = B00000000; // Initialze port C (pins 37 - 30) as inputs
   
   // Initialize pins as inputs or outputs
   pinMode(clearPin, OUTPUT); 
   pinMode(beep, OUTPUT);
   pinMode(testPin, OUTPUT);
   pinMode(switchPin, INPUT);
   
   // Set pins, initial conditions including initial count clear
   
   digitalWrite(beep, LOW);
 
   digitalWrite(switchPin,HIGH);
   
   // Start the serial moniter at 115200 baud
   Serial.begin(115200);

  // Start sd card. return error if failed
  if (!sd.begin(chipSelect, SPI_FULL_SPEED)) sd.initErrorHalt();

  // open the file for write at end like the Native SD library
  if (!myFile.open(file_name, O_RDWR | O_CREAT | O_AT_END)) {
    sd.errorHalt("opening for write failed");
  }
  else {
    Serial.println("Open Sucesful");
  }
  
    digitalWrite(clearPin, HIGH);
   digitalWrite(clearPin, LOW);
}

void loop() {
  
  // this is a test signal sent to the counter through testPin (pin 42).
   digitalWrite(testPin, LOW);
   digitalWrite(testPin, HIGH);
    delay(1); /* adjust this delay higher or lower to test the counter for the proper counting condition
     Values of 100 - 1000 will allow a visual test the first 8 bits and values of
    1 - 20 will allow a visual test of the next 8 bits */
    
  
  
  int Switch = digitalRead(switchPin);
  
  // if the save switch is pressed do the following:
  
  if (Switch != lastSwitchState) {
    if (Switch == LOW) {
      
      // close the file to save
      if (!myFile.close()) {
        Serial.println("Save Failed");
      }
        else {
      Serial.println("Save Succesful");
      
      // beep once for succesful save (useful if serial moniter is not available)
      digitalWrite(beep, HIGH);
      delay(100);
      digitalWrite(beep, LOW);
    
      
        }
        
        // reopen the file
      if (!myFile.open(file_name, O_RDWR | O_CREAT | O_AT_END)) {
    sd.errorHalt("opening for write failed");
  }
   else {
     
      
      
      
      /* --------------------   if the file reopens succsfully print in that the Save was succesful-----------
      ------------------------------           and the time of the save           ------------------------------
      */
      
      
      myFile.print("SAVE SUCCESFUL  "); 
      Serial.print("OPEN SUCCESFUL  ");
      time = millis();
      minute = time/60000; // integer value will cut off remainder
      second = (time % 60000)/1000; // modulus will take the integer remainder for second
      mils = (time % 1000); // modulus again will take the integer remainder for miliseconds
      myFile.print(minute);
      Serial.print(minute);
      myFile.print(":");
      Serial.print(":");
      if (second < 10 ) {
        myFile.print("0");
        Serial.print("0");
      }
      myFile.print(second);
      Serial.print(second);
      myFile.print(":");
      Serial.print(":");
      if (mils < 10) {
        myFile.print("00");
        Serial.print("00");
      }
      else if (mils < 100 && mils >=10) {
        myFile.print("0");
        Serial.print("0");
      }
      myFile.println(mils);
      Serial.println(mils);
      
      myFile.close(); // reclose the file to save the timestamp 
      if (!myFile.open(file_name, O_RDWR | O_CREAT | O_AT_END)) {
    sd.errorHalt("opening for write failed");
      }
      else {
        delay(50);
      digitalWrite(beep, HIGH); // beep a second time for a succesful reopening
      delay(100);
      digitalWrite(beep, LOW);
      }
    
  }
  digitalWrite(clearPin, HIGH); // clear the counter to begin a new count cycle
    digitalWrite(clearPin, LOW);
  previousMillis = millis(); // reset the count cycle 
    }
    
  }
  
  // Reset the switch state
  lastSwitchState = Switch;
    
   ones = PINA; // save the first 8 bits
   Two56 = PINC; // save the second 8 bits
   Two56 = Two56*256; // multiply the second 8 bits by 256
   num = ones + Two56; // total count
   
   
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = millis();
    
   
   
    digitalWrite(clearPin, HIGH); // clear the counter to begin a new count cycle
    digitalWrite(clearPin, LOW);
  
   Serial.print(i); // print interval numnber to Serial Moniter
   Serial.print(" "); 
   Serial.print(num); //print count to serial moniter
   Serial.print(" ");
   Serial.println(currentMillis); //print time in ms to serial moniter
   
   // repeat print to SD card file
   myFile.print(i);
   myFile.print(" ");
  myFile.print(num);
  myFile.print(" ");
  myFile.println(currentMillis);

  i = i + 1; //advance count interval by 1
   
  }
}
    
    
