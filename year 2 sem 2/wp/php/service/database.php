<?php
// Database data.
$servername = "localhost";
$username = "root";
$password = "Lasamacoaie123"; 
$dbname = "DumbNews";

// Database connection.
$connection = new mysqli($servername, $username, $password, $dbname);

// Check connection.
if(mysqli_connect_errno()) {  
    die("Failed to connect with MySQL: ". mysqli_connect_error());  
}

@session_start();
?>