#include "pch.h"

#include "ApiError.h"
#include "ApiTunnel.h"
#include "GeneralApi.h"

namespace NVAPIHooks
{
	namespace GeneralApi
	{
		void Initialize()
		{
			auto status = ApiTunnel::InitializeApi();
			if (status == NvAPI_Status::NVAPI_OK) return;
			throw ApiError("Failed to initialize NVAPI library.", status);
		}

		void Unload()
		{
			auto status = ApiTunnel::UnloadApi();
			if (status == NvAPI_Status::NVAPI_OK) return;
			throw ApiError("Failed to unload NVAPI library.", status);
		}
	}
}