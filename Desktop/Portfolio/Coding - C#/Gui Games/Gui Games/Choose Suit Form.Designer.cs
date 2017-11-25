namespace Gui_Games
{
    partial class ChooseSuitForm
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
            this.button1 = new System.Windows.Forms.Button();
            this.ClubsRadioButton = new System.Windows.Forms.RadioButton();
            this.DiamondsRadioButton = new System.Windows.Forms.RadioButton();
            this.HeartsRadioButton = new System.Windows.Forms.RadioButton();
            this.SpadesRadioButton = new System.Windows.Forms.RadioButton();
            this.ChooseASuitBox = new System.Windows.Forms.GroupBox();
            this.ChooseASuitBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(41, 172);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "OKAY";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // ClubsRadioButton
            // 
            this.ClubsRadioButton.AutoSize = true;
            this.ClubsRadioButton.Location = new System.Drawing.Point(17, 29);
            this.ClubsRadioButton.Name = "ClubsRadioButton";
            this.ClubsRadioButton.Size = new System.Drawing.Size(51, 17);
            this.ClubsRadioButton.TabIndex = 1;
            this.ClubsRadioButton.TabStop = true;
            this.ClubsRadioButton.Text = "Clubs";
            this.ClubsRadioButton.UseVisualStyleBackColor = true;
            this.ClubsRadioButton.CheckedChanged += new System.EventHandler(this.ClubsRadioButton_CheckedChanged);
            // 
            // DiamondsRadioButton
            // 
            this.DiamondsRadioButton.AutoSize = true;
            this.DiamondsRadioButton.Location = new System.Drawing.Point(17, 52);
            this.DiamondsRadioButton.Name = "DiamondsRadioButton";
            this.DiamondsRadioButton.Size = new System.Drawing.Size(72, 17);
            this.DiamondsRadioButton.TabIndex = 2;
            this.DiamondsRadioButton.TabStop = true;
            this.DiamondsRadioButton.Text = "Diamonds";
            this.DiamondsRadioButton.UseVisualStyleBackColor = true;
            this.DiamondsRadioButton.CheckedChanged += new System.EventHandler(this.DiamondsRadioButton_CheckedChanged);
            // 
            // HeartsRadioButton
            // 
            this.HeartsRadioButton.AutoSize = true;
            this.HeartsRadioButton.Location = new System.Drawing.Point(17, 75);
            this.HeartsRadioButton.Name = "HeartsRadioButton";
            this.HeartsRadioButton.Size = new System.Drawing.Size(56, 17);
            this.HeartsRadioButton.TabIndex = 3;
            this.HeartsRadioButton.TabStop = true;
            this.HeartsRadioButton.Text = "Hearts";
            this.HeartsRadioButton.UseVisualStyleBackColor = true;
            this.HeartsRadioButton.CheckedChanged += new System.EventHandler(this.HeartsRadioButton_CheckedChanged);
            // 
            // SpadesRadioButton
            // 
            this.SpadesRadioButton.AutoSize = true;
            this.SpadesRadioButton.Location = new System.Drawing.Point(17, 99);
            this.SpadesRadioButton.Name = "SpadesRadioButton";
            this.SpadesRadioButton.Size = new System.Drawing.Size(61, 17);
            this.SpadesRadioButton.TabIndex = 4;
            this.SpadesRadioButton.TabStop = true;
            this.SpadesRadioButton.Text = "Spades";
            this.SpadesRadioButton.UseVisualStyleBackColor = true;
            this.SpadesRadioButton.CheckedChanged += new System.EventHandler(this.SpadesRadioButton_CheckedChanged);
            // 
            // ChooseASuitBox
            // 
            this.ChooseASuitBox.Controls.Add(this.SpadesRadioButton);
            this.ChooseASuitBox.Controls.Add(this.HeartsRadioButton);
            this.ChooseASuitBox.Controls.Add(this.DiamondsRadioButton);
            this.ChooseASuitBox.Controls.Add(this.ClubsRadioButton);
            this.ChooseASuitBox.Location = new System.Drawing.Point(12, 22);
            this.ChooseASuitBox.Name = "ChooseASuitBox";
            this.ChooseASuitBox.Size = new System.Drawing.Size(103, 136);
            this.ChooseASuitBox.TabIndex = 5;
            this.ChooseASuitBox.TabStop = false;
            this.ChooseASuitBox.Text = "Choose a Suit";
            // 
            // ChooseSuitForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(170, 251);
            this.Controls.Add(this.ChooseASuitBox);
            this.Controls.Add(this.button1);
            this.Name = "ChooseSuitForm";
            this.Text = "Choose a Suit";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ChooseASuitBox.ResumeLayout(false);
            this.ChooseASuitBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.RadioButton ClubsRadioButton;
        private System.Windows.Forms.RadioButton DiamondsRadioButton;
        private System.Windows.Forms.RadioButton HeartsRadioButton;
        private System.Windows.Forms.RadioButton SpadesRadioButton;
        private System.Windows.Forms.GroupBox ChooseASuitBox;
    }
}