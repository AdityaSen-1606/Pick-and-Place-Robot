 
 ​//​ A0,A1,A2 are the IR Sensor input (All are the analog pins) 
 ​//​8,9,10,11 are the output pins of the motor (These are digital pins) 
  
 ​/*​ When IR sensor detect white or any other color then  
 ​   range of input is greater than 100 and for black is 
 ​   greater than 100. ​*/ 
  
 ​#​include​ ​<​Servo.h​>​  ​//​ apan ko stepper use karna padega 
 ​#​include​ ​<​Stepper.h​> 
  
 ​int​ a,b,c; 
 ​int​ currDirn = ​1​; ​//​ left = 1 right = -1, forward = 0  
 ​int​ currCompartment = ​1​; ​//​ blue = 1, green = 2, red = 3; 
  
 ​Servo compartment; 
 ​Servo hand2; 
 ​Stepper ​hand​(​72​, ​4​, ​5​, ​6​, ​7​); ​//​ 4 & 5 are used for clock wise rotation. 6 & 7 are used for anti-clockwise rotation 
 ​//​ one variable to store which direction we are currently moving in 
  
 ​void​ ​setup​() 
 ​{  
 ​  Serial.​begin​(​960​); 
 ​   
 ​  compartment.​attach​(​2​); 
 ​  hand2.​attach​(​3​); 
 ​  ​pinMode​(A0 , INPUT); ​//​Analog input pin for IR Sensor 
 ​  ​pinMode​(A1 , INPUT); ​//​Analog input pin for IR Sensor 
 ​  ​pinMode​(A2 , INPUT); ​//​Analog input pin for IR Sensor 
 ​  ​pinMode​(​8​ , OUTPUT); ​//​Output pin for motor output 1 (When high then motor driver drive the 1 & 4 wheel in clock wise direction) 
 ​  ​pinMode​(​9​ , OUTPUT); ​//​Output pin for motor output 1 (When high then motor driver drive the 1 & 4 wheel in anti-clock wise direction) 
 ​  ​pinMode​(​10​ , OUTPUT); ​//​Output pin for motor output 2 (When high then motor driver drive the 2 & 3 wheel in clock wise direction) 
 ​  ​pinMode​(​11​ , OUTPUT); ​//​Output pin for motor output 2 (When high then motor driver drive the 2 & 3 wheel in anti-clock wise direction) 
 ​   
 ​  ​Stop​(); 
 ​} 
  
  
 ​bool​ ​infrared​() 
 ​{ 
 ​    ​int​ A = ​analogRead​(A0); 
 ​    a = ​map​(A,​0​,​1023​,​0​,​255​); 
 ​    ​int​ B = ​analogRead​(A1); 
 ​    b = ​map​(B,​0​,​1023​,​0​,​255​); 
 ​    ​int​ C = ​analogRead​(A2); 
 ​    c = ​map​(C,​0​,​1023​,​0​,​255​); 
  
 ​    ​if​(a<​100​ && b<​100​ && c<​100​) ​return​ ​true​; 
 ​    ​else​ ​return​ ​false​; 
 ​} 
  
 ​void​ ​rotate​(​int​ rot_dirn) ​//​ 1 => clockwise  -1 => anticlockwise 
 ​{ 
 ​     
 ​}  
  
 ​void​ ​pick​(​int​ color) 
 ​{ 
 ​    ​Stop​(); 
  
 ​    ​if​(color==​1​) 
 ​    { 
 ​        ​Gripper​(); 
  
 ​        ​if​(currCompartment==​1​) 
 ​        ​else​ ​if​(currCompartment==​2​) ​rotate​(​1​); 
 ​        ​else​ ​rotate​(-​1​); 
 ​    } 
 ​    ​else​ ​if​(color==​2​) 
 ​    { 
 ​        ​if​(currCompartment==​1​) ​rotate​(-​1​); 
 ​        ​else​ ​if​(currCompartment==​2​)  
 ​        ​else​ ​rotate​(​1​); 
 ​    } 
 ​    ​else​ ​//​ if(color==3) 
 ​    { 
 ​        ​if​(currCompartment==​1​) ​rotate​(​1​); 
 ​        ​else​ ​if​(currCompartment==​2​) ​rotate​(-​1​); 
 ​        ​else 
 ​    } 
 ​} 
  
 ​void​ ​loop​() 
 ​{ 
 ​    ​bool​ ir = ​infrared​() 
  
 ​    Serial.​println​(a); 
 ​    Serial.​println​(b); 
 ​    Serial.​println​(c); 
 ​     
 ​    ​if​(ir) 
 ​    { 
 ​        ​if​(Serial.​available​()) 
 ​        { 
 ​            p = Serial.​read​(); 
  
 ​            ​if​(p==​'​1​'​) ​pick​(​1​); ​//​blue 
 ​            ​else​ ​if​(p==​2​) ​pick​(​2​); ​//​ green 
 ​            ​else​ ​pick​(​3​); ​//​ red 
 ​        } 
 ​        ​else​ ​move​(currDirn); 
 ​    }     
 ​    ​else 
 ​    { 
 ​        ​if​(currDirn==​1​) 
 ​        { 
 ​            currDirn = ​0​; 
 ​            ​move​(currDirn); 
 ​            currDirn = -​1​; 
 ​            ​move​(currDirn); 
 ​        } 
 ​        ​else​ ​if​(currDirn==-​1​) 
 ​        { 
 ​            currDirn = ​0​; 
 ​            ​move​(currDirn); 
 ​            currDirn = ​1​; 
 ​            ​move​(currDirn); 
 ​        } 
 ​    } 
 ​} 
  
 ​void​ ​Forward​(){ 
 ​        ​digitalWrite​(​8​,HIGH); 
 ​        ​digitalWrite​(​9​,LOW); 
 ​        ​digitalWrite​(​10​,HIGH); 
 ​        ​digitalWrite​(​11​,LOW); 
 ​} 
  
 ​void​ ​Leftward​(){ 
 ​        ​digitalWrite​(​8​,LOW); 
 ​        ​digitalWrite​(​9​,HIGH); 
 ​        ​digitalWrite​(​10​,HIGH); 
 ​        ​digitalWrite​(​11​,LOW); 
 ​} 
  
 ​void​ ​Rightward​(){ 
 ​        ​digitalWrite​(​8​, HIGH); 
 ​        ​digitalWrite​(​9​, LOW); 
 ​        ​digitalWrite​(​10​, LOW); 
 ​        ​digitalWrite​(​11​, HIGH); 
 ​} 
  
 ​void​ ​Stop​(){ 
 ​        ​digitalWrite​(​8​, LOW); 
 ​        ​digitalWrite​(​9​, LOW); 
 ​        ​digitalWrite​(​10​, LOW); 
 ​        ​digitalWrite​(​11​, LOW); 
 ​} 
  
 ​void​ ​Gripper​(){ 
 ​    hand.​setSpeed​(​60​); 
 ​    hand.​step​(​72​); ​//​assumed ball is incompressible so when gripper tighten its holding ball will not distort 
 ​    hand2.​write​(​180​); 
 ​    ​int​ i = ​0​; 
 ​    ​do​{ 
 ​        ​for​(i =​0​;i=​72​;i++){ 
 ​            hand.​step​(-i); 
 ​        } 
 ​    } 
 ​    ​while​ (i<=​72​); ​//​ motor will rotate untill make one rotation anti-clockwise (can be updated according to physical constraints) 
  
 ​    ​delay​(​20​); 
 ​}
