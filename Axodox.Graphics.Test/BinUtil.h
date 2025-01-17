#pragma once
#include "../ImGUI/imgui.h"

namespace BinUtilLib {

	struct ColoredTri
	{
		uint32_t id = 1;
		ImVec2 p0;
		ImVec2 p1;
		ImVec2 p2;
		ImColor col;
	};

	class BinUtil
	{
	public:
		static uint32_t FindMSB(uint32_t n)
		{
			n |= n >> 1; // 100010001 | 010000100 = 110011001
			n |= n >> 2; // 110011001 | 001100110 = 111111111
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;

			// if MSB is not the final bit
			n = ((n + 1) >> 1)
				// if MSB is the final bit
				| (n & (1 << ((sizeof(n) * CHAR_BIT) - 1)));
			return n;
		}

		// Finds the index (from the right) of the MSB
		// Note this is also the depth of the node.
		static uint32_t FindMSBIndex(uint32_t n)
		{
			return log2(FindMSB(n));
		}
	};
}