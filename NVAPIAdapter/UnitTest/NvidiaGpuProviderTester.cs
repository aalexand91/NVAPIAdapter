using Microsoft.VisualStudio.TestTools.UnitTesting;
using NSubstitute;
using System;
using System.Linq;

namespace NVAPIAdapter.UnitTest
{
    [TestClass]
    public class NvidiaGpuProviderTester
    {
        readonly IPhysicalGpuProviderAdapter myFakePhysicalGpuProvider = Substitute.For<IPhysicalGpuProviderAdapter>();

        const int FakeNumberOfGpus = 3;

        INvidiaGpuProvider CreateNvidiaGpuProvider() => new NvidiaGpuProvider();

        void RigForNumberOfGpus(int numberOfGpus)
        {
            myFakePhysicalGpuProvider.GetNumberOfGpus().Returns(numberOfGpus);
        }

        [TestInitialize]
        public void InitTest()
        {
            NvidiaGpuProvider.CreateNvidiaGpu = Substitute.For<NvidiaGpuProvider.CreateNvidiaGpuFunc>();
            NvidiaGpuProvider.CreatePhysicalGpuProvider = () => myFakePhysicalGpuProvider;
            NvidiaGpuProvider.InitializeApi = Substitute.For<NvidiaGpuProvider.InitializeFunc>();
            NvidiaGpuProvider.UnloadApi = Substitute.For<NvidiaGpuProvider.UnloadFunc>();
        }

        [TestMethod]
        public void CreateInstance_WhenCalled_ReturnsExpectedType()
        {
            // Act
            var instance = NvidiaGpuProvider.CreateInstance();

            // Assert
            Assert.IsInstanceOfType(instance, typeof(INvidiaGpuProvider));
        }

        [TestMethod]
        public void Initialize_WhenCalled_InitializesApi()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();

            // Act
            provider.Initialize();

            // Assert
            NvidiaGpuProvider.InitializeApi.Received().Invoke();
        }

        [TestMethod]
        public void Initialize_WhenCalledTwice_InitializesApiOnce()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            provider.Initialize();

            // Assert
            NvidiaGpuProvider.InitializeApi.Received(1).Invoke();
        }

        [TestMethod]
        public void Unload_WhenApiInitialized_UnloadsApi()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            provider.Unload();

            // Assert
            NvidiaGpuProvider.UnloadApi.Received().Invoke();
        }

        [TestMethod]
        public void Unload_WhenApiNotInitialized_DoesNotUnloadApi()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();

            // Act
            provider.Unload();

            // Assert
            NvidiaGpuProvider.UnloadApi.DidNotReceive().Invoke();
        }

        [TestMethod]
        public void GetNumberOfGpus_GivenNumberOfGpus_ReturnsIt()
        {
            // Arrange
            RigForNumberOfGpus(FakeNumberOfGpus);
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            var actual = provider.GetNumberOfGpus();

            // Assert
            Assert.AreEqual(FakeNumberOfGpus, actual);
        }

        [TestMethod]
        public void GetNumberOfGpus_WhenCalledBeforeInitializingApi_Throws()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();

            // Act
            var exception = Assert.ThrowsException<InvalidOperationException>(() => provider.GetNumberOfGpus());

            // Assert
            Assert.AreEqual(NvidiaGpuProvider.ApiNotInitializedMessage, exception.Message);
        }

        [DataTestMethod]
        [DataRow(0)]
        [DataRow(FakeNumberOfGpus - 1)]
        public void GetGpuByIndex_GivenValidIndex_ReturnsGpu(int index)
        {
            // Arrange
            RigForNumberOfGpus(FakeNumberOfGpus);
            var fakePhysicalGpu = Substitute.For<IPhysicalGpuAdapter>();
            myFakePhysicalGpuProvider.GetGpuByIndex(index).Returns(fakePhysicalGpu);
            var expectedGpu = Substitute.For<INvidiaGpu>();
            NvidiaGpuProvider.CreateNvidiaGpu(fakePhysicalGpu).Returns(expectedGpu);
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            var actualGpu = provider.GetGpuByIndex(index);

            // Assert
            Assert.AreSame(expectedGpu, actualGpu);
        }

        [DataTestMethod]
        [DataRow(-1)]
        [DataRow(FakeNumberOfGpus)]
        public void GetGpuByIndex_GivenInvalidIndex_Throws(int index)
        {
            // Arrange
            RigForNumberOfGpus(FakeNumberOfGpus);
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();
            const int maxIndex = FakeNumberOfGpus - 1;

            // Act
            var exception = Assert.ThrowsException<ArgumentException>(() => provider.GetGpuByIndex(index));

            // Assert
            StringAssert.Contains(exception.Message, "invalid");
            StringAssert.Contains(exception.Message, index.ToString());
            StringAssert.Contains(exception.Message, maxIndex.ToString());
        }

        [TestMethod]
        public void GetGpuByIndex_WhenApiNotInitalized_Throws()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();

            // Act
            void Act() => provider.GetGpuByIndex(0);
            var exception = Assert.ThrowsException<InvalidOperationException>(Act);

            // Assert
            Assert.AreEqual(NvidiaGpuProvider.ApiNotInitializedMessage, exception.Message);
        }

        [TestMethod]
        public void GetAllGpus_GivenGpus_ReturnsThem()
        {
            // Arrange
            RigForNumberOfGpus(FakeNumberOfGpus);
            var fakePhysicalGpu1 = Substitute.For<IPhysicalGpuAdapter>();
            var fakePhysicalGpu2 = Substitute.For<IPhysicalGpuAdapter>();
            var fakePhysicalGpu3 = Substitute.For<IPhysicalGpuAdapter>();
            var fakeNvidiaGpu1 = Substitute.For<INvidiaGpu>();
            var fakeNvidiaGpu2 = Substitute.For<INvidiaGpu>();
            var fakeNvidiaGpu3 = Substitute.For<INvidiaGpu>();
            myFakePhysicalGpuProvider.GetGpuByIndex(0).Returns(fakePhysicalGpu1);
            myFakePhysicalGpuProvider.GetGpuByIndex(1).Returns(fakePhysicalGpu2);
            myFakePhysicalGpuProvider.GetGpuByIndex(2).Returns(fakePhysicalGpu3);
            NvidiaGpuProvider.CreateNvidiaGpu(fakePhysicalGpu1).Returns(fakeNvidiaGpu1);
            NvidiaGpuProvider.CreateNvidiaGpu(fakePhysicalGpu2).Returns(fakeNvidiaGpu2);
            NvidiaGpuProvider.CreateNvidiaGpu(fakePhysicalGpu3).Returns(fakeNvidiaGpu3);
            var expected = new[] { fakeNvidiaGpu1, fakeNvidiaGpu2, fakeNvidiaGpu3 };
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            var actual = provider.GetAllGpus().ToArray();

            // Assert
            CollectionAssert.AreEquivalent(expected, actual);
        }

        [TestMethod]
        public void GetAllGpus_WhenApiNotInitialized_Throws()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();
            
            // Act
            var exception = Assert.ThrowsException<InvalidOperationException>(() => provider.GetAllGpus());

            // Assert
            Assert.AreEqual(NvidiaGpuProvider.ApiNotInitializedMessage, exception.Message);
        }

        [TestMethod]
        public void GetGpuByName_GivenValidName_ReturnsGpu()
        {
            // Arrange
            RigForNumberOfGpus(1);
            const string gpuName = "FakeGpu";
            var fakePhysicalGpu = Substitute.For<IPhysicalGpuAdapter>();
            myFakePhysicalGpuProvider.GetGpuByIndex(0).Returns(fakePhysicalGpu);
            var expectedGpu = Substitute.For<INvidiaGpu>();
            expectedGpu.GetName().Returns(gpuName);
            NvidiaGpuProvider.CreateNvidiaGpu(fakePhysicalGpu).Returns(expectedGpu);
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            var actualGpu = provider.GetGpuByName(gpuName);

            // Assert
            Assert.AreSame(expectedGpu, actualGpu);
        }

        [TestMethod]
        public void GetGpuByName_GivenInvalidName_Throws()
        {
            // Arrange
            RigForNumberOfGpus(1);
            var fakePhysicalGpu = Substitute.For<IPhysicalGpuAdapter>();
            myFakePhysicalGpuProvider.GetGpuByIndex(0).Returns(fakePhysicalGpu);
            var detectedGpu = Substitute.For<INvidiaGpu>();
            detectedGpu.GetName().Returns("DifferentGpu");
            NvidiaGpuProvider.CreateNvidiaGpu(fakePhysicalGpu).Returns(detectedGpu);
            const string givenName = "FakeGpu";
            var provider = CreateNvidiaGpuProvider();
            provider.Initialize();

            // Act
            void Act() => provider.GetGpuByName(givenName);
            var exception = Assert.ThrowsException<ArgumentException>(Act);

            // Assert
            StringAssert.Contains(exception.Message, "No GPU");
            StringAssert.Contains(exception.Message, givenName);
        }

        [TestMethod]
        public void GetGpuByName_WhenApiNotInitialized_Throws()
        {
            // Arrange
            var provider = CreateNvidiaGpuProvider();

            // Act
            void Act() => provider.GetGpuByName("FakeGpu");
            var exception = Assert.ThrowsException<InvalidOperationException>(Act);

            // Assert
            Assert.AreEqual(NvidiaGpuProvider.ApiNotInitializedMessage, exception.Message);
        }
    }
}
