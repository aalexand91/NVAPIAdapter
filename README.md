## NVAPIAdapter
Inspired by the complexity of the [NVAPI](https://developer.nvidia.com/rtx/path-tracing/nvapi/get-started) library and lack of open-source projects to simplify the integration of this library for .NET applications, NVAPIAdapter provides an easy to use .NET library to interface with NVIDIA GPUs, starting with just **2** lines of code!
``` csharp
using NVAPIAdapter;

namespace MyLibrary
{
    NVAPI.Initialize();
    var gpus = NVAPI.GetAllGpus();
    foreach (INvidiaGpu gpu in gpus)
    {
        Console.WriteLine("GPU name: " + gpu.Name);
    }
}
```

Query GPUs of interest via LINQ:
```csharp
NVAPI.Initialize();
var myGpu = NVAPI.GetAllGpus()
  .Where(gpu => gpu.CoreCount > 3000)
  .FirstOrDefault(gpu => gpu.Name.Contains("GeForce"));
```