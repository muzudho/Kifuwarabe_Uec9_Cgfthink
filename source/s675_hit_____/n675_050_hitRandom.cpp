#include <windows.h>								// rand() �����g�p���邽�߂ɁB
#include "../../header/h675_hit_____/n675_050_hitRandom.h"




HitRandom::HitRandom()
{
};




int HitRandom::Evaluate(
	)
{
	return rand() % 100; // 0 �` 99 �̃����_���ȕ]���l��^����B
}