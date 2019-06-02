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
	//No longer in Control Block
	ArgumentsBegin
};

}