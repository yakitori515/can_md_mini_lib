#include "mini_md_lib.h"
#include <cstdint>
#include <cmath>

mini_md_lib::mini_md_lib(CAN &can, int motor_num) 
        : _can(can), _motor_num(motor_num) {
        _can.frequency(1000000);
        _can.mode(CAN::Normal);    
}

int mini_md_lib::send(int* speed){
    int _abs_speed[_motor_num];
    CANMessage _msg;
    can_send_data data[_motor_num];
    for(int i = 0; i < _motor_num; i++){

        data[i].DATA.SPEED = abs(speed[i]);
        
        if(0 < speed[i]){
            data[i].DATA.STATE=0b01;
        }else if(speed[i] < 0){
            data[i].DATA.STATE=0b10;
        }else{
            data[i].DATA.STATE=0b00;
        }
        if(abs(speed[i]) > 10000){
            data[i].DATA.STATE=0b11;
        }

    }
    int data_count=0;
    for(int j=0;j<=(_motor_num/4);j++){
        _msg.id=0x301+j;
        for(int count=0;count<4;count++){
            if(data_count<_motor_num){
                _msg.data[count*2] = (char)(data[data_count].SEND_DATA >> 8);
                _msg.data[count*2+1] = (char)(data[data_count].SEND_DATA & 0xff);
            }
            data_count++;
        }
        if(!_can.write(_msg)){
            return -1;
        }
        wait_us(100);
    }

    return 1;
}
