 #define right_enc_A 21
 #define right_enc_B 19
 #define left_enc_A 34
 #define left_enc_B 35
  
 int right_counter = 0; 
 int right_aState;
 int right_aLastState;
 int right_counter_last = 0;
 int left_counter = 0; 
 int left_aState;
 int left_aLastState; 
 int left_counter_last = 0;

 void setup() { 
   pinMode (right_enc_A,INPUT);
   pinMode (right_enc_B,INPUT);
   pinMode (left_enc_A,INPUT);
   pinMode (left_enc_B,INPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   right_aLastState = digitalRead(right_enc_A);
   left_aLastState = digitalRead(left_enc_A);   
   attachInterrupt(digitalPinToInterrupt(right_enc_A), right_update, CHANGE);
   attachInterrupt(digitalPinToInterrupt(left_enc_A), left_update, CHANGE);
 } 

 void loop() {
     if (right_counter_last != right_counter) {
       Serial.print("Position RIGHT: ");
       Serial.println(right_counter);
       right_counter_last = right_counter;
     }
     if (left_counter_last != left_counter) {
       Serial.print("Position LEFT: ");
       Serial.println(left_counter);
       left_counter_last = left_counter;
     }
     delay(100);
 }
 
 void right_update() {
    right_aState = digitalRead(right_enc_A); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (right_aState != right_aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(right_enc_B) != right_aState) { 
       right_counter ++;
     } else {
       right_counter --;
     }
   } 
   right_aLastState = right_aState;
 }

  void left_update() {
    left_aState = digitalRead(left_enc_A); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (left_aState != left_aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(left_enc_B) != left_aState) { 
       left_counter ++;
     } else {
       left_counter --;
     }
   } 
   left_aLastState = left_aState;
 }
