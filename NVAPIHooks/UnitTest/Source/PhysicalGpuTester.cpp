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
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const auto actual = physicalGpu->GetName();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetName_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetName).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);
				
				// Act
				auto act = [&]() -> std::string { return physicalGpu->GetName(); };

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
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = physicalGpu->GetSystemType();

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
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = physicalGpu->GetSystemType();

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
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = physicalGpu->GetSystemType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetSystemType_WhenDetectingTypeFails_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetSystemType).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				auto act = [&]() -> std::string { return physicalGpu->GetSystemType(); };

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
				auto provider = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = provider->GetGpuType();

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
				auto provider = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = provider->GetGpuType();

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
				auto provider = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				const std::string actual = provider->GetGpuType();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetGpuType_WhenDetectingTypeFails_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetGpuType).Return(NvAPI_Status::NVAPI_ERROR);
				auto provider = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);

				// Act
				auto act = [&]() -> std::string { return provider->GetGpuType(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			NvPhysicalGpuHandle m_fakePhysicalGpuHandle{ 0 };
			MockRepository m_mocks;
		};
	}
}