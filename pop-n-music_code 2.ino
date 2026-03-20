#include <Keyboard.h>

const int buttonPins[9] =  {2, 3, 4, 5, 6, 7, 8, 9, 10};
const char keyMap[9] =     {'a', 's', 'd', 'f', ' ', 'j', 'k', 'l', ';'};

bool buttonState[9] = {0};
bool lastButtonState[9] = {0};
unsigned long lastDebounceTime[9] = {0};
const unsigned long debounceDelay = 50;

void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < 9; i++) {
    int reading = digitalRead(buttonPins[i]);

    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;

        if (buttonState[i] == LOW) {
          Keyboard.press(keyMap[i]);
        } else {
          Keyboard.release(keyMap[i]);
        }
      }
    }

    lastButtonState[i] = reading;
  }
}
