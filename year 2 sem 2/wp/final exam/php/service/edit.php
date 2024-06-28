<?php
    include('database.php');

    $userid = $_SESSION["exam_userID"];
    $userid = mysqli_real_escape_string($connection, $userid);
    $userid = htmlspecialchars($userid);
    $userid = strip_tags($userid);


    $id = $_POST['id'];
    $id = mysqli_real_escape_string($connection, $id);
    $id = htmlspecialchars($id);
    $id = strip_tags($id);
    $id = stripslashes($id);
    $id = trim($id);

    $name = $_POST['name'];
    $name = mysqli_real_escape_string($connection, $name);
    $name = htmlspecialchars($name);
    $name = strip_tags($name);
    $name = stripslashes($name);
    $name = trim($name);

    $age = $_POST['age'];
    $age = mysqli_real_escape_string($connection, $age);
    $age = htmlspecialchars($age);
    $age = strip_tags($age);
    $age = stripslashes($age);
    $age = trim($age);

    $powers = $_POST['powers'];
    $powers = mysqli_real_escape_string($connection, $powers);
    $powers = htmlspecialchars($powers);
    $powers = strip_tags($powers);
    $powers = stripslashes($powers);
    $powers = trim($powers);

    $rang = $_POST['rang'];
    $rang = mysqli_real_escape_string($connection, $rang);
    $rang = htmlspecialchars($rang);
    $rang = strip_tags($rang);
    $rang = stripslashes($rang);
    $rang = trim($rang);

    $date = date('Y-m-d');


    // $sql = "UPage Avatars SET name = '" . $name . "', age = '" . $age . "', powers = '" . $powers . "', rang = '" . $rang . "' WHERE id = " . $id;
    // doesn't work
    $sql = "UPDATE Avatars SET name = '$name', age = '$age', powers = '$powers', rang = '$rang' WHERE id = " . $id;
    $log = "INSERT INTO Logs (date, userid, action) VALUES ('$date', $userid, 'Edited avatar $name')";


    try {
        mysqli_query($connection, $sql);
        header('Location: ../avatars.php?id=' . $id);
    } catch (Exception $e) {
        $error=mysqli_error($connection);
        $backlink='../avatars.php?id=' . $id;
        include('../error.php');
    }
?>