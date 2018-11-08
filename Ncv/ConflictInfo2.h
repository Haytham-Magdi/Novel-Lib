#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>



namespace Ncv
{

	class ConflictInfo2 //: public Ncpp::Object
	{
	public:
		bool Exists;
		//void * pSide_1;
		//void * pSide_2;

		int Offset_Side_1;
		int Offset_Side_2;
	};

	class ConflictInfo2_Ex : public ConflictInfo2//: public Ncpp::Object
	{
	public:
		int Dir;
	};

	//typedef Ncpp::ObjRef< ConflictInfo2 > ConflictInfo2Ref;
}