// Copyright (c) 2024 Anthony Alexander

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

namespace NVAPIAdapter.IntegrationTest
{
    public partial class TestPanel : Form
    {
        [CanBeNull] private INvidiaGpu? mySelectedGpu = null;
        [NotNull] private readonly IReadOnlyCollection<INvidiaGpu> myDetectedGpus = [];

        public TestPanel()
        {
            InitializeComponent();
            NVAPI.Initialize();
            myDetectedGpus = NVAPI.GetAllGpus().ToList();
            InitializeGpuComboBox();
        }

        private void InitializeGpuComboBox()
        {
            if (!myDetectedGpus.Any())
            {
                const string message = "No Nvidia GPUs were detected. Make sure at least one is connected and restart the application.";
                MessageBox.Show(message, caption: "No GPUS detected", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            foreach (var gpu in myDetectedGpus)
            {
                GpuComboBox.Items.Add(gpu.Name);
            }
            GpuComboBox.Enabled = true;
        }

        private void GpuComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            mySelectedGpu = myDetectedGpus.ElementAt(GpuComboBox.SelectedIndex);
            CoreCountButton.Enabled = true;
            BusTypeButton.Enabled = true;
            SystemTypeButton.Enabled = true;
            PciIdButton.Enabled = true;
            PhysicalFrameBufferSizeButton.Enabled = true;
            VirtualFrameBufferSizeButton.Enabled = true;
            VbiosButton.Enabled = true;
            BusWidthButton.Enabled = true;
            PerformanceStateButton.Enabled = true;
            GpuCoreTempButton.Enabled = true;
            GraphicsClockFrequencyButton.Enabled = true;
            MemoryClockFrequencyButton.Enabled = true;
            ProcessorClockFrequencyButton.Enabled = true;
            VideoClockFrequencyButton.Enabled = true;
        }

        [NotNull] INvidiaGpu SelectedGpu => mySelectedGpu ?? throw new NullReferenceException("GPU was not selected.");

        private void CoreCountButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.CoreCount.ToString(), caption: "GPU Core Count", MessageBoxButtons.OK);
        }

        private void BusTypeButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.BusType, caption: "GPU Bus Type", MessageBoxButtons.OK);
        }

        private void SystemTypeButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.SystemType, caption: "GPU System Type", MessageBoxButtons.OK);
        }

        private void PciIdButton_Click(object sender, EventArgs e)
        {
            var pciIdentifier = SelectedGpu.GetPciIdentifier();
            var message = $@"Internal ID: {pciIdentifier.InternalId}
External ID: {pciIdentifier.ExternalId}
Revision ID: {pciIdentifier.RevisionId}
Subsystem ID: {pciIdentifier.SubsystemId}";
            MessageBox.Show(message, caption: "PCI Identifiers", MessageBoxButtons.OK);
        }

        private void PhysicalFrameBufferSizeButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.PhysicalFrameBufferSizeInKb.ToString(),
                caption: "GPU Physical Frame Buffer Size", MessageBoxButtons.OK);
        }

        private void VirtualFrameBufferSizeButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.VirtualFrameBufferSizeInKb.ToString(),
                caption: "GPU Virtual Frame Buffer Size", MessageBoxButtons.OK);
        }

        private void VbiosButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.VideoBiosVersion, caption: "VBIOS Version", MessageBoxButtons.OK);
        }

        private void BusWidthButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.RamBusWidth.ToString() + "-bit", caption: "GPU RAM Bus Width", MessageBoxButtons.OK);
        }

        private void PerformanceStateButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.GetCurrentPerformanceState(), caption: "GPU Performance State", MessageBoxButtons.OK);
        }

        private void GpuCoreTempButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(SelectedGpu.GetCoreTempInCelsius().ToString(), caption: "GPU Core Temp (C)", MessageBoxButtons.OK);
        }

        [NotNull]
        private string GetClockFrequencyString(ClockDomain clockDomain)
        {
            var frequency = SelectedGpu.GetClockFrequencyInKHz(clockDomain);
            return frequency > 0 ? frequency.ToString() : "Clock domain does not exist.";
        }

        private void GraphicsClockFrequencyButton_Click(object sender, EventArgs e)
        {
            var message = GetClockFrequencyString(ClockDomain.Graphics);
            MessageBox.Show(message, caption: "GPU Graphics Clock Frequency (kHz)", MessageBoxButtons.OK);
        }

        private void MemoryClockFrequencyButton_Click(object sender, EventArgs e)
        {
            var message = GetClockFrequencyString(ClockDomain.Memory);
            MessageBox.Show(message, caption: "GPU Memory Clock Frequency (kHz)", MessageBoxButtons.OK);
        }

        private void ProcessorClockFrequencyButton_Click(object sender, EventArgs e)
        {
            var message = GetClockFrequencyString(ClockDomain.Processor);
            MessageBox.Show(message, caption: "GPU Processor Clock Frequency (kHz)", MessageBoxButtons.OK);
        }

        private void VideoClockFrequencyButton_Click(object sender, EventArgs e)
        {
            var message = GetClockFrequencyString(ClockDomain.Video);
            MessageBox.Show(message, caption: "GPU Video Clock Frequency (kHz)", MessageBoxButtons.OK);
        }
    }
}
