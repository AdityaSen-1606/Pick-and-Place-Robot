 
 ​//​ A0,A1,A2 are the IR Sensor input (All are the analog pins) 
 ​//​8,9,10,11 are the output pins of the motor (These are digital pins) 
  
 ​/*​ When IR sensor detect white or any other color then  
 ​   range of input is greater than 100 and for black is 
 ​   greater than 100. ​*/ 
  
 ​#​include​ ​<​Servo.h​>​  ​//​ apan ko stepper use karna padega 
 ​#​include​ ​<​Stepper.h​> 
  
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
  
  
  
 ​void​ ​loop​() 
 ​{ 
 ​   
 ​  ​//​Infrared Input (3IR used) 
 ​  ​int​ A = ​analogRead​(A0); 
 ​  ​int​ a = ​map​(A,​0​,​1023​,​0​,​255​); 
 ​  ​int​ B = ​analogRead​(A1); 
 ​  ​int​ b = ​map​(B,​0​,​1023​,​0​,​255​); 
 ​  ​int​ C = ​analogRead​(A2); 
 ​  ​int​ c = ​map​(C,​0​,​1023​,​0​,​255​); 
 ​  ​int​ p=​0​; ​//​for any color of ball the bot get stop 
 ​   
 ​   
 ​  Serial.​println​(a); 
 ​  Serial.​println​(b); 
 ​  Serial.​println​(c); 
 ​   
 ​   
 ​  compartment.​write​(​90​); 
  
 ​  ​//​ pehle infrared se detect karege ki apan line ke upar he ki nahi  
 ​  ​//​ Initially the bot is placed rightmost part of the grid and start to scan on moving left 
 ​  ​if​(Serial.​available​()>=​0​) 
 ​  { 
 ​    p=Serial.​read​(); 
 ​    ​if​(p=​0​) ​//​No Ball is detcted so bot start to scan the row on moving leftward 
 ​    { 
 ​                                      ​//​ Leftside move on start 
 ​        ​if​ (a>​100​ && b>​100​ && c>​100​){ 
 ​        
 ​           ​Leftward​(); 
 ​           Serial.​println​(​"​Leftward movement​"​); 
  
 ​             ​if​ (a<​100​,b>​100​,c>​100​){ 
 ​                ​delay​(​1000​); 
 ​                                    ​//​Forward Move 
 ​              ​Forward​(); 
 ​              Serial.​println​(​"​Forward ward movement​"​); 
  
 ​                ​if​ (a<​100​ && b>​100​ && c>​100​){ 
 ​                   ​delay​ (​1000​); 
 ​                } 
 ​              } 
 ​            Serial.​println​(​"​********​"​); 
 ​        } 
 ​                                     ​//​Rightside Move 
 ​        ​if​ (a<​100​ && b>​100​ && c>​100​){ 
 ​            ​Rightward​(); 
 ​            Serial.​println​(​"​Rightward ward movement​"​); 
 ​           
 ​              ​if​ (a>​100​ && b>​100​ && c<​100​){ 
 ​                 ​delay​ (​1000​); 
 ​                    ​//​ Forward Move 
 ​                 ​Forward​(); 
 ​                 Serial.​println​(​"​Forward movement​"​); 
  
 ​                   ​if​ (a>​100​ && b>​100​ && c<​100​){ 
 ​                      ​delay​ (​1000​); 
 ​                    } 
 ​                } 
 ​            Serial.​println​(​"​********​"​); 
 ​        } 
 ​                                  ​//​ Leftside Move 
 ​        ​if​ (a>​100​ && b>​100​ && c<​100​){ 
 ​           ​Leftward​(); 
 ​           Serial.​println​(​"​Leftward movement​"​); 
  
 ​              ​if​ (a<​100​ && b>​100​ && c>​100​){ 
 ​                 ​delay​ (​1000​); 
 ​                                 ​//​ Forward Move 
 ​                 ​Forward​(); 
 ​                 Serial.​println​(​"​Forward movement​"​); 
  
 ​                    ​if​ (a<​100​ && b>​100​ && c>​100​){ 
 ​                       ​delay​ (​1000​); 
 ​                    } 
 ​                } 
 ​         } 
 ​      Serial.​println​(​"​********​"​); 
 ​    } 
 ​      ​//​ for blue ball the received number is 1 (ASCII 49) 
 ​      ​//​for green ball the received number is 2 (ASCII 50) 
 ​      ​//​for red ball the received number is 3 (ASCII 51) 
 ​    ​else​ ​if​(p==​49​){ 
 ​       ​Stop​(); 
 ​       Serial.​println​(​"​Stop:Picking up Blue Ball​"​); 
 ​       Serial.​println​(​"​********​"​); 
 ​       ​Gripper​(); 
 ​       ​delay​(​60000​); 
 ​      ​//​compartment will remain as it is 
 ​          } 
 ​    ​else​ ​if​ (p==​50​){ 
 ​       ​Stop​(); 
 ​       Serial.​println​(​"​Stop:Picking up Green Ball​"​); 
 ​       Serial.​println​(​"​********​"​); 
 ​       compartment.​write​(​0​); 
 ​       ​Gripper​(); 
 ​       ​delay​(​60000​); 
 ​          } 
 ​    ​else​ ​if​ (p==​51​){ 
 ​        ​Stop​(); 
 ​        Serial.​println​(​"​Stop:Picking up Red Ball​"​); 
 ​        Serial.​println​(​"​********​"​); 
 ​        compartment.​write​(​180​); 
 ​        ​Gripper​(); 
 ​        ​delay​(​60000​); 
 ​         } 
 ​ }   
 ​       
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
 ​    hand2.​write​(​0​); 
 ​    ​delay​(​20​); 
 ​}
