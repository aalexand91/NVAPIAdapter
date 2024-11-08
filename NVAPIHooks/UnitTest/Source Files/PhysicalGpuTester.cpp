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

#include <pch_UnitTest.h>

#include <ApiError.h>
#include <ApiTunnel.h>
#include <PhysicalGpu.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(PhysicalGpuTester)
		{
		public:
			TEST_METHOD_CLEANUP(CleanUpTest)
			{
				m_mocks.reset();
			}

			TEST_METHOD(GetCoreCount_WhenCalled_ReturnsIt)
			{
				// Arrange
				const auto expected = 12ul;
				m_mocks.OnCallFunc(ApiTunnel::GetGpuCoreCount)
					.With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long* coreCount) -> NvAPI_Status
						{
							*coreCount = expected;
							return NvAPI_Status::NVAPI_OK;
						});

				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				const auto actual = physicalGpu->GetCoreCount();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetCoreCount_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuCoreCount).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetCoreCount(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetFullName_OnSuccess_ReturnsName)
			{
				// Arrange
				const std::string expected = "FakeGpu";
				m_mocks.OnCallFunc(ApiTunnel::GetFullName)
					.With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, char* name) -> NvAPI_Status
						{
							sprintf_s(name, sizeof(expected), expected.c_str());
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetFullName();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetFullName_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetFullName).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> std::string { return physicalGpu->GetFullName(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetBusType_OnSuccess_ReturnsBusType)
			{
				// Arrange
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);
				for (const auto& [busTypeValue, busTypeString] : physicalGpu->m_busTypeMap)
				{
					m_mocks.OnCallFunc(ApiTunnel::GetBusType).With(m_fakeGpuHandle, _)
						.Do([&](NvPhysicalGpuHandle, NV_GPU_BUS_TYPE* busType) -> NvAPI_Status
							{
								*busType = busTypeValue;
								return NvAPI_Status::NVAPI_OK;
							});
					const std::string expected = busTypeString;

					// Act
					auto actual = physicalGpu->GetBusType();

					// Assert
					Assert::AreEqual(expected, actual);
				}
			}

			TEST_METHOD(GetBusType_OnApiTunnelFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetBusType).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> std::string { return physicalGpu->GetBusType(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetBusType_GivenUnknownBusType_ReturnsUnknown)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetBusType).Return(NvAPI_Status::NVAPI_OK);
				const std::string expected = "Unknown";
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetBusType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

		private:
			NvPhysicalGpuHandle m_fakeGpuHandle{ (NvPhysicalGpuHandle)1 };
			MockRepository m_mocks;
		};
	}
}