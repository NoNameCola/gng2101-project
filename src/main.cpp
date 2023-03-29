#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Joystick.h>
//#include <Adafruit_NeoPixel.h>

// set pins for mouse buttons
const int leftClick = 0;
const int rightClick = 1;
const int middleClick = 2;
const int stop = 3;

// set pins for mouse toggle
const int leftClickToggle = 8;
const int rightClickToggle = 9;
const int middleClickToggle = 10;

// set pins for joystick
int const AXIS_X_PIN = A0;
int const AXIS_Y_PIN = A1;

int lastXAxisValue = -1;
int lastYAxisValue = -1;

const bool testAutoSendMode = false;

const unsigned long gcCycleDelta = 1000;
const unsigned long gcAnalogDelta = 25;
const unsigned long gcButtonDelta = 500;
unsigned long gNextTime = 0;
unsigned int gCurrentStep = 0;

int debounce = 100;

Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 0,
                     0, true, true, false,
                     false, false, false,
                     false, false, false,
                     false, false);

void mouse() {
    if (digitalRead(rightClick) == LOW) {
        Mouse.click(MOUSE_RIGHT);
        Serial.print("right click");
        Serial.print("\n");
        delay(debounce);
    }
    if (digitalRead(middleClick) == LOW) {
        Mouse.click(MOUSE_MIDDLE);
        Serial.print("middle click");
        Serial.print("\n");
        delay(debounce);
    }
    if (digitalRead(leftClick) == LOW) {
        Mouse.click(MOUSE_LEFT);
        Serial.print("left click");
        Serial.print("\n");
        delay(debounce);
    }

    if (digitalRead(rightClickToggle) == LOW) {
        Mouse.press(MOUSE_RIGHT);
        Serial.print("right click toggle");
        Serial.print("\n");
    } else {
        Mouse.release(MOUSE_RIGHT);
    }

    if (digitalRead(middleClickToggle) == LOW) {
        Mouse.press(MOUSE_MIDDLE);
        Serial.print("middle click toggle");
        Serial.print("\n");
    } else {
        Mouse.release(MOUSE_MIDDLE);
    }

    if (digitalRead(leftClickToggle) == LOW) {
        Mouse.press(MOUSE_LEFT);
        Serial.print("left click toggle");
        Serial.print("\n");
    } else {
        Mouse.release(MOUSE_LEFT);
    }
}

void stick() {
    bool sendUpdate = false;
    const int currentXAxisValue = analogRead(AXIS_X_PIN);
    if (currentXAxisValue != lastXAxisValue)
    {
        controller.setXAxis(currentXAxisValue);
        lastXAxisValue = currentXAxisValue;
        sendUpdate = true;
    }

    const int currentYAxisValue = analogRead(AXIS_Y_PIN);
    if (currentYAxisValue != lastYAxisValue)
    {
        controller.setYAxis(currentYAxisValue);
        lastYAxisValue = currentYAxisValue;
        sendUpdate = true;
    }

    if (sendUpdate)
    {
        controller.sendState();
    }
    delay(50);
}

void setup() {
    // mouse buttons
    pinMode(rightClick, INPUT_PULLUP);
    pinMode(leftClick, INPUT_PULLUP);
    pinMode(middleClick, INPUT_PULLUP);
    pinMode(stop, INPUT_PULLUP);
    // mouse toggles
    pinMode(rightClickToggle, INPUT_PULLUP);
    pinMode(leftClickToggle, INPUT_PULLUP);
    pinMode(middleClickToggle, INPUT_PULLUP);

    Mouse.begin();
    Keyboard.begin();

    controller.setYAxisRange(0, 1023);
    controller.setYAxisRange(1023, 0);
    controller.begin(false);

    Serial.begin(9600);
}

void loop() {
    // click
    mouse();
    //encoder stuff
    //scroll();

    // joystick
    stick();

    if (digitalRead(stop) == LOW) {
        Mouse.end();
    }
    delay(50);
}