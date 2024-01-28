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

        [DataTestMethod]
        [DataRow(GpuSystemType.Laptop)]
        [DataRow(GpuSystemType.Desktop)]
        public void GetSystemType_GivenValidSystemType_ReturnsIt(GpuSystemType expected)
        {
            // Arrange
            myFakePhysicalGpu.GetSystemType().Returns(expected.ToString());
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetSystemType();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetSystemType_GivenUnknownSystemType_ReturnsUnknown()
        {
            // Arrange
            myFakePhysicalGpu.GetSystemType().Returns("FakeSystemType");
            var gpu = CreateNvidiaGpu();

            // Act
            var result = gpu.GetSystemType();

            // Assert
            Assert.AreEqual(GpuSystemType.Unknown, result);
        }
    }
}