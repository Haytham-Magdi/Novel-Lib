#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Element_Operations\Element_Operations.h>
#include <NovelCVLib\Element_Operations\Element_Operations_VectorVal.h>





namespace Ncv
{
	using namespace Ncpp;

	namespace Element_Operations
	{

#define T_Elm float
#define N_Dims 2

#include <NovelCVLib\Element_Operations\Element_Operations_VectorVal_CoreFile.cpp>

#undef T_Elm
#undef N_Dims

#define T_Elm float
#define N_Dims 3

#include <NovelCVLib\Element_Operations\Element_Operations_VectorVal_CoreFile.cpp>

#undef T_Elm
#undef N_Dims


#define T_Elm float
#define N_Dims 4

#include <NovelCVLib\Element_Operations\Element_Operations_VectorVal_CoreFile.cpp>

#undef T_Elm
#undef N_Dims


		//void Copy_ByPtr(VectorVal * a_pDest, VectorVal * a_pSrc)
		//{
		//	memcpy(a_pDest, a_pSrc, sizeof(VectorVal));
		//}

		//template<class T, const int >
		//float CalcMagSqr_ByPtr(VectorVal * a_pArg)
		//{
		//	float sum = 0;
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		sum += Sqr(a_pArg->Vals[i]);
		//	}

		//	return sum;
		//}

		//void Add_ByPtr(VectorVal * a_pInp1, VectorVal * a_pInp2, VectorVal * a_pOut)
		//{

		//	a_pOut->val0 = a_pInp1->val0 + a_pInp2->val0;
		//	a_pOut->val1 = a_pInp1->val1 + a_pInp2->val1;
		//	a_pOut->val2 = a_pInp1->val2 + a_pInp2->val2;
		//}

		//void Subtract_ByPtr(VectorVal * a_pInp1, VectorVal * a_pInp2, VectorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp1->val0 - a_pInp2->val0;
		//	a_pOut->val1 = a_pInp1->val1 - a_pInp2->val1;
		//	a_pOut->val2 = a_pInp1->val2 - a_pInp2->val2;
		//}

		//void DivideByNum_ByPtr(VectorVal * a_pInp, float a_num, VectorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp->val0 / a_num;
		//	a_pOut->val1 = a_pInp->val1 / a_num;
		//	a_pOut->val2 = a_pInp->val2 / a_num;
		//}

		//void MultiplyByNum_ByPtr(VectorVal * a_pInp, float a_num, VectorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp->val0 * a_num;
		//	a_pOut->val1 = a_pInp->val1 * a_num;
		//	a_pOut->val2 = a_pInp->val2 * a_num;
		//}

		//void SetToZero_ByPtr(VectorVal * a_pArg)
		//{
		//	a_pArg->val0 = 0;
		//	a_pArg->val1 = 0;
		//	a_pArg->val2 = 0;
		//}

	};
}