﻿// Copyright (c) 2024 Anthony Alexander

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

        [TestMethod]
        public void BusType_GivenBusType_ReturnsIt()
        {
            // Arrange
            const string expected = "FakeBusType";
            myFakePhysicalGpu.GetBusType().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.BusType;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void SystemType_GivenSystemType_ReturnsIt()
        {
            // Arrange
            const string expected = "FakeSystemType";
            myFakePhysicalGpu.GetSystemType().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.SystemType;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetPciIdentifier_GivenIdentifier_ReturnsEachId()
        {
            // Arrange
            const uint expectedInternalId = 11102024;
            myFakePhysicalGpu.GetPciInternalId().Returns(expectedInternalId);

            const uint expectedExternalId = 6212016;
            myFakePhysicalGpu.GetPciExternalId().Returns(expectedExternalId);

            const uint expectedRevisionId = 12202016;
            myFakePhysicalGpu.GetPciRevisionId().Returns(expectedRevisionId);

            const uint expectedSubsystemId = 2282020;
            myFakePhysicalGpu.GetPciSubsystemId().Returns(expectedSubsystemId);

            var gpu = CreateNvidiaGpu();

            // Act
            var pciIdentifier = gpu.GetPciIdentifier();

            // Assert
            Assert.AreEqual(expectedInternalId, pciIdentifier.InternalId);
            Assert.AreEqual(expectedExternalId, pciIdentifier.ExternalId);
            Assert.AreEqual(expectedRevisionId, pciIdentifier.RevisionId);
            Assert.AreEqual(expectedSubsystemId, pciIdentifier.SubsystemId);
        }

        [TestMethod]
        public void PhysicalFrameBufferSizeInKb_GivenSize_ReturnsIt()
        {
            // Arrange
            const uint expected = 11162024;
            myFakePhysicalGpu.GetPhysicalFrameBufferSizeInKb().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.PhysicalFrameBufferSizeInKb;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void VirtualFrameBufferSizeInKb_GivenSize_ReturnsIt()
        {
            // Arrange
            const uint expected = 9451116;
            myFakePhysicalGpu.GetVirtualFrameBufferSizeInKb().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.VirtualFrameBufferSizeInKb;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void VideoBiosVersion_GivenVersionString_ReturnsIt()
        {
            // Arrange
            const string expected = "AA.BB.CC.DD.EE";
            myFakePhysicalGpu.GetVideoBiosVersion().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.VideoBiosVersion;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void RamBusWidth_GivenBusWidthSize_ReturnsIt()
        {
            // Arrange
            const uint expected = 256u;
            myFakePhysicalGpu.GetRamBusWidth().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.RamBusWidth;

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetCurrentPerformanceState_GivenState_ReturnsIt()
        {
            // Arrange
            const string expected = "FakeState";
            myFakePhysicalGpu.GetCurrentPerformanceState().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetCurrentPerformanceState();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetGpuCoreTempInCelsius_GivenTemp_ReturnsIt()
        {
            // Arrange
            const int expected = 26;
            myFakePhysicalGpu.GetGpuCoreTempInCelsius().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetCoreTempInCelsius();

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetClockFrequencyInKHz_GivenGraphicsDomain_ReturnsGraphicsClockFrequency()
        {
            // Arrange
            const uint expected = 919;
            myFakePhysicalGpu.GetGraphicsClockDomainFrequencyInKHz().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetClockFrequencyInKHz(ClockDomain.Graphics);

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetClockFrequencyInKHz_GivenMemoryDomain_ReturnsMemoryClockFrequency()
        {
            // Arrange
            const uint expected = 921;
            myFakePhysicalGpu.GetMemoryClockDomainFrequencyInKHz().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetClockFrequencyInKHz(ClockDomain.Memory);

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetClockFrequencyInKHz_GivenProcessorDomain_ReturnsProcessorClockFrequency()
        {
            // Arrange
            const uint expected = 925;
            myFakePhysicalGpu.GetProcessorClockDomainFrequencyInKHz().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetClockFrequencyInKHz(ClockDomain.Processor);

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetClockFrequencyInKHz_GivenVideoDomain_ReturnsVideoClockFrequency()
        {
            // Arrange
            const uint expected = 1232024;
            myFakePhysicalGpu.GetVideoClockDomainFrequencyInKHz().Returns(expected);
            var gpu = CreateNvidiaGpu();

            // Act
            var actual = gpu.GetClockFrequencyInKHz(ClockDomain.Video);

            // Assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void GetClockFrequencyInKHz_GivenUnknownDomain_Throws()
        {
            // Arrange
            var gpu = CreateNvidiaGpu();

            // Act
            void Act() => gpu.GetClockFrequencyInKHz(ClockDomain.Unknown);
            var exception = Assert.ThrowsException<ArgumentException>(Act);

            // Assert
            StringAssert.Contains(exception.Message, "clock domain is unknown");
        }
    }
}
