// using digitial pin 2 for the output of the hall sensor
int hall_pin = 2;

//settingn number of trips for the RPM reading
float hall_thresh = 25;

void setup() {
  // initialsiing serial communication
  Serial.begin(9600);

  // making the happ pin an input
  pinMode(hall_pin, INPUT); 

  // printing head of csv
  Serial.println("time_delta, rpm");
  
}

void loop() {
  // allocating values for the tach
  float hall_count = 1.0;
  float start = micros();
  bool on_state = false;

  // counting the number of times the sensor is tripped
  while(true){
    if (digitalRead(hall_pin) == 0){
      if (on_state == false){
        on_state = true;
        hall_count += 1.0;
      }
    } else{
      on_state = false;
    }
    
    if (hall_count >= hall_thresh){
      break;
    }
  }

  float end_time = micros();
  float time_passed = ((end_time-start)/1000000.0);
  Serial.print(time_passed);
  Serial.print(", ");
  float rpm_val = (hall_count/time_passed)*60;
  Serial.println(rpm_val);

  //delay between reads for stability
  delay(1);
}
