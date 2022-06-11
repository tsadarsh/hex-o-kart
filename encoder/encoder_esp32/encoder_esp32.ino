 #define A 21
 #define B 19
 
 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (A,INPUT);
   pinMode (B,INPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(A);   
   attachInterrupt(digitalPinToInterrupt(A), update, CHANGE);
 } 

 void loop() { 
     Serial.print("Position: ");
     Serial.println(counter);
     delay(100);
 }
 void update() {
    aState = digitalRead(A); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(B) != aState) { 
       counter ++;
     } else {
       counter --;
     }
   } 
   aLastState = aState;
 }
