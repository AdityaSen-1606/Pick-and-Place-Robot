 
 ​import​ ​cv2 
 ​import​ ​numpy​ ​as​ ​np 
 ​import​ ​serial 
 ​import​ ​time 
 ​from​ ​picamera​.​array​ ​import​ ​PiRGBArray 
 ​from​ ​picamera​ ​import​ ​PiCamera 
  
  
 ​camera​=​PiCamera​() 
 ​camera​.​resolution​=​(​640​,​480​) 
 ​camera​.​framerate​=​32 
 ​rawCapture​=​PiRGBArray​(​camera​, ​size​=​(​640​,​480​)) 
 ​time​.​sleep​(​0.1​) 
  
 ​B​=​1 
 ​G​=​2 
 ​R​=​3 
 ​def​ ​nothing​(​x​): 
 ​    ​pass 
  
 ​cv2​.​namedWindow​(​"Trackers"​) 
 ​cv2​.​createTrackbar​(​"LH"​,​"Trackers"​,​0​,​255​,​nothing​) 
 ​cv2​.​createTrackbar​(​"LS"​,​"Trackers"​,​0​,​255​,​nothing​) 
 ​cv2​.​createTrackbar​(​"LV"​,​"Trackers"​,​0​,​255​,​nothing​) 
 ​cv2​.​createTrackbar​(​"UH"​,​"Trackers"​,​255​,​255​,​nothing​) 
 ​cv2​.​createTrackbar​(​"US"​,​"Trackers"​,​255​,​255​,​nothing​) 
 ​cv2​.​createTrackbar​(​"UV"​,​"Trackers"​,​255​,​255​,​nothing​) 
  
 ​#cap = cv2.VideoCapture(0) 
 ​s​=​serial​.​Serial​(​' '​,​9600​) 
 ​s​.​timeout​=​1 
  
 ​lh​=​cv2​.​getTrackbarPos​(​"LH"​,​"Trackers"​) 
 ​ls​=​cv2​.​getTrackbarPos​(​"LS"​,​"Trackers"​) 
 ​lv​=​cv2​.​getTrackbarPos​(​"LV"​,​"Trackers"​) 
 ​uh​=​cv2​.​getTrackbarPos​(​"UH"​,​"Trackers"​) 
 ​us​=​cv2​.​getTrackbarPos​(​"US"​,​"Trackers"​) 
 ​uv​=​cv2​.​getTrackbarPos​(​"UV"​,​"Trackers"​) 
  
 ​lower_green​ ​=​ ​np​.​array​([​50​,​100​,​100​]) 
 ​upper_green​ ​=​ ​np​.​array​([​70​,​255​,​255​]) 
  
 ​lower_red​ ​=​ ​np​.​array​([​136​,​87​,​11​]) 
 ​upper_red​ ​=​ ​np​.​array​([​180​,​255​,​255​]) 
  
 ​lower_blue​ ​=​ ​np​.​array​([​90​,​50​,​50​]) 
 ​upper_blue​ ​=​ ​np​.​array​([​130​,​255​,​255​]) 
  
  
 ​for​ ​frame​ ​in​ ​camera​.​capture_continuous​(​rawCapture​, ​format​=​"bgr"​,​use_video_port​=​True​): 
 ​    ​#ret,frame = cap.read() 
 ​    ​image​=​frame​.​array 
 ​    ​hsv​ ​=​ ​cv2​.​cvtColor​(​frame​, ​cv2​.​COLOR_BGR2HSV​) 
 ​    ​hsv​ ​=​ ​cv2​.​medianBlur​(​hsv​,​5​) 
 ​    ​mask_red​ ​=​ ​cv2​.​inRange​(​hsv​, ​lower_red​, ​upper_red​) 
 ​    ​mask_green​ ​=​ ​cv2​.​inRange​(​hsv​, ​lower_green​, ​upper_green​) 
 ​    ​mask_blue​ ​=​ ​cv2​.​inRange​(​hsv​, ​lower_blue​, ​upper_blue​) 
 ​    ​circles_red​ ​=​ ​cv2​.​HoughCircles​(​mask_red​, ​cv2​.​HOUGH_GRADIENT​, ​1​, ​1000​, ​param1​=​50​, ​param2​=​30​, ​minRadius​=​0​, ​maxRadius​=​0​) 
 ​    ​circles_blue​ ​=​ ​cv2​.​HoughCircles​(​mask_blue​, ​cv2​.​HOUGH_GRADIENT​, ​1​, ​1000​, ​param1​=​50​, ​param2​=​30​, ​minRadius​=​0​, ​maxRadius​=​0​) 
 ​    ​circles_green​ ​=​ ​cv2​.​HoughCircles​(​mask_green​, ​cv2​.​HOUGH_GRADIENT​, ​1​, ​1000​, ​param1​=​50​, ​param2​=​30​, ​minRadius​=​0​, ​maxRadius​=​0​) 
 ​    ​red​=​cv2​.​bitwise_and​(​frame​,​frame​,​mask​=​mask_red​) 
 ​    ​green​=​cv2​.​bitwise_and​(​frame​,​frame​,​mask​=​mask_green​) 
 ​    ​blue​=​cv2​.​bitwise_and​(​frame​,​frame​,​mask​=​mask_blue​) 
  
 ​    ​if​ ​circles_red​ ​is​ ​not​ ​None​: 
 ​            ​detected_circles​ ​=​ ​np​.​uint16​(​np​.​around​(​circles_red​)) 
 ​            ​for​ (​x​, ​y​, ​r​) ​in​ ​detected_circles​[​0​, :]: 
 ​                ​cv2​.​circle​(​red​, (​x​, ​y​), ​r​, (​0​, ​255​, ​2​), ​3​) 
 ​                ​cv2​.​circle​(​red​, (​x​, ​y​), ​2​, (​0​, ​255​, ​255​), ​3​) 
 ​            ​print​(​"found red ball"​) 
 ​            ​s​.​write​(​51​) 
 ​            ​cv2​.​imshow​(​'RED'​,​red​) 
 ​            ​time​.​sleep​(​60​) 
  
 ​    ​if​ ​circles_green​ ​is​ ​not​ ​None​: 
 ​            ​detected_circles​ ​=​ ​np​.​uint16​(​np​.​around​(​circles_green​)) 
 ​            ​for​ (​x​, ​y​, ​r​) ​in​ ​detected_circles​[​0​, :]: 
 ​                ​cv2​.​circle​(​green​, (​x​, ​y​), ​r​, (​0​, ​255​, ​2​), ​3​) 
 ​                ​cv2​.​circle​(​green​, (​x​, ​y​), ​2​, (​0​, ​255​, ​255​), ​3​) 
 ​            ​print​(​"found green ball"​) 
 ​            ​s​.​write​(​50​) 
 ​            ​cv2​.​imshow​(​'GREEN'​,​green​) 
 ​            ​time​.​sleep​(​60​) 
  
 ​    ​if​ ​circles_blue​ ​is​ ​not​ ​None​: 
 ​            ​detected_circles​ ​=​ ​np​.​uint16​(​np​.​around​(​circles_blue​)) 
 ​            ​for​ (​x​, ​y​, ​r​) ​in​ ​detected_circles​[​0​, :]: 
 ​                ​cv2​.​circle​(​blue​, (​x​, ​y​), ​r​, (​0​, ​255​, ​2​), ​3​) 
 ​                ​cv2​.​circle​(​blue​, (​x​, ​y​), ​2​, (​0​, ​255​, ​255​), ​3​) 
 ​            ​print​(​"found blue ball"​) 
 ​            ​s​.​write​(​49​) 
 ​            ​cv2​.​imshow​(​'BLUE'​,​blue​) 
 ​            ​time​.​sleep​(​60​) 
 ​    ​else​: 
 ​            ​print​ (​"no ball"​) 
              ​s​.​write​(​0​) 
  
 ​    ​rawCapture​.​truncate​(​0​) 
 ​    ​if​ ​cv2​.​waitKey​(​1​) ​&​ ​0xFF​ ​==​ ​ord​(​'q'​): 
 ​            ​break 
 ​s​.​close​() 
 ​cv2​.​destroyAllWindows​()
