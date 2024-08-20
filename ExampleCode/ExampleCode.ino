#include <Wire.h>
#include <Adafruit_MPR121.h>

#define BUZZER_PIN 39
#define MPR121_ADDR1 0x5A
#define MPR121_ADDR2 0x5B
Adafruit_MPR121 mpr121_1 = Adafruit_MPR121();
Adafruit_MPR121 mpr121_2 = Adafruit_MPR121();

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  Wire.begin();
  if (!mpr121_1.begin(MPR121_ADDR1)) {
    Serial.println("Failed to connect to MPR121 sensor 1.");
    while (1);
  }
  if (!mpr121_2.begin(MPR121_ADDR2)) {
    Serial.println("Failed to connect to MPR121 sensor 2.");
    while (1);
  }
  Serial.println("MPR121 sensors connected successfully.");
}

void loop() {
  uint16_t touch1 = mpr121_1.touched();
  uint16_t touch2 = mpr121_2.touched();

  for (int i = 0; i < 12; i++) {
    if (touch1 & (1 << i)) {
      playNoteOnBuzzer(i + 1);
    }
  }

  for (int i = 0; i < 12; i++) {
    if (touch2 & (1 << i)) {
      playNoteOnBuzzer(i + 13);
    }
  }
  delay(100);
}

void playNoteOnBuzzer(int note) {
  int frequency;
  
  
  switch (note) {
    case 1:  frequency = 261; break; //start from middle C
    case 2:  frequency = 293; break; 
    case 3:  frequency = 329; break; 
    case 4:  frequency = 349; break; 
    case 5:  frequency = 392; break; 
    case 6:  frequency = 440; break; 
    case 7:  frequency = 493; break; 
    case 8:  frequency = 523; break; 
    case 9:  frequency = 587; break; 
    case 10: frequency = 659; break; 
    case 11: frequency = 698; break; 
    case 12: frequency = 784; break; 
    case 13: frequency = 880; break; 
    case 14: frequency = 987; break; 
    case 15: frequency = 1047; break;
    case 16: frequency = 1175; break;
    case 17: frequency = 1319; break;
    case 18: frequency = 1397; break;
    case 19: frequency = 1568; break;
    case 20: frequency = 1760; break;
    case 21: frequency = 1976; break;
    case 22: frequency = 2093; break;
    case 23: frequency = 2349; break;
    case 24: frequency = 2637; break;
    case 25: frequency = 2794; break; (default 25th note)
    default: frequency = 0; break; 
  }

  if (frequency > 0) {
    tone(BUZZER_PIN, frequency);
  } else {
    noTone(BUZZER_PIN);
  }
}
