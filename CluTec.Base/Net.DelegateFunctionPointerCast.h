////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      Net.DelegateFunctionPointerCast.h
//
// summary:   Declares the net. delegate function pointer cast class
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

#pragma managed(push, on)

namespace Clu
{
	namespace Net
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gives access to the function pointer of a delegate and stores an instance
		/// 			of the delegate to avoid it being deleted by the GC. </summary>
		///
		/// <remarks>	Perwass,. </remarks>
		///
		/// <typeparam name="TNativeFunc">	Type of the native function. </typeparam>
		/// <typeparam name="TDelegate">  	Type of the delegate. </typeparam>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TNativeFunc, typename TDelegate>
		public ref class DelegateFunctionPointerCast : public System::Object
		{
		public:

			DelegateFunctionPointerCast()
			{
				Delegate = nullptr;
				m_pFunction = 0;
			}

			DelegateFunctionPointerCast(TDelegate^ xDelegate)
			{
				Delegate = xDelegate;
			}

			~DelegateFunctionPointerCast()
			{
				this->!DelegateFunctionPointerCast();
			}

			!DelegateFunctionPointerCast()
			{
				if (m_hDelegate.IsAllocated)
				{
					m_hDelegate.Free();
				}
			}

			property TDelegate^ Delegate
			{
				TDelegate^ get()
				{
					return m_xDelegate;
				}

				void set(TDelegate^ value)
				{
					if (m_hDelegate.IsAllocated)
					{
						m_hDelegate.Free();
					}

					m_xDelegate = value;

					// Create a handle to the delegate, so that the delegate is not deleted by the GC
					m_hDelegate = System::Runtime::InteropServices::GCHandle::Alloc(m_xDelegate);

					// Get the function pointer for the delegate
					m_pFunction = static_cast<TNativeFunc>(System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_xDelegate).ToPointer());
				}
			}

			property TNativeFunc Pointer
			{
				TNativeFunc get()
				{
					return m_pFunction;
				}
			}

		private:

			System::Runtime::InteropServices::GCHandle m_hDelegate;

			TDelegate^ m_xDelegate;
			TNativeFunc m_pFunction;
		};
	}
}

#pragma managed(pop)
