<?php
include('database.php');

// Retrieve form data.
$username = $_POST['username'];
$password = $_POST['password'];

// Check if not null.
if (empty($username) || empty($password)) {
    die("Authentification failed: Username or password is empty.");
}

// Prevent SQL injection.
$username = mysqli_real_escape_string($connection, $username);
$password = mysqli_real_escape_string($connection, $password);

// Query the database for the user.
$sql = "SELECT * FROM Users WHERE Username = '$username' AND Password = '$password'";

$result = mysqli_query($connection, $sql);  
$row = mysqli_fetch_array($result, MYSQLI_ASSOC);  
$count = mysqli_num_rows($result);  

if ($count == 1) {
    header("Location: ../index.php");
    $_SESSION["exam_loggedin"] = true;  
    $_SESSION["exam_userID"] = $row['id'];
    $_SESSION["exam_username"] = $username;
    exit;
} elseif($count == 0) {
    header("Location: ../index.php");
    $_SESSION["exam_loggedinerror"] = "Username or password is incorrect.";
    exit;
}
elseif($mysqli->error){
    header("Location: ../index.php");
    $_SESSION["exam_loggedinerror"] = $mysqli->error;
    exit;
}
?>
