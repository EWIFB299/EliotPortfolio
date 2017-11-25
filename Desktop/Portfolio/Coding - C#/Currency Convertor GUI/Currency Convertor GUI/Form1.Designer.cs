namespace Currency_Convertor_GUI {
    partial class Form1 {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.buttonConvert = new System.Windows.Forms.Button();
            this.inputBox = new System.Windows.Forms.TextBox();
            this.outputBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.inputSelect = new System.Windows.Forms.ComboBox();
            this.outputSelect = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.converBox = new System.Windows.Forms.GroupBox();
            this.conFalse = new System.Windows.Forms.RadioButton();
            this.conTrue = new System.Windows.Forms.RadioButton();
            this.outLab = new System.Windows.Forms.Label();
            this.inLab = new System.Windows.Forms.Label();
            this.converBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonConvert
            // 
            this.buttonConvert.Enabled = false;
            this.buttonConvert.Location = new System.Drawing.Point(180, 187);
            this.buttonConvert.Name = "buttonConvert";
            this.buttonConvert.Size = new System.Drawing.Size(72, 49);
            this.buttonConvert.TabIndex = 0;
            this.buttonConvert.Text = "Convert";
            this.buttonConvert.UseVisualStyleBackColor = true;
            this.buttonConvert.Click += new System.EventHandler(this.buttonConvert_Click);
            // 
            // inputBox
            // 
            this.inputBox.Enabled = false;
            this.inputBox.Location = new System.Drawing.Point(59, 204);
            this.inputBox.Name = "inputBox";
            this.inputBox.Size = new System.Drawing.Size(115, 22);
            this.inputBox.TabIndex = 1;
            this.inputBox.TextChanged += new System.EventHandler(this.inputBox_TextChanged);
            // 
            // outputBox
            // 
            this.outputBox.Enabled = false;
            this.outputBox.Location = new System.Drawing.Point(305, 204);
            this.outputBox.Name = "outputBox";
            this.outputBox.Size = new System.Drawing.Size(116, 22);
            this.outputBox.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(56, 180);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Amount I have";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(302, 180);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(96, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Amount I want";
            // 
            // inputSelect
            // 
            this.inputSelect.FormattingEnabled = true;
            this.inputSelect.Items.AddRange(new object[] {
            "AUD (Australia)",
            "CYN (China)",
            "DKK (Denmark)",
            "EUR (Europe)",
            "INR (India)",
            "NZD (New Zealand)",
            "AED (United Arab Emirates)",
            "GPB (United Kingdom)",
            "USD (United States)",
            "VND (Vietnam)"});
            this.inputSelect.Location = new System.Drawing.Point(25, 75);
            this.inputSelect.Name = "inputSelect";
            this.inputSelect.Size = new System.Drawing.Size(127, 24);
            this.inputSelect.TabIndex = 5;
            this.inputSelect.SelectedIndexChanged += new System.EventHandler(this.inputSelect_SelectedIndexChanged);
            // 
            // outputSelect
            // 
            this.outputSelect.Enabled = false;
            this.outputSelect.FormattingEnabled = true;
            this.outputSelect.Items.AddRange(new object[] {
            "AUD (Australia)",
            "CYN (China)",
            "DKK (Denmark)",
            "EUR (Europe)",
            "INR (India)",
            "NZD (New Zealand)",
            "AED (United Arab Emirates)",
            "GPB (United Kingdom)",
            "USD (United States)",
            "VND (Vietnam)"});
            this.outputSelect.Location = new System.Drawing.Point(293, 75);
            this.outputSelect.Name = "outputSelect";
            this.outputSelect.Size = new System.Drawing.Size(128, 24);
            this.outputSelect.TabIndex = 6;
            this.outputSelect.SelectedIndexChanged += new System.EventHandler(this.outputSelect_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 52);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(107, 17);
            this.label3.TabIndex = 7;
            this.label3.Text = "Currency I have";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(293, 52);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(105, 17);
            this.label4.TabIndex = 8;
            this.label4.Text = "Currency I want";
            // 
            // converBox
            // 
            this.converBox.Controls.Add(this.conFalse);
            this.converBox.Controls.Add(this.conTrue);
            this.converBox.Location = new System.Drawing.Point(114, 250);
            this.converBox.Name = "converBox";
            this.converBox.Size = new System.Drawing.Size(200, 100);
            this.converBox.TabIndex = 9;
            this.converBox.TabStop = false;
            this.converBox.Text = "Another Conversion?";
            this.converBox.Visible = false;
            this.converBox.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // conFalse
            // 
            this.conFalse.AutoSize = true;
            this.conFalse.Location = new System.Drawing.Point(18, 60);
            this.conFalse.Name = "conFalse";
            this.conFalse.Size = new System.Drawing.Size(50, 21);
            this.conFalse.TabIndex = 1;
            this.conFalse.TabStop = true;
            this.conFalse.Text = "NO";
            this.conFalse.UseVisualStyleBackColor = true;
            this.conFalse.CheckedChanged += new System.EventHandler(this.conFalse_CheckedChanged);
            // 
            // conTrue
            // 
            this.conTrue.AutoSize = true;
            this.conTrue.Location = new System.Drawing.Point(18, 33);
            this.conTrue.Name = "conTrue";
            this.conTrue.Size = new System.Drawing.Size(56, 21);
            this.conTrue.TabIndex = 0;
            this.conTrue.TabStop = true;
            this.conTrue.Text = "YES";
            this.conTrue.UseVisualStyleBackColor = true;
            this.conTrue.CheckedChanged += new System.EventHandler(this.conTrue_CheckedChanged);
            // 
            // outLab
            // 
            this.outLab.AutoSize = true;
            this.outLab.Location = new System.Drawing.Point(258, 204);
            this.outLab.Name = "outLab";
            this.outLab.Size = new System.Drawing.Size(12, 17);
            this.outLab.TabIndex = 10;
            this.outLab.Text = " ";
            // 
            // inLab
            // 
            this.inLab.AutoSize = true;
            this.inLab.Location = new System.Drawing.Point(12, 206);
            this.inLab.Name = "inLab";
            this.inLab.Size = new System.Drawing.Size(12, 17);
            this.inLab.TabIndex = 11;
            this.inLab.Text = " ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(447, 353);
            this.Controls.Add(this.inLab);
            this.Controls.Add(this.outLab);
            this.Controls.Add(this.converBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.outputSelect);
            this.Controls.Add(this.inputSelect);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.outputBox);
            this.Controls.Add(this.inputBox);
            this.Controls.Add(this.buttonConvert);
            this.Name = "Form1";
            this.Text = "Currency Converter";
            this.converBox.ResumeLayout(false);
            this.converBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonConvert;
        private System.Windows.Forms.TextBox inputBox;
        private System.Windows.Forms.TextBox outputBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox inputSelect;
        private System.Windows.Forms.ComboBox outputSelect;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox converBox;
        private System.Windows.Forms.RadioButton conFalse;
        private System.Windows.Forms.RadioButton conTrue;
        private System.Windows.Forms.Label outLab;
        private System.Windows.Forms.Label inLab;

     
    }
}

