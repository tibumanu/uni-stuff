<?php
    include('database.php');

    $userid = $_SESSION["exam_userID"];
    $userid = mysqli_real_escape_string($connection, $userid);
    $userid = htmlspecialchars($userid);
    $userid = strip_tags($userid);

    $name = $_POST['name'];
    $age = $_POST['age'];
    $powers = $_POST['powers'];
    $rang = $_POST['rang'];

    $name = mysqli_real_escape_string($connection, $name);
    $age = mysqli_real_escape_string($connection, $age);
    $powers = mysqli_real_escape_string($connection, $powers);
    $rang = mysqli_real_escape_string($connection, $rang);
    

    $date = date('Y-m-d');

    $name = htmlspecialchars($name);
    $age = htmlspecialchars($age);
    $powers = htmlspecialchars($powers);
    $rang = htmlspecialchars($rang);

    $name = strip_tags($name);
    $age = strip_tags($age);
    $powers = strip_tags($powers);
    $rang = strip_tags($rang);

    $name = stripslashes($name);
    $age = stripslashes($age);
    $powers = stripslashes($powers);
    $rang = stripslashes($rang);

    $name = trim($name);
    $age = trim($age);
    $powers = trim($powers);
    $rang = trim($rang);
    
    $sql = "INSERT INTO Avatars (name, age, powers, rang) VALUES ('$name', '$age', '$powers', '$rang')";
    $log = "INSERT INTO Logs (date, userid, text) VALUES ('$date', $userid, 'Added avatar named $name')";

    try {
        mysqli_query($connection, $sql);
        mysqli_query($connection, $log);
        header('Location: ../index.php');
    } catch (Exception $e) {
        $error=mysqli_error($connection);
        $backlink='../index.php';
        include('../error.php');
    }
?>