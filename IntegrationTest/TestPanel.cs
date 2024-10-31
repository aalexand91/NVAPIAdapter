// Copyright 2024 Anthony Alexander

using JetBrains.Annotations;

namespace NVAPIAdapter.IntegrationTest
{
    public partial class TestPanel : Form
    {
        [CanBeNull] private INvidiaGpu? mySelectedGpu = null;
        [NotNull] private readonly IReadOnlyCollection<INvidiaGpu> myDetectedGpus = new List<INvidiaGpu>();

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
        }

        private void CoreCountButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(mySelectedGpu?.CoreCount.ToString(), caption: "GPU Core Count", MessageBoxButtons.OK);
        }
    }
}
