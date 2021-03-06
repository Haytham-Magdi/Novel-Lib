#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>


namespace Ncv
{
	using namespace Ncpp::Math;
	using namespace std;

	class Signal1D : public Ncpp::Object
	{
	public:

		friend class Signal1DBuilder;

		vector<float> m_data;
		int m_nBgn;		
	};

	typedef Ncpp::ObjRef< Signal1D > Signal1DRef;



	class Signal1DBuilder : public Ncpp::Object
	{
	public:

		Signal1DBuilder(int a_capacity, int a_nBgn = 0)
		{
			Init(a_capacity, a_nBgn);

			m_bDone = false;
		}

		Signal1DBuilder()
		{
			Init(400, 0);

			m_bDone = false;
		}

		static Signal1DRef CreateConstSignal( float a_val, const int a_nSize, int a_nBgn = 0 )
		{
			Signal1DBuilder sb( a_nSize, a_nBgn );
			sb.AddConstArr( a_val, a_nSize );

			return sb.GetResult();
		}

		static Signal1DRef CreateStripSignal( float a_mag, int a_nStripFrq, 
			const int a_nSize, int a_nBgn = 0 )
		{
			Signal1DRef ret = CreateConstSignal( 0, a_nSize, a_nBgn );

			vector< float > & rData = ret->m_data;

			for( int i=0; i < rData.size(); i++ )
			{
				if( 0 != i % a_nStripFrq )
					continue;

				rData[ i ] = a_mag;
			}			

			return ret;
		}

		bool IsDone()
		{
			return m_bDone;
		}

		void AddValue( float a_value );

		void AddData( float * a_dataBuf, const int a_nSize );

		void AddConstArr( float a_val, const int a_nSize );

		Signal1DRef GetResult();



	protected:

		void Init(int a_capacity, int a_nBgn);
		void Build( );

	protected:

		Signal1DRef m_sig;
		bool m_bDone;
	};

	typedef Ncpp::ObjRef< Signal1DBuilder > Signal1DBuilderRef;




}
