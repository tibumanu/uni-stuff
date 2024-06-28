<header class="flex w-full py-4 border-b px-6 shadow-lg">
    <div class="my-auto">
        <a href="index.php" class="text-4xl"> Avatars </a>
    </div>

    <?php
    if (isset($_SESSION['exam_loggedin']) && $_SESSION['exam_loggedin'] == true) {
        echo '<div class="my-auto ml-auto">
            <a class="text-2xl text-emerald-400 my-auto hover:underline" href="write.php"> Add an avatar </a>
        </div>';
    }
?>

    <div class="ml-auto"></div>

    <div class="my-auto">
        <?php
            if (isset($_SESSION['exam_loggedin']) && $_SESSION['exam_loggedin'] == true) {
                echo '<a class="text-2xl ml-6 hover:underline" href="service/logout.php"> Log Out </a>';
            }
        ?>
        <a class="ml-6 text-2xl hover:underline" href="task.php"> help </a>
    </div>
</header>