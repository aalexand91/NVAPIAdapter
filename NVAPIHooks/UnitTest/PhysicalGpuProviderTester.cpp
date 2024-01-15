#include "pch.h"

#include <ApiError.h>
#include <ApiHooks.h>
#include <CppUnitTest.h>
#include <hippomocks.h>
#include <nvapi.h>
#include <PhysicalGpuProvider.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(PhysicalGpuProviderTester)
		{
		public:
			TEST_METHOD_CLEANUP(InitTest)
			{
				m_mocks.reset();
			}

			TEST_METHOD(Initialize_WhenInitializationSucceeds_Returns)
			{
				// Arrange
				m_mocks.ExpectCallFunc(NVAPIHooks::InitializeApi).Return(NvAPI_Status::NVAPI_OK);
				auto provider = std::make_unique<PhysicalGpuProvider>();

				// Act
				provider->Initialize();

				// Assert
				m_mocks.VerifyAll();
			}

			TEST_METHOD(Initialize_WhenInitializationFails_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(NVAPIHooks::InitializeApi).Return(NvAPI_Status::NVAPI_ACCESS_DENIED);
				auto provider = std::make_unique<PhysicalGpuProvider>();
				auto act = [&] { provider->Initialize(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(Initialize_WhenCalledTwice_InitializesApiOnce)
			{
				// Arrange
				const int expectedNumberOfInitializations = 1;
				int actualNumberOfInitializations = 0;
				m_mocks.OnCallFunc(NVAPIHooks::InitializeApi).Do([&]() -> NvAPI_Status
					{
						actualNumberOfInitializations++;
						return NvAPI_Status::NVAPI_OK;
					});
				auto provider = std::make_unique<PhysicalGpuProvider>();
				provider->Initialize();

				// Act
				provider->Initialize();

				// Assert
				Assert::AreEqual(expectedNumberOfInitializations, actualNumberOfInitializations);
			}

			TEST_METHOD(Unload_WhenUnloadingSucceeds_Returns)
			{
				// Arrange
				RigForApiInitialized();
				m_mocks.ExpectCallFunc(NVAPIHooks::UnloadApi).Return(NvAPI_Status::NVAPI_OK);
				auto provider = std::make_unique<PhysicalGpuProvider>();
				provider->Initialize();

				// Act
				provider->Unload();

				// Assert
				m_mocks.VerifyAll();
			}

			TEST_METHOD(Unload_WhenApiIsNotInitialized_DoesNothing)
			{
				// Arrange
				bool apiUnloaded = false;
				m_mocks.OnCallFunc(NVAPIHooks::UnloadApi).Do([&]() -> NvAPI_Status
					{
						apiUnloaded = true;
						return NvAPI_Status::NVAPI_OK;
					});
				auto provider = std::make_unique<PhysicalGpuProvider>();

				// Act
				provider->Unload();

				// Assert
				Assert::IsFalse(apiUnloaded, L"Expected API to not be unloaded but was.");
			}

			TEST_METHOD(Unload_WhenUnloadingFails_Throws)
			{
				// Arrange
				RigForApiInitialized();
				m_mocks.OnCallFunc(NVAPIHooks::UnloadApi).Return(NvAPI_Status::NVAPI_ERROR);
				auto provider = std::make_unique<PhysicalGpuProvider>();
				provider->Initialize();
				auto act = [&] { provider->Unload(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetNumberOfGpus_WhenApiInitialized_ReturnsNumberOfGpus)
			{
				// Arrange
				RigForApiInitialized();
				const unsigned int expected = 2u;
				m_mocks.OnCallFunc(NVAPIHooks::GetPhysicalGpuHandles)
					.Do([&](std::unique_ptr<NvPhysicalGpuHandle>&, unsigned long* numberOfGpus) -> NvAPI_Status 
						{
							*numberOfGpus = 2ul;
							return NvAPI_Status::NVAPI_OK;
						});
				auto provider = std::make_unique<PhysicalGpuProvider>();
				provider->Initialize();

				// Act
				auto actual = provider->GetNumberOfGpus();

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetNumberOfGpus_WhenDeterminingNumberOfGpusFails_Throws)
			{
				// Arrange
				RigForApiInitialized();
				m_mocks.OnCallFunc(NVAPIHooks::GetPhysicalGpuHandles).Return(NvAPI_Status::NVAPI_ERROR);
				auto provider = std::make_unique<PhysicalGpuProvider>();
				provider->Initialize();
				auto act = [&]() -> unsigned int { return provider->GetNumberOfGpus(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetNumberOfGpus_WhenApiNotInitialized_Throws)
			{
				// Arrange
				auto provider = std::make_unique<PhysicalGpuProvider>();

				try
				{
					// Act
					provider->GetNumberOfGpus();
				}
				catch (const std::runtime_error& error)
				{
					// Assert
					Assert::AreEqual("API is not initialized.", error.what());
					return;
				}
				FailTestForNotThrowing();
			}

		private:
			MockRepository m_mocks;

			static void FailTestForNotThrowing()
			{
				Assert::Fail(L"Expected excpetion to be thrown but did not.");
			}

			void RigForApiInitialized()
			{
				m_mocks.OnCallFunc(NVAPIHooks::InitializeApi).Return(NvAPI_Status::NVAPI_OK);
			}
		};
	}
}