#pragma once

namespace iron
{

namespace ControlOffsets
{

enum ControlOffsets
{
	Callback,
	InternalsOffset,
	InputsOffset,
	OutputsOffset,
	TotalSize,
	Count,
	//No longer in Control Block
	ArgumentsBegin = Count
};

}
}