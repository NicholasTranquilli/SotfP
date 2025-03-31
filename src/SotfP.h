#pragma once

#include "OTF/OTF.h"

namespace lb
{
	class SotfP
	{
		lb::OTF vOTF;

	public:
		struct PathElement
		{
			unsigned char op[2];
			std::vector<int> data;
		};

		/// <summary>
		/// Constructor to instantiate OTF class
		/// </summary>
		/// <param name="v_file">Path to OTF font file</param>
		SotfP(std::string v_file);

		/// <summary>
		/// One of the main functions of this class.
		/// Directly query any character in the font and recieve it structured glyph data in return.
		/// </summary>
		/// <param name="v_character">character thats glyph data will be returned</param>
		/// <returns>Glyph data for supplied character</returns>
		std::vector<PathElement> GetGlyph(char v_character);

		/// <summary>
		/// Parses raw glyph data into structured glyph data.
		/// This function is for debugging and special case situations.
		/// </summary>
		/// <param name="v_rawGlyph">Vector of raw glyph data bytes</param>
		/// <returns>Structured glyph data</returns>
		std::vector<PathElement> ParseRawGlyph(std::vector<unsigned char> v_rawGlyph);
	};
}