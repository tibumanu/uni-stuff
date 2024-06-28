using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        DataSet dataset;
        SqlDataAdapter dataAdapter;
        SqlConnection conn = new SqlConnection("Data Source=DESKTOP-LF9HLFA\\SQLEXPRESS;Initial Catalog = MOONBASE DB; Integrated Security = true");

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'mOONBASE_DBDataSet.Station' table. You can move, or remove it, as needed.
            this.stationTableAdapter.Fill(this.mOONBASE_DBDataSet.Station);
            // TODO: This line of code loads data into the 'mOONBASE_DBDataSet.Task' table. You can move, or remove it, as needed.
            this.taskTableAdapter.Fill(this.mOONBASE_DBDataSet.Task);
            // TODO: This line of code loads data into the 'mOONBASE_DBDataSet.Planet' table. You can move, or remove it, as needed.
            this.planetTableAdapter.Fill(this.mOONBASE_DBDataSet.Planet);
            // TODO: This line of code loads data into the 'mOONBASE_DBDataSet.Human' table. You can move, or remove it, as needed.
            this.humanTableAdapter.Fill(this.mOONBASE_DBDataSet.Human);


        }
        private void clearTextBoxes()
        {
            textBox1.Clear(); textBox2.Clear();
            textBox3.Clear();
            textBox4.Clear();
            textBox5.Clear();
            textBox6.Clear();
            textBox7.Clear();
            textBox8.Clear();
            textBox9.Clear();
        }


        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                DataGridViewRow selectedRow = dataGridView3.Rows[e.RowIndex];
                textBox2.Text = selectedRow.Cells[0].Value.ToString();
                textBox3.Text = selectedRow.Cells[1].Value.ToString();
                textBox4.Text = selectedRow.Cells[2].Value.ToString();
                textBox5.Text = selectedRow.Cells[3].Value.ToString();
                textBox6.Text = selectedRow.Cells[4].Value.ToString();
                textBox7.Text = selectedRow.Cells[5].Value.ToString();
                textBox8.Text = selectedRow.Cells[6].Value.ToString();
                textBox1.Text = selectedRow.Cells[7].Value.ToString();
                textBox9.Text = selectedRow.Cells[8].Value.ToString();

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {

            if (textBox2.Text != "" && textBox1.Text != "")
            {
                try
                {


                    string updateCommand = "update Human set height = @height, firstName = @FN, lastName = @LN," +
                        " stationID = @SID, buildingID = @BID, teamID = @TID, coordTaskID = @CTID, " +
                        "dob = @DOB where id = @id";
                    SqlCommand pls = new SqlCommand(updateCommand, conn);
                    dataAdapter.UpdateCommand = pls;
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@id", textBox2.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@height", textBox9.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@FN", textBox3.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@LN", textBox4.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@SID", textBox5.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@BID", textBox6.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@TID", textBox7.Text);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@CTID", textBox8.Text);
                    var date = DateTime.ParseExact(textBox1.Text, "dd.MM.yyyy hh:mm:ss", CultureInfo.InvariantCulture);
                    dataAdapter.UpdateCommand.Parameters.AddWithValue("@DOB", date);

                    conn.Open();

                    dataAdapter.UpdateCommand.ExecuteNonQuery();
                    MessageBox.Show("Data updated successfully.");
                    string selectCommand = "select * from Human where stationID = @id";
                    dataAdapter.SelectCommand = new SqlCommand(selectCommand, conn);
                    dataAdapter.SelectCommand.Parameters.AddWithValue("@id", textBox5.Text);
                    dataset = new DataSet();
                    dataAdapter.Fill(dataset, "Human");
                    dataGridView3.DataSource = dataset.Tables["Human"];
                    dataGridView3.Update();
                    clearTextBoxes();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
                finally
                {
                    conn.Close();
                }
            }
        }

        private void taskDataGridView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var id = dataGridView1.Rows[e.RowIndex].Cells[0].Value;
            string sqlCommand = "select * from Robot where id=@taskID";
            SqlCommand getHumansByBuilding = new SqlCommand(sqlCommand, conn);
            getHumansByBuilding.Parameters.AddWithValue("@taskID", id);

            DataSet ds = new DataSet();
            SqlDataAdapter dataAd = new SqlDataAdapter(getHumansByBuilding);

            dataAd.Fill(ds, "Task");

            dataGridView3.DataSource = ds.Tables["Task"];
        }

        private void stationDataGridView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var id = stationDataGridView.Rows[e.RowIndex].Cells[0].Value;
            string sqlCommand = "select * from Human where stationID=@stationID";
            SqlCommand getHumansByStation = new SqlCommand(sqlCommand, conn);
            getHumansByStation.Parameters.AddWithValue("@stationID", id);

            DataSet ds = new DataSet();
            dataAdapter = new SqlDataAdapter(getHumansByStation);

            dataAdapter.Fill(ds, "Human");

            dataGridView3.DataSource = ds.Tables["Human"];
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
        private void addButton_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox3.Text != "")
            {
                try
                {
                    string insertCommand = "INSERT INTO Human (id, firstName, lastName, stationID, buildingID, teamID, coordTaskID, dob, height) VALUES (@id, @FN, @LN, @SID, @BID, @TID, @CTID, @DOB, @height)";
                    dataAdapter.InsertCommand = new SqlCommand(insertCommand, conn);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@id", textBox2.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@height", textBox9.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@FN", textBox3.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@LN", textBox4.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@SID", textBox5.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@BID", textBox6.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@TID", textBox7.Text);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@CTID", textBox8.Text);
                    var date = DateTime.ParseExact(textBox1.Text, "dd.MM.yyyy hh:mm:ss", CultureInfo.InvariantCulture);
                    dataAdapter.InsertCommand.Parameters.AddWithValue("@DOB", date);


                    conn.Open();

                    dataAdapter.InsertCommand.ExecuteNonQuery();

                    MessageBox.Show("Data inserted successfully.");


                    string selectCommand = "select * from Human where stationID = @id";
                    dataAdapter.SelectCommand = new SqlCommand(selectCommand, conn);
                    dataAdapter.SelectCommand.Parameters.AddWithValue("@id", textBox5.Text);
                    dataset = new DataSet();
                    dataAdapter.Fill(dataset, "Human");
                    dataGridView3.DataSource = dataset.Tables["Human"];
                    dataGridView3.Update();
                    clearTextBoxes();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
                finally
                {
                    conn.Close();
                }
            }
            else
            {
                MessageBox.Show("Please fill all fields before adding.");
            }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button6_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox3.Text != "")
            {
                try
                {
                    string deleteCommand = "delete from Human where id = @id";
                    dataAdapter.DeleteCommand = new SqlCommand(deleteCommand, conn);
                    dataAdapter.DeleteCommand.Parameters.AddWithValue("@id", textBox2.Text);
                  


                    conn.Open();

                    dataAdapter.DeleteCommand.ExecuteNonQuery();

                    MessageBox.Show("Data inserted successfully.");


                    string selectCommand = "select * from Human where stationID = @id";
                    dataAdapter.SelectCommand = new SqlCommand(selectCommand, conn);
                    dataAdapter.SelectCommand.Parameters.AddWithValue("@id", textBox5.Text);
                    dataset = new DataSet();
                    dataAdapter.Fill(dataset, "Human");
                    dataGridView3.DataSource = dataset.Tables["Human"];
                    dataGridView3.Update();
                    clearTextBoxes();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
                finally
                {
                    conn.Close();
                }
            }
        }
    }
}

