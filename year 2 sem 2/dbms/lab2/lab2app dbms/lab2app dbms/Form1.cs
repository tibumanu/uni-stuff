using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Collections.Specialized;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;
using System.Data.Common;
using System.Reflection;

namespace lab2app_dbms
{
    public partial class Form1 : Form
    {
        // set up variables
        SqlConnection connectionString;
        DataSet dataset = new DataSet();
        SqlDataAdapter daParent, daChild;
        BindingSource bsParent = new BindingSource();
        BindingSource bsChild = new BindingSource();
        SqlCommandBuilder sqlCommandBuilder;
        DataRelation dataRelation;
     

        public Form1()
        {
            InitializeComponent();
        }

        private string getConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["connn"].ConnectionString.ToString();

        }

        private string getParentTableName()
        {
            return ConfigurationManager.AppSettings["ParentTableName"].ToString();
        }

        private string getChildTableName()
        {
            return ConfigurationManager.AppSettings["ChildTableName"].ToString();
        }

        private string getChildByParentSelectQuery()
        {
            return ConfigurationManager.AppSettings["ChildByParentSelectQuery"].ToString();
        }

        private string getParentSelectQuery()
        {
            return ConfigurationManager.AppSettings["ParentSelectQuery"].ToString();
        }

        private string getChildSelectQuery()
        {
            return ConfigurationManager.AppSettings["ChildSelectQuery"].ToString();
        }

        private string getForeignKey()
        {
            return ConfigurationManager.AppSettings["ForeignKey"].ToString();
        }

        private string getReferencedKey()
        {
            return ConfigurationManager.AppSettings["ReferencedKey"].ToString();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if(dataGridView1.SelectedRows.Count > 0)
            {
                string selected = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                string selectQuery = getChildByParentSelectQuery() + selected;
                daChild.SelectCommand = new SqlCommand(selectQuery, connectionString);
            }else{
                MessageBox.Show("Please select a row");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            connectionString = new SqlConnection(getConnectionString());
            //connectionString.Open();
            dataset = new DataSet();

            daParent = new SqlDataAdapter(getParentSelectQuery(), connectionString);
            daParent.Fill(dataset, getParentTableName());

            daChild = new SqlDataAdapter(getChildSelectQuery(), connectionString);
            daChild.Fill(dataset, getChildTableName());

            sqlCommandBuilder = new SqlCommandBuilder(daChild);

            DataColumn referenceId = dataset.Tables[getParentTableName()].Columns[getReferencedKey()];
            DataColumn foreignKey = dataset.Tables[getChildTableName()].Columns[getForeignKey()];

            dataRelation = new DataRelation("FK_ParentChild", referenceId, foreignKey);
            dataset.Relations.Add(dataRelation);


            bsParent.DataSource = dataset;
            bsParent.DataMember = getParentTableName();

            bsChild.DataSource = bsParent;
            bsChild.DataMember = "FK_ParentChild";

            dataGridView1.DataSource = bsParent;
            dataGridView2.DataSource = bsChild;

            // parent table shouldn't be available for editing
            dataGridView1.ReadOnly = true;
            dataGridView2.ReadOnly = false;
            // and neither should the user be able to enter new rows
            dataGridView1.AllowUserToAddRows = false;
            dataGridView2.AllowUserToAddRows = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            daChild.Update(dataset, getChildTableName());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataset.Tables[getChildTableName()].Clear();
            dataset.Tables[getParentTableName()].Clear();
            daParent.Fill(dataset, getParentTableName());
            daChild.Fill(dataset, getChildTableName());
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            ;
        }
    }
}
