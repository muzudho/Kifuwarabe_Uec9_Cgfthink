#include <windows.h>								// rand() �����g�p���邽�߂ɁB
#include "../../header/h190_board___/n190_100_board.h"
#include "../../header/h190_board___/n190_150_liberty.h"
#include "../../header/h675_hit_____/n675_250_hitGnugo12Random.h"



int HitGnugo12Random::Evaluate(
	int		color,
	int		node,
	Board*	pBoard
	)
{
	int score = 0;

#ifndef RANDOM_MOVE_ONLY

	int boardSize = pBoard->GetSize();
	if (boardSize<9)
	{
		// �X�H�Ղ�菬�������̂͑ΏۊO�B
		goto gt_EndMethod;
	}

	int x, y;
	AbstractBoard::ConvertToXy(x, y, node);

	// �u�������Ȃ��ʒu�� avoid �_���ŕ\���B
	int avoid = 0;

	int waku = 1;
	int good = 1;
	int bad;
	if (18<boardSize) {
		bad = 3;
	}
	else if (12 < boardSize) {
		bad = 2;
	}
	else {
		bad = 1;
	}

	//----------------------------------------
	// x���ɂ���
	//----------------------------------------

	if (x<waku+bad)
	{
		// �[�ɂ͒u�������Ȃ��B
		avoid++;
	}
	else if (x<waku + bad + good)
	{
		// �[���炿����Ɨ��ꂽ�|�C���g�̓I�b�P�[
	}
	else if (x<waku + 2 * bad + good)
	{
		// ���̐�͂܂����B
		avoid++;
	}
	else if (x<waku + 2 * bad + 2 * good)
	{
		// ���̐�͂܂��I�b�P�[�B
	}
	else if ((boardSize - waku - bad)<x)
	{
		// �[�ɂ͒u�������Ȃ��B
		avoid++;
	}
	else if ((boardSize - waku - (bad + good))<x)
	{
		// �[���炿����Ɨ��ꂽ�|�C���g�̓I�b�P�[
	}
	else if ((boardSize - waku - (2 * bad + good))<x)
	{
		// ���̐�͂܂����B
		avoid++;
	}
	else if ((boardSize - waku - (2 * bad + 2 * good))<x)
	{
		// ���̐�͂܂��I�b�P�[�B
	}
	else
	{
		// �����n�т͂��₾�B
		avoid++;
	}


	//----------------------------------------
	// y���ɂ���
	//----------------------------------------

	if (y<waku+bad) {
		// �[�ɂ͒u�������Ȃ��B
		avoid++;
	}
	else if (y< waku + bad + good)
	{
		// �[���炿����Ɨ��ꂽ�|�C���g�̓I�b�P�[
	}
	else if (y<waku + 2 * bad + good)
	{
		// ���̐�͂܂����B
		avoid++;
	}
	else if (y<waku + 2 * bad + 2 * good)
	{
		// ���̐�͂܂��I�b�P�[�B
	}
	else if ((boardSize - waku - bad)<y)
	{
		// �[�ɂ͒u�������Ȃ��B
		avoid++;
	}
	else if ((boardSize - waku - (bad + good))<y)
	{
		// �[���炿����Ɨ��ꂽ�|�C���g�̓I�b�P�[
	}
	else if ((boardSize - waku - (2 * bad + good))<y)
	{
		// ���̐�͂܂����B
		avoid++;
	}
	else if ((boardSize - waku - (2 * bad + 2 * good))<7)
	{
		// ���̐�͂܂��I�b�P�[�B
	}
	else
	{
		// �����n�т͂��₾�B
		avoid++;
	}

	
	// ���������ꏊ
	// �A�̌ċz�_�� 0 �` 1 �����Ȃ��ꍇ�B
	Liberty liberty;
	liberty.Count(node, color, pBoard);
	if (liberty.liberty < 2)
	{
		avoid++;
	}

	//----------------------------------------
	// avoid �� 4 �i�K
	//----------------------------------------
	if (2 < avoid)
	{
		score = 6 + rand() % 94;
	}
	else if (1 < avoid) {
		score = 12 + rand() % 88;
	}
	else if (0 < avoid) {
		score = 25 + rand() % 75;
	}
	else {
		score = 50 + rand() % 50;
	}

	//----------------------------------------
	// �����ڂɔ{�����|���܂��B
	//----------------------------------------
	score *= 80 / 10;

gt_EndMethod:

#endif

	return score;
}