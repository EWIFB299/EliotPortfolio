namespace Gui_Games {
    partial class Start_Game_Form {
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
            this.components = new System.ComponentModel.Container();
            this.ChooseGameLabel = new System.Windows.Forms.Label();
            this.ChooseGameComboBox = new System.Windows.Forms.ComboBox();
            this.StartGameButton = new System.Windows.Forms.Button();
            this.ExitGameButton = new System.Windows.Forms.Button();
            this.GameChoiceTip = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // ChooseGameLabel
            // 
            this.ChooseGameLabel.AutoSize = true;
            this.ChooseGameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ChooseGameLabel.Location = new System.Drawing.Point(47, 38);
            this.ChooseGameLabel.Name = "ChooseGameLabel";
            this.ChooseGameLabel.Size = new System.Drawing.Size(176, 20);
            this.ChooseGameLabel.TabIndex = 1;
            this.ChooseGameLabel.Text = "Choose a Game to Play";
            this.ChooseGameLabel.Click += new System.EventHandler(this.ChooseGameLabel_Click);
            // 
            // ChooseGameComboBox
            // 
            this.ChooseGameComboBox.FormattingEnabled = true;
            this.ChooseGameComboBox.Items.AddRange(new object[] {
            "Crazy Eights",
            "Solitaire"});
            this.ChooseGameComboBox.Location = new System.Drawing.Point(51, 72);
            this.ChooseGameComboBox.Name = "ChooseGameComboBox";
            this.ChooseGameComboBox.Size = new System.Drawing.Size(225, 21);
            this.ChooseGameComboBox.TabIndex = 2;
            this.GameChoiceTip.SetToolTip(this.ChooseGameComboBox, "Must select one of these games");
            this.ChooseGameComboBox.SelectedIndexChanged += new System.EventHandler(this.ChooseGameComboBox_SelectedIndexChanged);
            // 
            // StartGameButton
            // 
            this.StartGameButton.Enabled = false;
            this.StartGameButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartGameButton.Location = new System.Drawing.Point(120, 132);
            this.StartGameButton.Name = "StartGameButton";
            this.StartGameButton.Size = new System.Drawing.Size(103, 35);
            this.StartGameButton.TabIndex = 3;
            this.StartGameButton.Text = "Start";
            this.StartGameButton.UseVisualStyleBackColor = true;
            this.StartGameButton.Click += new System.EventHandler(this.StartGameButton_Click);
            // 
            // ExitGameButton
            // 
            this.ExitGameButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ExitGameButton.Location = new System.Drawing.Point(120, 186);
            this.ExitGameButton.Name = "ExitGameButton";
            this.ExitGameButton.Size = new System.Drawing.Size(103, 33);
            this.ExitGameButton.TabIndex = 4;
            this.ExitGameButton.Text = "Exit";
            this.ExitGameButton.UseVisualStyleBackColor = true;
            this.ExitGameButton.Click += new System.EventHandler(this.ExitGameButton_Click);
            // 
            // Start_Game_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 262);
            this.Controls.Add(this.ExitGameButton);
            this.Controls.Add(this.StartGameButton);
            this.Controls.Add(this.ChooseGameComboBox);
            this.Controls.Add(this.ChooseGameLabel);
            this.Name = "Start_Game_Form";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Which Game To Play";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label ChooseGameLabel;
        private System.Windows.Forms.ComboBox ChooseGameComboBox;
        private System.Windows.Forms.Button StartGameButton;
        private System.Windows.Forms.Button ExitGameButton;
        private System.Windows.Forms.ToolTip GameChoiceTip;
    }
}

