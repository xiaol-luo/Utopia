#pragma once

// ������λ�¼�
enum ESceneEvent
{
	ESU_PosChange = 0,				// λ�øı�
	ESU_EnterScene,					// ���볡��
	ESU_LeaveScene,					// �뿪����

	ESU_VolecityChange,				// su�ٶȸı�
	ESU_MoveStateChange,			// su�ƶ�״̬�ı�
	
	ESU_FightParamChange,			// ս����������
	ESU_DizzinessChange,			// su����״̬�ı� true:atttach,  false:deattach
	ESU_ImmobilizedChange,			// su����״̬�ı� true:atttach,  false:deattach
	ESU_BlindChange,				// su��ä״̬�ı� true:atttach,  false:deattach
	ESU_SilenceChange,				// su��Ĭ״̬�ı� true:atttach,  false:deattach
	ESU_DeadChange,					// su����״̬�ı� true:atttach,  false:deattach
	
	ESU_HpChange,					// Ѫ���ı�
	ESU_MpChange,					// ħ���İ�

	ES_ReloadConfig,				// ����������
	ES_TestHeartBeat,				// ������

};