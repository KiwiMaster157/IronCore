#pragma once

namespace iron
{

enum ControlOffsets
{
	Callback,
	InternalsOffset,
	InputsOffset,
	OutputsOffset,
	TotalSize,
	PreviousSize,
	Count,
	//No longer in Control Block
	ArgumentsBegin = Count
};

}