#pragma once

	//--------------------------------------------------------------------------------
	// enum �܂Ƃ�
	//--------------------------------------------------------------------------------

	// �R���s���[�^�[�͌�\�t�g�w�ʁx�̃X�N���[���V���b�g�ł��������Ƃ̂���l�����邩������Ȃ��A
	// �ՖʁA�΂̏�ɕ`���L��
	// (�` | �F) �Ŏw�肷��B���Ŏl�p��`���ꍇ�� (FIGURE_SQUARE | FIGURE_BLACK)
	enum FigureType {
		FIGURE_NONE,			// �����`���Ȃ�
		FIGURE_TRIANGLE,		// �O�p�`
		FIGURE_SQUARE,			// �l�p
		FIGURE_CIRCLE,			// �~
		FIGURE_CROSS,			// �~
		FIGURE_QUESTION,		// "�H"�̋L��	
		FIGURE_HORIZON,			// ����
		FIGURE_VERTICAL,		// �c��
		FIGURE_LINE_LEFTUP,		// �΂߁A���ォ��E��
		FIGURE_LINE_RIGHTUP,	// �΂߁A��������E��
		FIGURE_BLACK = 0x1000,	// ���ŕ`���i�F�w��)
		FIGURE_WHITE = 0x2000,	// ���ŕ`��	(�F�w��j
	};
