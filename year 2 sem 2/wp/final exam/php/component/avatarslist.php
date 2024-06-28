<?php
    include('service/database.php');

    $sql = "SELECT * FROM Avatars";

    $result = mysqli_query($connection, $sql);

    if (mysqli_num_rows($result) > 0) {
        while($row = mysqli_fetch_assoc($result)) {
        
            echo '<div class="flex flex-col border-b border-gray-400 py-4">';
            echo '<div class="flex">';
            echo '<a class="text-2xl hover:underline font-bold" href="avatars.php?id=' . $row['id'] . '">' . $row['name'] . '</a>';
            echo '<div class="text-sm my-auto ml-2"> having rank ' . $row['age'] . '</div>';
            echo '<div class="ml-auto text-sm">' . $row['powers'] . '</div>';
            echo '</div>';
            echo '</div>';
        }
    } else {
        echo '<div class="text-2xl text-center"> No Avatars available. </div>';
    }
?>