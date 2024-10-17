// Copyright 2024 Anthony Alexander

#include <pch.h>

#include <ApiError.h>
#include <ApiTunnel.h>

namespace NVAPIHooks
{
	std::string ApiError::GetErrorMessage()
	{
		char apiErrorMessage[NVAPI_SHORT_STRING_MAX] = "\0";
		ApiTunnel::GetApiErrorMessage(m_apiStatusCode, apiErrorMessage);
		return std::string(m_context) + " " + std::string(apiErrorMessage);
	}
}