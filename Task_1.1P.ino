//C++ Code
int light_pin = 13;

//Getting pin number for button
int button_status = 2;

//Setting dotdelay for 200ms
int dotdelay = 200;

//Value to check if button is pressed
bool pressed = true;

//Condition set so that once I complete repeated button press
//No matter how much the button has been pressed, it goes
//Back to reset
bool back = false;

//My name represented as a char array
char* name[] = {
  ".---",//J
  "---", //O
  "...", //S
  "....",//H
  "..-", //U
  ".-"   //A
};

//Things I need to setup before going to the loop
void setup()
{
    pinMode(light_pin, OUTPUT);
  	pinMode(button_status, INPUT);
    attachInterrupt(0,interruptFunction, HIGH);
}

//Catches if I press the button during when the while
//Loop occurs
void interruptFunction() 
{
  bool c_state = digitalRead(button_status);
  if (c_state == true)
  {
    loop();
    back = true;
  }
}

//main loop
void loop()
{
  	//I want no interrupts because when I press the button
  	//I want it to not return straight away to the loop
  	//And I want it to execute the code
  	noInterrupts();
  	bool current_state = digitalRead(button_status);
  	if (current_state == pressed)
    {
      //Needed to seperate the process betweed
      //Choosing the current state and looping through
      //The letters of my name
      logic();
      
    }
}

//Logic for iterating through each letter
void logic()
{
  noInterrupts();
  int i = 0;  
  delay(500);
  bool c_state = digitalRead(button_status);
  while (i < 6 || c_state != true || back != true)
  {
    interrupts();
    //Using the char array to do sequence for each letter
    morseCodeSequence(name[i]);
    delay(3000);
    i++;
  }
  //Goes back to loop
  loop();
}

//Here, while looping what to do for each char in an
//array of characters
void morseCodeSequence(char* sequence)
{
    int i = 0;

    while (sequence[i] != NULL)
    {
  		bool c_state = digitalRead(button_status);
      	//Function to output light sequence for morse code
        outputSequence(sequence[i]);
        i++;
    }
    
    delay(dotdelay * 3);
}

//Output sequence function
void outputSequence(char DoD)
{
  	//Turn light on
    digitalWrite(light_pin, HIGH);
  	//Change function depending of if - or . detected
  	//Leaves light on for certain time period
  	if (DoD == '.')
    {
        delay(dotdelay);
    }
    else
    {
        delay(dotdelay * 3);
    }
  	//Turns off light sequence
    digitalWrite(light_pin, LOW);
    delay(dotdelay);
}

