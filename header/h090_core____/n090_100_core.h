#pragma once


#include <windows.h>	// rand() �����g�p���邽�߂ɁB
#include <tchar.h> // Unicode�Ή��� _T() �֐����g�p���邽�߂ɁB


//--------------------------------------------------------------------------------
// ���샂�[�h
//--------------------------------------------------------------------------------

// �����_���ł���p���[�h�ɂ��邺���i�O���O�j
//#define RANDOM_MOVE_ONLY

// �U���I�ȕ]���֐����g�������i�O���O�j
#define ENABLE_MOVE_ATTACK

// �ُ�Ȏw����̏ꍇ�A�ł���̂�蒼�����\�ɂ��邺���i�O���O�j
#define ENABLE_MOVE_RETRY

// �R���\�[���ɁA�]���l�̃��O���o�����������i�O���O�j
//#define EVAL_LOG

// �R���\�[���ɁA����m�F�p�̃��O���o�����������i�O���O�j
//#define CHECK_LOG


//--------------------------------------------------------------------------------
// ��`
//--------------------------------------------------------------------------------

#define PRT_LEN_MAX 256			// �ő�256�����܂ŏo�͉�


class Core {
public:
	HANDLE hConsoleWindow;
public:

	// printf()�̑�p�֐��B�R���\�[���ɏo�́B
	void PRT(		
		const _TCHAR* format,
		...
		);

	// �ꎞ�I��Windows�ɐ����n���܂��B
	// �v�l���ɂ��̊֐����ĂԂƎv�l���f�{�^�����L���ɂȂ�܂��B
	// ���b30��ȏ�Ă΂��悤�ɂ���ƃX���[�Y�ɒ��f�ł��܂��B
	static void YieldWindowsSystem(
		void
		);

};

