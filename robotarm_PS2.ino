#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>

#define PS2_DAT   D6
#define PS2_CMD   D7
#define PS2_SEL   D8
#define PS2_CLK   D5
#define pressures   false
#define rumble      false

#define pinServo1 D9 
#define pinServo2 D4 
#define pinServo3 D3 
#define pinServo4 D2 
#define pinServo5 D1 
#define pinServo6 D0 

#define servo_base_angle_mid  90
#define servo_base_angle_max  180
#define servo_base_angle_min  0

#define servo_base_arm_angle_mid  90
#define servo_base_arm_angle_max  180
#define servo_base_arm_angle_min  0

#define servo_mid_arm_angle_45   45
#define servo_mid_arm_angle_max  180
#define servo_mid_arm_angle_min  0

#define servo_neck_angle_mid   90
#define servo_neck_angle_max  180
#define servo_neck_angle_min  0

#define servo_gripper_angle_mid   90
#define servo_gripper_angle_max  180
#define servo_gripper_angle_min  0

#define servo_gripper_mid   90
#define servo_gripper_max  180
#define servo_gripper_min  0
 
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;


PS2X ps2x; // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;

uint servo_base_angle = servo_base_angle_mid;
uint servo_base_arm_angle = servo_base_arm_angle_mid;
uint servo_mid_arm_angle = servo_mid_arm_angle_45;
uint servo_neck_angle = servo_neck_angle_mid;
uint servo_gripper_angle = servo_gripper_angle_mid;
uint servo_gripper = servo_gripper_mid;

void setup(){
 
  Serial.begin(57600);
  
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
	if (pressures)
	  Serial.println("true ");
	else
	  Serial.println("false");
	Serial.print("rumble = ");
	if (rumble)
	  Serial.println("true)");
	else
	  Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }

  servo1.attach(pinServo1,500,2500);
  servo1.write(servo_base_angle);   
  servo2.attach(pinServo2,500,2500);
  servo2.write(servo_base_arm_angle); 
  //servo2.write(80); // 80 (middle) 0 -150 degrees
  servo3.attach(pinServo3,500,2500);
  servo3.write(servo_mid_arm_angle_45);
  //servo3.write(90);  // 0 -180 degrees
  servo4.attach(pinServo4,500,2500);
  servo4.write(servo_neck_angle); 
  //servo4.write(90);  // 0 - 180 degrees  
  servo5.attach(pinServo5,500,2500);
  servo5.write(servo_gripper_angle); 
  //servo5.write(0);   // 0 - 90 degrees
  servo6.attach(pinServo6,500,2500);
  servo6.write(servo_gripper);
  //servo6.write(135);  //180 -95 degrees
}

void loop() {
  if(error == 1) //skip loop if no controller found
    return; 
  
  // if(type == 2){ //Guitar Hero Controller
  //   ps2x.read_gamepad();          //read controller 
   
  //   if(ps2x.ButtonPressed(GREEN_FRET))
  //     Serial.println("Green Fret Pressed");
  //   if(ps2x.ButtonPressed(RED_FRET))
  //     Serial.println("Red Fret Pressed");
  //   if(ps2x.ButtonPressed(YELLOW_FRET))
  //     Serial.println("Yellow Fret Pressed");
  //   if(ps2x.ButtonPressed(BLUE_FRET))
  //     Serial.println("Blue Fret Pressed");
  //   if(ps2x.ButtonPressed(ORANGE_FRET))
  //     Serial.println("Orange Fret Pressed"); 

  //   if(ps2x.ButtonPressed(STAR_POWER))
  //     Serial.println("Star Power Command");
    
  //   if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
  //     Serial.println("Up Strum");
  //   if(ps2x.Button(DOWN_STRUM))
  //     Serial.println("DOWN Strum");
 
  //   if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
  //     Serial.println("Start is being held");
  //   if(ps2x.Button(PSB_SELECT))
  //     Serial.println("Select is being held");
    
  //   if(ps2x.Button(ORANGE_FRET)) {     // print stick value IF TRUE
  //     Serial.print("Wammy Bar Position:");
  //     Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
  //   } 
  // }
  //DualShock Controller
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
  
  // if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
  //   Serial.println("Start is being held");
  // if(ps2x.Button(PSB_SELECT))
  //   Serial.println("Select is being held");      

  if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  }
  if(ps2x.Button(PSB_PAD_RIGHT)){
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if(ps2x.Button(PSB_PAD_LEFT)){
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if(ps2x.Button(PSB_PAD_DOWN)){
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  }   

  //vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
  if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2x.Button(PSB_L3))
      Serial.println("L3 pressed");
    if(ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");
    if(ps2x.Button(PSB_L2))
      Serial.println("L2 pressed");
    if(ps2x.Button(PSB_R2))
      Serial.println("R2 pressed");
    if(ps2x.Button(PSB_TRIANGLE))
      Serial.println("Triangle pressed");        
  }

  if(ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
    Serial.println("Circle just pressed");
  if(ps2x.NewButtonState(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
    Serial.println("X just changed");
  if(ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
    Serial.println("Square just released");     

  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC); 
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC); 
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC); 
  }     

  // For base rotation
  if(ps2x.Analog(PSS_LX) < 128) {
    Serial.print("Base rotate clockwise\n");
    if(servo_base_angle < servo_base_angle_max)  {
      servo1.write(++servo_base_angle);
      delay(5);
    }
  }
  if(ps2x.Analog(PSS_LX) > 128) {
    Serial.print("Base rotate anti-clockwise\n");
    if(servo_base_angle > servo_base_angle_min)  {
      servo1.write(--servo_base_angle);
      delay(5);
    }
  }

  // For base arm up and down rotation
  if(ps2x.Analog(PSS_LY) < 128) {
    Serial.print("Base arm move downwards\n");
    if(servo_base_arm_angle > servo_base_arm_angle_min)  {
      servo2.write(--servo_base_arm_angle);
      delay(5);
    }
  }
  if(ps2x.Analog(PSS_LY) > 128) {
    Serial.print("Base arm move upwards\n");
    if(servo_base_arm_angle < servo_base_arm_angle_max)  {
      servo2.write(++servo_base_arm_angle);
      delay(5);
    }
  }


  // For mid arm up and down rotation
  if(ps2x.Analog(PSS_RY) > 128) {
    Serial.print("Mid arm move downwards\n");
    if(servo_mid_arm_angle > servo_mid_arm_angle_min)  {
      servo3.write(--servo_mid_arm_angle);
      delay(5);
    }
  }
  if(ps2x.Analog(PSS_RY) < 128) {
    Serial.print("Mid arm move upwards\n");
    if(servo_mid_arm_angle < servo_mid_arm_angle_max)  {
      servo3.write(++servo_mid_arm_angle);
      delay(5);
    }
  }

  // For neck rotation
  if(ps2x.Analog(PSS_RX) > 128) {
    Serial.print("Neck rotate clockwise\n");
    if(servo_neck_angle < servo_neck_angle_max)  {
      servo4.write(++servo_neck_angle);
      delay(5);
    }
  }
  if(ps2x.Analog(PSS_RX) < 128) {
    Serial.print("Neck rotate anti-clockwise\n");
    if(servo_neck_angle > servo_neck_angle_min)  {
      servo4.write(--servo_neck_angle);
      delay(5);
    }
  }

  // For gripper up and down rotation
  if(ps2x.Button(PSB_PAD_UP)) {
    Serial.print("Gripper move downwards\n");
    if(servo_gripper_angle > servo_gripper_angle_min)  {
      servo5.write(--servo_gripper_angle);
      delay(5);
    }
  }
  if(ps2x.Button(PSB_PAD_DOWN)) {
    Serial.print("Gripper move upwards\n");
    if(servo_gripper_angle < servo_gripper_angle_max)  {
      servo5.write(++servo_gripper_angle);
      delay(5);
    }
  }

  // For gripper open and close
  if(ps2x.Button(PSB_CIRCLE)) {
    Serial.print("Gripper opening\n");
    Serial.print("The angle of gripper is :");
    Serial.print(servo_gripper, DEC);
    Serial.print("/n");
    if(servo_gripper < servo_gripper_mid)  {
      servo6.write(++servo_gripper);
      delay(5);
    }
  }
  if(ps2x.Button(PSB_CROSS)) {
    Serial.print("Gripper closing\n");
    Serial.print("The angle of gripper is :");
    Serial.print(servo_gripper, DEC);
    Serial.print("/n");
    if(servo_gripper > servo_gripper_min)  {
      servo6.write(--servo_gripper);
      delay(5);
    }
  }

  delay(50);  
}
