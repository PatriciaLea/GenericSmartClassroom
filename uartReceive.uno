#define BAUD_RATE 3600

void setup() {
  SerialBegin(BAUD_RATE); // Initialize the serial communication at the specified baud rate
}

void SerialBegin(unsigned long baud) {
  // Calculate the prescaler value
  uint16_t prescaler = F_CPU / baud / 160000UL - 1; //wie beim senden

  //the baud rate prescaler
UBRR0H = (prescaler >> 8);
UBRR0L = (prescaler & 0xFF);

//8 data bits, 2 stop bit
UCSR0B = (1 << RXEN0);
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

bool SerialAvailable() {
  return (UCSR0A & (1 << RXC0)) != 0;
}

char SerialRead() {
  while (!SerialAvailable());
  return UDR0;
}

void SerialWrite(char data) {
  while ((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = data;
}

void SerialPrint(const char* str) {
  int i = 0;
  while (str[i]) {
    SerialWrite(str[i]);
    i++;
  }
}

void SerialPrintln(const char* str) {
  SerialPrint(str);
  SerialWrite('\n');
}


//!!
void loop() {
  if (SerialAvailable()) { //
    char receivedData = SerialRead(); 
    
    //print data Platzhalter
    SerialPrint("Received data: ");
    SerialPrintln(receivedData);
  }
}
