namespace AdapterIntegrationTest
{
    partial class TestPanel
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                GpuProvider.Unload();
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SelectionComboBox = new System.Windows.Forms.ComboBox();
            this.InstructionsLabel = new System.Windows.Forms.Label();
            this.SystemTypeButton = new System.Windows.Forms.Button();
            this.GpuTypeButton = new System.Windows.Forms.Button();
            this.PciIdentifiersButton = new System.Windows.Forms.Button();
            this.BusIdButton = new System.Windows.Forms.Button();
            this.VbiosButton = new System.Windows.Forms.Button();
            this.PhysicalFrameBufferButton = new System.Windows.Forms.Button();
            this.VirtualFrameBufferButton = new System.Windows.Forms.Button();
            this.GpuCoreButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // SelectionComboBox
            // 
            this.SelectionComboBox.FormattingEnabled = true;
            this.SelectionComboBox.Location = new System.Drawing.Point(205, 28);
            this.SelectionComboBox.Name = "SelectionComboBox";
            this.SelectionComboBox.Size = new System.Drawing.Size(356, 24);
            this.SelectionComboBox.TabIndex = 1;
            this.SelectionComboBox.SelectedIndexChanged += new System.EventHandler(this.SelectionComboBox_SelectedIndexChanged);
            // 
            // InstructionsLabel
            // 
            this.InstructionsLabel.AutoSize = true;
            this.InstructionsLabel.Location = new System.Drawing.Point(66, 9);
            this.InstructionsLabel.Name = "InstructionsLabel";
            this.InstructionsLabel.Size = new System.Drawing.Size(634, 16);
            this.InstructionsLabel.TabIndex = 2;
            this.InstructionsLabel.Text = "Instructions: Select a GPU (if any) from the drop down. After selection, press an" +
    "y of the buttons below to test.";
            // 
            // SystemTypeButton
            // 
            this.SystemTypeButton.Enabled = false;
            this.SystemTypeButton.Location = new System.Drawing.Point(29, 81);
            this.SystemTypeButton.Name = "SystemTypeButton";
            this.SystemTypeButton.Size = new System.Drawing.Size(137, 34);
            this.SystemTypeButton.TabIndex = 3;
            this.SystemTypeButton.Text = "Get System Type";
            this.SystemTypeButton.UseVisualStyleBackColor = true;
            this.SystemTypeButton.Click += new System.EventHandler(this.SystemTypeButton_Click);
            // 
            // GpuTypeButton
            // 
            this.GpuTypeButton.Enabled = false;
            this.GpuTypeButton.Location = new System.Drawing.Point(29, 121);
            this.GpuTypeButton.Name = "GpuTypeButton";
            this.GpuTypeButton.Size = new System.Drawing.Size(137, 34);
            this.GpuTypeButton.TabIndex = 4;
            this.GpuTypeButton.Text = "Get GPU Type";
            this.GpuTypeButton.UseVisualStyleBackColor = true;
            this.GpuTypeButton.Click += new System.EventHandler(this.GpuTypeButton_Click);
            // 
            // PciIdentifiersButton
            // 
            this.PciIdentifiersButton.Enabled = false;
            this.PciIdentifiersButton.Location = new System.Drawing.Point(29, 161);
            this.PciIdentifiersButton.Name = "PciIdentifiersButton";
            this.PciIdentifiersButton.Size = new System.Drawing.Size(137, 34);
            this.PciIdentifiersButton.TabIndex = 5;
            this.PciIdentifiersButton.Text = "Get PCI Identifiers";
            this.PciIdentifiersButton.UseVisualStyleBackColor = true;
            this.PciIdentifiersButton.Click += new System.EventHandler(this.PciIdentifiersButton_Click);
            // 
            // BusIdButton
            // 
            this.BusIdButton.Enabled = false;
            this.BusIdButton.Location = new System.Drawing.Point(29, 201);
            this.BusIdButton.Name = "BusIdButton";
            this.BusIdButton.Size = new System.Drawing.Size(137, 34);
            this.BusIdButton.TabIndex = 6;
            this.BusIdButton.Text = "Get Bus ID";
            this.BusIdButton.UseVisualStyleBackColor = true;
            this.BusIdButton.Click += new System.EventHandler(this.BusIdButton_Click);
            // 
            // VbiosButton
            // 
            this.VbiosButton.Enabled = false;
            this.VbiosButton.Location = new System.Drawing.Point(29, 241);
            this.VbiosButton.Name = "VbiosButton";
            this.VbiosButton.Size = new System.Drawing.Size(137, 34);
            this.VbiosButton.TabIndex = 7;
            this.VbiosButton.Text = "Get VBIOS";
            this.VbiosButton.UseVisualStyleBackColor = true;
            this.VbiosButton.Click += new System.EventHandler(this.VbiosButton_Click);
            // 
            // PhysicalFrameBufferButton
            // 
            this.PhysicalFrameBufferButton.Enabled = false;
            this.PhysicalFrameBufferButton.Location = new System.Drawing.Point(29, 281);
            this.PhysicalFrameBufferButton.Name = "PhysicalFrameBufferButton";
            this.PhysicalFrameBufferButton.Size = new System.Drawing.Size(137, 74);
            this.PhysicalFrameBufferButton.TabIndex = 8;
            this.PhysicalFrameBufferButton.Text = "Get Physical Framebuffer Size";
            this.PhysicalFrameBufferButton.UseVisualStyleBackColor = true;
            this.PhysicalFrameBufferButton.Click += new System.EventHandler(this.PhysicalFrameBufferButton_Click);
            // 
            // VirtualFrameBufferButton
            // 
            this.VirtualFrameBufferButton.Enabled = false;
            this.VirtualFrameBufferButton.Location = new System.Drawing.Point(29, 361);
            this.VirtualFrameBufferButton.Name = "VirtualFrameBufferButton";
            this.VirtualFrameBufferButton.Size = new System.Drawing.Size(137, 74);
            this.VirtualFrameBufferButton.TabIndex = 9;
            this.VirtualFrameBufferButton.Text = "Get Virtual Framebuffer Size";
            this.VirtualFrameBufferButton.UseVisualStyleBackColor = true;
            this.VirtualFrameBufferButton.Click += new System.EventHandler(this.VirtualFrameBufferButton_Click);
            // 
            // GpuCoreButton
            // 
            this.GpuCoreButton.Enabled = false;
            this.GpuCoreButton.Location = new System.Drawing.Point(172, 81);
            this.GpuCoreButton.Name = "GpuCoreButton";
            this.GpuCoreButton.Size = new System.Drawing.Size(137, 34);
            this.GpuCoreButton.TabIndex = 10;
            this.GpuCoreButton.Text = "Get Core Count";
            this.GpuCoreButton.UseVisualStyleBackColor = true;
            this.GpuCoreButton.Click += new System.EventHandler(this.GpuCoreButton_Click);
            // 
            // TestPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.GpuCoreButton);
            this.Controls.Add(this.VirtualFrameBufferButton);
            this.Controls.Add(this.PhysicalFrameBufferButton);
            this.Controls.Add(this.VbiosButton);
            this.Controls.Add(this.BusIdButton);
            this.Controls.Add(this.PciIdentifiersButton);
            this.Controls.Add(this.GpuTypeButton);
            this.Controls.Add(this.SystemTypeButton);
            this.Controls.Add(this.InstructionsLabel);
            this.Controls.Add(this.SelectionComboBox);
            this.Name = "TestPanel";
            this.Text = "NVAPIAdapter Test Panel";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox SelectionComboBox;
        private System.Windows.Forms.Label InstructionsLabel;
        private System.Windows.Forms.Button SystemTypeButton;
        private System.Windows.Forms.Button GpuTypeButton;
        private System.Windows.Forms.Button PciIdentifiersButton;
        private System.Windows.Forms.Button BusIdButton;
        private System.Windows.Forms.Button VbiosButton;
        private System.Windows.Forms.Button PhysicalFrameBufferButton;
        private System.Windows.Forms.Button VirtualFrameBufferButton;
        private System.Windows.Forms.Button GpuCoreButton;
    }
}

