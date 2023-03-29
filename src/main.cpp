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
const int xAxis = A0;
const int yAxis = A1;

int range = 12;             // output range of X or Y movement
int responseDelay = 5;
int threshold = range / 4;
int center = range / 2;

bool mouseIsActive = true;

int debounce = 100;

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

int readAxis(int thisAxis) {
    // read the analog input:
    int reading = analogRead(thisAxis);
    Serial.print(reading);
    Serial.print("\n");

    // map the reading from the analog input range to the output range:
    reading = map(reading, 0, 1023, 0, range);

    // if the output reading is outside from the rest position threshold, use it:
    int distance = reading - center;

    if (abs(distance) < threshold) {
        distance = 0;
    }

    // return the distance for this axis:
    return distance;
}


void stick() {
    int xReading = readAxis(xAxis);
    int yReading = readAxis(yAxis);

    if (mouseIsActive) {
        Mouse.move(xReading, yReading, 0);
    }

    delay(responseDelay);
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