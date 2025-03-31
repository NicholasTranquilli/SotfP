#include "SotfP.h"

lb::SotfP::SotfP(std::string v_file)
	: vOTF(v_file)
{

}

std::vector<lb::SotfP::PathElement> lb::SotfP::GetGlyph(char v_character)
{
	std::vector<unsigned char> vRawGlyph = this->vOTF.GetGlyph(v_character);
	std::vector<lb::SotfP::PathElement> vGlyph = this->ParseRawGlyph(vRawGlyph);
	return vGlyph;
}

std::vector<lb::SotfP::PathElement> lb::SotfP::ParseRawGlyph(std::vector<unsigned char> v_rawGlyph)
{
	std::vector<lb::SotfP::PathElement> vResult;
	std::vector<int> vDataBuffer;
	PathElement vPathElementBuffer;

#define LB_PARSE_CHAR_SWITCH(what)							\
case lb::cff::CFF_OPERATOR::what:							\
	vPathElementBuffer.op[0] = lb::cff::CFF_OPERATOR::what;	\
	vPathElementBuffer.op[1] = 0;							\
	vPathElementBuffer.data = vDataBuffer;					\
	vDataBuffer.clear();									\
	vResult.push_back(vPathElementBuffer);					\
	vPathElementBuffer = {0};								\
	break							

#define LB_PARSE_CHAR_SWITCH2(what)							\
case lb::cff::CFF_OPERATOR::what:							\
	vPathElementBuffer.op[1] = lb::cff::CFF_OPERATOR::what;	\
	vPathElementBuffer.data = vDataBuffer;					\
	vDataBuffer.clear();									\
	vResult.push_back(vPathElementBuffer);					\
	vPathElementBuffer = {0};								\
	break							

	for (int i = 0; i < v_rawGlyph.size(); i++)
	{
		int val = v_rawGlyph[i];
		switch (val)
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
			vPathElementBuffer.op[0] = lb::cff::CFF_OPERATOR::escape;
			val = v_rawGlyph[++i];
			switch (val)
			{
				LB_PARSE_CHAR_SWITCH2(cff_and);
				LB_PARSE_CHAR_SWITCH2(cff_or);
				LB_PARSE_CHAR_SWITCH2(cff_not);
				LB_PARSE_CHAR_SWITCH2(cff_abs);
				LB_PARSE_CHAR_SWITCH2(cff_add);
				LB_PARSE_CHAR_SWITCH2(cff_sub);
				LB_PARSE_CHAR_SWITCH2(cff_div);
				LB_PARSE_CHAR_SWITCH2(cff_neg);
				LB_PARSE_CHAR_SWITCH2(cff_eq);
				LB_PARSE_CHAR_SWITCH2(cff_drop);
				LB_PARSE_CHAR_SWITCH2(cff_put);
				LB_PARSE_CHAR_SWITCH2(cff_get);
				LB_PARSE_CHAR_SWITCH2(cff_ifelse);
				LB_PARSE_CHAR_SWITCH2(cff_random);
				LB_PARSE_CHAR_SWITCH2(cff_mul);
				LB_PARSE_CHAR_SWITCH2(cff_sqrt);
				LB_PARSE_CHAR_SWITCH2(cff_dup);
				LB_PARSE_CHAR_SWITCH2(cff_exch);
				LB_PARSE_CHAR_SWITCH2(cff_index);
				LB_PARSE_CHAR_SWITCH2(cff_roll);
				LB_PARSE_CHAR_SWITCH2(hflex);
				LB_PARSE_CHAR_SWITCH2(flex);
				LB_PARSE_CHAR_SWITCH2(hflex1);
				LB_PARSE_CHAR_SWITCH2(flex1);
			default:
				vDataBuffer.push_back(this->vOTF.GetCFF().DecodeInt(v_rawGlyph, i));
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
			case lb::cff::CFF_OPERATOR::shortint:
				vDataBuffer.push_back(this->vOTF.GetCFF().DecodeInt(v_rawGlyph, i));
				break;
			LB_PARSE_CHAR_SWITCH(callgsubr);
			LB_PARSE_CHAR_SWITCH(vhcurveto);
			LB_PARSE_CHAR_SWITCH(hvcurveto);
		default:
			vDataBuffer.push_back(this->vOTF.GetCFF().DecodeInt(v_rawGlyph, i));
			break;
		}
	}

#undef LB_PARSE_CHAR_SWITCH
#undef LB_PARSE_CHAR_SWITCH2

	return vResult;
}
