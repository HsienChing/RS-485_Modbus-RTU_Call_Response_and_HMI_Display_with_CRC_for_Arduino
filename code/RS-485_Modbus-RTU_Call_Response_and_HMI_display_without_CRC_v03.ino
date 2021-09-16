/*
  Sketch name: RS-485 Modbus-RTU call response and HMI display without CRC v03
  Suggested board: Arduino MEGA 2560 Rev3
  Purpose: 
    1. Send Modbus-RTU command to the device through RS-485 via Serial3.
    2. Get responses from the device through RS-485.
    3. Send the device responses to the human-machine interface (HMI) via Serial1.
    4. Arduino can monitor the device responses from the serial monitor.
  Additional features:
    1. The CRC is not coded for the check of value resolving.
    2. The "CODE BLOCK 1" is turned off. As it is turned on, the incoming Data_Modbus[i] will be shown on the serial monitor.
  Suggested system setup: 
    1. A "RS-485 to TTL module" is used to convert the RS-485 signal because Arduino MEGA 2560 Rev3 does not support RS-485 directly.
    2. A HMI with the UART interface is used to show the device responses through the Serial2 channel of the Arduino.
    
  Date:   6 July 2021
  Author: Dr. Hsien-Ching Chung
  ORCID:  https://orcid.org/0000-0001-9364-8858
  
  Project Link: https://github.com/HsienChing/RS-485_Modbus-RTU_Call_Response_and_HMI_Display_with_CRC_for_Arduino
  
  License: MIT License
  Copyright (c) 2021 Hsien-Ching Chung
*/

byte Command_Modbus[8] = {0x01,0x04,0x30,0x00,0x00,0x0B,0xBE,0xCD}; // Modbus-RTU Command
// [Modbus address convention]
// The usage of the Modbus address (0x3000 = 12288) in "Command_Modbus[8]" does not follow the traditional Modbus address convention.
// Convention: discrete input numbers (1 bit (off/on), 0 or 1) start with 1 and span from 10001 to 19999.
// The users are suggested to design the system following the address convention (or following the device's address convention).
// Ref: https://en.wikipedia.org/wiki/Modbus

byte Data_Modbus[27];                                               // Modbus-RTU Data

// Device responses to Command_Modbus
int   VAC_out;
float VAC_out_f;
int   V_Batt;
float V_Batt_f;
int   Load_percent; 
int   Load_power;

byte EndHex[3] = {0xFF,0xFF,0xFF}; // End command for HMI

void setup() {
  Serial. begin(115200);  // Serial  for Arduino serial monitor
  Serial3.begin(  9600);  // Serial3 for RS-485 to TTL
  Serial1.begin(115200);  // Serial1 for HMI with UART interface
}

void loop() {
  establishContact1();  // Send a byte to establish contact until receiver responds

  if (Serial3.available() > 0 ) {

    for (int i = 0; i < 27; i++)
    {
      Data_Modbus[i] = Serial3.read(); // Get incoming data
    }

//  //----------CODE BLOCK 1----------
//  // Show the Incoming Data_Modbus[i] byte array on the serial monitor
//  Serial.println("Incoming Data_Modbus[i]:");
//  for (int i = 0; i < 27; i++) // 
//  {
//    Serial.print("Data_Modbus[");
//    Serial.print(i);
//    Serial.print("] = 0x");
//    Serial.println(Data_Modbus[i], HEX);
//  }
//  //--------------------------------

    // Combine/Merge two bytes into one
    // uint16_t value = (highByte << 8) | lowByte ;
    uint16_t value = (Data_Modbus[5] << 8) | Data_Modbus[6] ;
    VAC_out = value; 
    VAC_out_f = float(value) / 10.0;  // Resolve the value

    Serial.print("VAC_out(V):");      // Show the value on the serial monitor
    Serial.println(VAC_out_f); 

    Serial1.print("x1.val=");         // Send device response to HMI
    Serial1.print(VAC_out);
    Serial1.write(EndHex,3);


    value = (Data_Modbus[7] << 8) | Data_Modbus[8] ;
    V_Batt = value;
    V_Batt_f = float(value) / 10.0;   // Resolve the value
    
    Serial.print("V_Batt(V):");       // Show the value on the serial monitor
    Serial.println(V_Batt_f); 

    Serial1.print("x0.val=");         // Send device response to HMI
    Serial1.print(V_Batt);
    Serial1.write(EndHex,3);


    Load_percent = Data_Modbus[12];   // Resolve the value
    
    Serial.print("Load_percent(%):"); // Show the value on the serial monitor
    Serial.println(Load_percent); 

    Serial1.print("n0.val=");         // Send device response to HMI
    Serial1.print(Load_percent);
    Serial1.write(EndHex,3);


    value = (Data_Modbus[13] << 8) | Data_Modbus[14] ;
    Load_power = value;               // Resolve the value
    
    Serial.print("Load_power(W):");   // Show the value on the serial monitor
    Serial.println(Load_power); 

    int HMI_Pointer = map(Load_power, 0, 2000, 0, 240); // map(value, fromLow, fromHigh, toLow, toHigh)

    Serial1.print("z0.val=");         // Send device response to HMI
    Serial1.print(HMI_Pointer);
    Serial1.write(EndHex,3);


    Serial3.flush(); // flush buffer
  }

}

void establishContact1() {
  while (Serial3.available() <= 0) {
    Serial3.write(Command_Modbus,8);  // Send the command
    //Serial1.flush();
    delay(50);
  }
}
