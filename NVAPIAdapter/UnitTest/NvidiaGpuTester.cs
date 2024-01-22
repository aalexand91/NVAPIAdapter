using Microsoft.VisualStudio.TestTools.UnitTesting;
using NVAPIAdapter;
using NSubstitute;

namespace NVAPIAdapterUnitTest
{
    [TestClass]
    public class NvidiaGpuTester
    {
        readonly IPhysicalGpu myFakePhysicalGpu = Substitute.For<IPhysicalGpu>();

        INvidiaGpu CreateNvidiaGpu() => new NvidiaGpu(myFakePhysicalGpu);

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