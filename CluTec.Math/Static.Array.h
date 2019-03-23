////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Array.h
//
// summary:   Declares the static. array class
//
//            Copyright (c) 2019 by Christian Perwass.
//
//            This file is part of the CluTecLib library.
//
//            The CluTecLib library is free software: you can redistribute it and / or modify
//            it under the terms of the GNU Lesser General Public License as published by
//            the Free Software Foundation, either version 3 of the License, or
//            (at your option) any later version.
//
//            The CluTecLib library is distributed in the hope that it will be useful,
//            but WITHOUT ANY WARRANTY; without even the implied warranty of
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//            GNU Lesser General Public License for more details.
//
//            You should have received a copy of the GNU Lesser General Public License
//            along with the CluTecLib library.
//            If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

namespace Clu
{
	template<class _TValue, uint32_t t_nDim>
	struct _SArray
	{
		using TThis = _SArray<_TValue, t_nDim>;
		using TValue = _TValue;
		using TValuePtr = TValue*;
		using TValueRef = TValue&;
		using TConstValuePtr = const TValue*;
		using TConstValueRef = const TValue&;

		using TSize = uint32_t;
		using TIdx = uint32_t;

		static const TSize ElementCount = t_nDim;

	protected:
		TValue pData[ElementCount];


	public:

		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////

#pragma region Initialization
		__CUDA_HDI__ TThis& operator= (const TThis& xA)
		{
			Assign(xA);
			return *this;
		}

		__CUDA_HDI__ void Assign(const TThis& xA)
		{
#if defined(__NVCC__)
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				pData[i] = xA.pData[i];
			}
#else
			memcpy(pData, xA.pData, ElementCount * sizeof(TValue));
#endif
		}


		__CUDA_HDI__ void Assign(const TValue pArrayData[ElementCount])
		{
			ForEachElementIdx([&pArrayData](TValue& xValue, TIdx i)
			{
				xValue = pArrayData[i];
			});
		}

		__CUDA_HDI__ void Assign(const TValuePtr pArrayData, TSize nSize)
		{
#if defined (__NVCC__)
			if (nSize < ElementCount)
			{
				return;
			}
#else
			throw CLU_EXCEPTION("Data array size is to small to initialize array");
#endif

			ForEachElementIdx([&pArrayData](TValue& xValue, TIdx i)
			{
				xValue = pArrayData[i];
			});
		}


		__CUDA_HDI__ void ToArray(TValue pArrayData[ElementCount]) const
		{
#if defined(__NVCC__)
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				pArrayData[i] = pData[i];
			}
#else
			memcpy(pArrayData, pData, ElementCount * sizeof(TValue));
#endif
		}

		__CUDA_HDI__ void SetZero()
		{
			ForEachElement([](TValue& xValue)
			{
				xValue = TValue(0);
			});
		}

		__CUDA_HDI__ void SetToValue(const TValue& xVal)
		{
			ForEachElement([&xVal](TValue& xValue)
			{
				xValue = xVal;
			});
		}

		__CUDA_HDI__ void SetToValue(const TValue& xVal, TIdx nOffset)
		{
			for (TIdx i = nOffset; i < ElementCount; ++i)
			{
				pData[i] = xVal;
			}
		}


		template<TIdx nIdx, typename TValue2, typename... TPars>
		__CUDA_HDI__ void SetElements_Impl(TValue2 xValue, TPars&&... xPars)
		{
			static_assert(nIdx < ElementCount, "Too many parameters in setting vector values");

			pData[nIdx] = TValue(xValue);
			SetElements_Impl<nIdx + 1>(xPars...);
		}

		template<TIdx nIdx>
		__CUDA_HDI__ void SetElements_Impl()
		{
			// Set remaining elements in vector to zero
			SetToValue(TValue(0), nIdx);
		}

		template<typename... TPars>
		__CUDA_HDI__ void SetElements(TPars&&... xPars)
		{
			SetElements_Impl<0>(xPars...);
		}


		template<typename TValue2>
		__CUDA_HDI__ void CastFrom(const _SArray<TValue2, t_nDim>& xB)
		{
			ForEachElementIdx([&xB](TValue& xValue, TIdx iIdx)
			{
				xValue = TValue(xB[iIdx]);
			});
		}

		template<typename TValue2>
		__CUDA_HDI__ void CastFrom(const TValue2 pArrayData[ElementCount])
		{
			ForEachElementIdx([&pArrayData](TValue& xValue, TIdx i)
			{
				xValue = TValue(pArrayData[i]);
			});
		}

		template<typename TValue2>
		__CUDA_HDI__ void CastFrom(const TValue2* pArrayData, TSize nSize)
		{
#if defined (__NVCC__)
			if (nSize < ElementCount)
			{
				return;
			}
#else
			throw CLU_EXCEPTION("Data array size is to small to initialize array");
#endif

			ForEachElementIdx([&pArrayData](TValue& xValue, TIdx i)
			{
				xValue = TValue(pArrayData[i]);
			});
		}
#pragma endregion

		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////


#pragma region Access
		__CUDA_HDI__ TValueRef operator[] (TIdx nIdx)
		{
			CLU_ASSERT(nIdx < ElementCount);
			return pData[nIdx];
		}

		__CUDA_HDI__ const TValue& operator[] (TIdx nIdx) const
		{
			CLU_ASSERT(nIdx < ElementCount);
			return pData[nIdx];
		}


		__CUDA_HDI__ TValuePtr DataPointer()
		{
			return pData;
		}

		__CUDA_HDI__ const TValue* DataPointer() const
		{
			return pData;
		}

#pragma endregion

		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////


#pragma region Algorithms

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElement(FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i]);
			}
		}

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElement(FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i]);
			}
		}


		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElementPair(const TThis& xArray, FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i], xArray.pData[i]);
			}
		}

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElementPair(const TThis& xArray, FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i], xArray.pData[i]);
			}
		}


		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElementTriplet(const TThis& xA, const TThis& xB, FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i], xA.pData[i], xB.pData[i]);
			}
		}

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElementTriplet(const TThis& xA, const TThis& xB, FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i], xA.pData[i], xB.pData[i]);
			}
		}




		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElementIdx(FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i], i);
			}
		}

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachElementIdx(FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				funcOp(pData[i], i);
			}
		}


		template<typename FuncOp>
		__CUDA_HDI__ bool ForEachElementTest(FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				if (!funcOp(pData[i]))
					return false;
			}
			return true;
		}

		template<typename FuncOp>
		__CUDA_HDI__ bool ForEachElementTest(FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				if (!funcOp(pData[i]))
					return false;
			}
			return true;
		}

		template<typename FuncOp>
		__CUDA_HDI__ bool ForEachElementPairTest(const TThis& xArray, FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				if (!funcOp(pData[i], xArray.pData[i]))
					return false;
			}
			return true;
		}

		template<typename FuncOp>
		__CUDA_HDI__ bool ForEachElementPairTest(const TThis& xArray, FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				if (!funcOp(pData[i], xArray.pData[i]))
					return false;
			}
			return true;
		}

		template<typename FuncOp>
		__CUDA_HDI__ bool ForEachElementIdxTest(FuncOp funcOp)
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				if (!funcOp(pData[i], i))
					return false;
			}
			return true;
		}

		template<typename FuncOp>
		__CUDA_HDI__ bool ForEachElementIdxTest(FuncOp funcOp) const
		{
			for (TIdx i = 0; i < ElementCount; ++i)
			{
				if (!funcOp(pData[i], i))
					return false;
			}
			return true;
		}
#pragma endregion

		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////


#pragma region Tests
		__CUDA_HDI__ bool IsZero()
		{
			return ForEachElementTest([](TValue& xValue) -> bool
			{
				return (xValue == TValue(0));
			});
		}

		__CUDA_HDI__ bool operator==(const TThis& xB)
		{
			return ForEachElementPairTest(xB, [](TValue& xValue, const TValue& xValB) -> bool
			{
				return (xValue == xValB);
			});
		}

		__CUDA_HDI__ bool operator!=(const TThis& xA)
		{
			return !(*this == xA);
		}
#pragma endregion


		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////
		// /////////////////////////////////////////////////////////////////////////////////////////


#pragma region Arithmetics
		__CUDA_HDI__ void operator+= (const TThis& xB)
		{
			ForEachElementPair(xB, [](TValue& xValue, const TValue& xValB)
			{
				xValue += xValB;
			});
		}

		__CUDA_HDI__ void operator-= (const TThis& xB)
		{
			ForEachElementPair(xB, [](TValue& xValue, const TValue& xValB)
			{
				xValue -= xValB;
			});
		}

		__CUDA_HDI__ void operator*= (const TThis& xB)
		{
			ForEachElementPair(xB, [](TValue& xValue, const TValue& xValB)
			{
				xValue *= xValB;
			});
		}

		__CUDA_HDI__ void operator/= (const TThis& xB)
		{
			ForEachElementPair(xB, [](TValue& xValue, const TValue& xValB)
			{
				xValue /= xValB;
			});
		}

		__CUDA_HDI__ void operator+= (const TValue& xVal)
		{
			ForEachElement([&xVal](TValue& xValue)
			{
				xValue += xVal;
			});
		}

		__CUDA_HDI__ void operator-= (const TValue& xVal)
		{
			ForEachElement([&xVal](TValue& xValue)
			{
				xValue -= xVal;
			});
		}

		__CUDA_HDI__ void operator*= (const TValue& xVal)
		{
			ForEachElement([&xVal](TValue& xValue)
			{
				xValue *= xVal;
			});
		}

		__CUDA_HDI__ void operator/= (const TValue& xVal)
		{
			ForEachElement([&xVal](TValue& xValue)
			{
				xValue /= xVal;
			});
		}


		__CUDA_HDI__ void CompRecip()
		{
			ForEachElement([](TValue& xValue)
			{
				xValue = TValue(1) / xValue;
			});
		}


		template<typename... TPars>
		__CUDA_HDI__ void LinearCombination_Impl(TValue& dValue, uint32_t iIdx, const TValue& dFactor, const TThis& xArray, TPars&&... xPars)
		{
			dValue += dFactor * xArray.pData[iIdx];
			LinearCombination_Impl(dValue, iIdx, xPars...);
		}

		__CUDA_HDI__ void LinearCombination_Impl(TValue& dValue, uint32_t iIdx)
		{}

		template<typename... TPars>
		__CUDA_HDI__ void LinearCombination(TPars&&... xPars)
		{
			ForEachElementIdx([&](TValue& dValC, uint32_t iIdx)
			{
				dValC = 0;
				LinearCombination_Impl(dValC, iIdx, xPars...);
			});
		}
#pragma endregion
	};



} // namespace Clu
