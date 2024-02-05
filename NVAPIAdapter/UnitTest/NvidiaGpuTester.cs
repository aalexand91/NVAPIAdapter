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

        [TestMethod]
        public void GetPciIdentifiers_WhenCalled_ReturnsThem()
        {
            // Arrange
            var expectedIdentifiers = new PciIdentifier
            {
                DeviceId = 1,
                SubsystemId = 2,
                RevisionId = 3,
                ExternalDeviceId = 4,
            };
            myFakePhysicalGpu.GetPciIdentifiers().Returns(expectedIdentifiers);
            var gpu = CreateNvidiaGpu();

            // Act
            var actualIdentifiers = gpu.GetPciIdentifiers();

            // Assert
            Assert.AreEqual(expectedIdentifiers.DeviceId, actualIdentifiers.DeviceId);
            Assert.AreEqual(expectedIdentifiers.SubsystemId, actualIdentifiers.SubsystemId);
            Assert.AreEqual(expectedIdentifiers.RevisionId, actualIdentifiers.RevisionId);
            Assert.AreEqual(expectedIdentifiers.ExternalDeviceId, actualIdentifiers.ExternalDeviceId);
        }

        [TestMethod]
        public void GetBusId_GivenBusId_ReturnsIt()
        {
            // Arrange
            const uint expected = 0xDEADBEEF;
            myFakePhysicalGpu.GetBusId().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetBusId();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetVideoBiosVersion_GivenVideoBiosVersion_ReturnsIt()
        {
            // Arrange
            const string expected = "AA.BB.CC.DD.EE";
            myFakePhysicalGpu.GetVideoBiosVersion().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetVideoBiosVersion();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetPhysicalFrameBufferSizeInKb_GivenSize_ReturnsIt()
        {
            // Arrange
            const uint expected = 12345u;
            myFakePhysicalGpu.GetPhysicalFrameBufferSizeInKb().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetPhysicalFrameBufferSizeInKb();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetVirtualFrameBufferSizeInKb_GivenSize_ReturnsIt()
        {
            // Arrange
            const uint expected = 67890u;
            myFakePhysicalGpu.GetVirtualFrameBufferSizeInKb().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetVirtualFrameBufferSizeInKb();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetCoreCount_GivenCount_ReturnsIt()
        {
            // Arrange
            const uint expected = 12u;
            myFakePhysicalGpu.GetGpuCoreCount().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetCoreCount();

            // Assert
            Assert.AreEqual(expected, actual);
        }
    }
}