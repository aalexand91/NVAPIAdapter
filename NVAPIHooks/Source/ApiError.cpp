#include "pch.h"

#include "ApiError.h"
#include "StatusInterpreter.h"

namespace NVAPIHooks
{
	const char* ApiError::what() const noexcept
	{
		static const auto message = m_message + std::string(" ") + StatusInterpreter::GetErrorMessage(m_apiStatus);
		return message.c_str();
	}
}