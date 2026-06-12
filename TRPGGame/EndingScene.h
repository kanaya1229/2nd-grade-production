#pragma once

#pragma once

enum EndingType
{
	ENDING_NONE,
	ENDING_1,
	ENDING_1A,
	ENDING_2,
	ENDING_3
};

void StartEnding(EndingType type);
void UpdateEnding();
void DrawEnding();

bool IsEndingFinished();