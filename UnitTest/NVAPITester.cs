// Copyright (c) 2024 Anthony Alexander

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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