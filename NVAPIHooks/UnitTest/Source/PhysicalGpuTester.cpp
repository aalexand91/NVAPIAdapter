#include "pch.h"

#include <ApiError.h>
#include <ApiTunnel.h>
#include "CppUnitTest.h"
#include <hippomocks.h>
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

			TEST_METHOD(GetName_OnSuccess_ReturnsIt)
			{
				// Arrange
				const std::string expected = "FakeGpuName";
				m_mocks.OnCallFunc(ApiTunnel::GetName).With(m_fakePhysicalGpuHandle, _)
					.Do([&](NvPhysicalGpuHandle, char* buffer) -> NvAPI_Status
						{
							strncpy_s(buffer, 256u, expected.c_str(), 256u);
							return NvAPI_Status::NVAPI_OK;
						});
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const auto actual = gpu->GetName();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetName_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetName).Return(NvAPI_Status::NVAPI_ERROR);
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);
				
				// Act
				auto act = [&]() -> std::string { return gpu->GetName(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetSystemType_GivenLaptopType_ReturnsIt)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType)
					.Do([&](NvPhysicalGpuHandle, NV_SYSTEM_TYPE* systemType) -> NvAPI_Status
						{
							*systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_LAPTOP;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Laptop";
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = gpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_GivenDesktopType_ReturnsIt)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType)
					.Do([&](NvPhysicalGpuHandle, NV_SYSTEM_TYPE* systemType) -> NvAPI_Status
						{
							*systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_DESKTOP;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Desktop";
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = gpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_GivenUnknownType_ReturnsUnknown)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType)
					.Do([&](NvPhysicalGpuHandle, NV_SYSTEM_TYPE* systemType) -> NvAPI_Status
						{
							*systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_UNKNOWN;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Unknown";
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = gpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_WhenDetectingTypeFails_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType).Return(NvAPI_Status::NVAPI_ERROR);
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				auto act = [&]() -> std::string { return gpu->GetSystemType(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetGpuType_GivenIntegratedType_ReturnsIt)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuType)
					.Do([&](NvPhysicalGpuHandle, NV_GPU_TYPE* gpuType) -> NvAPI_Status
						{
							*gpuType = NV_GPU_TYPE::NV_SYSTEM_TYPE_IGPU;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Integrated";
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = gpu->GetGpuType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetGpuType_GivenDiscreteType_ReturnsIt)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuType)
					.Do([&](NvPhysicalGpuHandle, NV_GPU_TYPE* gpuType) -> NvAPI_Status
						{
							*gpuType = NV_GPU_TYPE::NV_SYSTEM_TYPE_DGPU;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Discrete";
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = gpu->GetGpuType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetGpuType_GivenUnknownType_ReturnsUnknown)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuType)
					.Do([&](NvPhysicalGpuHandle, NV_GPU_TYPE* gpuType) -> NvAPI_Status
						{
							*gpuType = NV_GPU_TYPE::NV_SYSTEM_TYPE_GPU_UNKNOWN;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = "Unknown";
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = gpu->GetGpuType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetGpuType_WhenDetectingTypeFails_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuType).Return(NvAPI_Status::NVAPI_ERROR);
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				auto act = [&]() -> std::string { return gpu->GetGpuType(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetPciIdentifiers_GivenIdentifiers_ReturnsThem)
			{
				// Arrange
				const unsigned long expectedDeviceId = 1ul;
				const unsigned long expectedSubSystemId = 2ul;
				const unsigned long expectedRevisionId = 3ul;
				const unsigned long expectedExternalDeviceId = 4ul;
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers)
					.Do([&](NvPhysicalGpuHandle, unsigned long* deviceId, unsigned long* subSystemId,
						unsigned long* revisionId, unsigned long* externalDeviceId) -> NvAPI_Status
						{
							*deviceId = expectedDeviceId;
							*subSystemId = expectedSubSystemId;
							*revisionId = expectedRevisionId;
							*externalDeviceId = expectedExternalDeviceId;
							return NvAPI_Status::NVAPI_OK;
						});
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				auto actualIdentifiers = gpu->GetPciIdentifiers();

				// Assert
				Assert::AreEqual(expectedDeviceId, actualIdentifiers.m_deviceId, L"PCI device IDs are not equal.");
				Assert::AreEqual(expectedSubSystemId, actualIdentifiers.m_subSystemId, L"PCI subsystem IDs are not equal.");
				Assert::AreEqual(expectedRevisionId, actualIdentifiers.m_revisionId, L"PCI revision IDs are not equal.");
				Assert::AreEqual(expectedExternalDeviceId, actualIdentifiers.m_externalDeviceId, L"PCI external device IDs are not equal.");
			}

			TEST_METHOD(GetPciIdentifiers_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_ERROR);
				auto gpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				auto act = [&]() -> PciIdentifiers { return gpu->GetPciIdentifiers(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			NvPhysicalGpuHandle m_fakePhysicalGpuHandle{ 0 };
			MockRepository m_mocks;
		};
	}
}