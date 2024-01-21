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
			TEST_METHOD(GetName_OnSuccess_ReturnsIt)
			{
				// Arrange
				const std::string expected = "FakeGpuName";
				MockRepository mocks;
				mocks.OnCallFunc(ApiTunnel::GetName).With(m_fakePhysicalGpuHandle, _)
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
				MockRepository mocks;
				mocks.OnCallFunc(ApiTunnel::GetName).Return(NvAPI_Status::NVAPI_ERROR);
				auto physicalGpu = std::make_unique<PhysicalGpu>(m_fakePhysicalGpuHandle);
				auto act = [&]() -> std::string { return physicalGpu->GetName(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			NvPhysicalGpuHandle m_fakePhysicalGpuHandle{ 0 };
		};
	}
}