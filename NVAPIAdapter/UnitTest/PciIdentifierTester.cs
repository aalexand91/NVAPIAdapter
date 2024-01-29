using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    public class PciIdentifierTester
    {
        [TestMethod]
        public void ToString_WhenCalled_ReturnsExpectedString()
        {
            // Arrange
            const uint deviceId = 1;
            const uint subSystemId = 2;
            const uint revisionId = 3;
            const uint externalDeviceId = 4;
            var identifier = new PciIdentifier
            {
                DeviceId = deviceId,
                SubsystemId = subSystemId,
                RevisionId = revisionId,
                ExternalDeviceId = externalDeviceId,
            };

            // Act
            var result = identifier.ToString();

            // assert
            StringAssert.Contains(result, $"Device ID: {deviceId}");
            StringAssert.Contains(result, $"Subsystem ID: {subSystemId}");
            StringAssert.Contains(result, $"Revision ID: {revisionId}");
            StringAssert.Contains(result, $"External ID: {externalDeviceId}");
        }
    }
}
