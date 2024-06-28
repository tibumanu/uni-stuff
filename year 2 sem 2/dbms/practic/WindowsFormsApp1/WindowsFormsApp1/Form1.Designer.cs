namespace WindowsFormsApp1
{
    partial class Form1
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
            this.dgvUser = new System.Windows.Forms.DataGridView();
            this.dgvLiked = new System.Windows.Forms.DataGridView();
            this.Save = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvUser)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvLiked)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvUser
            // 
            this.dgvUser.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvUser.Location = new System.Drawing.Point(73, 24);
            this.dgvUser.Margin = new System.Windows.Forms.Padding(2);
            this.dgvUser.Name = "dgvUser";
            this.dgvUser.RowHeadersWidth = 72;
            this.dgvUser.RowTemplate.Height = 31;
            this.dgvUser.Size = new System.Drawing.Size(401, 280);
            this.dgvUser.TabIndex = 0;
            //this.dgvUser.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // dgvLiked
            // 
            this.dgvLiked.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvLiked.Location = new System.Drawing.Point(531, 24);
            this.dgvLiked.Margin = new System.Windows.Forms.Padding(2);
            this.dgvLiked.Name = "dgvLiked";
            this.dgvLiked.RowHeadersWidth = 72;
            this.dgvLiked.RowTemplate.Height = 31;
            this.dgvLiked.Size = new System.Drawing.Size(401, 280);
            this.dgvLiked.TabIndex = 1;
            // 
            // Save
            // 
            this.Save.Location = new System.Drawing.Point(27, 492);
            this.Save.Margin = new System.Windows.Forms.Padding(2);
            this.Save.Name = "Save";
            this.Save.Size = new System.Drawing.Size(161, 41);
            this.Save.TabIndex = 2;
            this.Save.Text = "save";
            this.Save.UseVisualStyleBackColor = true;
            this.Save.Click += new System.EventHandler(this.button1_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(237, 492);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 41);
            this.button1.TabIndex = 3;
            this.button1.Text = "refresh";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1017, 555);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Save);
            this.Controls.Add(this.dgvLiked);
            this.Controls.Add(this.dgvUser);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvUser)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvLiked)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvUser;
        private System.Windows.Forms.DataGridView dgvLiked;
        private System.Windows.Forms.Button Save;
        private System.Windows.Forms.Button button1;
    }
}

