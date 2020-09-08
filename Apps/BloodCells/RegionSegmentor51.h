#pragma once

#include <NovelCVLib\Cpp\Common\commonLib.h>
#include <NovelCVLib\Cpp\Math\mathLib.h>
#include <NovelCVLib\Hcv\CvIncludes.h>
#include <NovelCVLib\Hcv\Types.h>
#include <NovelCVLib\Hcv\error.h>
#include <vector>
#include <NovelCVLib\Hcv\Channel.h>
#include <NovelCVLib\Hcv\Image.h>

#include <NovelCVLib\Hcv\ConflictScanner2.h>
#include <NovelCVLib\Hcv\BadRootScanner.h>

#include <NovelCVLib\Hcv\SlideMgr.h>

//#include <NovelCVLib\Hcv\ScanTryMgr_9.h>
#include <NovelCVLib\Hcv\ImgScanMgr.h>

#include <NovelCVLib\Hcv\ImgDataElm_CovMat.h>

#include <NovelCVLib\Ncpp\Common\MultiAllocProvider.h>


namespace Hcv
{
	class ImgSegDataMgr;


	using namespace Hcpl::Math;


	class RegionSegmentor51 // : public IRegionSegmentor20
	{
//////////////////////////////////////////////////////////////

		typedef enum
		{
			RC = 0, 
			RB, CB, LB,
			LC,		
			LT, CT, RT
		}RgnLinkDir;


	public:



		class LinkTypeMgr;

		class MgrOfLinkTypes
		{ 

		public:
			class CoreStuff
			{
			public:

				CoreStuff() : m_mapIndexCalc(8, 8), m_dxyIndexCalc(3, 3)
				{
					InitLinkTypeMgrs();
					InitMaps();
				}

				float GetDist(int a_i, int a_j)
				{
					return m_distMap[ 
						//m_mapIndexCalc.Calc(a_i, a_j) ];
						m_mapIndexCalc.Calc(a_j, a_i) ];
				}

				int GetNbr(int a_i, int a_j)
				{
					return m_nbrMap[ 
						//m_mapIndexCalc.Calc(a_i, a_j) ];
						m_mapIndexCalc.Calc(a_j, a_i) ];
				}

				int GetInverseLinkIndex(int a_index)
				{
					return (&m_linkTypeMgrVect[a_index])->GetInverseLinkTypeMgr()->GetIndex();
				}

				int GetLinkIndex(int a_dx, int a_dy)
				{
					int index = m_dxyIndexMap[ m_dxyIndexCalc.Calc( a_dx + 1, a_dy + 1) ];

					return index;
				}
				


			protected:
				void InitLinkTypeMgrs();				
				void InitMaps();

			protected:
				FixedVector<LinkTypeMgr> m_linkTypeMgrVect;
				float m_distMap[64];
				int m_nbrMap[64];
				IndexCalc2D m_mapIndexCalc;

				int m_dxyIndexMap[9];
				IndexCalc2D m_dxyIndexCalc;

			};


		public:
			static CoreStuff * GetCore()
			{
				static CoreStuff core;

				return &core;
			}


		protected:
			//static CoreStuff m_core;


		};


		class LinkTypeMgr
		{
			friend class MgrOfLinkTypes;

		public:

			F32Point GetDirXY()
			{
				return m_dirXY;
			}

			F32Point GetUnitDirXY()
			{
				return m_unitDirXY;
			}

			int GetIndex()
			{
				return (int)m_dir;
			}

			RgnLinkDir GetLinkDir()
			{
				return m_dir;
			}

			LinkTypeMgr * GetInverseLinkTypeMgr()
			{
				return m_pInverseLinkTypeMgr;
			}

		protected:
			void Init(LinkTypeMgr * a_pLTM0, int a_i, F32Point & a_dirXY)
			{
				m_dirXY = a_dirXY;
				m_unitDirXY = a_dirXY.GetUnitVect();
				m_dir = (RgnLinkDir)a_i;

				RgnLinkDir inverseDir;

				if( a_i < 4 )
				{
					inverseDir = (RgnLinkDir)( a_i + 4 );
				}
				else
				{
					inverseDir = (RgnLinkDir)( a_i - 4 );
				}

				m_pInverseLinkTypeMgr = &a_pLTM0[ (int)inverseDir ]; 
			}
		
		
		protected:
			F32Point m_dirXY;
			F32Point m_unitDirXY;
			RgnLinkDir m_dir;
			//RgnLinkDir m_inverseDir;
			LinkTypeMgr * m_pInverseLinkTypeMgr;
			//float * m_dists
		};






//////////////////////////////////////////////////////////////

	protected:

		class RgnInfo;
		class RgnLink;


	public:



		struct RgnConflict
		{
			RgnInfo * pPeerRgn;

			// RgnInfo * pOrgEdge;
			// RgnInfo * pOrgR1;
			// RgnInfo * pOrgR2;

			// RgnInfo * pOrgDeep1;
			// RgnInfo * pOrgDeep2;

			// ImgScanMgr_Ns::EdgeInfo * pEI;

			struct _RgnConflict * pNext;	//	for being APtrList Entry
			struct _RgnConflict * pPrev;	//	for being APtrList Entry
		};



		class LinkAction;


		class RgnLink
		{
		public:

			RgnLink()
			{
				bInTrace = false;
				//pInvLink = NULL;

				pCurLA = NULL;
			}

			//RgnInfo * pPeerRgn;

			RgnInfo * pRgn1;
			RgnInfo * pRgn2;

			RgnLink * GetInvLinkPtr()
			{
				return & pRgn2->links[ ( (int)dir + 4 ) % 8 ];
			}

			RgnLinkDir dir;
			bool bProcessed;
			bool bExists;
			// bool bInTrace;

			// float DistMag;
			// F32ColorVal UnitDist;

			LinkAction * pCurLA;

			// RgnLink * pPrev;	//	for being ListQue Entry
		};

		class RgnInfoListElm;

/*
			class RgnInfoListElm
			{
			public:
				RgnInfo * pRgn;
				RgnInfoListElm * pNext;
			};
*/

		class RgnInfo : public PixelRgn<RgnInfo>
		{
		protected:
			RgnInfo * pActRgn;

			// // bool bIsRoot;
			RgnInfo * pRootRgn;

		public:


			RgnInfo()
			{
			}

			RgnInfo * GetRootRgn()
			{
				return pRootRgn;
			}

			// void SetRootRgn(RgnInfo * a_pRootRgn)
			// {
			// 	nMergeOrder = s_MergeOrder++;

			// 	this->pRootRgn = a_pRootRgn;
			// }



			int nIndex;

			int nSegIndex;


			F32ColorVal * pixColors;



			// F32Point pos;

			//bool bIsInConflict;


			RgnLink links[8];
			APtrList< RgnConflict > conflictList;

			// bool bHasConflicts;


			RgnInfo * pSrcRgn;

			int nTraceID;

			int nMergeOrder;

			// bool bIsPassiveRoot;

			static int s_MergeOrder;

			int nLastVisitID;

			RgnInfo * pPrev;	//	for being ListQue Entry
		};


		class LinkAction_2 : public MultiListQueMember< LinkAction_2 >
		{
		public:

			int nIndex;

			RgnInfo * pRgn1;
			RgnInfo * pRgn2;
		};

		class LinkAction : public MultiListQueMember< LinkAction >
		{
		public:

			LinkAction()
			{
				bShowTrace = false;
				bActionCanceled = false;
				bIntersected = false;
				nIndex = 0;
				bIsActive = false;
			}


			//RgnInfo * pRgn1;
			//RgnInfo * pRgn2;

			RgnLink * pLink1;
			//RgnLink * pLink2;

			bool bIsActive;

			bool bShowTrace;
			bool bActionCanceled;
			bool bIntersected;

			int nScaledDist;

			int nIndex;

		};





	public:
		RegionSegmentor51(F32ImageRef a_src, S16ImageRef a_rootImg,
			int a_nDifThreshold = 15, F32ImageRef a_rootValImg = NULL);

		~RegionSegmentor51();


		
		static inline bool HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn);


		virtual void Segment();
		virtual S16ImageRef GenSegmentedImage(bool a_bShowMeanColor = true);
		
		virtual F32ImageRef GenSegmentedImage2(bool a_bShowMeanColor = true);


	protected:

		//void Manage_EI_Activation( RgnInfo * a_pRgn_1, RgnInfo * a_pRgn_2 );

		float GetRgnGradVal( RgnInfo * a_pRgn )
		{
			return *m_srcGrad->GetPixAt( a_pRgn->pos.x, a_pRgn->pos.y );
		}

		void ScanImageLines();
		void PostScanPrepare();

		void InitLinks(void);
		void ProcessEdgeQues();
		void TraceLinkActionRoots( LinkAction * a_pLA );
			//RgnInfo ** a_ppRoot1, RgnInfo ** a_ppRoot2 );

		void RegionSegmentor51::AddFwdTraceUnit(RgnInfo * a_pRgn, int a_nFwdIndex, int a_nBkdIndex);
		void RegionSegmentor51::AddBkdTraceUnit(RgnInfo * a_pRgn, int a_nFwdIndex, int a_nBkdIndex);

		int GetInverseLinkIndex(int a_index)
		{
			return MgrOfLinkTypes::GetCore()->GetInverseLinkIndex(a_index);
		}

		void PrepareTraceListPtrs();




		void ProcessLinkActionTrace( LinkAction * a_pLA );
		void InitRgnInfoVect(void);
		void PrepareConflicts();
		void PrepareRgnConflicts( RgnInfo * a_pRgn );

		int GetMaxDif() { return m_nMaxDif; }
		float m_difScale;

		void InitMaxDif() 
		{ 
			m_difScale = 100;
			//m_difScale = 1;

			m_nMaxDif =  (int)( m_difScale *  
				sqrt( 
			//m_nMaxDif =  ( (
				//(float) ( 3 * Sqr(255)) )); 				
				//(float) ( 3 * Sqr(500)) )); 				
				(float) ( 3 * Sqr(700)) )); 				
				//(float) ( 3 * Sqr(255)) ) * 1.4); 				

			m_nMaxDif += m_nAprSize;
		}

		inline float CalcRgnDif(RgnInfo * a_pRgn1, RgnInfo * a_pRgn2);

		// With Space
		inline float CalcRgnDifWS(RgnInfo * a_pRgn1, RgnInfo * a_pRgn2);
		inline bool IsConflictDist(float a_dist)
		{			
			return  ( a_dist >= (m_difThreshold * m_difScale) );
		}

		inline void CreateLink( RgnInfo * a_pRgn, 
			int x, int y, RgnLinkDir a_dir);

		RgnInfo * GetPointRgn(int x, int y)
		{ 
			return &m_rgnInfoVect[m_rgnIndexCalc.Calc(x, y)]; 
		}

		inline void UpdateActRgn(RgnInfo * a_pRgn);

		inline void PrepareLinkAction( RgnLink & a_rLink, float a_distBef, 
			bool a_bSetProcessed = true);

		//inline LinkAction * ProvideLinkAction(RgnInfo * a_pRgn, RgnLinkDir a_dir, bool a_bSetProcessed = true);
		inline LinkAction * ProvideLinkAction( RgnInfo * a_pRgn, RgnLinkDir a_dir );

		inline LinkAction * ProvideLinkAction( RgnInfo * a_pRgn, RgnInfo * a_pRgn2 );

		//inline LinkAction * CloneLinkAction(LinkAction * a_pLA );

		inline RgnConflict * GetConflictIfExists( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn);

		inline void RemoveDuplicateConflicts( RgnInfo * a_pRgn );

		inline void PrepareRgnLinkActions( RgnInfo * a_pRgn, float a_distBef );

		inline void CreateConflict( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2, RgnInfo * pOrgEdge = NULL, ImgScanMgr_Ns::EdgeInfo * a_pEI = NULL );


		F32ImageRef GenScanImage();

		F32ImageRef GenRootRgnImage();

		F32ImageRef GenMergeOrderImage();

		F32ImageRef Gen_FalseMergeImage();

		F32ImageRef Gen_FalseMergeImage_2();

		void ProcessLineScanResult( RgnLinkDir a_dir );

		void PrepareSrcGradImg();

		RgnLink * GetLinkBetweenRgns( int a_nIdx_1, int a_nIdx_2 );



	protected:

		SlideMgrRef m_slideMgr;

		F32ImageRef m_src;
		F32ImageRef m_srcGrad;
		F32ImageRef m_orgSrc;
		F32ImageRef m_rootRgnImg;
		F32ImageRef m_slideRootDifImg;

		LinkAction * pLADbg; 

		int m_nMaxDif;
		IndexCalc2D m_rgnIndexCalc;

		
		FixedVector< FillInfo > m_fillInfoVect;

		FixedVector<RgnInfo> m_rgnInfoVect;
		FixedVector<RgnInfo *> m_medTraceRgnPtrVect;

		FixedVector< RgnInfoListElm > m_traceRootAllocVect;

		FixedVector<TraceUnit> m_edgeFwdRgnVect;
		FixedVector<TraceUnit> m_edgeBkdRgnVect;


		//FixedVector<LinkAction> m_linkActionVect;

		// MultiAllocProvider< LinkAction > m_linkAction_Provider;
		MultiAllocProviderRef< LinkAction > m_linkAction_Provider;

		FixedVector< LinkAction_2 > m_linkAction_2_Arr;

		//int m_nofLinkActions;

		FixedVector<RgnConflict> m_rgnConflictVect;
		int m_nofConflicts;
		int m_nofPrimConfRgns;

		//MultiListQue< LinkAction > m_difQues;
		MultiListQueMgr< LinkAction_2 > m_linkActionMergeQues;
		MultiListQueMgr< LinkAction > m_linkActionEdgeQues;


		//MultiListQue< LinkAction > m_difQues2;
		ListQue< RgnInfo > m_RgnOfConflictQue;
		float m_difThreshold;

		int m_nVisitID;

		RgnInfo * m_pAnyRoot;

		RgnInfo * m_pDbgRgn;

		MultiListQue< LinkAction > m_medTraceQues;


		MultiListQueMgr< ImgScanMgr_Ns::EdgeInfo > m_edgeInfo_Ques;

		
		//F32ImageRef m_scanImg;

		ImgScanMgrRef m_imgScanMgr; 

		float * m_dir_difBuf_Arr[8];

		float * m_maxDif_Buf;

		float * m_standDev_Buf;

		EdgeScan::PixInfo * m_scanPix_Buf;


		float * m_standDiv_Buf;

		//ImgDataElm_CovMat * m_dataElm_Buf;

		//ImgDataElm_CovMat * m_dataElm_Mean_Buf;

		//float * m_avgSqrMag_Buf;


		//FixedVector< RgnInfo * > m_rgnInTraceArr;
		//FixedVector< RgnInfo * > m_rgnOfBadSrcArr;

		//FixedVector< RgnInfo * > m_rgnOf_FstBadSrcArr;

		//int m_nCurGrpID;

		//FixedVector< RgnInfo * > m_rgnOf_FstBadSrcArr_2;

		//FixedVector< RgnInfo * > m_rgnOf_OpenEnd_Arr;

		//FixedDeque< RgnInfo * > m_fillDeq;

		//FixedDeque< RgnInfo * > m_unfill_Deq;

		//FixedVector< ImgScanMgr_Ns::EdgeInfo * > m_fstFromBad_EI_Arr;

		//FixedVector< ImgScanMgr_Ns::EdgeInfo * > m_shortest_FromBad_EI_Arr;

		int m_nTestRgnIdx;

		
		const int m_nAprSize;

		
		
	};


	typedef Hcpl::ObjRef< RegionSegmentor51 > RegionSegmentor51Ref;
}