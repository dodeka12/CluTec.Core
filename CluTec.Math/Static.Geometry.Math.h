////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Geometry.Math.h
//
// summary:   Declares the static. geometry. mathematics class
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
#include <vector>
#include "Static.Geometry.h"

namespace Clu
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Tries to determine the intersection point of a 3D line with a 3D plane.
	/// Return false if the line is parallel to the plane.
	/// </summary>
	///
	/// <param name="vfIntersectionPoint">	[out] The intersection point. </param>
	/// <param name="xPlane">			  	The plane. </param>
	/// <param name="xLine">			  	The line. </param>
	///
	/// <returns>	Scale of direction for intersection. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename TValue>
	__CUDA_HDI__ bool TryIntersect(_SVector<TValue, 3>& vfIntersectionPoint, const SPlane3D<TValue>& xPlane, const SLine3D<TValue>& xLine, TValue fPrec)
	{
		const TValue fFactor = Clu::Dot(xLine.vDir, xPlane.vNormal);
		if (abs(fFactor) <= fPrec)
		{
			return false;
		}

		const TValue fDirScale = (xPlane.tDistance - Clu::Dot(xLine.vOrigin, xPlane.vNormal)) / fFactor;
		vfIntersectionPoint = xLine.vOrigin + fDirScale * xLine.vDir;

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Attempts to intersect two 3D lines. Returns the point closes to both lines if they do not
	/// intersect.
	/// </summary>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="vfIntersectionPoint">	[in,out] The vf intersection point. </param>
	/// <param name="xLineA">			  	The line a. </param>
	/// <param name="xLineB">			  	The line b. </param>
	/// <param name="fPrec">			  	The prec. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue>
	__CUDA_HDI__ bool TryIntersect(_SVector<TValue, 3>& vfIntersectionPoint, const SLine3D<TValue>& xLineA, const SLine3D<TValue>& xLineB, TValue fPrec)
	{
		SPlane3D<TValue> xPlane;
		_SVector<TValue, 3> vN, vM;
		_SVector<TValue, 3> vA, vB;

		vN = xLineA.vDir ^ xLineB.vDir;
		TValue fN = Length(vN);

		if (fN <= fPrec)
		{
			return false;
		}
		
		vN /= fN;

		vM = Normalize(vN ^ xLineA.vDir);
		xPlane.Create(xLineA.vOrigin, vM);

		if (!TryIntersect(vA, xPlane, xLineB, fPrec))
		{
			return false;
		}

		vM = Normalize(vN ^ xLineB.vDir);
		xPlane.Create(xLineB.vOrigin, vM);

		if (!TryIntersect(vB, xPlane, xLineA, fPrec))
		{
			return false;
		}

		vfIntersectionPoint = vA + (vB - vA) / TValue(2);

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Attempts to intersect a line with a line segment. Returns false if both lines are parallel.
	/// </summary>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="vX">	   	[in,out] The v x coordinate. </param>
	/// <param name="xLineSeg">	The line segment. </param>
	/// <param name="xLine">   	The line. </param>
	/// <param name="fPrec">   	The prec. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue>
	__CUDA_HDI__ bool TryIntersect(_SVector<TValue, 2>& vX, const _SLine2D<TValue>& xLineA, const _SLine2D<TValue>& xLineB, TValue fPrec)
	{
		using TVec2 = typename _SLine2D<TValue>::TVec2;

		TVec2 vNormal;
		
		// Normal to line segment
		vNormal.SetElements(-xLineA.Dir()[1], xLineA.Dir()[0]);

		TValue dA = Dot(xLineB.Dir(), vNormal);

		if (abs(dA) <= fPrec)
		{
			// No intersection. The two lines are parallel
			return false;
		}

		// The intersection point
		vX = xLineB.Origin() + Dot(xLineA.Origin() - xLineB.Origin(), vNormal) / dA * xLineB.Dir();
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Intersects a line with a quadrilateral. Returns only those intersection of the line
	/// 			that lie on the (finite) edges of the quadrilateral.</summary>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="xQuad">	The quad. </param>
	/// <param name="xLine">	The line. </param>
	/// <param name="fPrec">	The prec. </param>
	///
	/// <returns>	A std::vector&lt;_SVector&lt;TValue,2&gt;&gt; </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue>
	std::vector<_SVector<TValue, 2>> Intersect(const _SQuad2D<TValue>& xQuad, const _SLine2D<TValue>& xLine, TValue fPrec)
	{
		using TQuad2D = _SQuad2D<TValue>;
		using TLineSeg2D = typename TQuad2D::TLineSeg2D;
		using TVec2 = typename TQuad2D::TVec2;

		using TIdx = typename _SQuad2D<TValue>::TIdx;

		std::vector<_SVector<TValue, 2>> vecX;

		// Loop over all quad edges
		xQuad.ForEachEdgeIdx([&](const TLineSeg2D& xLineSeg, TIdx uIdx)
		{
			TVec2 vX;
			// Try to intersect the given line with the current edge
			if (TryIntersect(vX, xLineSeg, xLine, fPrec))
			{
				// If an intersection could be calculated,
				// test whether the intersection point is on the edge.
				if (xLineSeg.IsInside(vX, fPrec))
				{
					// vX is a valid intersection, so store it.
					vecX.push_back(vX);
				}
			}
		});

		return vecX;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Attempts to find the largest rectangle aligned with the canonical 2D coordinate frame of the
	/// given aspect ratio inside a quadrilateral that is centered on a given line.
	/// </summary>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="xRect">   	[in,out] The rectangle. </param>
	/// <param name="xQuad">   	The quad. </param>
	/// <param name="xCtrLine">	The line. </param>
	/// <param name="dAspect"> 	The aspect ratio of the rectangle. </param>
	/// <param name="dPrec">   	The precision. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue>
	bool TryFindLargestRectangleInsideQuadOnLine(_SAlignedRect2D<TValue>& xRect, const _SQuad2D<TValue>& xQuad, const _SLine2D<TValue>& xCtrLine, TValue dAspect, TValue dPrec)
	{
		using TQuad2D = _SQuad2D<TValue>;
		using TLineSeg2D = typename TQuad2D::TLineSeg2D;
		using TLine2D = _SLine2D<TValue>;

		using TVec2 = typename TQuad2D::TVec2;

		using TIdx = typename _SQuad2D<TValue>::TIdx;

		std::vector<TVec2> vecX;
		std::vector<TValue> vecLength;

		// Find intersections of given center line with Quad
		vecX = Intersect(xQuad, xCtrLine, dPrec);

		// If the center line does not have 2 intersections we cannot do anything.
		if (vecX.size() != 2)
		{
			return false;
		}

		// Set center point for rectangle.
		TVec2 vCtr = vecX[0] + (vecX[1] - vecX[0]) / TValue(2);

		// Create a diagonal direction of the target rectangle
		TVec2 vDiag;
		vDiag.SetElements(1, dAspect);
		vDiag = Normalize(vDiag);

		// Create the diagonal line passing through the center point
		TLine2D xDiagLine;
		xDiagLine.Create(vCtr, vDiag);

		// Now intersect the quad with this line
		vecX = Intersect(xQuad, xDiagLine, dPrec);

		// If we do not get two intersections on the edges of the quad, something went horribly wrong.
		if (vecX.size() != 2)
		{
			return false;
		}

		// Calculate length from center point to intersection points.
		for (TVec2 vX : vecX)
		{
			vecLength.push_back(Distance(vX, vCtr));
		}

		// Now perform the same calculations for the other diagonal
		vDiag[0] = -vDiag[0];
		xDiagLine.Create(vCtr, vDiag);

		vecX = Intersect(xQuad, xDiagLine, dPrec);

		// If we do not get two intersections on the edges of the quad, something went horribly wrong.
		if (vecX.size() != 2)
		{
			return false;
		}

		// Calculate length from center point to intersection points.
		for (TVec2 vX : vecX)
		{
			vecLength.push_back(Distance(vX, vCtr));
		}

		// Now vecLength contains the distances from the center to the 4 intersection points
		// of the two rectangle diagonals with the quad edges. The minimum length gives the 
		// maximal scale of a rectangle of given aspect ration that fits in the the quad.
		TValue dMin = vecLength[0];
		for (TValue dValue : vecLength)
		{
			dMin = (dValue < dMin ? dValue : dMin);
		}

		// Calculate the two corners of the rectangle along the diagonal.
		TVec2 vA, vB;
		vA = vCtr + dMin * vDiag;
		vB = vCtr - dMin * vDiag;

		// And finally create the rectangle.
		xRect.Create(vA, vB);

		return true;
	}
}
