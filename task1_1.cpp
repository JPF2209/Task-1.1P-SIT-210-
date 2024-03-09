int light_pin = 13;

bool check = false;

int button_status = 2;

int dotdelay = 200;

int repeat_status = 0;

bool pressed = true;

void setup()
{
    pinMode(light_pin, OUTPUT);
}

void loop()
{
  	bool current_state = digitalRead(button_status);
  	if (current_state == pressed)
    {
       morseCodeSequence(".---"); //J
       delay(3000);
       morseCodeSequence("---"); //O
       delay(3000);
       morseCodeSequence("..."); //S
       delay(3000);
       morseCodeSequence("...."); //H
       delay(3000);
       morseCodeSequence("..-"); //U
       delay(3000);
       morseCodeSequence(".-"); //A
       delay(1000); //Wait for 1 second
      
    }
}

void morseCodeSequence(char* sequence)
{
    int i = 0;

    while (sequence[i] != NULL)
    {
        DotorDash(sequence[i]);
        i++;
    }

    delay(dotdelay * 3);
}

void DotorDash(char DoD)
{
    digitalWrite(light_pin, HIGH);
    if (DoD == '.')
    {
        delay(dotdelay);
    }
    else
    {
        delay(dotdelay * 3);
    }
    digitalWrite(light_pin, LOW);
    delay(dotdelay);
}