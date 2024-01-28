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
        public void GetSystemType_GivenKnownType_ReturnsIt(GpuSystemType expected)
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
        public void GetSystemType_GivenUnknownType_ReturnsUnknown()
        {
            // Arrange
            myFakePhysicalGpu.GetSystemType().Returns("FakeSystemType");
            var gpu = CreateNvidiaGpu();

            // Act
            var result = gpu.GetSystemType();

            // Assert
            Assert.AreEqual(GpuSystemType.Unknown, result);
        }

        [DataTestMethod]
        [DataRow(GpuType.Integrated)]
        [DataRow(GpuType.Discrete)]
        public void GetGpuType_GivenKnownType_ReturnsIt(GpuType expected)
        {
            // Arrange
            myFakePhysicalGpu.GetGpuType().Returns(expected.ToString());
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetGpuType();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetGpuType_GivenUnknownType_ReturnsUnknown()
        {
            // Arrange
            myFakePhysicalGpu.GetGpuType().Returns("FakeGpuType");
            var gpu = CreateNvidiaGpu();

            // Act
            var result = gpu.GetGpuType();

            // Assert
            Assert.AreEqual(GpuType.Unknown, result);
        }
    }
}