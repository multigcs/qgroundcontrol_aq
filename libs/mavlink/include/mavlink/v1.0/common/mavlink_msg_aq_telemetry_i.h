// MESSAGE AQ_TELEMETRY_I PACKING

#define MAVLINK_MSG_ID_AQ_TELEMETRY_I 151

typedef struct __mavlink_aq_telemetry_i_t
{
 int32_t value1; ///< value1
 int32_t value2; ///< value2
 int32_t value3; ///< value3
 int32_t value4; ///< value4
 int32_t value5; ///< value5
 int32_t value6; ///< value6
 int32_t value7; ///< value7
 int32_t value8; ///< value8
 int32_t value9; ///< value9
 int32_t value10; ///< value10
 int32_t value11; ///< value11
 int32_t value12; ///< value12
 int32_t value13; ///< value13
 int32_t value14; ///< value14
 int32_t value15; ///< value15
 int32_t value16; ///< value16
 int32_t value17; ///< value17
 int32_t value18; ///< value18
 int32_t value19; ///< value19
 int32_t value20; ///< value20
 uint16_t Index; ///< Index of message
} mavlink_aq_telemetry_i_t;

#define MAVLINK_MSG_ID_AQ_TELEMETRY_I_LEN 82
#define MAVLINK_MSG_ID_151_LEN 82



#define MAVLINK_MESSAGE_INFO_AQ_TELEMETRY_I { \
	"AQ_TELEMETRY_I", \
	21, \
	{  { "value1", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_aq_telemetry_i_t, value1) }, \
         { "value2", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_aq_telemetry_i_t, value2) }, \
         { "value3", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_aq_telemetry_i_t, value3) }, \
         { "value4", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_aq_telemetry_i_t, value4) }, \
         { "value5", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_aq_telemetry_i_t, value5) }, \
         { "value6", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_aq_telemetry_i_t, value6) }, \
         { "value7", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_aq_telemetry_i_t, value7) }, \
         { "value8", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_aq_telemetry_i_t, value8) }, \
         { "value9", NULL, MAVLINK_TYPE_INT32_T, 0, 32, offsetof(mavlink_aq_telemetry_i_t, value9) }, \
         { "value10", NULL, MAVLINK_TYPE_INT32_T, 0, 36, offsetof(mavlink_aq_telemetry_i_t, value10) }, \
         { "value11", NULL, MAVLINK_TYPE_INT32_T, 0, 40, offsetof(mavlink_aq_telemetry_i_t, value11) }, \
         { "value12", NULL, MAVLINK_TYPE_INT32_T, 0, 44, offsetof(mavlink_aq_telemetry_i_t, value12) }, \
         { "value13", NULL, MAVLINK_TYPE_INT32_T, 0, 48, offsetof(mavlink_aq_telemetry_i_t, value13) }, \
         { "value14", NULL, MAVLINK_TYPE_INT32_T, 0, 52, offsetof(mavlink_aq_telemetry_i_t, value14) }, \
         { "value15", NULL, MAVLINK_TYPE_INT32_T, 0, 56, offsetof(mavlink_aq_telemetry_i_t, value15) }, \
         { "value16", NULL, MAVLINK_TYPE_INT32_T, 0, 60, offsetof(mavlink_aq_telemetry_i_t, value16) }, \
         { "value17", NULL, MAVLINK_TYPE_INT32_T, 0, 64, offsetof(mavlink_aq_telemetry_i_t, value17) }, \
         { "value18", NULL, MAVLINK_TYPE_INT32_T, 0, 68, offsetof(mavlink_aq_telemetry_i_t, value18) }, \
         { "value19", NULL, MAVLINK_TYPE_INT32_T, 0, 72, offsetof(mavlink_aq_telemetry_i_t, value19) }, \
         { "value20", NULL, MAVLINK_TYPE_INT32_T, 0, 76, offsetof(mavlink_aq_telemetry_i_t, value20) }, \
         { "Index", NULL, MAVLINK_TYPE_UINT16_T, 0, 80, offsetof(mavlink_aq_telemetry_i_t, Index) }, \
         } \
}


/**
 * @brief Pack a aq_telemetry_i message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Index Index of message
 * @param value1 value1
 * @param value2 value2
 * @param value3 value3
 * @param value4 value4
 * @param value5 value5
 * @param value6 value6
 * @param value7 value7
 * @param value8 value8
 * @param value9 value9
 * @param value10 value10
 * @param value11 value11
 * @param value12 value12
 * @param value13 value13
 * @param value14 value14
 * @param value15 value15
 * @param value16 value16
 * @param value17 value17
 * @param value18 value18
 * @param value19 value19
 * @param value20 value20
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_aq_telemetry_i_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t Index, int32_t value1, int32_t value2, int32_t value3, int32_t value4, int32_t value5, int32_t value6, int32_t value7, int32_t value8, int32_t value9, int32_t value10, int32_t value11, int32_t value12, int32_t value13, int32_t value14, int32_t value15, int32_t value16, int32_t value17, int32_t value18, int32_t value19, int32_t value20)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[82];
	_mav_put_int32_t(buf, 0, value1);
	_mav_put_int32_t(buf, 4, value2);
	_mav_put_int32_t(buf, 8, value3);
	_mav_put_int32_t(buf, 12, value4);
	_mav_put_int32_t(buf, 16, value5);
	_mav_put_int32_t(buf, 20, value6);
	_mav_put_int32_t(buf, 24, value7);
	_mav_put_int32_t(buf, 28, value8);
	_mav_put_int32_t(buf, 32, value9);
	_mav_put_int32_t(buf, 36, value10);
	_mav_put_int32_t(buf, 40, value11);
	_mav_put_int32_t(buf, 44, value12);
	_mav_put_int32_t(buf, 48, value13);
	_mav_put_int32_t(buf, 52, value14);
	_mav_put_int32_t(buf, 56, value15);
	_mav_put_int32_t(buf, 60, value16);
	_mav_put_int32_t(buf, 64, value17);
	_mav_put_int32_t(buf, 68, value18);
	_mav_put_int32_t(buf, 72, value19);
	_mav_put_int32_t(buf, 76, value20);
	_mav_put_uint16_t(buf, 80, Index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 82);
#else
	mavlink_aq_telemetry_i_t packet;
	packet.value1 = value1;
	packet.value2 = value2;
	packet.value3 = value3;
	packet.value4 = value4;
	packet.value5 = value5;
	packet.value6 = value6;
	packet.value7 = value7;
	packet.value8 = value8;
	packet.value9 = value9;
	packet.value10 = value10;
	packet.value11 = value11;
	packet.value12 = value12;
	packet.value13 = value13;
	packet.value14 = value14;
	packet.value15 = value15;
	packet.value16 = value16;
	packet.value17 = value17;
	packet.value18 = value18;
	packet.value19 = value19;
	packet.value20 = value20;
	packet.Index = Index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 82);
#endif

	msg->msgid = MAVLINK_MSG_ID_AQ_TELEMETRY_I;
	return mavlink_finalize_message(msg, system_id, component_id, 82, 73);
}

/**
 * @brief Pack a aq_telemetry_i message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param Index Index of message
 * @param value1 value1
 * @param value2 value2
 * @param value3 value3
 * @param value4 value4
 * @param value5 value5
 * @param value6 value6
 * @param value7 value7
 * @param value8 value8
 * @param value9 value9
 * @param value10 value10
 * @param value11 value11
 * @param value12 value12
 * @param value13 value13
 * @param value14 value14
 * @param value15 value15
 * @param value16 value16
 * @param value17 value17
 * @param value18 value18
 * @param value19 value19
 * @param value20 value20
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_aq_telemetry_i_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t Index,int32_t value1,int32_t value2,int32_t value3,int32_t value4,int32_t value5,int32_t value6,int32_t value7,int32_t value8,int32_t value9,int32_t value10,int32_t value11,int32_t value12,int32_t value13,int32_t value14,int32_t value15,int32_t value16,int32_t value17,int32_t value18,int32_t value19,int32_t value20)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[82];
	_mav_put_int32_t(buf, 0, value1);
	_mav_put_int32_t(buf, 4, value2);
	_mav_put_int32_t(buf, 8, value3);
	_mav_put_int32_t(buf, 12, value4);
	_mav_put_int32_t(buf, 16, value5);
	_mav_put_int32_t(buf, 20, value6);
	_mav_put_int32_t(buf, 24, value7);
	_mav_put_int32_t(buf, 28, value8);
	_mav_put_int32_t(buf, 32, value9);
	_mav_put_int32_t(buf, 36, value10);
	_mav_put_int32_t(buf, 40, value11);
	_mav_put_int32_t(buf, 44, value12);
	_mav_put_int32_t(buf, 48, value13);
	_mav_put_int32_t(buf, 52, value14);
	_mav_put_int32_t(buf, 56, value15);
	_mav_put_int32_t(buf, 60, value16);
	_mav_put_int32_t(buf, 64, value17);
	_mav_put_int32_t(buf, 68, value18);
	_mav_put_int32_t(buf, 72, value19);
	_mav_put_int32_t(buf, 76, value20);
	_mav_put_uint16_t(buf, 80, Index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 82);
#else
	mavlink_aq_telemetry_i_t packet;
	packet.value1 = value1;
	packet.value2 = value2;
	packet.value3 = value3;
	packet.value4 = value4;
	packet.value5 = value5;
	packet.value6 = value6;
	packet.value7 = value7;
	packet.value8 = value8;
	packet.value9 = value9;
	packet.value10 = value10;
	packet.value11 = value11;
	packet.value12 = value12;
	packet.value13 = value13;
	packet.value14 = value14;
	packet.value15 = value15;
	packet.value16 = value16;
	packet.value17 = value17;
	packet.value18 = value18;
	packet.value19 = value19;
	packet.value20 = value20;
	packet.Index = Index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 82);
#endif

	msg->msgid = MAVLINK_MSG_ID_AQ_TELEMETRY_I;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 82, 73);
}

/**
 * @brief Encode a aq_telemetry_i struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param aq_telemetry_i C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_aq_telemetry_i_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_aq_telemetry_i_t* aq_telemetry_i)
{
	return mavlink_msg_aq_telemetry_i_pack(system_id, component_id, msg, aq_telemetry_i->Index, aq_telemetry_i->value1, aq_telemetry_i->value2, aq_telemetry_i->value3, aq_telemetry_i->value4, aq_telemetry_i->value5, aq_telemetry_i->value6, aq_telemetry_i->value7, aq_telemetry_i->value8, aq_telemetry_i->value9, aq_telemetry_i->value10, aq_telemetry_i->value11, aq_telemetry_i->value12, aq_telemetry_i->value13, aq_telemetry_i->value14, aq_telemetry_i->value15, aq_telemetry_i->value16, aq_telemetry_i->value17, aq_telemetry_i->value18, aq_telemetry_i->value19, aq_telemetry_i->value20);
}

/**
 * @brief Send a aq_telemetry_i message
 * @param chan MAVLink channel to send the message
 *
 * @param Index Index of message
 * @param value1 value1
 * @param value2 value2
 * @param value3 value3
 * @param value4 value4
 * @param value5 value5
 * @param value6 value6
 * @param value7 value7
 * @param value8 value8
 * @param value9 value9
 * @param value10 value10
 * @param value11 value11
 * @param value12 value12
 * @param value13 value13
 * @param value14 value14
 * @param value15 value15
 * @param value16 value16
 * @param value17 value17
 * @param value18 value18
 * @param value19 value19
 * @param value20 value20
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_aq_telemetry_i_send(mavlink_channel_t chan, uint16_t Index, int32_t value1, int32_t value2, int32_t value3, int32_t value4, int32_t value5, int32_t value6, int32_t value7, int32_t value8, int32_t value9, int32_t value10, int32_t value11, int32_t value12, int32_t value13, int32_t value14, int32_t value15, int32_t value16, int32_t value17, int32_t value18, int32_t value19, int32_t value20)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[82];
	_mav_put_int32_t(buf, 0, value1);
	_mav_put_int32_t(buf, 4, value2);
	_mav_put_int32_t(buf, 8, value3);
	_mav_put_int32_t(buf, 12, value4);
	_mav_put_int32_t(buf, 16, value5);
	_mav_put_int32_t(buf, 20, value6);
	_mav_put_int32_t(buf, 24, value7);
	_mav_put_int32_t(buf, 28, value8);
	_mav_put_int32_t(buf, 32, value9);
	_mav_put_int32_t(buf, 36, value10);
	_mav_put_int32_t(buf, 40, value11);
	_mav_put_int32_t(buf, 44, value12);
	_mav_put_int32_t(buf, 48, value13);
	_mav_put_int32_t(buf, 52, value14);
	_mav_put_int32_t(buf, 56, value15);
	_mav_put_int32_t(buf, 60, value16);
	_mav_put_int32_t(buf, 64, value17);
	_mav_put_int32_t(buf, 68, value18);
	_mav_put_int32_t(buf, 72, value19);
	_mav_put_int32_t(buf, 76, value20);
	_mav_put_uint16_t(buf, 80, Index);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AQ_TELEMETRY_I, buf, 82, 73);
#else
	mavlink_aq_telemetry_i_t packet;
	packet.value1 = value1;
	packet.value2 = value2;
	packet.value3 = value3;
	packet.value4 = value4;
	packet.value5 = value5;
	packet.value6 = value6;
	packet.value7 = value7;
	packet.value8 = value8;
	packet.value9 = value9;
	packet.value10 = value10;
	packet.value11 = value11;
	packet.value12 = value12;
	packet.value13 = value13;
	packet.value14 = value14;
	packet.value15 = value15;
	packet.value16 = value16;
	packet.value17 = value17;
	packet.value18 = value18;
	packet.value19 = value19;
	packet.value20 = value20;
	packet.Index = Index;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AQ_TELEMETRY_I, (const char *)&packet, 82, 73);
#endif
}

#endif

// MESSAGE AQ_TELEMETRY_I UNPACKING


/**
 * @brief Get field Index from aq_telemetry_i message
 *
 * @return Index of message
 */
static inline uint16_t mavlink_msg_aq_telemetry_i_get_Index(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  80);
}

/**
 * @brief Get field value1 from aq_telemetry_i message
 *
 * @return value1
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field value2 from aq_telemetry_i message
 *
 * @return value2
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field value3 from aq_telemetry_i message
 *
 * @return value3
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field value4 from aq_telemetry_i message
 *
 * @return value4
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field value5 from aq_telemetry_i message
 *
 * @return value5
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value5(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field value6 from aq_telemetry_i message
 *
 * @return value6
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value6(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field value7 from aq_telemetry_i message
 *
 * @return value7
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value7(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Get field value8 from aq_telemetry_i message
 *
 * @return value8
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value8(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  28);
}

/**
 * @brief Get field value9 from aq_telemetry_i message
 *
 * @return value9
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value9(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  32);
}

/**
 * @brief Get field value10 from aq_telemetry_i message
 *
 * @return value10
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value10(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  36);
}

/**
 * @brief Get field value11 from aq_telemetry_i message
 *
 * @return value11
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value11(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  40);
}

/**
 * @brief Get field value12 from aq_telemetry_i message
 *
 * @return value12
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value12(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  44);
}

/**
 * @brief Get field value13 from aq_telemetry_i message
 *
 * @return value13
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value13(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  48);
}

/**
 * @brief Get field value14 from aq_telemetry_i message
 *
 * @return value14
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value14(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  52);
}

/**
 * @brief Get field value15 from aq_telemetry_i message
 *
 * @return value15
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value15(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  56);
}

/**
 * @brief Get field value16 from aq_telemetry_i message
 *
 * @return value16
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value16(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  60);
}

/**
 * @brief Get field value17 from aq_telemetry_i message
 *
 * @return value17
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value17(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  64);
}

/**
 * @brief Get field value18 from aq_telemetry_i message
 *
 * @return value18
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value18(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  68);
}

/**
 * @brief Get field value19 from aq_telemetry_i message
 *
 * @return value19
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value19(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  72);
}

/**
 * @brief Get field value20 from aq_telemetry_i message
 *
 * @return value20
 */
static inline int32_t mavlink_msg_aq_telemetry_i_get_value20(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  76);
}

/**
 * @brief Decode a aq_telemetry_i message into a struct
 *
 * @param msg The message to decode
 * @param aq_telemetry_i C-struct to decode the message contents into
 */
static inline void mavlink_msg_aq_telemetry_i_decode(const mavlink_message_t* msg, mavlink_aq_telemetry_i_t* aq_telemetry_i)
{
#if MAVLINK_NEED_BYTE_SWAP
	aq_telemetry_i->value1 = mavlink_msg_aq_telemetry_i_get_value1(msg);
	aq_telemetry_i->value2 = mavlink_msg_aq_telemetry_i_get_value2(msg);
	aq_telemetry_i->value3 = mavlink_msg_aq_telemetry_i_get_value3(msg);
	aq_telemetry_i->value4 = mavlink_msg_aq_telemetry_i_get_value4(msg);
	aq_telemetry_i->value5 = mavlink_msg_aq_telemetry_i_get_value5(msg);
	aq_telemetry_i->value6 = mavlink_msg_aq_telemetry_i_get_value6(msg);
	aq_telemetry_i->value7 = mavlink_msg_aq_telemetry_i_get_value7(msg);
	aq_telemetry_i->value8 = mavlink_msg_aq_telemetry_i_get_value8(msg);
	aq_telemetry_i->value9 = mavlink_msg_aq_telemetry_i_get_value9(msg);
	aq_telemetry_i->value10 = mavlink_msg_aq_telemetry_i_get_value10(msg);
	aq_telemetry_i->value11 = mavlink_msg_aq_telemetry_i_get_value11(msg);
	aq_telemetry_i->value12 = mavlink_msg_aq_telemetry_i_get_value12(msg);
	aq_telemetry_i->value13 = mavlink_msg_aq_telemetry_i_get_value13(msg);
	aq_telemetry_i->value14 = mavlink_msg_aq_telemetry_i_get_value14(msg);
	aq_telemetry_i->value15 = mavlink_msg_aq_telemetry_i_get_value15(msg);
	aq_telemetry_i->value16 = mavlink_msg_aq_telemetry_i_get_value16(msg);
	aq_telemetry_i->value17 = mavlink_msg_aq_telemetry_i_get_value17(msg);
	aq_telemetry_i->value18 = mavlink_msg_aq_telemetry_i_get_value18(msg);
	aq_telemetry_i->value19 = mavlink_msg_aq_telemetry_i_get_value19(msg);
	aq_telemetry_i->value20 = mavlink_msg_aq_telemetry_i_get_value20(msg);
	aq_telemetry_i->Index = mavlink_msg_aq_telemetry_i_get_Index(msg);
#else
	memcpy(aq_telemetry_i, _MAV_PAYLOAD(msg), 82);
#endif
}