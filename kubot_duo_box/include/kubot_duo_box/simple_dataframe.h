#ifndef KUBOT_SIMPLE_DATAFRAME_H_
#define KUBOT_SIMPLE_DATAFRAME_H_

#include "dataframe.h"
#include <string.h>

static const unsigned short MESSAGE_BUFFER_SIZE = 255;

#define FIX_HEAD 0x5A

struct Head
{
    unsigned char flag;   // 標頭, 固定 0X5A
    unsigned char msg_id; // 消息ID, 表示消息具體作用,决定消息體格式
    unsigned char length; // 消息體長度
};

struct Message
{
    struct Head head;
    unsigned char data[MESSAGE_BUFFER_SIZE];
    unsigned char check;
    unsigned char recv_count; //已經接收的字節數

    Message() {}
    Message(unsigned char msg_id, unsigned char *data = 0, unsigned char len = 0)
    {
        head.flag = FIX_HEAD;
        head.msg_id = msg_id;
        head.length = recv_count = len;
        check = 0;

        if (data != 0 && len != 0)
            memcpy(this->data, data, len);

        unsigned char *_send_buffer = (unsigned char *)this;

        unsigned int i = 0;
        for (i = 0; i < sizeof(head) + head.length; i++)
            check += _send_buffer[i];

        _send_buffer[sizeof(head) + head.length] = check;
    }
};

enum RECEIVE_STATE
{
    STATE_RECV_FIX = 0,
    STATE_RECV_ID,
    STATE_RECV_LEN,
    STATE_RECV_DATA,
    STATE_RECV_CHECK
};

#endif /* KUBOT_SIMPLE_DATAFRAME_H_ */