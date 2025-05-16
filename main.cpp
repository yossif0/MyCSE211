#include "mbed.h"

// 7-Segment shift register pins
DigitalOut latch(D4);    // ST_CP
DigitalOut clockPin(D7); // SH_CP
DigitalOut data(D8);     // DS

// Buttons as interrupts
InterruptIn s1_button(A1);  // S1
InterruptIn s3_button(A3);  // S3
AnalogIn pot(A0);           // Potentiometer
Timer timer;

// 7-segment maps (Common Anode – inverted)
const char SEGMENT_MAP[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

// Digit enable (only one digit active at a time)
const char DIGIT_SELECT[4] = { 0x08, 0x04, 0x02, 0x01 };

Ticker displayTicker;

volatile bool counting = false;
volatile bool showVoltage = false;
volatile bool s1_flag = false;
volatile bool s3_flag = false;

int current_digit = 0;
int elapsedSeconds = 0;

// ISR for S1 press
void onS1Press() {
    s1_flag = true;
}

// ISR for S3 press
void onS3Press() {
    s3_flag = true;
}

// ShiftOut function to send data to shift registers
void shiftOut(char dataOut) {
    for (int i = 7; i >= 0; i--) {
        clockPin = 0;
        data = (dataOut >> i) & 0x01;
        clockPin = 1;
    }
}

// Update display each 1 ms (adjusted for smoother display)
void updateDisplay() {
    int digits[4];

    if (showVoltage) {
        float voltage = pot.read() * 3.3f;
        int volt = (int)(voltage * 100); // e.g., 3.27V -> 327

        digits[0] = volt % 10;           // ones
        digits[1] = (volt / 10) % 10;    // tens
        digits[2] = (volt / 100) % 10;   // hundreds
        digits[3] = 0;                   // blank
    } else {
        if (counting)
            elapsedSeconds = (int)timer.read(); // Cast to int

        int minutes = elapsedSeconds / 60;
        int seconds = elapsedSeconds % 60;

        digits[0] = seconds % 10;
        digits[1] = seconds / 10;
        digits[2] = minutes % 10;
        digits[3] = minutes / 10;
    }

    // Display current digit
    latch = 0;
    shiftOut(SEGMENT_MAP[digits[current_digit]]);
    shiftOut(DIGIT_SELECT[current_digit]);
    latch = 1;

    current_digit = (current_digit + 1) % 4;
}

int main() {
    s1_button.mode(PullUp);
    s3_button.mode(PullUp);
    s1_button.fall(&onS1Press);
    s3_button.fall(&onS3Press);

    timer.reset();
    displayTicker.attach_us(&updateDisplay, 1000); // every 1ms

    while (true) {
        if (s1_flag) {
            s1_flag = false;
            counting = !counting;

            if (counting) {
                timer.reset();
                timer.start();
            } else {
                timer.stop();
                elapsedSeconds = 0;
            }
        }

        if (s3_flag) {
            s3_flag = false;
            showVoltage = !showVoltage;
        }

ThisThread::sleep_for(100);
    }
}