namespace RGB_Color_Mixer
{
    partial class RGBmixer
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.RGBcolorDialog = new System.Windows.Forms.PictureBox();
            this.labelR = new System.Windows.Forms.Label();
            this.labelG = new System.Windows.Forms.Label();
            this.labelB = new System.Windows.Forms.Label();
            this.trackBarRed = new System.Windows.Forms.TrackBar();
            this.trackBarGreen = new System.Windows.Forms.TrackBar();
            this.trackBarBlue = new System.Windows.Forms.TrackBar();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.txtHexValue = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RGBcolorDialog)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarGreen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBlue)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 13.41463F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 86.58537F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 186F));
            this.tableLayoutPanel1.Controls.Add(this.RGBcolorDialog, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.labelR, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.labelG, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelB, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.trackBarRed, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.trackBarGreen, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.trackBarBlue, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.txtHexValue, 2, 3);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 27);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 46F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 46F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 46F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(593, 172);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // RGBcolorDialog
            // 
            this.RGBcolorDialog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RGBcolorDialog.BackColor = System.Drawing.Color.White;
            this.RGBcolorDialog.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.RGBcolorDialog.Location = new System.Drawing.Point(409, 3);
            this.RGBcolorDialog.Name = "RGBcolorDialog";
            this.tableLayoutPanel1.SetRowSpan(this.RGBcolorDialog, 3);
            this.RGBcolorDialog.Size = new System.Drawing.Size(181, 132);
            this.RGBcolorDialog.TabIndex = 3;
            this.RGBcolorDialog.TabStop = false;
            // 
            // labelR
            // 
            this.labelR.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelR.BackColor = System.Drawing.Color.Red;
            this.labelR.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelR.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelR.Location = new System.Drawing.Point(3, 7);
            this.labelR.Name = "labelR";
            this.labelR.Size = new System.Drawing.Size(48, 32);
            this.labelR.TabIndex = 1;
            this.labelR.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // labelG
            // 
            this.labelG.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelG.BackColor = System.Drawing.Color.Green;
            this.labelG.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelG.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelG.Location = new System.Drawing.Point(3, 53);
            this.labelG.Name = "labelG";
            this.labelG.Size = new System.Drawing.Size(48, 32);
            this.labelG.TabIndex = 3;
            this.labelG.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // labelB
            // 
            this.labelB.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelB.BackColor = System.Drawing.Color.Blue;
            this.labelB.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labelB.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelB.Location = new System.Drawing.Point(3, 99);
            this.labelB.Name = "labelB";
            this.labelB.Size = new System.Drawing.Size(48, 32);
            this.labelB.TabIndex = 5;
            this.labelB.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // trackBarRed
            // 
            this.trackBarRed.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBarRed.Location = new System.Drawing.Point(57, 3);
            this.trackBarRed.Maximum = 255;
            this.trackBarRed.Name = "trackBarRed";
            this.trackBarRed.Size = new System.Drawing.Size(346, 40);
            this.trackBarRed.TabIndex = 0;
            this.trackBarRed.TickFrequency = 15;
            this.trackBarRed.Scroll += new System.EventHandler(this.trackBarRed_Scroll);
            // 
            // trackBarGreen
            // 
            this.trackBarGreen.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBarGreen.Location = new System.Drawing.Point(57, 49);
            this.trackBarGreen.Maximum = 255;
            this.trackBarGreen.Name = "trackBarGreen";
            this.trackBarGreen.Size = new System.Drawing.Size(346, 40);
            this.trackBarGreen.TabIndex = 1;
            this.trackBarGreen.TickFrequency = 15;
            this.trackBarGreen.Scroll += new System.EventHandler(this.trackBarGreen_Scroll);
            // 
            // trackBarBlue
            // 
            this.trackBarBlue.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBarBlue.Location = new System.Drawing.Point(57, 95);
            this.trackBarBlue.Maximum = 255;
            this.trackBarBlue.Name = "trackBarBlue";
            this.trackBarBlue.Size = new System.Drawing.Size(346, 40);
            this.trackBarBlue.TabIndex = 2;
            this.trackBarBlue.TickFrequency = 15;
            this.trackBarBlue.Scroll += new System.EventHandler(this.trackBarBlue_Scroll);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(617, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // txtHexValue
            // 
            this.txtHexValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.txtHexValue.BackColor = System.Drawing.Color.White;
            this.txtHexValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtHexValue.Location = new System.Drawing.Point(409, 144);
            this.txtHexValue.Name = "txtHexValue";
            this.txtHexValue.ReadOnly = true;
            this.txtHexValue.Size = new System.Drawing.Size(181, 22);
            this.txtHexValue.TabIndex = 7;
            this.txtHexValue.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // RGBmixer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(617, 203);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "RGBmixer";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Arduino RGB Color Mixer";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RGBcolorDialog)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarGreen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBlue)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TrackBar trackBarRed;
        private System.Windows.Forms.TrackBar trackBarGreen;
        private System.Windows.Forms.TrackBar trackBarBlue;
        private System.Windows.Forms.PictureBox RGBcolorDialog;
        private System.Windows.Forms.Label labelR;
        private System.Windows.Forms.Label labelG;
        private System.Windows.Forms.Label labelB;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.TextBox txtHexValue;
    }
}

