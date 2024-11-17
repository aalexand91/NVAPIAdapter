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
            // TestPanel
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(839, 450);
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
    }
}
