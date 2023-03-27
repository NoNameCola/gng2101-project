#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Joystick.h>

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

int lastXAxisValue = -1;
int lastYAxisValue = -1;

/*
Joystick_ Joystick(bool includeZAxis = false, bool includeRxAxis = false,
                   bool includeRyAxis = false, bool includeRzAxis = false,
                   bool includeRudder = false, bool includeThrottle = false,
                   bool includeAccelerator = false, bool includeBrake = false,
                   bool includeSteering = false);
const unsigned long gcCycleDelta = 1000;
const unsigned long gcAnalogDelta = 25;
const unsigned long gcButtonDelta = 500;
unsigned long gNextTime = 0;
unsigned int gCurrentStep = 0;
*/

Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 0,
                     0, true, true, false,
                     false, false, false,
                     false, false, false,
                     false, false);

void XYAxiis() {
    controller.setXAxisRange(0, 1023);
    controller.setYAxisRange(1023, 0);
    controller.begin(false);
};

void setup() {
    // mouse buttons
    pinMode(rightClick, INPUT_PULLUP);
    pinMode(leftClick, INPUT_PULLUP);
    pinMode(middleClick, INPUT_PULLUP);
    // mouse toggles
    pinMode(rightClickToggle, INPUT_PULLUP);
    pinMode(leftClickToggle, INPUT_PULLUP);
    pinMode(middleClickToggle, INPUT_PULLUP);
    // joystick input pins
    // pinMode(joyXAxis,INPUT);
    // pinMode(joyYAxis, INPUT);
    /*
    Joystick().setXAxisRange(-127, 127);
    Joystick().setYAxisRange(-127, 127);
    */
    Mouse.begin();
    Keyboard.begin();
    //Joystick().begin();
    XYAxiis();

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