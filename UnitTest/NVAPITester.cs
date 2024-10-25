// Copyright 2024 Anthony Alexander

using JetBrains.Annotations;
using NSubstitute;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    [DoNotParallelize]
    public class NVAPITester
    {
        [NotNull] readonly NVAPI.InitializeApiFunc myInitializeApiSpy = Substitute.For<NVAPI.InitializeApiFunc>();
        [NotNull] readonly NVAPI.UnloadApiFunc myUnloadApiSpy = Substitute.For<NVAPI.UnloadApiFunc>();

        [TestInitialize]
        public void InitTest()
        {
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
    }
}