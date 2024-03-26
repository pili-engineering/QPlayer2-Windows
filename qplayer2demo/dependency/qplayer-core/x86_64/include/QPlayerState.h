#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QPlayerState : uint32_t {
		NONE = 0,//��ʼ״̬
		INIT = 1,//��������ʼ�������ֶ��� û�ж�Ӧ��state �����������ϱ����״̬
		PREPARE = 2,//��ʼ����Ƶ���ݽ���任�ȣ����»���ַ�󣬶������״̬
		PLAYING = 4,//������
		PAUSED_RENDER = 6,//�û���ͣ
		COMPLETED = 7,//�������
		SEEKING = 8, //SEEK

		STOPPED = 9,//������ֹͣ��
		MISTAKE = 10,//���ų����Ƿ���Ҫ�� �ɻָ� �� ���ɻָ� ��
		END = 11,//�������ͷŸ��ֶ������
		MEDIA_ITEM_PREPARE = 12, //��ʼ����Ƶ���ݽ���任�ȣ����»���ַ�󣬶������״̬ ���Media Item��play ��ʽ
		RELEASE = 13 //���������������ͷŸ�����Դ
	};
}