    #include <EnableInterrupt.h>
    
    #define SERIAL_PORT_SPEED 9600
    #define RC_NUM_CHANNELS  4
    
    #define RC_CH1  0
    #define RC_CH2  1
    #define RC_CH3  2
    #define RC_CH4  3
    
    #define RC_CH1_PIN  12
    #define RC_CH2_PIN  9
    #define RC_CH3_PIN  8
    #define RC_CH4_PIN  7
    
    uint16_t rc_values[RC_NUM_CHANNELS];
    uint32_t rc_start[RC_NUM_CHANNELS];
    volatile uint16_t rc_shared[RC_NUM_CHANNELS];
    
    void rc_read_values() {
      noInterrupts();
      memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
      interrupts();
    }
    
    void calc_input(uint8_t channel, uint8_t input_pin) {
      if (digitalRead(input_pin) == HIGH) {
        rc_start[channel] = micros();
      } else {
        uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
        rc_shared[channel] = rc_compare;
      }
    }
    
    void calc_ch1() {
      calc_input(RC_CH1, RC_CH1_PIN);
    }
    void calc_ch2() {
      calc_input(RC_CH2, RC_CH2_PIN);
    }
    void calc_ch3() {
      calc_input(RC_CH3, RC_CH3_PIN);
    }
    void calc_ch4() {
      calc_input(RC_CH4, RC_CH4_PIN);
    }
    
    void setup() {
      Serial.begin(SERIAL_PORT_SPEED);
    
      pinMode(RC_CH1_PIN, INPUT); //side wheel
      pinMode(RC_CH2_PIN, INPUT); //trigger
      pinMode(RC_CH3_PIN, INPUT); // side knob
      pinMode(RC_CH4_PIN, INPUT); //bottom button
    
      enableInterrupt(RC_CH1_PIN, calc_ch1, CHANGE);
      enableInterrupt(RC_CH2_PIN, calc_ch2, CHANGE);
      enableInterrupt(RC_CH3_PIN, calc_ch3, CHANGE);
      enableInterrupt(RC_CH4_PIN, calc_ch4, CHANGE);
    
      pinMode(3, OUTPUT);
      pinMode(5, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(10, OUTPUT);
    }
    
    void loop() {
      rc_read_values();
    
      //  Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
      //  Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
      //  Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
      //  Serial.print("CH4:"); Serial.println(rc_values[RC_CH4]);
    
      delay(200);
    
      // robot moving forward and in reverse using Hobby RC controller
      if (rc_values[RC_CH2] > 1600) {
        forward(map(rc_values[RC_CH2], 1600, 2100, 0, 255));
      }
      else if (rc_values[RC_CH2] < 1400) reverse(map(rc_values[RC_CH2], 1400, 900, 0, 255));
    
      // robot moving right and left using Hobby RC controller
    
      else if (rc_values[RC_CH1] > 1600) right(map(rc_values[RC_CH1], 1600, 2100, 0, 255));
      else if (rc_values[RC_CH1] < 1400) left (map(rc_values[RC_CH1], 1400, 900, 0, 255));
      else stop();
    
    
    }
    
    void reverse(int speed) {
      Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]);
      Serial.print(" front: "); Serial.println(speed);
      analogWrite(3, 0);
      analogWrite(5, speed);
      analogWrite(6, 0);
      analogWrite(10, speed);
    
    }
    
    void forward(int speed) {
      Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]);
      Serial.print(" back: "); Serial.println(speed);
      analogWrite(3, speed);
      analogWrite(5, 0);
      analogWrite(6, speed);
      analogWrite(10, 0);
    
    }
    
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
    
    
    void stop() {
      analogWrite(3, 0);
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(10, 0);
    }