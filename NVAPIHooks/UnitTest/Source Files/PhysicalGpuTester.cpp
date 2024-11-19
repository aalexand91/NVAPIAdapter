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

			TEST_METHOD(GetSystemType_GivenLaptopType_ReturnsLaptop)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType).With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, NV_SYSTEM_TYPE* systemType) -> NvAPI_Status
						{
							*systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_LAPTOP;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Laptop";
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_GivenDesktopType_ReturnsDesktop)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType).With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, NV_SYSTEM_TYPE* systemType) -> NvAPI_Status
						{
							*systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_DESKTOP;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Desktop";
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_GivenUnknownType_ReturnsUnknown)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType).With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, NV_SYSTEM_TYPE* systemType) -> NvAPI_Status
						{
							*systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_UNKNOWN;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Unknown";
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]()-> std::string {return physicalGpu->GetSystemType(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetPciInternalId_OnSuccess_ReturnsInternalId)
			{
				// Arrange
				const unsigned long expected = 11102024ul;
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).With(m_fakeGpuHandle, _, _, _, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long* internalId, unsigned long*,
						unsigned long*, unsigned long*) -> NvAPI_Status
						{
							*internalId = expected;
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetPciInternalId();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetPciInternalId_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetPciInternalId(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetPciExternalId_OnSuccess_ReturnsExternalId)
			{
				// Arrange
				const unsigned long expected = 1959ul;
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).With(m_fakeGpuHandle, _, _, _, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long*, unsigned long*,
						unsigned long*, unsigned long* externalId) -> NvAPI_Status
						{
							*externalId = expected;
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetPciExternalId();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetPciExternalId_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetPciExternalId(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetPciRevisionId_OnSuccess_ReturnsRevisionId)
			{
				// Arrange
				const unsigned long expected = 3022024ul;
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).With(m_fakeGpuHandle, _, _, _, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long*, unsigned long*,
						unsigned long* revisionId, unsigned long*) -> NvAPI_Status
						{
							*revisionId = expected;
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetPciRevisionId();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetPciRevisionId_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetPciRevisionId(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetPciSubsystemId_OnSuccess_ReturnsSubsystemId)
			{
				// Arrange
				const unsigned long expected = 8012019ul;
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).With(m_fakeGpuHandle, _, _, _, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long*, unsigned long* subsystemId,
						unsigned long*, unsigned long*) -> NvAPI_Status
						{
							*subsystemId = expected;
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetPciSubsystemId();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetPciSubsystemId_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetPciSubsystemId(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			// Ideally, we don't test private methods as they get tested through the public ones that use them.
			// This is an exception to that since we can't really pass an unknown type through the public methods.
			TEST_METHOD(GetPciIdentifier_GivenUnknownPciIdType_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_OK);
				const char* expectedMessage = "Unknown PCI identifier type provided.";
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				try
				{
					// Act
					auto identifier = physicalGpu->GetPciIdentifier(PciIdentifierType::UNKNOWN);
				}
				catch (const std::invalid_argument& ex)
				{
					// Assert
					Assert::AreEqual(expectedMessage, ex.what());
					return;
				}
				Assert::Fail(L"Expected exception to be thrown but did not.");
			}

			TEST_METHOD(GetPhysicalFrameBufferSize_OnSuccss_ReturnsSize)
			{
				// Arrange
				const unsigned long expected = 0xABCDEF;
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalFrameBufferSize).With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long* bufferSize) -> NvAPI_Status
						{
							*bufferSize = expected;
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetPhysicalFrameBufferSize();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetPhysicalFrameBufferSize_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalFrameBufferSize).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetPhysicalFrameBufferSize(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetVirtualFrameBufferSize_OnSuccess_ReturnsSize)
			{
				// Arrange
				const unsigned long expected = 0xFEDCBA;
				m_mocks.OnCallFunc(ApiTunnel::GetVirtualFrameBufferSize).With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, unsigned long* bufferSize) -> NvAPI_Status
						{
							*bufferSize = expected;
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetVirtualFrameBufferSize();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetVirtualFrameBufferSize_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetVirtualFrameBufferSize).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> unsigned long { return physicalGpu->GetVirtualFrameBufferSize(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetVbiosVersion_OnSuccess_ReturnsVbiosVersion)
			{
				// Arrange
				const std::string expected = "01.23.45.67.89";
				m_mocks.OnCallFunc(ApiTunnel::GetVbiosVersion).With(m_fakeGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, char* vbiosVersion) -> NvAPI_Status
						{
							sprintf_s(vbiosVersion, sizeof(expected), expected.c_str());
							return NvAPI_Status::NVAPI_OK;
						});
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto actual = physicalGpu->GetVbiosVersion();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetVbiosVersion_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetVbiosVersion).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakeGpuHandle);

				// Act
				auto act = [&]() -> std::string {return physicalGpu->GetVbiosVersion(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			NvPhysicalGpuHandle m_fakeGpuHandle{ (NvPhysicalGpuHandle)1 };
			MockRepository m_mocks;
		};
	}
}