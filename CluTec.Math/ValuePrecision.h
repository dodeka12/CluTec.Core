////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      ValuePrecision.h
//
// summary:   Declares the value precision class
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

#include <stdlib.h>
#include "CluTec.Base/Defines.h"

namespace Clu
{
	template<typename TValue>
	class CValuePrecision
	{
	public:

		__CUDA_HDI__ CValuePrecision() { }
		__CUDA_HDI__ ~CValuePrecision() { }

		CValuePrecision(const TValue& dPrec)
		{
			m_dPrec = dPrec;
		}

		CValuePrecision(const CValuePrecision<TValue>& xValPrec)
		{
			*this = xValPrec;
		}

		__CUDA_HDI__ static TValue DefaultPrecision();

		__CUDA_HDI__ void Reset()
		{
			m_dPrec = DefaultPrecision();	//std::numeric_limits<TValue>::epsilon();
		}

		__CUDA_HDI__ CValuePrecision<TValue>& operator=(const CValuePrecision<TValue>& xValPrec)
		{
			m_dPrec = xValPrec.m_dPrec;
			return *this;
		}

		__CUDA_HDI__ void SetValuePrecision(const TValue& dPrec)
		{
			m_dPrec = dPrec;
		}

		__CUDA_HDI__ TValue GetValuePrecision() const
		{
			return m_dPrec;
		}

		__CUDA_HDI__ bool IsZero(const TValue& dA) const
		{
			return dA >= -m_dPrec && dA <= m_dPrec;
		}

		__CUDA_HDI__ bool IsEqual(const TValue& dA, const TValue& dB) const
		{
			return ::abs(dA - dB) <= m_dPrec;
		}

		__CUDA_HDI__ bool IsUnity(const TValue& dA) const
		{
			return IsEqual(dA, TValue(1));
		}

		__CUDA_HDI__ int Compare(const TValue& dA, const TValue& dB) const
		{
			TValue dDiff = dA - dB;
			if (dDiff < -m_dPrec)
			{
				return -1;
			}
			else if (dDiff > m_dPrec)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

	protected:

		TValue m_dPrec;
	};
}


// Include the implementation of some template specializations only if a CUDA file is compiled.
#if defined(__CUDACC__)
#include "ValuePrecision_Impl.h"
#endif