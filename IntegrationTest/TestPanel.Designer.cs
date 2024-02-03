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
            this.InstructionsLabel.Location = new System.Drawing.Point(103, 9);
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
            // TestPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
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
    }
}

