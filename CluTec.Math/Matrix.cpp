////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Matrix.cpp
//
// summary:   Implements the matrix class
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

#include <cstdint>

#include "Matrix.h"
#include "Matrix.Algo.SVD.h"
#include "Matrix.Algo.GE.h"

#ifdef _DEBUG
// ///////////////////////////////////////////////////////////////////
// Compile matrix class and matrix algos for specific types
// to find compile errors.
using namespace Clu;

template class CMatrix<float>;
template class CMatrix<double>;

template class CMatrix<int32_t>;
template class CMatrix<int64_t>;

// Compile matrix algos
 
template Clu::CMatrixAlgoSVD<double>;
template Clu::CMatrixAlgoGE<double>;
template Clu::CMatrixAlgoGE<int32_t>;
template Clu::CMatrixAlgoGE<int64_t>;
// ///////////////////////////////////////////////////////////////////
#endif
