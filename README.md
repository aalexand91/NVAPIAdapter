# NVAPIAdapter
Provides a simple and easy to use .NET (Framework) API to interact with Nvidia GPUs using the [NVAPI](https://developer.nvidia.com/rtx/path-tracing/nvapi/get-started#documentation) library.

## Getting Started
Getting an interface to the GPU is as simple as writing 3 lines of code!
``` csharp
var gpuProvider = NvidiaGpuProvider.CreateInstance();
gpuProvider.Initialize();
var gpu = gpuProvider.GetGpuByName("Quadro FX 1400");
```

Need to determine all GPUs in the system? No problem! Simply invoke the `NvidiaGpuProvider` to provide all GPUs:
``` csharp
var gpuProvider = NvidiaGpuProvider.CreateInstance();
gpuProvider.Initialize();
var allGpus = gpuProvider.GetAllGpus();
```

[Linq](https://learn.microsoft.com/en-us/dotnet/csharp/linq/) expressions can also be used to filter for specific GPUs or GPU information:
``` csharp
var gpuProvider = NvidiaGpuProvider.CreateInstance();
gpuProvider.Initialize();
var discreteGpusNames = gpuProvider.GetAllGpus()
                          .Where(gpu => gpu.GpuType == GpuType.Discrete)
                          .Select(gpu => gpu.GetName());
```
