# Preforming_Robots

## Final Robot
[Video Link](https://www.youtube.com/shorts/Z11REMjYteA?si=B3Kr4TuOJMTn-b3M)
![](https://github.com/fnassar/Preforming_Robots/blob/main/images/robot4.jpg)
![](https://github.com/fnassar/Preforming_Robots/blob/main/images/robot3.jpg)
![](https://github.com/fnassar/Preforming_Robots/blob/main/images/robot2.jpg)
![](https://github.com/fnassar/Preforming_Robots/blob/main/images/robot1.jpg)


## September 18
### Robot-1 Base

### Robot Sketch
<img src="https://github.com/fnassar/Preforming_Robots/blob/main/robot_1/sketch-robot-1.jpg" alt="Sketch, Robot 1" width="600"/>

### -> Project and Idea by Jannah and Fatema

## September 24
### Story
[Music](https://www.youtube.com/watch?v=lRXLAeogv5U)

## October 1
### [video with controler](https://youtube.com/shorts/kRtGvE6MrPE?si=v4go1Dmkk7r4-h21)
### [code]()

## October 16
### Proposed Performance Script
#### Idenity:
Robot characters: 
- 3antar -> Jannah and Fatema -> Identity: (egyptian/arab)
- < name1 > -> Hamad and Yerk -> Identity: (Exploring/finding/understanding) --suggestion
- < name2 > -> Shanaia and Aadhar -> Identity: (South Aisian) --suggestion
- < name3 > -> Nouf and Shaikha -> Identity: (Emarati/Gulf) --suggestion
- < name4 > -> Akhat and Yunho -> Identity: (central/east aisian?) --suggestion
- < name5 > -> Andres and Ryan -> Identity: (Exploring/finding/understanding) --suggestion
- < name6 > -> Akif and Marta -> Therapist/counselor robot

__The idea__ is of a comedic script showing a group of robots trying to find room to fit in in a new enviroment.\

#### __ACT 1__: 2 humans woke up as robots and are left confused
name5  *to no one in particular*: ** "I woke up today and I was not human, a new world of robots and I am trying to find my path"\
name2  *to <name5>*: ** "Dude, same I dont know what's happening. There seems to be groups over there, idk man I am confusedddd"\
name5  *to <name2>*: ** "wait u too? this is sadd, what about our human form what where you"\
name2  *to <name5>*: ** "Heh, I was a mix of stuff. OOOOOOOO THAT IS WHY I CAME UP IN NO GROUPS"\
name5  *to <name2>*: ** "Ohh... me too. i guess"\

#### __ACT 2__: 2 older robots talking before they notice the other 2 robots in the back confused and maybe crying
*3antar dancing in the middle*\
*name3  comes up to them*\
name3 : ** *sarcastic but annoyed* "my man what are you doing! I am betraying my wires to get married here what are you doing please"\
3antar: ** *dramaticly* "girl! you think my creator is happy with this, I will end up running away, at least the egyptian batteries are still giving me life, I could be dead"\
name3 : ** *sighs* "why do I even..."\
name3 : ** *sees name2 and name5* "wait are they lost, 3antar look at them they're looping around they'll break their wires"\

*3antar and name3 go up to name2 and name5*\
3antar: ** "yoooo, y'all good?"\
name3 : ** *whispers* "do they look good? be nice""what do i see in him idk"\
name5 : ** "man I was human yesterday I have no clue what's happening"\
name2 : ** *Screatching* "dudddeeee me toooo dont leave me out of this"\
name5 : ** *says while sighing* "are you always like this?" "I am trying to get help here can u please just let me be for a second" *under his breath* "so childish"\
name2 : ** "okok im sorry do your thing, u better get me in on this tho" *toung out sound* *turns around and acts sad*\
name5 : ** "ill deal with him, name3, 3antar help please."\

# Robot Design:
<img src="https://github.com/fnassar/Preforming_Robots/blob/main/images/cactus.jpg" alt="base1" height="500"/>

# Robot Production:
## Mechanics: 
### Design:
<img src="https://github.com/fnassar/Preforming_Robots/blob/main/images/robot1.jpg" alt="robot1" height="500"/>
First, we designed the robot on fusion and decided to add the motors at every moving part of the body

### WOOD ROBOT:

Then we built the wood in wood to check how the mechanism will work

<img src="https://github.com/fnassar/Preforming_Robots/blob/main/images/robot2.jpg" alt="robot1" height="500"/>

### Metal:

We last built the robot with aluminum to reduce the weight of the robot's body to help its over all stability.

We added wood braces, to hold the fabric we plan to dress the robot with.

<img src="https://github.com/fnassar/Preforming_Robots/blob/main/images/robot3.jpg" alt="robot1" height="500"/>

### Challenges:

Our main challenges were:
- Dealing with aluminum was a lot harder than wood, it was harder to drill, and stabilize.
- Stabilizing the aluminum rods on the shaft was a main struggle
  - We first tried to drill holes in the motor shaft to control the stability, but it was harder than expected to drill a hole in the steel shaft.
  - Finally, we decided to weld the shaft to the hub to keep the metal rods from moving around
 - the robot's stability was still affected and we had to extend the front and back wheels to make it more stable and prevent it from toppling over

### Final Robot:

<img src="https://github.com/fnassar/Preforming_Robots/blob/main/images/robot4.jpg" alt="robot1" height="500"/>

## Code:

### Wheels:
#### Main Difference:
The different thing we added to the wheels was the speed, we mapped the RC controller input to the speed and passed it to the forward, reverse, left and right functions that control the movements:
```
    if (rc_values[RC_CH2] > 1600) {
      forward(map(rc_values[RC_CH2], 1600, 2100, 0, 255));
    }
    else if (rc_values[RC_CH2] < 1400) reverse(map(rc_values[RC_CH2], 1400, 900, 0, 255));
    // robot moving right and left using Hobby RC controller
    else if (rc_values[RC_CH1] > 1600) right(map(rc_values[RC_CH1], 1600, 2100, 0, 255));
    else if (rc_values[RC_CH1] < 1400) left (map(rc_values[RC_CH1], 1400, 900, 0, 255));
    else stop();
```
The code for the different motions is as follows:
- Backward:
```
    void reverse(int speed) {
      Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]);
      Serial.print(" front: "); Serial.println(speed);
      analogWrite(3, 0);
      analogWrite(5, speed);
      analogWrite(6, 0);
      analogWrite(10, speed);
    
    }
```
- Forward:
```
    
    void forward(int speed) {
      Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]);
      Serial.print(" back: "); Serial.println(speed);
      analogWrite(3, speed);
      analogWrite(5, 0);
      analogWrite(6, speed);
      analogWrite(10, 0);
    
    }
```
- Right and left
  - for this one, we made the motion so that the wheels move in opposite directions
```
    
    void right(int speed) {
      Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]);
      Serial.print(" right: "); Serial.println(speed);
      analogWrite(3, 0);
      analogWrite(5, speed);
      analogWrite(6, speed);
      analogWrite(10, 0);
    
    }
    
    void left(int speed) {
      Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]);
      Serial.print(" left: "); Serial.println(speed);
      analogWrite(3, speed);
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(10, speed);
    
    }
```
- The stop was to control when the robot was not moving.
```   
    
    void stop() {
      analogWrite(3, 0);
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(10, 0);
    }
```
### Transmitter:
- For the transmitter we tried to use an extra button to stop the robot from all the receiver control, but we ran into errors so instead we used the inputs as follows with 18 being the one to stop the motion:
```
char* theStates[] = {
  "0 robot nothing",
  "1 robot line1",
  "2 robot line2",
  "3 robot line3",
  "4 robot line4",
  "5 robot line5",
  "6 robot line6",
  "7 robot line7",
  "8 robot line8",
  "9 robot line9",
  "10 robot line10",
  "11 robot monologue",
  "12 robot alejandro",
  "13 robot agreed",
  "14 robot GASP",
  "15 robot wohoo",
  "16 robot SHIKSHAK",
  "17 robot seto ana",
  "18 stop",
};
``` 

### Receiver:
- We had many challenges with the receiver:
  - first was the fact that our code needs to run in loops, however, the code with the receiver & transmitter stopped that, so we added case codes with loops inside that were controlled by the sound playing, the loop ends when the sound ends:
```
    case 1:
        Serial.println(F("Playing track 001"));
        musicPlayer.startPlayingFile("/track1.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;
```
- each case controlled a specific audio, and we added the data.stateNumber == 18 to stop the code from executing when 18 is transmitted.
- One other struggle we had was that 2 of the audio files would not play, we weren't sure why.
  - to figure it out, we printed the names of everything on the SD card, and we found that the names were not being read, as they were longer than 8 characters.
  - We reduced the names of all our audio to 8 characters then it worked perfectly.
 
- We used millis to control different items looping together.
- Our looping cases:
  - led strip around the robot
```
void ledStrip() {
  unsigned long currentMillis = millis();
  // Handling the other LED strip
  if (currentMillis - previousMillis >= interval2) {
    previousMillis = currentMillis;

    pixelsOther.clear();
    pixelsOther.setPixelColor(currentLED, pixelsOther.Color(random(255), random(255), random(255)));
    pixelsOther.show();

    currentLED = (currentLED + 1) % NUMPIXELS_OTHER;
  }
}
```
  - Dancing:
```

void dance() {
  unsigned long currentMillis = millis();
  Serial.print("servo: ");

  if ((unsigned long)(currentMillis - previousMillis2) >= interval) {
    previousMillis2 = currentMillis;
    myservo1.write(pos);
    myservo2.write(pos2);
    myservo3.write(pos3);
    // check direction and add for one/ subtract for one
    if (flag) {
      pos -= 1;
      pos2 -= 1;
      pos3 -= 1;
    } else {
      pos += 1;
      pos2 += 1;
      pos3 += 1;
    }
    // check location and change flag if direction will change
    if (pos >= pos12) {
      flag = true;
    }
    if (pos <= pos11) {
      flag = false;
    }
  }
}
```
  - Talking Mouth
```
void talkingMouth() {
  unsigned long currentMouthMillis = millis();
  if (currentState == 0) {                                                                           // Closed mouth
    displayMouth(pixelsMouth, mouthClosed, sizeof(mouthClosed) / sizeof(mouthClosed[0]), 0xFF0000);  // Change color as needed
    if (currentMouthMillis - previousMouthMillis >= CLOSED_DELAY) {
      previousMouthMillis = currentMouthMillis;
      currentState = 1;  // Change state to open mouth
    }
  } else {                                                                                     // Open mouth
    displayMouth(pixelsMouth, mouthOpen, sizeof(mouthOpen) / sizeof(mouthOpen[0]), 0xFF0000);  // Change color as needed
    if (currentMouthMillis - previousMouthMillis >= OPEN_DELAY) {
      previousMouthMillis = currentMouthMillis;
      currentState = 0;  // Change state to closed mouth
    }
  }
}
```

