#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{
	class OffsetCalc_1D;
	typedef Ncpp::ObjRef< OffsetCalc_1D > OffsetCalc_1D_Ref;

	class OffsetCalc_1D : public Ncpp::Object
	{
	public:

		OffsetCalc_1D(int a_nOuterNofElms, int a_nAbsoluteStepSize)
		{
			m_isLocked = false;
			Init(a_nOuterNofElms, a_nAbsoluteStepSize, 0, a_nOuterNofElms - 1);
		}

		OffsetCalc_1D_Ref Clone()
		{
			OffsetCalc_1D_Ref pRet = new OffsetCalc_1D();

			//	This could be dangerous in case that any ref member exists!
			*pRet = *this;

			pRet->m_isLocked = false;
			return pRet;
		}

		bool IsLocked()
		{
			return m_isLocked;
		}

		void Lock()
		{
			m_isLocked = true;
		}

		void Unlock()
		{
			m_isLocked = false;
		}

		void SetRange_Relative(int a_nRelativeBgnStep, int a_nRelativeEndStep)
		{
			if (m_isLocked)
				throw "m_isLocked";

			Ncpp_ASSERT(a_nRelativeBgnStep >= 0);
			Ncpp_ASSERT(a_nRelativeBgnStep < m_NofElms);

			Ncpp_ASSERT(a_nRelativeEndStep >= 0);
			Ncpp_ASSERT(a_nRelativeEndStep < m_NofElms);

			int nRelativeRangeDiff = a_nRelativeEndStep - a_nRelativeBgnStep;
			Ncpp_ASSERT(0 != nRelativeRangeDiff);

			int nDir = m_nActualStepSize / m_nAbsoluteStepSize;

			int nNewInnerBgnStep = m_nInnerBgnStep + nDir * a_nRelativeBgnStep;
			int nNewInnerEndStep = m_nInnerBgnStep + nDir * a_nRelativeEndStep;

			SetRange_Absolute(nNewInnerBgnStep, nNewInnerEndStep);
		}

		int GetOffsetPart1()
		{
			return m_nOffsetPart1;
		}

		int CalcPart2(int a_nStep)
		{
			return a_nStep * m_nActualStepSize;
		}

		int ReverseCalc(int a_nOffset)
		{
			Ncpp_ASSERT(0 == a_nOffset % m_nAbsoluteStepSize);
			//int nStep = ((a_nOffset - m_nOffsetPart1) % m_nOuterLimOffset) / m_nAbsoluteStepSize;

			int nStep = ReverseCalcPart2(a_nOffset - m_nOffsetPart1);
			return nStep;
		}

		int ReverseCalcPart2(int a_nOffsetPart2)
		{
			Ncpp_ASSERT(0 == a_nOffsetPart2 % m_nAbsoluteStepSize);
			
			int nStep = (a_nOffsetPart2 % m_nOuterLimOffset) / m_nAbsoluteStepSize;
			return nStep;
		}

		//int GetAbsoluteStepSize()
		//{
		//	return m_nAbsoluteStepSize;
		//}

		int GetActualStepSize()
		{
			return m_nActualStepSize;
		}

		int GetActualLimOffset()
		{
			return m_nActualLimOffset;
		}

		int GetOuterLimOffset()
		{
			return m_nOuterLimOffset;
		}

		int GetOuterNofElms()
		{
			return m_nOuterNofElms;
		}

		int GetNofElms()
		{
			return m_NofElms;
		}

		void ResetRange()
		{
			SetRange_Absolute(0, m_nOuterNofElms - 1);
		}

	protected:

		OffsetCalc_1D()
		{
			m_isLocked = false;
		}

		void Init(int a_nOuterNofElms, int a_nAbsoluteStepSize, int a_nInnerBgnStep, int a_nInnerEndStep)
		{
			if (m_isLocked)
				throw "m_isLocked";

			Ncpp_ASSERT(a_nOuterNofElms > 0);
			Ncpp_ASSERT(a_nAbsoluteStepSize > 0);

			m_nOuterNofElms = a_nOuterNofElms;
			m_nAbsoluteStepSize = a_nAbsoluteStepSize;
			m_nOuterLimOffset = m_nOuterNofElms * m_nAbsoluteStepSize;

			SetRange_Absolute(a_nInnerBgnStep, a_nInnerEndStep);
		}

		void SetRange_Absolute(int a_nInnerBgnStep, int a_nInnerEndStep)
		{
			if (m_isLocked)
				throw "m_isLocked";

			Ncpp_ASSERT(a_nInnerBgnStep >= 0);
			Ncpp_ASSERT(a_nInnerBgnStep < m_nOuterNofElms);

			Ncpp_ASSERT(a_nInnerEndStep >= 0);
			Ncpp_ASSERT(a_nInnerEndStep < m_nOuterNofElms);

			//int nInnerRangeDiff = a_nInnerEndStep - a_nInnerBgnStep;
			int nInnerRangeDiff = (a_nInnerEndStep + 1) - a_nInnerBgnStep;
			Ncpp_ASSERT(0 != nInnerRangeDiff);

			m_NofElms = abs(nInnerRangeDiff);

			m_nInnerBgnStep = a_nInnerBgnStep;
			m_nInnerEndStep = a_nInnerEndStep;

			m_nOffsetPart1 = m_nInnerBgnStep * m_nAbsoluteStepSize;

			if (nInnerRangeDiff > 0)
			{
				m_nActualStepSize = m_nAbsoluteStepSize;
			}
			else
			{
				m_nActualStepSize = -m_nAbsoluteStepSize;
			}

			m_nActualLimOffset = m_nOffsetPart1 + CalcPart2(m_nInnerEndStep + 1);
		}

	protected:

		int m_nOffsetPart1;
		int m_nActualLimOffset;

		int m_nAbsoluteStepSize;
		int m_nActualStepSize;

		int m_nOuterNofElms;
		int m_nOuterLimOffset;

		int m_NofElms;
		int m_nInnerBgnStep;
		int m_nInnerEndStep;

		bool m_isLocked;
	};

}