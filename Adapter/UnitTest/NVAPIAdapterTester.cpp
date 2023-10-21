#include "pch.h"

#include "CppUnitTest.h"
#include "hippomocks.h"
#include <NVAPIAdapter.h>
#include <NVAPIError.h>
#include <NVAPIStatusInterpreter.h>
#include <NVAPITunnel.h>

using namespace Adapter;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdapterUnitTest 
{
	TEST_CLASS(NVAPIAdapterTester) 
	{
	public:
		TEST_METHOD(Initialize_OnSuccess_Returns)
		{
			// Arrange
			MockRepository mocks;
			mocks.ExpectCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);

			// Act & Assert
			adapter->Initialize();
		}

		TEST_METHOD(Initialize_OnFailure_Throws)
		{
			// Arrange
			MockRepository mocks;
			mocks.ExpectCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_LIBRARY_NOT_FOUND);
			const char* fakeStatusMessage = "API library not found.";
			mocks.OnCallFunc(NVAPIStatusInterpreter::GetStatusMessage).Return(fakeStatusMessage);
			const std::string expectedMessage = "Failed to initialize Nvidia API. " + std::string(fakeStatusMessage);
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);

			try
			{
				// Act
				adapter->Initialize();
			}
			catch (const NVAPIError& error)
			{
				// Assert
				Assert::AreEqual(expectedMessage, error.m_message);
				return;
			}
			FailTestForNotThrowing();
		}

		TEST_METHOD(Initialize_WhenCalledTwice_InitializesOnce)
		{
			// Arrange
			const int expectedNumberOfInitializes = 1;
			int actualNumberOfInitializes = 0;
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize)
				.Do([&]() -> NvAPI_Status
					{
						actualNumberOfInitializes++;
						return NvAPI_Status::NVAPI_OK;
					});
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			// Act
			adapter->Initialize();

			// Assert
			Assert::AreEqual(expectedNumberOfInitializes, actualNumberOfInitializes);
		}

		TEST_METHOD(Unload_WhenApiInitialized_UnloadsApi)
		{
			// Arrange
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NVAPI_OK);
			mocks.ExpectCallFunc(NVAPITunnel::Unload).Return(NVAPI_OK);
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			// Act & Assert
			adapter->Unload();
		}

		TEST_METHOD(Unload_WhenApiNotInitialized_DoesNothing)
		{
			// Arrange
			bool apiUnloaded = false;
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Unload).Do([&]() -> NvAPI_Status
				{
					apiUnloaded = true;
					return NvAPI_Status::NVAPI_OK;
				});
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);

			// Act
			adapter->Unload();

			// Assert
			Assert::IsFalse(apiUnloaded, L"Expected API to not unload but did.");
		}

		TEST_METHOD(Unload_WhenCalledAfterApiUnloads_DoesNothing)
		{
			// Arrange
			const int expectedNumberOfUnloads = 2;
			int actualNumberOfUnloads = 0;
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);

			auto& firstUnload = mocks.ExpectCallFunc(NVAPITunnel::Unload).Do([&]() -> NvAPI_Status
				{
					actualNumberOfUnloads++;
					return NvAPI_Status::NVAPI_API_IN_USE;
				});
			auto& secondUnload = mocks.ExpectCallFunc(NVAPITunnel::Unload).Do([&]() -> NvAPI_Status
				{
					actualNumberOfUnloads++;
					return NvAPI_Status::NVAPI_OK;
				}).After(firstUnload);
			mocks.OnCallFunc(NVAPITunnel::Unload).Do([&]() -> NvAPI_Status
				{
					actualNumberOfUnloads++;
					return NvAPI_Status::NVAPI_OK;
				}).After(secondUnload);

			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();
			adapter->Unload();
			adapter->Unload();

			// Act
			adapter->Unload();

			// Assert
			Assert::AreEqual(expectedNumberOfUnloads, actualNumberOfUnloads);
		}

		TEST_METHOD(GetName_OnSuccess_ReturnsIt)
		{
			// Arrange
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			const std::string expected = "Fake Full Name";
			mocks.OnCallFunc(NVAPITunnel::GetFullName).With(m_fakePhysicalHandler, _)
				.Do([&](NvPhysicalGpuHandle, char* name) -> NvAPI_Status
					{
						strcpy_s(name, 15, expected.c_str());
						return NvAPI_Status::NVAPI_OK;
					});
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			// Act
			const std::string actual = adapter->GetName();

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetName_OnFailure_Throws)
		{
			// Arrange
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			mocks.OnCallFunc(NVAPITunnel::GetFullName).Return(NvAPI_Status::NVAPI_ERROR);
			mocks.OnCallFunc(NVAPIStatusInterpreter::GetStatusMessage).Return("Fake Error.");
			const std::string expectedMessage = "Failed to get graphics card name. Fake Error.";
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			try
			{
				// Act
				adapter->GetName();
			}
			catch (const NVAPIError& error)
			{
				// Assert
				Assert::AreEqual(expectedMessage, error.m_message);
				return;
			}
			FailTestForNotThrowing();
		}

		TEST_METHOD(GetName_WhenApiNotInitialized_Throws) 
		{
			// Arrange
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);

			// Act & Assert
			auto act = [&]() -> std::string { return adapter->GetName(); };
			Assert::ExpectException<NVAPIError>(act);
		}

		TEST_METHOD(GetGpuType_OnSuccess_ReturnsIt)
		{
			// Arrange
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			std::unordered_map<NV_GPU_TYPE, std::string> map =
			{
				{NV_GPU_TYPE::NV_SYSTEM_TYPE_DGPU, "Discrete"},
				{NV_GPU_TYPE::NV_SYSTEM_TYPE_IGPU, "Integrated"},
			};
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();
			for (const auto& gpuTypePair : map)
			{
				mocks.OnCallFunc(NVAPITunnel::GetGpuType).With(m_fakePhysicalHandler, _)
					.Do([&](NvPhysicalGpuHandle, NV_GPU_TYPE* gpuType) -> NvAPI_Status
						{
							*gpuType = gpuTypePair.first;
							return NvAPI_Status::NVAPI_OK;
						});
				const std::string expected = gpuTypePair.second;

				// Act
				const std::string actual = adapter->GetGpuType();

				// Assert
				Assert::AreEqual(expected, actual);
			}
		}

		TEST_METHOD(GetGpuType_OnFailure_ReturnsUnknown)
		{
			// Arrange
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			mocks.OnCallFunc(NVAPITunnel::GetGpuType).Return(NvAPI_Status::NVAPI_ERROR);
			const std::string expected = "Unknown";
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			// Act
			const std::string actual = adapter->GetGpuType();

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetGpuType_WhenApiNotInitialized_Throws)
		{
			// Arrange
			auto graphicsCard = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);

			// Act & Assert
			auto act = [&]() -> std::string { return graphicsCard->GetGpuType(); };
			Assert::ExpectException<NVAPIError>(act);
		}

		TEST_METHOD(GetPciIdentifiers_OnSuccess_ReturnsThem)
		{
			// Arrange
			const unsigned long expectedInternalId = 1ul;
			const unsigned long expectedSubsystemId = 2ul;
			const unsigned long expectedRevisionId = 3ul;
			const unsigned long expectedExternalId = 4ul;
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			mocks.OnCallFunc(NVAPITunnel::GetPciIdentifiers).With(m_fakePhysicalHandler, _)
				.Do([&](NvPhysicalGpuHandle, PciIdentifier& pciIdentifier) -> NvAPI_Status
					{
						pciIdentifier.m_internalId = expectedInternalId;
						pciIdentifier.m_subsystemId = expectedSubsystemId;
						pciIdentifier.m_revisionId = expectedRevisionId;
						pciIdentifier.m_externalId = expectedExternalId;
						return NvAPI_Status::NVAPI_OK;
					});
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			// Assert
			const auto actualPciIdentifier = adapter->GetPciIdentifiers();

			// Assert
			Assert::AreEqual(expectedInternalId, actualPciIdentifier.m_internalId);
			Assert::AreEqual(expectedSubsystemId, actualPciIdentifier.m_subsystemId);
			Assert::AreEqual(expectedRevisionId, actualPciIdentifier.m_revisionId);
			Assert::AreEqual(expectedExternalId, actualPciIdentifier.m_externalId);
		}

		TEST_METHOD(GetPciIdentifiers_OnFailure_Throws)
		{
			// Arrange
			MockRepository mocks;
			mocks.OnCallFunc(NVAPITunnel::Initialize).Return(NvAPI_Status::NVAPI_OK);
			mocks.OnCallFunc(NVAPITunnel::GetPciIdentifiers).Return(NvAPI_Status::NVAPI_ERROR);
			mocks.OnCallFunc(NVAPIStatusInterpreter::GetStatusMessage).With(NvAPI_Status::NVAPI_ERROR).Return("Fake Message.");
			const std::string expectedMessage = "Failed to get PCI identifiers. Fake Message.";
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);
			adapter->Initialize();

			try
			{
				// Act
				adapter->GetPciIdentifiers();
			}
			catch (const NVAPIError& error)
			{
				// Assert
				Assert::AreEqual(expectedMessage, error.m_message);
				return;
			}
			FailTestForNotThrowing();
		}

		TEST_METHOD(GetPciIdentifiers_WhenApiNotInitialized_Throws)
		{
			// Arrange
			const std::string expectedMessage = "Fake API not initialized error.";
			MockRepository mocks;
			mocks.OnCallFunc(NVAPIStatusInterpreter::GetStatusMessage).Return(expectedMessage);
			auto adapter = std::make_unique<NVAPIAdapter>(m_fakePhysicalHandler);

			try
			{
				// Act
				adapter->GetPciIdentifiers();
			}
			catch (const NVAPIError& error)
			{
				// Assert
				Assert::AreEqual(expectedMessage, error.m_message);
				return;
			}
			FailTestForNotThrowing();
		}

	private:
		NvPhysicalGpuHandle m_fakePhysicalHandler{ 0 };

		static void FailTestForNotThrowing()
		{
			Assert::Fail(L"Expected exception to be thrown but did not.");
		}
	};
}