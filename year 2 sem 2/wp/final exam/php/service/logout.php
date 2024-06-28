<?php
include('database.php');

$_SESSION["exam_loggedin"] = false;
$_SESSION["exam_username"] = "";
$_SESSION["exam_userID"] = 0;

header("Location: ../index.php");
exit;
?>
