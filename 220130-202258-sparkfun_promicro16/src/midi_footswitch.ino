/**
 * @file midi_footswitch.ino
 * @author Florian Grabmeier (https://github.com/flooxo/midi-usb-box)
 * @brief
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "MIDIUSB.h"
#include <Bounce2.h>

//---------------------| attributes |---------------------//
// buttons
Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();
Bounce2::Button button5 = Bounce2::Button();
Bounce2::Button button6 = Bounce2::Button();
Bounce2::Button button7 = Bounce2::Button();
Bounce2::Button button8 = Bounce2::Button();

// leds
uint8_t ledPin[] = {10, 16, 14, 15};
uint8_t ledState[] = {LOW, LOW, LOW, LOW};
bool ledChanged[] = {false, false, false, false};

// delay
uint32_t interval[] = {500, 250, 100, 1000}; // ms
unsigned long previousMillis[] = {0, 0, 0, 0};

//--------------------| MIDI-signal |--------------------//
void noteOn(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
    MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
    MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
    midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
    MidiUSB.sendMIDI(event);
}

//-------------------| initalisation |-------------------//
void setup() {
    delay(2000);
    Serial.begin(115200);
    Serial.println("Booting....");

    setupButtons();
    setupLeds();

    Serial.println("Boot finished!");
}

void setupButtons() {
    button1.attach(9, INPUT_PULLUP);
    button1.interval(5);

    button2.attach(2, INPUT_PULLUP);
    button2.interval(5);

    button3.attach(3, INPUT_PULLUP);
    button3.interval(5);

    button4.attach(4, INPUT_PULLUP);
    button4.interval(5);

    button5.attach(5, INPUT_PULLUP);
    button5.interval(5);

    button6.attach(6, INPUT_PULLUP);
    button6.interval(5);

    button7.attach(7, INPUT_PULLUP);
    button7.interval(5);

    button8.attach(8, INPUT_PULLUP);
    button8.interval(5);
}

void setupLeds() {
    for (int i = 0; i < sizeof(ledPin) / sizeof(ledPin[0]); i++) {
        pinMode(ledPin[i], OUTPUT);
        digitalWrite(ledPin[i], ledState[i]);
    }

    // boot animation
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[3], HIGH);
    delay(300);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);
    delay(300);
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], LOW);
    digitalWrite(ledPin[3], LOW);
}

//------------------------| main |------------------------//
void loop() {
    updateButtons();
    updateLeds();
}

//------------------------| LEDs |------------------------//
void updateLeds() {
    for (int i = 0; i < sizeof(ledPin) / sizeof(ledPin[0]); i++) {
        unsigned long currentMillis = millis();
        if (ledChanged[i] && currentMillis - previousMillis[i] >= interval[i]) {
            previousMillis[i] = currentMillis;
            if (ledState[i] == LOW) {
                ledState[i] = HIGH;
            } else {
                ledState[i] = LOW;
            }
            digitalWrite(ledPin[i], ledState[i]);
        } else if (!ledChanged[i]) {
            ledState[i] = LOW;
            digitalWrite(ledPin[i], ledState[i]);
        }
    }
}

//----------------------| buttons |----------------------//
void updateButtons() {
    if (button1.update()) {
        ledChanged[0] = !ledChanged[0]; // change to button is pressed or not
        if (button1.released()) {
            noteOn(0, 48, 64);
            MidiUSB.flush();
        } else if (button1.pressed()) {
            noteOff(0, 48, 64);
            MidiUSB.flush();
        }
    }

    if (button2.update()) {
        ledChanged[1] = !ledChanged[1];
        if (button2.released()) {
            noteOn(0, 50, 64);
            MidiUSB.flush();
        } else if (button2.pressed()) {
            noteOff(0, 50, 64);
            MidiUSB.flush();
        }
    }

    if (button3.update()) {
        if (button3.released()) {
            pageDownAnimation();
            // ledChanged[2] = true;
            // noteOn(0, 52, 64);
            // MidiUSB.flush();
        } else if (button3.pressed()) {
            pageDownAnimation();
            // ledChanged[2] = false;
            // noteOff(0, 52, 64);
            // MidiUSB.flush();
        }
    }

    if (button4.update()) {
        if (button4.released()) {
            pageUpAnimation();
            // noteOn(0, 54, 64);
            // MidiUSB.flush();
        } else if (button4.pressed()) {
            pageUpAnimation();
            // ledChanged[3] = false;
            // noteOff(0, 54, 64);
            // MidiUSB.flush();
        }
    }

    button5.update();
    if (button5.released()) {
        noteOn(0, 56, 64);
        MidiUSB.flush();
    } else if (button5.pressed()) {
        noteOff(0, 56, 64);
        MidiUSB.flush();
    }

    button6.update();
    if (button6.released()) {
        noteOn(0, 58, 64);
        MidiUSB.flush();
    } else if (button6.pressed()) {
        noteOff(0, 58, 64);
        MidiUSB.flush();
    }

    button7.update();
    if (button7.released()) {
        noteOn(0, 60, 64);
        MidiUSB.flush();
    } else if (button7.pressed()) {
        noteOff(0, 60, 64);
        MidiUSB.flush();
    }

    button8.update();
    if (button8.released()) {
        noteOn(0, 62, 64);
        MidiUSB.flush();
    } else if (button8.pressed()) {
        noteOff(0, 62, 64);
        MidiUSB.flush();
    }
}

// FIX remove delay
void pageDownAnimation() {
    for (int i = sizeof(ledPin) / sizeof(ledPin[0]) - 1; i >= 0; i--) {
        digitalWrite(ledPin[i], LOW);
    }
    delay(250);
    for (int i = sizeof(ledPin) / sizeof(ledPin[0]) - 1; i >= 0; i--) {
        digitalWrite(ledPin[i], HIGH);
        delay(75);
    }
    for (int i = sizeof(ledPin) / sizeof(ledPin[0]) - 1; i >= 0; i--) {
        digitalWrite(ledPin[i], LOW);
        delay(50);
    }
}

void pageUpAnimation() {
    for (int i = sizeof(ledPin) / sizeof(ledPin[0]) - 1; i >= 0; i--) {
        digitalWrite(ledPin[i], LOW);
    }
    delay(250);
    for (int i = 0; i < sizeof(ledPin) / sizeof(ledPin[0]); i++) {
        digitalWrite(ledPin[i], HIGH);
        delay(75);
    }
    for (int i = 0; i < sizeof(ledPin) / sizeof(ledPin[0]); i++) {
        digitalWrite(ledPin[i], LOW);
        delay(50);
    }
}