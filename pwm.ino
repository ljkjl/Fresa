#define PINPOT A0
#define PINSTART 3
#define PINSTOP 2
#define PINENABLE 8
#define PINUSC 9

int pot;
int pwm;
bool stato;
int cicli_starter;

void setup() {
  pinMode(PINPOT, INPUT);
  pinMode(PINSTART, INPUT_PULLUP);
  pinMode(PINSTOP, INPUT_PULLUP);
  pinMode(PINENABLE, OUTPUT);
  pinMode(PINUSC, OUTPUT);

  Serial.begin(9600);
  
  stato = false;
  cicli_starter = 0;

  void scan(int pin1, int pin2);
}

void loop() {
  pot = analogRead(PINPOT);
  pwm = map(pot, 0, 1023, 0, 255);

  digitalWrite(PINENABLE, stato);
  digitalWrite(LED_BUILTIN, stato);

  scan(PINSTART, PINSTOP);
  
  if(stato == true)
  {
    analogWrite(PINUSC, pwm);
  }
  else
  {
    digitalWrite(PINUSC, LOW);
  }

  delay(1);
}

void scan(int pin1, int pin2)
{
  static bool prec1, prec2;
  static bool att1, att2;
  static bool primogiro = true;

  att1 = digitalRead(pin1);
  att2 = digitalRead(pin2);

  if(att1 == LOW && prec1 == HIGH)
    stato = true;

  if(att2 == LOW && prec2 == HIGH)
    stato = false;
  
  prec1 = att1;
  prec2 = att2;

  if(primogiro)
  {
      stato = false;
      primogiro = false;
  }
  
  return;
}

