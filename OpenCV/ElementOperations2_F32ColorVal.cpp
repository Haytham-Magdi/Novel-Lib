#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2_Float.h>
#include <NovelCVLib\OpenCV\ElementOperations2_F32ColorVal.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2_Float.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{

		void Assign(F32ColorVal * a_pDest, const F32ColorVal & a_src)
		{
			Assign(&a_pDest->val0, a_src.val0);
			Assign(&a_pDest->val1, a_src.val1);
			Assign(&a_pDest->val2, a_src.val2);
		}

		float CalcMagSqr(const F32ColorVal & a_arg)
		{
			float sum = 0;
			sum += CalcMagSqr(a_arg.val0);
			sum += CalcMagSqr(a_arg.val1);
			sum += CalcMagSqr(a_arg.val2);

			return sum;
		}

		void Add(const F32ColorVal & a_inp1, const F32ColorVal & a_inp2, F32ColorVal * a_pOut)
		{
			Add(a_inp1.val0, a_inp2.val0, &a_pOut->val0);
			Add(a_inp1.val1, a_inp2.val1, &a_pOut->val1);
			Add(a_inp1.val2, a_inp2.val2, &a_pOut->val2);
		}

		void Subtract(const F32ColorVal & a_inp1, const F32ColorVal & a_inp2, F32ColorVal * a_pOut)
		{
			Subtract(a_inp1.val0, a_inp2.val0, &a_pOut->val0);
			Subtract(a_inp1.val1, a_inp2.val1, &a_pOut->val1);
			Subtract(a_inp1.val2, a_inp2.val2, &a_pOut->val2);
		}

		void DivideByNum(const F32ColorVal & a_inp, const float a_num, F32ColorVal * a_pOut)
		{
			DivideByNum(a_inp.val0, a_num, &a_pOut->val0);
			DivideByNum(a_inp.val1, a_num, &a_pOut->val1);
			DivideByNum(a_inp.val2, a_num, &a_pOut->val2);
		}

		void MultiplyByNum(const F32ColorVal & a_inp, const float a_num, F32ColorVal * a_pOut)
		{
			MultiplyByNum(a_inp.val0, a_num, &a_pOut->val0);
			MultiplyByNum(a_inp.val1, a_num, &a_pOut->val1);
			MultiplyByNum(a_inp.val2, a_num, &a_pOut->val2);
		}

		void SetToZero(F32ColorVal * a_pArg)
		{
			SetToZero(&a_pArg->val0);
			SetToZero(&a_pArg->val1);
			SetToZero(&a_pArg->val2);
		}

		bool IsUndefined(const F32ColorVal & a_arg)
		{
			return IsUndefined(a_arg.val0);
		}

		void SetToUndefined(F32ColorVal * a_pArg)
		{
			SetToUndefined(&a_pArg->val0);
			SetToUndefined(&a_pArg->val1);
			SetToUndefined(&a_pArg->val2);
		}













		//void Copy_ByPtr(F32ColorVal * a_pDest, F32ColorVal * a_pSrc)
		//{
		//	memcpy(a_pDest, a_pSrc, sizeof(F32ColorVal));
		//}

		//float CalcMagSqr_ByPtr(F32ColorVal * a_pArg)
		//{
		//	return a_pArg->CalcMagSqr();
		//}

		//void AssertValue_ByPtr(F32ColorVal * a_pArg)
		//{
		//	Ncpp_ASSERT(a_pArg->val0 > -3000000.0f && a_pArg->val0 < 3000000.0f);
		//	Ncpp_ASSERT(a_pArg->val1 > -3000000.0f && a_pArg->val1 < 3000000.0f);
		//	Ncpp_ASSERT(a_pArg->val2 > -3000000.0f && a_pArg->val2 < 3000000.0f);
		//}

		//void Add_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp1->val0 + a_pInp2->val0;
		//	a_pOut->val1 = a_pInp1->val1 + a_pInp2->val1;
		//	a_pOut->val2 = a_pInp1->val2 + a_pInp2->val2;
		//}

		//void Subtract_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp1->val0 - a_pInp2->val0;
		//	a_pOut->val1 = a_pInp1->val1 - a_pInp2->val1;
		//	a_pOut->val2 = a_pInp1->val2 - a_pInp2->val2;
		//}

		//void DivideByNum_ByPtr(F32ColorVal * a_pInp, const float a_num, F32ColorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp->val0 / a_num;
		//	a_pOut->val1 = a_pInp->val1 / a_num;
		//	a_pOut->val2 = a_pInp->val2 / a_num;
		//}

		//void MultiplyByNum_ByPtr(F32ColorVal * a_pInp, const float a_num, F32ColorVal * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp->val0 * a_num;
		//	a_pOut->val1 = a_pInp->val1 * a_num;
		//	a_pOut->val2 = a_pInp->val2 * a_num;
		//}

		//void SetToZero_ByPtr(F32ColorVal * a_pArg)
		//{
		//	a_pArg->val0 = 0;
		//	a_pArg->val1 = 0;
		//	a_pArg->val2 = 0;
		//}

		//bool IsUndefined_ByPtr(F32ColorVal * a_pArg)
		//{
		//	return IsUndefined_ByPtr<float>(&a_pArg->val0);
		//}

		//void SetToUndefined_ByPtr(F32ColorVal * a_pArg)
		//{
		//	SetToUndefined_ByPtr<float>(&a_pArg->val0);
		//	SetToUndefined_ByPtr<float>(&a_pArg->val1);
		//	SetToUndefined_ByPtr<float>(&a_pArg->val2);
		//}

	};
}