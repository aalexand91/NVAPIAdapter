using Microsoft.VisualStudio.TestTools.UnitTesting;
using NSubstitute;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    public class NvidiaGpuTester
    {
        readonly IPhysicalGpuAdapter myFakePhysicalGpu = Substitute.For<IPhysicalGpuAdapter>();

        INvidiaGpu CreateNvidiaGpu() => new NvidiaGpu(myFakePhysicalGpu);

        [TestMethod]
        public void CreateInstance_GivenPhysicalGpu_ReturnsExpectedType()
        {
            // Act
            var instance = NvidiaGpu.CreateInstance(myFakePhysicalGpu);

            // Assert
            Assert.IsInstanceOfType(instance, typeof(INvidiaGpu));
        }

        [TestMethod]
        public void GetName_WhenCalled_ReturnsIt()
        {
            // Arrange
            const string expected = "FakeGpuName";
            myFakePhysicalGpu.GetName().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetName();

            // Assert
            Assert.AreEqual(expected, actual);
        }
    }
}