#define POT_PIN_NUMBER 0

float voltage;
int number;
int fraction;

void setup() {
  DDRB = DDRB | B00111111;
  DDRC = DDRC | B00011110;
  DDRD = DDRD | B11111100;  
}

void loop() {
  voltage = (float) AD_conversion()*5/1023;  
  number = voltage - ( ( (int) voltage*100 ) % 100);
  fraction =  round((voltage - number)*100*9/100);
  
  PORTD = B00000000 | digit_conversion(2, fraction);
  PORTB = B00000000 | digit_conversion(0, fraction-8);

  number_conversion(number);
}

int AD_conversion() {
  DIDR0 = B11111001;
  ADMUX |= B01000000 | POT_PIN_NUMBER;
  ADCSRA |= B11000000;
  while( (ADCSRA & B01000000) != 0 );  
  return ADC;
}

int digit_conversion(int start_pin, int n){
  double output = 0;
  for (int i=start_pin; i<=n+1; ++i) output += pow(2,i);
  return (int) round(output + 0.0001);
}

int number_conversion(int n){
    switch(n) {
        case 0:
          PORTB = B00000000 | (8 + 16 + 32) | PORTB;
          PORTC = B00000000 | (4 + 8 + 16);
          break;
        case 1:
          PORTB = B00000000 | 32 | PORTB;
          PORTC = B00000000 | 16;
          break;
        case 2:
          PORTB = B00000000 | (8 + 16) | PORTB;
          PORTC = B00000000 | (8 + 16 + 2);
          break;
        case 3:
          PORTB = B00000000 | (32 + 16) | PORTB;
          PORTC = B00000000 | (8 + 16 + 2);
          break;
        case 4:
          PORTB = B00000000 | 32 | PORTB;
          PORTC = B00000000 | (4 + 2 + 16);
          break;
        case 5:
          PORTB = B00000000 | (32 + 16) | PORTB;
          PORTC = B00000000 | (8 + 4 + 2);
          break;
        default:
          break;
    }
}
