//Variables for thermistors
int Thermistor1Pin = 0;
int Thermistor2Pin = 1;
int Vo, V1;
float R1 = 10000;
float R3 = 10000;
float logR2, logR4, R2, R4, T1, Tc1, Tf1, T2, Tc2, Tf2;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float AverageTemp; 
//variable for LED
int LED = 2;
bool outside = false;
//Variable for peltier
int In1 = 3;
int In2 = 4;


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
}

void loop() {

  //Thermister1
  Vo = analogRead(Thermistor1Pin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc1 = T1 - 273.15;
  Tf1 = (Tc1 * 9.0) / 5.0 + 32.0;

  //Thermister2
  V1 = analogRead(Thermistor2Pin);
  R4 = R3 * (1023.0 / (float)V1 - 1.0);
  logR4 = log(R4);
  T2 = (1.0 / (c1 + c2 * logR4 + c3 * logR4 * logR4 * logR4));
  Tc2 = T2 - 273.15;
  Tf2 = (Tc2 * 9.0) / 5.0 + 32.0;

  AverageTemp = (Tc1 + Tc2) / 2; 

  if (outsideRange() == 1)//calls fuction to check if internal temp outside of range
  {
    //blink LED
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  else 
  {
    //light on -> shows decive is on 
    digitalWrite(LED, HIGH);
  }

  if ( AverageTemp < 12 ) //12 adds a buffer to heat sooner
  {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    Serial.println("HEATING");
  }
  else if ( AverageTemp > 27 ) //27 adds buffer to cool sooner
  {
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    Serial.println("COOLING");
  }
  
//  Serial.print("Temperature C: ");
//  Serial.println(AverageTemp);
  

  delay(500);
}

bool outsideRange() //returns boolean for temp check
{
  if ( AverageTemp < 10 )
  {
    return true;
  }
  else if ( AverageTemp > 30 )
  {
    return true;
  }
  else
  return false;
}
