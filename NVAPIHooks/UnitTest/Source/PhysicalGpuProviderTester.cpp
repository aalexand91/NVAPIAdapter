#include "pch.h"

#include <ApiError.h>
#include <ApiTunnel.h>
#include <CppUnitTest.h>
#include <hippomocks.h>
#include <PhysicalGpuProvider.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(PhysicalGpuProviderTester)
		{
		public:
			TEST_METHOD_CLEANUP(CleanUpTest)
			{
				m_mocks.reset();
			}

			TEST_METHOD(GetNumberOfGpus_WhenGpusDetected_ReturnsHowMany)
			{
				// Arrange
				const int expected = 3;
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalGpuHandles)
					.Do([&](NvPhysicalGpuHandle*, unsigned long* numberOfGpus) -> NvAPI_Status
						{
							*numberOfGpus = static_cast<unsigned long>(expected);
							return NvAPI_Status::NVAPI_OK;
						});
				auto provider = std::make_unique<PhysicalGpuProvider>();

				// Act
				const int actual = provider->GetNumberOfGpus();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetNumberOfGpus_WhenCalledTwice_DetectsNumberOfGpusOnce)
			{
				// Arrange
				const int expectedNumberOfDetections = 1;
				int actualNumberOfDetections = 0;
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalGpuHandles)
					.Do([&](NvPhysicalGpuHandle*, unsigned long* gpuCount) -> NvAPI_Status
						{
							actualNumberOfDetections++;
							*gpuCount = 3;
							return NvAPI_Status::NVAPI_OK;
						});
				auto provider = std::make_unique<PhysicalGpuProvider>();

				// Act
				provider->GetNumberOfGpus();

				// Assert
				Assert::AreEqual(expectedNumberOfDetections, actualNumberOfDetections);
			}

			TEST_METHOD(GetNumberOfGpus_WhenDetectingGpusFails_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalGpuHandles).Return(NvAPI_Status::NVAPI_ERROR);
				auto provider = std::make_unique<PhysicalGpuProvider>();
				auto act = [&]() -> int { return provider->GetNumberOfGpus(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetGpuByIndex_GivenValidIndex_ReturnsGpu)
			{
				// Arrange
				NvPhysicalGpuHandle fakeHandle = 0;
				auto fakePhysicalGpu = m_mocks.Mock<IPhysicalGpu>();
				const std::string fakeName = "FakeName";
				m_mocks.OnCall(fakePhysicalGpu, IPhysicalGpu::GetName).Return(fakeName);
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalGpuHandles)
					.Do([&](NvPhysicalGpuHandle* physicalGpuHandles, unsigned long* numberOfGpus) -> NvAPI_Status
						{
							physicalGpuHandles[0] = fakeHandle;
							*numberOfGpus = 1ul;
							return NvAPI_Status::NVAPI_OK;
						});

				std::shared_ptr<IPhysicalGpu> expectedGpu;
				m_mocks.OnCallFunc(PhysicalGpuProvider::RealGetPhysicalGpu).With(fakeHandle)
					.Do([&](NvPhysicalGpuHandle) -> std::shared_ptr<IPhysicalGpu>
						{
							expectedGpu = std::shared_ptr<IPhysicalGpu>(fakePhysicalGpu);
							return expectedGpu;
						});
				m_mocks.OnCallFunc(ApiTunnel::GetName).With(fakeHandle, _)
					.Do([&](NvPhysicalGpuHandle, char* buffer) -> NvAPI_Status
						{
							strncpy_s(buffer, 256u, fakeName.c_str(), 256u);
							return NvAPI_Status::NVAPI_OK;
						});
				
				auto provider = std::make_unique<PhysicalGpuProvider>();

				// Act
				auto& actualGpu = provider->GetGpuByIndex(0);

				// Assert
				Assert::AreEqual(fakePhysicalGpu->GetName(), actualGpu->GetName());
			}

		private:
			MockRepository m_mocks;

			static void FailTestForNotThrowing()
			{
				Assert::Fail(L"Expected exception to be thrown but did not.");
			}
		};
	}
}