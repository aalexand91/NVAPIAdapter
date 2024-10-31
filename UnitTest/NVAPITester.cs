// Copyright 2024 Anthony Alexander

using JetBrains.Annotations;
using NSubstitute;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    [DoNotParallelize]
    public class NVAPITester
    {
        [NotNull] readonly NVAPI.CreateNvidiaGpuFunc myFakeCreateNvidiaGpu = Substitute.For<NVAPI.CreateNvidiaGpuFunc>();
        [NotNull] readonly NVAPI.GetAllPhysicalGpusFunc myFakeGetAllPhysicalGpus = Substitute.For<NVAPI.GetAllPhysicalGpusFunc>();
        [NotNull] readonly NVAPI.InitializeApiFunc myInitializeApiSpy = Substitute.For<NVAPI.InitializeApiFunc>();
        [NotNull] readonly NVAPI.UnloadApiFunc myUnloadApiSpy = Substitute.For<NVAPI.UnloadApiFunc>();

        [TestInitialize]
        public void InitTest()
        {
            NVAPI.CreateNvidiaGpu = myFakeCreateNvidiaGpu;
            NVAPI.GetAllPhysicalGpus = myFakeGetAllPhysicalGpus;
            NVAPI.InitializeApi = myInitializeApiSpy;
            NVAPI.UnloadApi = myUnloadApiSpy;
        }

        [TestMethod]
        public void Initialize_WhenCalled_InitializesApi()
        {
            // Act
            NVAPI.Initialize();

            // Assert
            myInitializeApiSpy.Received().Invoke();
        }

        [TestMethod]
        public void Unload_WhenCalled_UnloadsApi()
        {
            // Act
            NVAPI.Unload();

            // Assert
            myUnloadApiSpy.Received().Invoke();
        }

        [TestMethod]
        public void GetAllGpus_GivenGpus_ReturnsThem()
        {
            // Arrange
            var gpuAdapterA = Substitute.For<IPhysicalGpuAdapter>();
            var gpuAdapterB = Substitute.For<IPhysicalGpuAdapter>();
            myFakeGetAllPhysicalGpus.Invoke().Returns([gpuAdapterA, gpuAdapterB]);

            var gpuA = Substitute.For<INvidiaGpu>();
            myFakeCreateNvidiaGpu.Invoke(gpuAdapterA).Returns(gpuA);
            var gpuB = Substitute.For<INvidiaGpu>();
            myFakeCreateNvidiaGpu.Invoke(gpuAdapterB).Returns(gpuB);

            // Act
            var gpus = NVAPI.GetAllGpus().ToList();

            // Assert
            CollectionAssert.Contains(gpus, gpuA);
            CollectionAssert.Contains(gpus, gpuB);
        }
    }
}