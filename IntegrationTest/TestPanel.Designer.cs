// Copyright 2024 Anthony Alexander

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
            // TestPanel
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
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
    }
}
