#ifndef __INCLUDE_MINI_MD_LIB_H__
#define __INCLUDE_MINI_MD_LIB_H__

#include "mbed.h"
#include <cstdint>
#include <cmath>

class mini_md_lib{
    public:
    mini_md_lib(CAN &can, int motor_num);
    int send(int* speed);

    private:
    typedef union{
        uint16_t SEND_DATA;
        struct {
            uint16_t SPEED:14;
            unsigned char STATE:2;
        }DATA;
    }can_send_data;
    
    enum State{
        Free,
        CW,
        CCW,
        Brake,
    };
    CAN &_can;
    int _i, _motor_num;   
};

#endif
