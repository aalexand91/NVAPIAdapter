#include "pch.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute(L"NVAPIAdapter")];
[assembly:AssemblyDescriptionAttribute(L"Provides a .NET (framework) API that encapsulates the native NVAPI library.")];

#ifdef _DEBUG
[assembly:AssemblyConfigurationAttribute(L"Debug")];
#else
[assembly::AssemblyConfigurationAttribute(L"Release")];
#endif

[assembly:AssemblyProductAttribute(L"NVAPIAdapter")];
[assembly:AssemblyCopyrightAttribute(L"Copyright (c)  2024")];
[assembly:AssemblyVersionAttribute(L"1.0.*")];

// Allow the internal assemblies to be assessible to the unit tests and mocking framework (Castle.Core).
[assembly:InternalsVisibleToAttribute(L"NVAPIAdapterUnitTest")]
[assembly:InternalsVisibleToAttribute(L"DynamicProxyGenAssembly2")]

[assembly:ComVisible(false)];
