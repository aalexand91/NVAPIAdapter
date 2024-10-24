// Copyright 2024 Anthony Alexander

using JetBrains.Annotations;
using NSubstitute;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    public class NVAPITester
    {
        [TestInitialize]
        public void InitTest()
        {
            NVAPI.InitializeApi = Substitute.For<NVAPI.InitializeApiFunc>();
        }

        [TestMethod]
        public void Initialize_WhenCalled_InitializesApi()
        {
            // Act
            NVAPI.Initialize();

            // Assert
            NVAPI.InitializeApi.Received().Invoke();
        }
    }
}