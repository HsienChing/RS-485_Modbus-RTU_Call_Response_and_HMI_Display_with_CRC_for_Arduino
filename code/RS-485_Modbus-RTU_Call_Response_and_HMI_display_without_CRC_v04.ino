/*
  Sketch name: RS-485 Modbus-RTU call response and HMI display without CRC v04
  Suggested board: Arduino MEGA 2560 Rev3
  Purpose: 
    1. Send Modbus-RTU command to the device through RS-485 via the assigned "RS485_Serial."
    2. Get responses from the device through RS-485.
    3. Send the device responses to the human-machine interface (HMI) via the assigned "HMI_Serial."
    4. Arduino can monitor the device responses from the serial monitor.
  Additional features:
    1. The cyclic redundancy check (CRC) is not coded for the check of value resolving.
    2. The "CODE BLOCK 1" is turned off. As it is turned on, the incoming Data_Modbus[i] will be shown on the serial monitor.
  Suggested system setup: 
    1. A "RS-485 to TTL module" is used to convert the RS-485 signal because Arduino MEGA 2560 Rev3 does not support RS-485 directly.
    2. A HMI with the UART interface is used to show the device responses through the assigned HMI_Serial channel of the Arduino.
    
  Date:   7 July 2021
  Author: Dr. Hsien-Ching Chung
  ORCID:  https://orcid.org/0000-0001-9364-8858
*/

#define HMI_Serial   Serial1 // Assign serial port
#define RS485_Serial Serial3 // Assign serial port

byte Command_Modbus[8] = {0x01,0x04,0x30,0x00,0x00,0x0B,0xBE,0xCD}; // Modbus-RTU Command
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
  Serial.      begin(115200);  // Serial setting for the Arduino serial monitor
  RS485_Serial.begin(  9600);  // Serial setting for the RS-485 to TTL
  HMI_Serial.  begin(115200);  // Serial setting for the HMI with the UART interface
}

void loop() {
  establishContact1();  // Send a byte to establish contact until receiver responds

  if (RS485_Serial.available() > 0 ) {

    for (int i = 0; i < 27; i++)
    {
      Data_Modbus[i] = RS485_Serial.read(); // Get incoming data
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

    HMI_Serial.print("x1.val=");      // Send device response to HMI
    HMI_Serial.print(VAC_out);
    HMI_Serial.write(EndHex,3);


    value = (Data_Modbus[7] << 8) | Data_Modbus[8] ;
    V_Batt = value;
    V_Batt_f = float(value) / 10.0;   // Resolve the value
    
    Serial.print("V_Batt(V):");       // Show the value on the serial monitor
    Serial.println(V_Batt_f); 

    HMI_Serial.print("x0.val=");      // Send device response to HMI
    HMI_Serial.print(V_Batt);
    HMI_Serial.write(EndHex,3);


    Load_percent = Data_Modbus[12];   // Resolve the value
    
    Serial.print("Load_percent(%):"); // Show the value on the serial monitor
    Serial.println(Load_percent); 

    HMI_Serial.print("n0.val=");      // Send device response to HMI
    HMI_Serial.print(Load_percent);
    HMI_Serial.write(EndHex,3);


    value = (Data_Modbus[13] << 8) | Data_Modbus[14] ;
    Load_power = value;               // Resolve the value
    
    Serial.print("Load_power(W):");   // Show the value on the serial monitor
    Serial.println(Load_power); 

    int HMI_Pointer = map(Load_power, 0, 2000, 0, 240); // map(value, fromLow, fromHigh, toLow, toHigh)

    HMI_Serial.print("z0.val=");      // Send device response to HMI
    HMI_Serial.print(HMI_Pointer);
    HMI_Serial.write(EndHex,3);


    RS485_Serial.flush(); // flush buffer
  }

}

void establishContact1() {
  while (RS485_Serial.available() <= 0) {
    RS485_Serial.write(Command_Modbus,8);  // Send the command
    //Serial1.flush();
    delay(1000);
  }
}
