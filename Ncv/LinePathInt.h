#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncpp\Math\mathLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>

#include <Novel-Lib\Ncv\LinePath.h>

namespace Ncv
{
	//using namespace Ncpp::Math;


	class LinePathInt : public LinePath
	{
	public:

		LinePathInt( int a_x1, int a_y1, int a_x2, int a_y2 );

		F32Point GetCurrent()
		{
			return m_curPnt.Round();
			//return m_curPnt;
		}

		bool MoveNext();




	protected:


		const F32Point m_bgnPnt;
		const F32Point m_endPnt;

		int m_nReqSteps;
		int m_nDoneSteps;

		F32Point m_curPnt;

		F32Point m_stepPnt;
	};


	typedef Ncpp::ObjRef< LinePathInt > LinePathIntRef;

}