#include "SotfP.h"

// Debug print glyph data
void DebugPrintGlyphData(std::vector<lb::SotfP::PathElement> v_glyphData);

int main()
{
	//lb::SotfP myFont("Path/To/MyFont.otf");
	lb::SotfP myFont("D:/Resources/test3-lg.otf", lb::SotfP::Processing_type::PreProcess);

	// Example use 
	std::vector<lb::SotfP::PathElement> glyphData = myFont.GetGlyph('A');
	DebugPrintGlyphData(glyphData);
	printf("\n\n");

	lb::SotfP::DrawableData draw = myFont.GetDrawableData('A');

}


/********************************/
//		Debug Printing Code		//
/********************************/


#define LB_PARSE_CHAR_SWITCH(what)			\
case lb::cff::CFF_OPERATOR::what:			\
	printf("%s ", #what);					\
	break							

void DebugPrintGlyphData(std::vector<lb::SotfP::PathElement> v_glyphData)
{
	lb::cff::CFF_OPERATOR::TWO_BYTE val;
	for (auto& i : v_glyphData)
	{
		for (auto& t : i.data) 
			printf("%d ", t);

		switch (i.op[0])
		{
			LB_PARSE_CHAR_SWITCH(hstem);
			LB_PARSE_CHAR_SWITCH(vstem);
			LB_PARSE_CHAR_SWITCH(vmoveto);
			LB_PARSE_CHAR_SWITCH(rlineto);
			LB_PARSE_CHAR_SWITCH(hlineto);
			LB_PARSE_CHAR_SWITCH(vlineto);
			LB_PARSE_CHAR_SWITCH(rrcurveto);
			LB_PARSE_CHAR_SWITCH(callsubr);
			LB_PARSE_CHAR_SWITCH(sub_return);
		case lb::cff::CFF_OPERATOR::escape:
			printf("escape-");
			switch (i.op[1])
			{
				LB_PARSE_CHAR_SWITCH(cff_and);
				LB_PARSE_CHAR_SWITCH(cff_or);
				LB_PARSE_CHAR_SWITCH(cff_not);
				LB_PARSE_CHAR_SWITCH(cff_abs);
				LB_PARSE_CHAR_SWITCH(cff_add);
				LB_PARSE_CHAR_SWITCH(cff_sub);
				LB_PARSE_CHAR_SWITCH(cff_div);
				LB_PARSE_CHAR_SWITCH(cff_neg);
				LB_PARSE_CHAR_SWITCH(cff_eq);
				LB_PARSE_CHAR_SWITCH(cff_drop);
				LB_PARSE_CHAR_SWITCH(cff_put);
				LB_PARSE_CHAR_SWITCH(cff_get);
				LB_PARSE_CHAR_SWITCH(cff_ifelse);
				LB_PARSE_CHAR_SWITCH(cff_random);
				LB_PARSE_CHAR_SWITCH(cff_mul);
				LB_PARSE_CHAR_SWITCH(cff_sqrt);
				LB_PARSE_CHAR_SWITCH(cff_dup);
				LB_PARSE_CHAR_SWITCH(cff_exch);
				LB_PARSE_CHAR_SWITCH(cff_index);
				LB_PARSE_CHAR_SWITCH(cff_roll);
				LB_PARSE_CHAR_SWITCH(hflex);
				LB_PARSE_CHAR_SWITCH(flex);
				LB_PARSE_CHAR_SWITCH(hflex1);
				LB_PARSE_CHAR_SWITCH(flex1);
			default:
				break;
			}
			break;
			LB_PARSE_CHAR_SWITCH(endchar);
			LB_PARSE_CHAR_SWITCH(hstemhm);
			LB_PARSE_CHAR_SWITCH(hintmask);
			LB_PARSE_CHAR_SWITCH(cntrmask);
			LB_PARSE_CHAR_SWITCH(rmoveto);
			LB_PARSE_CHAR_SWITCH(hmoveto);
			LB_PARSE_CHAR_SWITCH(vstemhm);
			LB_PARSE_CHAR_SWITCH(rcurveline);
			LB_PARSE_CHAR_SWITCH(rlinecurve);
			LB_PARSE_CHAR_SWITCH(vvcurveto);
			LB_PARSE_CHAR_SWITCH(hhcurveto);
			LB_PARSE_CHAR_SWITCH(callgsubr);
			LB_PARSE_CHAR_SWITCH(vhcurveto);
			LB_PARSE_CHAR_SWITCH(hvcurveto);
		default:
			break;
		}
	}
}

#undef LB_PARSE_CHAR_SWITCH