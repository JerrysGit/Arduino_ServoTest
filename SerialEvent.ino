void serialEvent(){
    static uint8_t RxState = 0, RxCount = 0, RxCks = 0;
    uint8_t temp[16];
    while (Serial.available()) {
        switch(RxState){
            case 0:
                if(Serial.read() == 0xAA){
                    digitalWrite(LED_BUILTIN, HIGH); 
                    RxState++;
                }
                break;
            case 1:
                if(Serial.read() == 0x55)
                    RxState++;
                else
                    RxState = 0;
                break;
            case 2:      
                if(Serial.read() == 0xE1)
                    RxState++;
                else
                    RxState = 0;
                break;
            case 3:
                if(Serial.read() == 0x03)
                    RxState++;
                else
                    RxState = 0;
                break;  
            case 4:
                temp[RxCount] = Serial.read();
                RxCks += temp[RxCount];
                RxCount++;
                if(RxCount > 15)
                    RxState++;
                break;
            case 5:
                if(RxCks == Serial.read()){
                    digitalWrite(LED_BUILTIN, LOW);
                    ServoDuty.b[1] = temp[0];
                    ServoDuty.b[0] = temp[1];
                    s.writeMicroseconds(ServoDuty.Duty);
                }
                RxCks = 0;
                RxCount = 0;
                RxState = 0;                
                break;                
        }
    }
}

