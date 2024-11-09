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
    }
}
