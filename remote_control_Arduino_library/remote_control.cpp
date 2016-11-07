#include "remote_control.h"

remote_control::remote_control(Stream &Serial_)
{
	mySerial = &Serial_;
}

bool remote_control::keyPressed( Interested_Keys key )
{
	if (mySerial->available()) {     //是否有可接收数据
		do {
			if (mySerial->peek() != 0x5A) {  //第一个字节是否为0x5A,如果不是丢弃
				mySerial->read();
			} else {
				if (mySerial->available() >= sizeof(tx_data)) {  //可接收数据是否达到要求
					mySerial->readBytes((uint8_t *)&tx_data, sizeof(tx_data)); //读取数据
					if (Verify_CRC8_Check_Sum((uint8_t *)&tx_data, sizeof(tx_data))) { //校验crc是否正确
						m_PressedKeys = tx_data.temp_data;      //如果数据正确，复制数据到本地变量
						last_rx_time = millis();
					}
				}
			}
		}while(mySerial->available() >= sizeof(tx_data));  //如果可读取数据依然大于要求，继续读取
	}
	if (millis() - last_rx_time >= 200)
		m_PressedKeys = 0;
    return m_PressedKeys & ( 1 << key );
}

uint8_t  remote_control::Get_CRC8_Check_Sum(uint8_t  *message, uint32_t length, uint8_t CRC8)
{
	uint8_t index;
	if (message == NULL)
	{
		return 0xFF;
	}
	while (length--)
	{
		index = CRC8^(*message++);
		CRC8 = CRC8_TAB[index];
	}
	return (CRC8);
}

/*
** Descriptions: CRC8 Verify function
** Input: Data to Verify,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
bool remote_control::Verify_CRC8_Check_Sum(uint8_t *message, uint32_t length)
{
	uint8_t expected = 0;
	if ((message == NULL) || (length <= 2)) return 0;
	expected = Get_CRC8_Check_Sum(message, length-1, CRC8_INIT);
	return ( expected == message[length-1] );
}