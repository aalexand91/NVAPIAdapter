﻿using NVAPIAdapter;
using System;
using System.Data;
using System.Linq;
using System.Windows.Forms;

namespace AdapterIntegrationTest
{
    public partial class TestPanel : Form
    {
        INvidiaGpuProvider GpuProvider => myGpuProvider.Value;
        Lazy<INvidiaGpuProvider> myGpuProvider;

        public TestPanel()
        {
            InitializeComponent();
            myGpuProvider = new Lazy<INvidiaGpuProvider>(GetGpuProvider);
            PopulateSelectionComboBox();
        }

        INvidiaGpuProvider GetGpuProvider()
        {
            var provider = NvidiaGpuProvider.CreateInstance();
            provider.Initialize();
            return provider;
        }

        void PopulateSelectionComboBox()
        {
            var gpuNames = GpuProvider.GetAllGpus()
                .Select(gpu => gpu.GetName());
            foreach (var name in gpuNames) SelectionComboBox.Items.Add(name);
        }

        INvidiaGpu myGpu;

        void SelectionComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            myGpu = GpuProvider.GetGpuByIndex(SelectionComboBox.SelectedIndex);
            SystemTypeButton.Enabled = true;
            GpuTypeButton.Enabled = true;
            PciIdentifiersButton.Enabled = true;
            BusIdButton.Enabled = true;
            VbiosButton.Enabled = true;
            PhysicalFrameBufferButton.Enabled = true;
            VirtualFrameBufferButton.Enabled = true;
        }

        void ShowMessage(string message, string caption) => MessageBox.Show(message, caption, MessageBoxButtons.OK);
        void SystemTypeButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetSystemType().ToString(), "GPU System Type");
        void GpuTypeButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetGpuType().ToString(), "GPU Type");
        void PciIdentifiersButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetPciIdentifiers().ToString(), "PCI Identifiers");
        void BusIdButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetBusId().ToString(), "Bus ID");
        void VbiosButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetVideoBiosVersion(), "Video BIOS Version");
        void PhysicalFrameBufferButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetPhysicalFrameBufferSizeInKb().ToString(), "Physical Framebuffer Size in KB");
        void VirtualFrameBufferButton_Click(object sender, EventArgs e) => ShowMessage(myGpu.GetVirtualFrameBufferSizeInKb().ToString(), "Virtual Framebuffer Size in KB");
    }
}
