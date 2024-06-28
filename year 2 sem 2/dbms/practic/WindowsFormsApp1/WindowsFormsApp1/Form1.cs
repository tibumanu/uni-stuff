using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        SqlConnection connectionString = new SqlConnection("Data Source = DESKTOP-LF9HLFA\\SQLEXPRESS; Initial Catalog = whatever; Integrated Security = true");
        DataSet ds = new DataSet();
        SqlDataAdapter daParent, daChild;
        BindingSource bsParent = new BindingSource();
        BindingSource bsChild = new BindingSource();
        SqlCommandBuilder commandBuilder;
        DataRelation dataRelation;

        public Form1()
        {
            InitializeComponent();
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            daParent = new SqlDataAdapter("select * from Userr", connectionString);
            daChild = new SqlDataAdapter("select * from Liked_Video", connectionString);

            commandBuilder = new SqlCommandBuilder(daChild);

            daParent.Fill(ds, "Userr");
            daChild.Fill(ds, "Liked_Video");

            dataRelation = new DataRelation("FK_Liked_Video_Userr", ds.Tables["Userr"].Columns["id"], ds.Tables["Liked_Video"].Columns["userid"]);
            ds.Relations.Add(dataRelation);

            bsParent = new BindingSource();
            bsChild = new BindingSource();

            bsParent.DataSource = ds;
            bsChild.DataSource = bsParent;

            bsParent.DataMember = "Userr";
            bsChild.DataMember = "FK_Liked_Video_Userr";

            dgvUser.DataSource = bsParent;
            dgvLiked.DataSource = bsChild;

            dgvUser.ReadOnly = true;
            dgvUser.AllowUserToAddRows = false;
            dgvUser.AllowUserToDeleteRows = false;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {

            ds.Tables["Liked_Video"].Clear();
            ds.Tables["Userr"].Clear();
            daParent.Fill(ds, "Userr");
            daChild.Fill(ds, "Liked_Video");
        }


        private void button1_Click(object sender, EventArgs e)
        {
            daChild.Update(ds, "Liked_Video");
        }
    }
}
