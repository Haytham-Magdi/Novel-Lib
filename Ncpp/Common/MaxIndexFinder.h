#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
//#include <NovelCVLib\Ncpp\Common\indexcalc.h>




namespace Ncpp
{
	template< class T >
	class MaxIndexFinder : public Ncpp::Object
	{
	public :

		MaxIndexFinder( T a_valOrg = -10000000 )
		{
			m_valOrg = a_valOrg;
			m_valCur = a_valOrg;
		}

		void PushValue( T a_val, int a_nIdx )
		{
			if( a_val > m_valCur )
			{
				m_valCur = a_val;
				m_nIdx = a_nIdx;
			}
		}

		T FindMax()
		{
			return m_valCur;
		}

		T FindMaxIdx()
		{
			return m_nIdx;
		}


		void Reset()
		{
			m_valCur = m_valOrg;
			m_nIdx = -1;
		}


	protected:

		T m_valOrg;
		T m_valCur;

		int m_nIdx;
	};

}