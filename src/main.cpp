#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Joystick.h>
//#include <Adafruit_NeoPixel.h>

// set pins for mouse buttons
const int leftClick = 2;
const int rightClick = 3;
const int middleClick = 4;

// set pins for mouse toggle
const int leftClickToggle = 5;
const int rightClickToggle = 6;
const int middleClickToggle = 7;

// set pins for joystick
int const AXIS_X_PIN = A0;
int const AXIS_Y_PIN = A1;

const int encoderA = 8;
const int encoderB = 9;

int lastXAxisValue = -1;
int lastYAxisValue = -1;

Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 0,
                     0, true, true, false,
                     false, false, false,
                     false, false, false,
                     false, false);

void scroll() {
    if (digitalRead(encoderA) > digitalRead(encoderB)) {
        Mouse.move(0, 0, 1);
        delay(50);
        return;
    }
    if (digitalRead(encoderB) > digitalRead(encoderA)) {
        Mouse.move(0, 0, -1);
        delay(50);
        return;
    }
}

void setup() {
    // mouse buttons
    pinMode(rightClick, INPUT_PULLUP);
    pinMode(leftClick, INPUT_PULLUP);
    pinMode(middleClick, INPUT_PULLUP);
    // mouse toggles
    pinMode(rightClickToggle, INPUT_PULLUP);
    pinMode(leftClickToggle, INPUT_PULLUP);
    pinMode(middleClickToggle, INPUT_PULLUP);
    //encoder
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);

    Mouse.begin();
    Keyboard.begin();

    controller.setXAxisRange(0, 1023);
    controller.setYAxisRange(1023, 0);
    controller.begin(false);

    Serial.begin(9600);
}

void loop() {
    // click
    if (digitalRead(rightClick) == LOW) {
        Mouse.click(MOUSE_RIGHT);
    }
    if (digitalRead(middleClick) == LOW) {
        Mouse.click(MOUSE_MIDDLE);
    }
    if (digitalRead(leftClick) == LOW) {
        Mouse.click(MOUSE_LEFT);
    }
    //encoder stuff
    scroll();

    // joystick
    bool sendUpdate = false;
    // x-axis
    const int nowXAxisValue = analogRead(AXIS_X_PIN);
    if (nowXAxisValue != lastXAxisValue) {
        lastXAxisValue = nowXAxisValue;
        sendUpdate = true;
    }
    // y-axis
    const int nowYAxisValue = analogRead(AXIS_Y_PIN);
    if (nowYAxisValue != lastYAxisValue) {
        lastYAxisValue = nowYAxisValue;
        sendUpdate = true;
    }
    if (sendUpdate) {
        controller.sendState();
    }
    delay(1);
}