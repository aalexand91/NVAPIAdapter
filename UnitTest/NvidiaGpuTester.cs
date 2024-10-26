// Copyright 2024 Anthony Alexander

using JetBrains.Annotations;
using NSubstitute;
using System;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    public class NvidiaGpuTester
    {
        [NotNull] readonly IPhysicalGpuAdapter myFakePhysicalGpu = Substitute.For<IPhysicalGpuAdapter>();

        [NotNull] INvidiaGpu CreateNvidiaGpu() => NvidiaGpu.CreateInstance(myFakePhysicalGpu);

        [TestMethod]
        public void CoreCount_GivenCoreCount_ReturnsIt()
        {
            // Arrange
            const uint expected = 32;
            myFakePhysicalGpu.GetCoreCount().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.CoreCount;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void Name_GivenName_ReturnsIt()
        {
            // Arrange
            const string expected = "FakeName";
            myFakePhysicalGpu.GetFullName().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.Name;

            // Assert
            Assert.AreEqual(expected, actual);
        }
    }
}
