#ifndef KUBOT_DATA_FRAME_H_
#define KUBOT_DATA_FRAME_H_

enum MESSAGE_ID
{
   ID_GET_VERSION = 0,
   ID_GET_LED_STATUS = 1,
   ID_SET_LED_STATUS = 2,
   ID_GET_SERVO_STATUS = 3,
   ID_SET_SERVO_STATUS = 4,
   ID_MESSGAE_MAX
};

class Notify
{
public:
	virtual void update(const MESSAGE_ID id, void* data) = 0;
};

class Dataframe
{
public:
	virtual bool init() = 0;
	virtual void register_notify(const MESSAGE_ID id, Notify* _nf) = 0;
	virtual bool data_recv(unsigned char c) = 0;
	virtual bool data_parse() = 0;
	virtual bool interact(const MESSAGE_ID id) = 0;
};

#endif /* KUBOT_DATAFRAME_H_ */