/*
  Sketch name: RS-485 Modbus-RTU call response and HMI display with CRC
  Suggested board: Arduino MEGA 2560 Rev3
  Purpose: 
    1. Send Modbus-RTU command to the device through RS-485 via the assigned "RS485_Serial."
    2. Get responses from the device through RS-485.
    3. Send the device responses to the human-machine interface (HMI) via the assigned "HMI_Serial."
    4. Arduino can monitor the device responses from the serial monitor.
  Additional features:
    1. The cyclic redundancy check (CRC) is coded for the check of receiving data.
    2. The function "Show_DataModbus()" is turned off. As it is turned on, the incoming Data_Modbus.Array[i] will be shown on the serial monitor.
  Suggested system setup: 
    1. A "RS-485 to TTL module" is used to convert the RS-485 signal because Arduino MEGA 2560 Rev3 does not support RS-485 directly.
    2. A HMI with the UART interface is used to show the device responses through the assigned HMI_Serial channel of the Arduino.
    
  Date:   8 July 2021
  Author: Dr. Hsien-Ching Chung
  ORCID:  https://orcid.org/0000-0001-9364-8858
*/

#include "CRC16.h" // CRC library from Rob Tillaart
#include "CRC.h"   // Ref: https://github.com/RobTillaart/CRC

#define HMI_Serial   Serial1 // Assign serial port
#define RS485_Serial Serial3 // Assign serial port
// The example program about the assigned serial can be found in the Ref.
// Ref: https://github.com/HsienChing/Example_Code_Arduino/blob/main/code/Serial_Passthrough_by_the_Assigned_Serial.ino

// Modbus-RTU Command
byte Command_Modbus[8] = {0x01,0x04,0x30,0x00,0x00,0x0B,0xBE,0xCD}; 

// Modbus-RTU Data
struct ByteArray { 
  byte Array[27];  
} Data_Modbus;
// A structure type is a user-defined composite type. 
// It is composed of fields or members that can have different types. 
// It enables the programmer to create a variable that structures a selected set of data.

// Device responses to Command_Modbus
int   VAC_out;
float VAC_out_f;
int   V_Batt;
float V_Batt_f;
int   Load_percent; 
int   Load_power;

byte EndHex[3] = {0xFF,0xFF,0xFF}; // End command for HMI

void setup() {
  Serial.      begin(115200);  // Serial setting for the Arduino serial monitor
  RS485_Serial.begin(  9600);  // Serial setting for the RS-485 to TTL
  HMI_Serial.  begin(115200);  // Serial setting for the HMI with the UART interface
}

void loop() {
  establishContact1();  // Send a byte to establish contact until receiver responds

  int DataSize = sizeof(Data_Modbus.Array);

  if ( RS485_Serial.available() > 0 ) {

    for (int i = 0; i < DataSize; i++)
    {
      Data_Modbus.Array[i] = RS485_Serial.read(); // Get incoming data
    }

//    //---------------------------
//    Show_DataModbus(Data_Modbus);
//    //---------------------------

    if ( CRC_comparison(Data_Modbus) ) {

      // Combine/Merge two bytes into one
      // uint16_t value = (highByte << 8) | lowByte ;
      uint16_t value = (Data_Modbus.Array[5] << 8) | Data_Modbus.Array[6] ;
      VAC_out = value; 
      VAC_out_f = float(value) / 10.0;  // Resolve the value

      Serial.print("VAC_out(V):");      // Show the value on the serial monitor
      Serial.println(VAC_out_f); 

      HMI_Serial.print("x1.val=");      // Send device response to HMI
      HMI_Serial.print(VAC_out);
      HMI_Serial.write(EndHex,3);


      value = (Data_Modbus.Array[7] << 8) | Data_Modbus.Array[8] ;
      V_Batt = value;
      V_Batt_f = float(value) / 10.0;   // Resolve the value
    
      Serial.print("V_Batt(V):");       // Show the value on the serial monitor
      Serial.println(V_Batt_f); 

      HMI_Serial.print("x0.val=");      // Send device response to HMI
      HMI_Serial.print(V_Batt);
      HMI_Serial.write(EndHex,3);


      Load_percent = Data_Modbus.Array[12];   // Resolve the value
    
      Serial.print("Load_percent(%):"); // Show the value on the serial monitor
      Serial.println(Load_percent); 

      HMI_Serial.print("n0.val=");      // Send device response to HMI
      HMI_Serial.print(Load_percent);
      HMI_Serial.write(EndHex,3);


      value = (Data_Modbus.Array[13] << 8) | Data_Modbus.Array[14] ;
      Load_power = value;               // Resolve the value
    
      Serial.print("Load_power(W):");   // Show the value on the serial monitor
      Serial.println(Load_power); 

      int HMI_Pointer = map(Load_power, 0, 2000, 0, 240); // map(value, fromLow, fromHigh, toLow, toHigh)

      HMI_Serial.print("z0.val=");      // Send device response to HMI
      HMI_Serial.print(HMI_Pointer);
      HMI_Serial.write(EndHex,3);


      RS485_Serial.flush(); // flush buffer
    }
    else {
      Serial.println("CRC failed. Resend and Reread the message.");
    }   
  }
}

void establishContact1() {
  while ( RS485_Serial.available() <= 0 ) {
    RS485_Serial.write(Command_Modbus,8);  // Send the command
    //Serial1.flush();
    delay(50);
  }
}

void Show_DataModbus(struct ByteArray Data_Modbus) {
  // Show the Incoming Data_Modbus.Array[i] on the serial monitor
  int DataSize = sizeof(Data_Modbus.Array);
  Serial.print("DataSize = ");
  Serial.println(DataSize);
  
  Serial.println("Incoming Data_Modbus.Array[i]:");
  for (int i = 0; i < DataSize; i++) // 
  {
    Serial.print("Data_Modbus.Array[");
    Serial.print(i);
    Serial.print("] = 0x");
    Serial.println(Data_Modbus.Array[i], HEX);
  }
}

bool CRC_comparison(struct ByteArray Data_Modbus) {
// The example program about the CRC_comparison() can be found in the Refs.
// Ref 1: https://github.com/HsienChing/Example_Code_Arduino/blob/main/code/CRC16_Calculation_for_Modbus_RTU.ino
// Ref 2: https://github.com/HsienChing/Example_Code_Arduino/blob/main/code/CRC16_Calculation_for_Modbus_RTU_Function_Version.ino

  bool CRC_PASS;
  int  DataSize = sizeof(Data_Modbus.Array);
  Serial.print("DataSize = ");
  Serial.println(DataSize);

  // Calculate CRC16. All parameters are set at once.
  // The parameters for calculting the CRC16/Modbus can be found in https://crccalc.com/ 
  // uint16_t = crc16(array, length, polynome = 0xA001, start = 0, end = 0, reverseIn = false, reverseOut = false)
  uint16_t CRCx16 = crc16(Data_Modbus.Array, DataSize-2, 0x8005, 0xFFFF, 0, true, true); 

  Serial.print("CRCx16: ");
  Serial.println(CRCx16, HEX);      // Show the CRC16 code on the serial monitor
  
  byte HI_CRC16 = highByte(CRCx16); // Separate the CRC16 value into two bytes (highByte and lowByte)
  Serial.print("HI_CRC16: ");
  Serial.println(HI_CRC16, HEX);    // Show the high byte of the CRC16 code on the serial monitor
  byte LO_CRC16 = lowByte(CRCx16);
  Serial.print("LO_CRC16: ");
  Serial.println(LO_CRC16, HEX);    // Show the low byte of the CRC16 code on the serial monitor

  // Compare the data array and the HI/LO bytes of the CRC16 code
  if ( Data_Modbus.Array[DataSize-2] == LO_CRC16 && Data_Modbus.Array[DataSize-1] == HI_CRC16 ) {
    CRC_PASS = true;
    Serial.println(CRC_PASS);
    Serial.println("CRC success.");
  } else {
    CRC_PASS = false;
    Serial.println(CRC_PASS);
    Serial.println("CRC failed. ");
  }
  return CRC_PASS;
}
