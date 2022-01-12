//Defining pin numbers.
int sensor1 = 19; /*Outward  sensor*/
int sensor2 = 17; /*Railing sensor*/
int buzz = 6;
//Defining variables to temporarily store the sensor's output.
int state1;
int state2;
int freq = 20000;
//Defining temporary variables.
int i;

void setup() {
  // Start Serial Communication.
  Serial.begin(9600);
  Serial.println("Communication Began");

  //Seting up pin modes.
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(buzz, OUTPUT);

}

void loop() {
  // Getting sensor 1 output.
  Serial.println("Reading Sensor 1");
  state1 = digitalRead(sensor1);

  //Excecute some code only when the outward sensor detects something.
  if(state1 == 1){
    Serial.println("Sensor 1 state: detected");
    i = 0; /*Resetting i to 0*/
    //Make a while loop to look for railing sensor detection only.
    /* If outward sensor detects something, 
     * there is a good chance it could be a pigeon.
     * But to double check, we look for a detection
     * from the outward sensor for about 3 seconds.*/
    while(i < 10){
      //Getting sensor 2 output.
      state2 == digitalRead(sensor2);
      //If we detect, then buzz and exit the loop
      if(state2 == 1){
        Serial.println("Sensor 2 state: detected");
        //Play the buzzer
        for(int k = 0; k <= 75; k++){
          Serial.println(freq);
          tone(buzz, freq);
          delay(200);
          noTone(buzz);
          freq += 200;
        }
        freq = 20000;
      }
      //Otherwise we wait for 0.5 seconds.
      /* Ideally, the sensor will continue to give a
       * positive output for 3s after detection;
       * so waiting for 0.5s won't do any harm. */
      else{
        i++;
        Serial.println("Sensor 2 state: nada");
        delay(500);
      }
    }
  }
  /* If sensor one detects nothing, we know a pigeon
   * isn't there so lets wait for 0.5s before trying
   * again. */
  else{
    Serial.println("Sensor 1 state: nada");
    delay(500);
  }
}
