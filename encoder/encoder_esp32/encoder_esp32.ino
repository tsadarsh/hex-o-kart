 #define right_enc_A 21
 #define right_enc_B 19
 
 int right_counter = 0; 
 int right_aState;
 int right_aLastState;  

 void setup() { 
   pinMode (right_enc_A,INPUT);
   pinMode (right_enc_B,INPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   right_aLastState = digitalRead(right_enc_A);   
   attachInterrupt(digitalPinToInterrupt(right_enc_A), right_update, CHANGE);
 } 

 void loop() { 
     Serial.print("Position RIGHT: ");
     Serial.println(right_counter);
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
