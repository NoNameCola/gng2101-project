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

// const int encoderA = 8;
// const int encoderB = 9;

int lastXAxisValue = -1;
int lastYAxisValue = -1;
int debounce = 100;

Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 0,
                     0, true, true, false,
                     false, false, false,
                     false, false, false,
                     false, false);
/*
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
*/
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
    }
    else {
        Mouse.release(MOUSE_RIGHT);
    }

    if (digitalRead(middleClickToggle) == LOW) {
        Mouse.press(MOUSE_MIDDLE);
        Serial.print("middle click toggle");
        Serial.print("\n");
    }
    else {
        Mouse.release(MOUSE_MIDDLE);
    }

    if (digitalRead(leftClickToggle) == LOW) {
        Mouse.press(MOUSE_LEFT);
        Serial.print("left click toggle");
        Serial.print("\n");
    }
    else {
        Mouse.release(MOUSE_LEFT);
    }

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
    // encoder
    // pinMode(encoderA, INPUT);
    // pinMode(encoderB, INPUT);

    Mouse.begin();
    Keyboard.begin();

    controller.setXAxisRange(0, 1023);
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
    bool sendUpdate = false;
    // x-axis
    const int nowXAxisValue = analogRead(AXIS_X_PIN);
    if (nowXAxisValue != lastXAxisValue) {
        lastXAxisValue = nowXAxisValue;
        Serial.print("X-value");
        Serial.print(nowXAxisValue);
        Serial.print('\n');
        sendUpdate = true;
    }
    // y-axis
    const int nowYAxisValue = analogRead(AXIS_Y_PIN);
    if (nowYAxisValue != lastYAxisValue) {
        lastYAxisValue = nowYAxisValue;
        Serial.print("Y-value");
        Serial.print(nowYAxisValue);
        Serial.print('\n');
        sendUpdate = true;
    }
    if (sendUpdate) {
        controller.sendState();
    }

    if (digitalRead(stop) == LOW)   {
        Mouse.end();
    }
    delay(50);
}