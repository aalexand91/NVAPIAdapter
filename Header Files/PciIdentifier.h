// Copyright (c) 2024 Anthony Alexander

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

namespace NVAPIAdapter
{
	public interface class IPciIdentifier
	{
		property System::UInt32 InternalId
		{
			System::UInt32 get();
		}

		property System::UInt32 ExternalId
		{
			System::UInt32 get();
		}

		property System::UInt32 RevisionId
		{
			System::UInt32 get();
		}

		property System::UInt32 SubsystemId
		{
			System::UInt32 get();
		}
	};

	ref class PciIdentifier : IPciIdentifier
	{
	public:
		PciIdentifier(const System::UInt32 internalId, const System::UInt32 externalId,
			const System::UInt32 revisionId, const System::UInt32 subsystemId)
		{
			m_internalId = internalId;
			m_externalId = externalId;
			m_revisionId = revisionId;
			m_subsystemId = subsystemId;
		}

		virtual property System::UInt32 InternalId
		{
			System::UInt32 get() { return m_internalId; };
		}

		virtual property System::UInt32 ExternalId
		{
			System::UInt32 get() { return m_externalId; };
		}

		virtual property System::UInt32 RevisionId
		{
			System::UInt32 get() { return m_revisionId; };
		}

		virtual property System::UInt32 SubsystemId
		{
			System::UInt32 get() { return m_subsystemId; };
		}

	private:
		System::UInt32 m_internalId{ 0ul };
		System::UInt32 m_externalId{ 0ul };
		System::UInt32 m_revisionId{ 0ul };
		System::UInt32 m_subsystemId{ 0ul };
	};
}
