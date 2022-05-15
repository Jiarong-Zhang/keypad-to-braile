
#include <Keypad.h>

// setup parameters for the keypad
const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'F','0','E','D'}
};
byte rowPins[rows] = {11, 10, 9, 8}; // the I/O pins used for the row connections
byte colPins[cols] = {17, 16, 15, 14}; //the I/O pins used for the column connections

// braille code 
// braille[0] corresponds to ASCII 0x20
// braille[1] corresponds to ASCII 0x21...
char braille[64] = {0b000000, 0b011011, 0b000100, 0b010111, 0b111001, 0b110001, 0b111011, 0b000010, 
                    0b101111, 0b011111, 0b100001, 0b010011, 0b000001, 0b000011, 0b010001, 0b010010, 
                    0b000111, 0b001000, 0b001010, 0b001100, 0b001101, 0b001001, 0b001110, 0b001111, 
                    0b001011, 0b000110, 0b100101, 0b000101, 0b101001, 0b111111, 0b010110, 0b110101, 
                    0b010000, 0b100000, 0b101000, 0b110000, 0b110100, 0b100100, 0b111000, 0b111100, 
                    0b101100, 0b011000, 0b011100, 0b100010, 0b101010, 0b110010, 0b110110, 0b100110, 
                    0b111010, 0b111110, 0b101110, 0b011010, 0b011110, 0b100011, 0b101011, 0b011101, 
                    0b110011, 0b110111, 0b100111, 0b011001, 0b101101, 0b111101, 0b010100, 0b010101};

// initialize the keypad library
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

// this function runs once when the Arduino boots
void setup() {
  // also initialise ther serial port (useful for debugging)
  Serial.begin(9600);
  Serial.println("system initialised");
  // set up the LED ports
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  
  PORTD = braille[62]<<2;
  
  //reset lights 
   digitalWrite(7, LOW);
   digitalWrite(6, LOW);
   digitalWrite(5, LOW);
   digitalWrite(4, LOW);
   digitalWrite(3, LOW);
   digitalWrite(2, LOW);
  

}

void loop() {
  //a1793769 Digital Electronics S2 2020

  char key1;
  char key2;
  int count = 1;
  bool stat;
  int working;
  int check[6] = {0};
  int checkCount = 0;
  
  
  //receive first input
  while(count == 1){
    key1 = keypad.getKey(); // check if a key has been pressed
    
    if(key1 != NO_KEY){
      Serial.println(key1); // also output it on the serial port
      count++;
      break;
    }
  }
  
  //recieve second input
  while(count == 2){
    key2 = keypad.getKey(); // check if a key has been pressed
    
    if(key2 != NO_KEY){
      Serial.println(key2); // also output it on the serial port
      break;
    }
  }
  
  
  //reset lights 
   digitalWrite(7, LOW);
   digitalWrite(6, LOW);
   digitalWrite(5, LOW);
   digitalWrite(4, LOW);
   digitalWrite(3, LOW);
   digitalWrite(2, LOW);
  
  //read first input
  switch(key1){
    case '2':
    working = 0;
    break;
    
    case '3':
    working = 16;
    break;
    
    case '4':
    working = 32;
    break;
    
    case '5':
    working = 48;
    break;
    
  }
  
  //read second input
  switch(key2){
  
    case '0':
    working = working + 0;
    break;
    
    case '1':
    working = working + 1;
    break;

    case '2':
    working = working + 2;
    break;

    case '3':
    working = working + 3;
    break;

    case '4':
    working = working + 4;
    break;

    case '5':
    working = working + 5;
    break;

    case '6':
    working = working + 6;
    break;

    case '7':
    working = working + 7;
    break;
    
    case '8':
    working = working + 8;
    break;

    case '9':
    working = working + 9;
    break;

    case 'A':
    working = working + 10;
    break;

    case 'B':
    working = working + 11;
    break;

    case 'C':
    working = working + 12;
    break;

    case 'D':
    working = working + 13;
    break;

    case 'E':
    working = working + 14;
    break;

    case 'F':
    working = working + 15;
    break;

  }
  
  //copy binary digits into array
  for (int i = 5; i > -1; i--){
    check[checkCount] = bitRead(braille[working], i);
    Serial.println(check[checkCount]);       //send to serial just to check
    checkCount++;
  }

  //turn lights on
  for(int i = 7; i > 1; i--){
    if(check[7 - i] == 1){
      digitalWrite(i, HIGH);
    }
  }
  
}

  
