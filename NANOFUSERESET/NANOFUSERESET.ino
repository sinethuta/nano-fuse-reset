//PIN ASSIGNMENTS

#define DATA1 1
#define DATA2 2
#define DATA3 3
#define DATA4 4
#define DATA5 5
#define DATA6 6
#define DATA7 7
#define XA0 8
#define BS2 9
#define WR 10
#define OE 11
#define VCC 12
#define RDYBSY 13

#define BJT A0
#define DATA0 A1
#define BS1 A2
#define XTAL1 A3
#define XA1 A4
#define PAGEL A5
#define DATA1 1


void setup() {
  
  PINMODE_INIT(); //initialize IN/OUT modes for reset 328p
  digitalWrite(BJT,HIGH);
  DATA_CLEAR();
  DATA_INPUT();
  
  PROG_MODE(); 
  RESET_LFUSE();
  EXIT();
  delay(10);
  
  PROG_MODE();
  RESET_HFUSE();
  EXIT();
  delay(10);
  
  PROG_MODE();
  RESET_XFUSE();
  EXIT();
  delay(10);
  
  PROG_MODE(); 
  CHIPERASE();
  EXIT();
  delay(10);


}

void loop() {
 digitalWrite(BJT,HIGH);
 DATA_CLEAR();
 DATA_INPUT();
}


void EXIT(){    //EXIT PROG MODE
   DATA_CLEAR();
   DATA_INPUT();
  digitalWrite(BJT,HIGH);
  delay(1);
  digitalWrite(OE, LOW);
  digitalWrite(WR, LOW);
  digitalWrite(PAGEL, LOW);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
  digitalWrite(VCC, LOW);
  }
void PINMODE_INIT(){  //INITIAL PIN SETUP
  pinMode(OE,OUTPUT);
  pinMode(WR,OUTPUT);
  pinMode(BS1,OUTPUT);
  pinMode(XA0,OUTPUT);
  pinMode(XA1,OUTPUT);
  pinMode(PAGEL,OUTPUT);
  pinMode(XTAL1,OUTPUT);
  pinMode(BJT,OUTPUT);
  pinMode(VCC,OUTPUT);
  pinMode(RDYBSY,INPUT);
  }
void DATA_OUTPUT(){   //MAKE ALL DATA PINS OUTPUT
  pinMode(DATA0,OUTPUT);
  pinMode(DATA1,OUTPUT);
  pinMode(DATA2,OUTPUT);
  pinMode(DATA3,OUTPUT);
  pinMode(DATA4,OUTPUT);
  pinMode(DATA5,OUTPUT);
  pinMode(DATA6,OUTPUT);
  pinMode(DATA7,OUTPUT);
  }
  
void DATA_INPUT(){  //MAKE ALL DATA PINS INPUT
  pinMode(DATA0, INPUT);
  pinMode(DATA1, INPUT);
  pinMode(DATA2, INPUT);
  pinMode(DATA3, INPUT);
  pinMode(DATA4, INPUT);
  pinMode(DATA5, INPUT);
  pinMode(DATA6, INPUT);
  pinMode(DATA7, INPUT);
  }
 void DATA_CLEAR(){ //CLEAR ALL DATA PINS
  digitalWrite(DATA0, 0);
  digitalWrite(DATA1, 0);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA3, 0);
  digitalWrite(DATA4, 0);
  digitalWrite(DATA5, 0);
  digitalWrite(DATA6, 0);
  digitalWrite(DATA7, 0);
  }
void PROG_MODE(){ //ENTER PROGRAMMING MODE
//1. Set Prog_enable to “0000”, RESET pin to 0V and VCC to 0V. 
    DATA_CLEAR();
    DATA_INPUT(); 
    digitalWrite(PAGEL,LOW);
    digitalWrite(XA1,LOW);
    digitalWrite(XA0,LOW);
    digitalWrite(BS1,LOW);
    digitalWrite(BS2,LOW);
    digitalWrite(VCC,LOW);
    digitalWrite(WR, LOW);
    digitalWrite(OE, LOW);

//2. Apply 4.5 - 5.5V between VCC and GND.
    digitalWrite(VCC, HIGH);  // Apply VCC to start programming process
//3. Wait 20-60us and apply 12V to RESET.
    delayMicroseconds(80);
    digitalWrite(BJT, LOW);   // Apply 12V to RESET 
    delay(10);
    digitalWrite(OE, HIGH);
    digitalWrite(WR, HIGH);   // disable !WR
    delay(1);
 }

void CHIPERASE(){
  digitalWrite(XA1,HIGH);
  digitalWrite(XA0,LOW); //ENABLE COMMAND LOADING
  digitalWrite(BS1,LOW);
  
  digitalWrite(DATA0, 0);
  digitalWrite(DATA1, 0);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA3, 0);
  digitalWrite(DATA4, 0);
  digitalWrite(DATA5, 0);
  digitalWrite(DATA6, 0);
  digitalWrite(DATA7, 1); //COMMAND FOR CHIP ERASE
  DATA_OUTPUT();
  XTAL1_PULSE();
  DATA_CLEAR();
  DATA_INPUT();
  delay(10);
  WR_PULSE();
  
  while (digitalRead(RDYBSY) == LOW); //CHIP ERASE PROCESS. DONE IF HIGH
  DATA_CLEAR();
  DATA_INPUT();
}

void RESET_LFUSE() {

//A:
  digitalWrite(XA1,HIGH);
  digitalWrite(XA0,LOW); //ENABLE COMMAND LOADING
  digitalWrite(BS1,LOW);

  digitalWrite(DATA0, 0);
  digitalWrite(DATA1, 0);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA3, 0);
  digitalWrite(DATA4, 0);
  digitalWrite(DATA5, 0);
  digitalWrite(DATA6, 1);
  digitalWrite(DATA7, 0); 
  DATA_OUTPUT();
    
  XTAL1_PULSE();
  DATA_CLEAR;
  DATA_INPUT;

//C:
  digitalWrite(XA1,LOW);
  digitalWrite(XA0,HIGH);
  digitalWrite(BS1, LOW);
  delay(1);
 
  digitalWrite(DATA0, 0);
  digitalWrite(DATA1, 1);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA3, 0);
  digitalWrite(DATA4, 0);
  digitalWrite(DATA5, 1);
  digitalWrite(DATA6, 1);
  digitalWrite(DATA7, 0);
  DATA_OUTPUT();
  XTAL1_PULSE();
   
  DATA_CLEAR;
  DATA_INPUT;
  WR_PULSE();
  
  while (digitalRead(RDYBSY) == LOW); //CHIP ERASE PROCESS. DONE IF HIGH
  digitalWrite(BS1, LOW);  // program LFUSE
  digitalWrite(BS2, LOW);
  // Reset control lines to original state

  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
}

void RESET_HFUSE() {

//A:
  digitalWrite(XA1,HIGH);
  digitalWrite(XA0,LOW); //ENABLE COMMAND LOADING
  digitalWrite(BS1,LOW);

  digitalWrite(DATA0, 0);
  digitalWrite(DATA1, 0);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA3, 0);
  digitalWrite(DATA4, 0);
  digitalWrite(DATA5, 0);
  digitalWrite(DATA6, 1);
  digitalWrite(DATA7, 0); 
  DATA_OUTPUT();
  
  XTAL1_PULSE();
  DATA_CLEAR;
  DATA_INPUT;

//C:
  digitalWrite(XA1,LOW);
  digitalWrite(XA0,HIGH);
  digitalWrite(BS1, LOW);
  
  digitalWrite(DATA7, 1);
  digitalWrite(DATA6, 1);
  digitalWrite(DATA5, 0);
  digitalWrite(DATA4, 1);
  digitalWrite(DATA3, 1);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA1, 0);
  digitalWrite(DATA0, 1);
  DATA_OUTPUT();
  
  XTAL1_PULSE();
  DATA_CLEAR;
  DATA_INPUT;

  digitalWrite(BS1, HIGH);
  digitalWrite(BS2, LOW);
  
  WR_PULSE();
  while (digitalRead(RDYBSY) == LOW); //CHIP ERASE PROCESS. DONE IF HIGH
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);

}

void RESET_XFUSE() {


//A:
  digitalWrite(XA1,HIGH);
  digitalWrite(XA0,LOW); //ENABLE COMMAND LOADING
  digitalWrite(BS1,LOW);

  digitalWrite(DATA0, 0);
  digitalWrite(DATA1, 0);
  digitalWrite(DATA2, 0);
  digitalWrite(DATA3, 0);
  digitalWrite(DATA4, 0);
  digitalWrite(DATA5, 0);
  digitalWrite(DATA6, 1);
  digitalWrite(DATA7, 0); 
  DATA_OUTPUT();
  
  XTAL1_PULSE();
  DATA_CLEAR;
  DATA_INPUT;

//C:
  digitalWrite(XA1,LOW);
  digitalWrite(XA0,HIGH);
  digitalWrite(BS1, LOW);
  
  digitalWrite(DATA0, 1);
  digitalWrite(DATA1, 1);
  digitalWrite(DATA2, 1);
  digitalWrite(DATA3, 1);
  digitalWrite(DATA4, 1);
  digitalWrite(DATA5, 1);
  digitalWrite(DATA6, 1);
  digitalWrite(DATA7, 1);
  DATA_OUTPUT();
  
  XTAL1_PULSE();
  DATA_CLEAR;
  DATA_INPUT;

  digitalWrite(BS1, LOW);
  digitalWrite(BS2, HIGH);
  
  WR_PULSE();
  while (digitalRead(RDYBSY) == LOW); //CHIP ERASE PROCESS. DONE IF HIGH
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
}


void XTAL1_PULSE() {  // Positive PULSE on XTAL1
  delay(10);
  digitalWrite(XTAL1,HIGH);
  delay(10);
  digitalWrite(XTAL1,LOW);
}

void WR_PULSE(){  // Negative PULSE on WR
  delay(1);
  digitalWrite(WR,LOW);
  delay(1);
  digitalWrite(WR,HIGH);
}
