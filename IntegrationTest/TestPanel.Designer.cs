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

namespace NVAPIAdapter.IntegrationTest
{
    partial class TestPanel
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            NVAPI.Unload();
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TestPanel));
            InstructionLabel = new Label();
            GpuComboBox = new ComboBox();
            CoreCountButton = new Button();
            BusTypeButton = new Button();
            SystemTypeButton = new Button();
            PciIdButton = new Button();
            PhysicalFrameBufferSizeButton = new Button();
            VirtualFrameBufferSizeButton = new Button();
            VbiosButton = new Button();
            BusWidthButton = new Button();
            PerformanceStateButton = new Button();
            GpuCoreTempButton = new Button();
            GraphicsClockFrequencyButton = new Button();
            MemoryClockFrequencyButton = new Button();
            ProcessorClockFrequencyButton = new Button();
            VideoClockFrequencyButton = new Button();
            SuspendLayout();
            // 
            // InstructionLabel
            // 
            InstructionLabel.AutoSize = true;
            InstructionLabel.Location = new Point(12, 9);
            InstructionLabel.Name = "InstructionLabel";
            InstructionLabel.Size = new Size(786, 40);
            InstructionLabel.TabIndex = 0;
            InstructionLabel.Text = resources.GetString("InstructionLabel.Text");
            // 
            // GpuComboBox
            // 
            GpuComboBox.Enabled = false;
            GpuComboBox.FormattingEnabled = true;
            GpuComboBox.Location = new Point(183, 52);
            GpuComboBox.Name = "GpuComboBox";
            GpuComboBox.Size = new Size(462, 28);
            GpuComboBox.TabIndex = 1;
            GpuComboBox.Text = "Select GPU to test";
            GpuComboBox.SelectedIndexChanged += GpuComboBox_SelectedIndexChanged;
            // 
            // CoreCountButton
            // 
            CoreCountButton.Enabled = false;
            CoreCountButton.Location = new Point(12, 92);
            CoreCountButton.Name = "CoreCountButton";
            CoreCountButton.Size = new Size(157, 71);
            CoreCountButton.TabIndex = 2;
            CoreCountButton.Text = "Get Core Count";
            CoreCountButton.UseVisualStyleBackColor = true;
            CoreCountButton.Click += CoreCountButton_Click;
            // 
            // BusTypeButton
            // 
            BusTypeButton.Enabled = false;
            BusTypeButton.Location = new Point(175, 92);
            BusTypeButton.Name = "BusTypeButton";
            BusTypeButton.Size = new Size(157, 71);
            BusTypeButton.TabIndex = 3;
            BusTypeButton.Text = "Bus Type";
            BusTypeButton.UseVisualStyleBackColor = true;
            BusTypeButton.Click += BusTypeButton_Click;
            // 
            // SystemTypeButton
            // 
            SystemTypeButton.Enabled = false;
            SystemTypeButton.Location = new Point(338, 92);
            SystemTypeButton.Name = "SystemTypeButton";
            SystemTypeButton.Size = new Size(157, 71);
            SystemTypeButton.TabIndex = 4;
            SystemTypeButton.Text = "System Type";
            SystemTypeButton.UseVisualStyleBackColor = true;
            SystemTypeButton.Click += SystemTypeButton_Click;
            // 
            // PciIdButton
            // 
            PciIdButton.Enabled = false;
            PciIdButton.Location = new Point(12, 169);
            PciIdButton.Name = "PciIdButton";
            PciIdButton.Size = new Size(157, 71);
            PciIdButton.TabIndex = 5;
            PciIdButton.Text = "PCI Identifiers";
            PciIdButton.UseVisualStyleBackColor = true;
            PciIdButton.Click += PciIdButton_Click;
            // 
            // PhysicalFrameBufferSizeButton
            // 
            PhysicalFrameBufferSizeButton.Enabled = false;
            PhysicalFrameBufferSizeButton.Location = new Point(501, 92);
            PhysicalFrameBufferSizeButton.Name = "PhysicalFrameBufferSizeButton";
            PhysicalFrameBufferSizeButton.Size = new Size(157, 71);
            PhysicalFrameBufferSizeButton.TabIndex = 6;
            PhysicalFrameBufferSizeButton.Text = "Physical Frame Buffer Size (KB)";
            PhysicalFrameBufferSizeButton.UseVisualStyleBackColor = true;
            PhysicalFrameBufferSizeButton.Click += PhysicalFrameBufferSizeButton_Click;
            // 
            // VirtualFrameBufferSizeButton
            // 
            VirtualFrameBufferSizeButton.Enabled = false;
            VirtualFrameBufferSizeButton.Location = new Point(664, 92);
            VirtualFrameBufferSizeButton.Name = "VirtualFrameBufferSizeButton";
            VirtualFrameBufferSizeButton.Size = new Size(157, 71);
            VirtualFrameBufferSizeButton.TabIndex = 7;
            VirtualFrameBufferSizeButton.Text = "Virtual Frame Buffer Size (KB)";
            VirtualFrameBufferSizeButton.UseVisualStyleBackColor = true;
            VirtualFrameBufferSizeButton.Click += VirtualFrameBufferSizeButton_Click;
            // 
            // VbiosButton
            // 
            VbiosButton.Enabled = false;
            VbiosButton.Location = new Point(175, 169);
            VbiosButton.Name = "VbiosButton";
            VbiosButton.Size = new Size(157, 71);
            VbiosButton.TabIndex = 8;
            VbiosButton.Text = "VBIOS Version";
            VbiosButton.UseVisualStyleBackColor = true;
            VbiosButton.Click += VbiosButton_Click;
            // 
            // BusWidthButton
            // 
            BusWidthButton.Enabled = false;
            BusWidthButton.Location = new Point(338, 169);
            BusWidthButton.Name = "BusWidthButton";
            BusWidthButton.Size = new Size(157, 71);
            BusWidthButton.TabIndex = 9;
            BusWidthButton.Text = "RAM Bus Width";
            BusWidthButton.UseVisualStyleBackColor = true;
            BusWidthButton.Click += BusWidthButton_Click;
            // 
            // PerformanceStateButton
            // 
            PerformanceStateButton.Enabled = false;
            PerformanceStateButton.Location = new Point(501, 169);
            PerformanceStateButton.Name = "PerformanceStateButton";
            PerformanceStateButton.Size = new Size(157, 71);
            PerformanceStateButton.TabIndex = 10;
            PerformanceStateButton.Text = "Current Performance State";
            PerformanceStateButton.UseVisualStyleBackColor = true;
            PerformanceStateButton.Click += PerformanceStateButton_Click;
            // 
            // GpuCoreTempButton
            // 
            GpuCoreTempButton.Enabled = false;
            GpuCoreTempButton.Location = new Point(664, 169);
            GpuCoreTempButton.Name = "GpuCoreTempButton";
            GpuCoreTempButton.Size = new Size(157, 71);
            GpuCoreTempButton.TabIndex = 11;
            GpuCoreTempButton.Text = "GPU Core Temp (C)";
            GpuCoreTempButton.UseVisualStyleBackColor = true;
            GpuCoreTempButton.Click += GpuCoreTempButton_Click;
            // 
            // GraphicsClockFrequencyButton
            // 
            GraphicsClockFrequencyButton.Enabled = false;
            GraphicsClockFrequencyButton.Location = new Point(12, 246);
            GraphicsClockFrequencyButton.Name = "GraphicsClockFrequencyButton";
            GraphicsClockFrequencyButton.Size = new Size(157, 71);
            GraphicsClockFrequencyButton.TabIndex = 12;
            GraphicsClockFrequencyButton.Text = "Graphics Clock Frequency (kHz)";
            GraphicsClockFrequencyButton.UseVisualStyleBackColor = true;
            GraphicsClockFrequencyButton.Click += GraphicsClockFrequencyButton_Click;
            // 
            // MemoryClockFrequencyButton
            // 
            MemoryClockFrequencyButton.Enabled = false;
            MemoryClockFrequencyButton.Location = new Point(175, 246);
            MemoryClockFrequencyButton.Name = "MemoryClockFrequencyButton";
            MemoryClockFrequencyButton.Size = new Size(157, 71);
            MemoryClockFrequencyButton.TabIndex = 13;
            MemoryClockFrequencyButton.Text = "Memory Clock Frequency (kHz)";
            MemoryClockFrequencyButton.UseVisualStyleBackColor = true;
            MemoryClockFrequencyButton.Click += MemoryClockFrequencyButton_Click;
            // 
            // ProcessorClockFrequencyButton
            // 
            ProcessorClockFrequencyButton.Enabled = false;
            ProcessorClockFrequencyButton.Location = new Point(338, 246);
            ProcessorClockFrequencyButton.Name = "ProcessorClockFrequencyButton";
            ProcessorClockFrequencyButton.Size = new Size(157, 71);
            ProcessorClockFrequencyButton.TabIndex = 14;
            ProcessorClockFrequencyButton.Text = "Processor Clock Frequency (kHz)";
            ProcessorClockFrequencyButton.UseVisualStyleBackColor = true;
            ProcessorClockFrequencyButton.Click += ProcessorClockFrequencyButton_Click;
            // 
            // VideoClockFrequencyButton
            // 
            VideoClockFrequencyButton.Enabled = false;
            VideoClockFrequencyButton.Location = new Point(501, 246);
            VideoClockFrequencyButton.Name = "VideoClockFrequencyButton";
            VideoClockFrequencyButton.Size = new Size(157, 71);
            VideoClockFrequencyButton.TabIndex = 15;
            VideoClockFrequencyButton.Text = "Video Clock Frequency (kHz)";
            VideoClockFrequencyButton.UseVisualStyleBackColor = true;
            VideoClockFrequencyButton.Click += VideoClockFrequencyButton_Click;
            // 
            // TestPanel
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(839, 450);
            Controls.Add(VideoClockFrequencyButton);
            Controls.Add(ProcessorClockFrequencyButton);
            Controls.Add(MemoryClockFrequencyButton);
            Controls.Add(GraphicsClockFrequencyButton);
            Controls.Add(GpuCoreTempButton);
            Controls.Add(PerformanceStateButton);
            Controls.Add(BusWidthButton);
            Controls.Add(VbiosButton);
            Controls.Add(VirtualFrameBufferSizeButton);
            Controls.Add(PhysicalFrameBufferSizeButton);
            Controls.Add(PciIdButton);
            Controls.Add(SystemTypeButton);
            Controls.Add(BusTypeButton);
            Controls.Add(CoreCountButton);
            Controls.Add(GpuComboBox);
            Controls.Add(InstructionLabel);
            Name = "TestPanel";
            Text = "NVAPIAdapter Test Panel";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label InstructionLabel;
        private ComboBox GpuComboBox;
        private Button CoreCountButton;
        private Button BusTypeButton;
        private Button SystemTypeButton;
        private Button PciIdButton;
        private Button PhysicalFrameBufferSizeButton;
        private Button VirtualFrameBufferSizeButton;
        private Button VbiosButton;
        private Button BusWidthButton;
        private Button PerformanceStateButton;
        private Button GpuCoreTempButton;
        private Button GraphicsClockFrequencyButton;
        private Button MemoryClockFrequencyButton;
        private Button ProcessorClockFrequencyButton;
        private Button VideoClockFrequencyButton;
    }
}
