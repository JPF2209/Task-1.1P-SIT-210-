//C++ Code
int light_pin = 13;

//Getting pin number for button
int button_status = 2;

//Setting dotdelay for 200ms
int dotdelay = 200;

//Value to check if button is pressed
bool pressed = true;

//Condition set so that once I complete repeated button press
//No matter how much the button has been pressed, it goes back to reset
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
    attachInterrupt(0,interruptFunction, CHANGE);
}

//Catches if I press the button during when the while the loop occurs
void interruptFunction() 
{
  bool c_state = digitalRead(button_status);
  if (c_state == true)
  {
    logic();
    back = true;
  }
}

//main loop
void loop()
{
  	//I want no interrupts because when I press the button, I want it to not 
    //return straight away to the loop & I want it to execute the code
  	noInterrupts();
  	bool current_state = digitalRead(button_status);
  	//Setting back, back to false
  	back = false;
  	if (current_state == pressed)
    {
      //Needed to seperate the process between choosing the current state and 
      //looping through the letters of my name
      logic();
      
    }
}

//Logic for iterating through each letter
void logic()
{
  noInterrupts();
  int i = 0;  
  delay(500);
  //And condition makes sure if one isn't there, the whole thing shuts down
  while (i < 6 && back != true)
  {
    interrupts();
    //Using the char array to do sequence for each letter
    morseCodeSequence(name[i]);
    delay(500);
    i++;
  }
}

//Here, while looping what to do for each char in an array of characters
void morseCodeSequence(char* sequence)
{
    int i = 0;

  	//For last method so that it doesn't do anything if back equals true
    while (sequence[i] != NULL && back != true)
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
  	//Change function depending of if - or . detected, it leaves light on for certain time period
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

