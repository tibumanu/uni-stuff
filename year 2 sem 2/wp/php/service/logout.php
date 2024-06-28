<?php
include('database.php');

$_SESSION["DumbNews_loggedin"] = false;
$_SESSION["DumbNews_username"] = "";
$_SESSION["DumbNews_elevation"] = 0;
$_SESSION["DumbNews_userID"] = 0;

header("Location: ../index.php");
exit;
?>
