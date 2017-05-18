#include <Servo.h>

typedef union short2byte{
    uint16_t Duty;
    uint8_t  b[2];
}Short2Byte;

Short2Byte ServoDuty;
Servo s;

void setup() {
    s.attach(3);
    Serial.begin(115200);
    s.writeMicroseconds(1500);
}

void loop() {

}
