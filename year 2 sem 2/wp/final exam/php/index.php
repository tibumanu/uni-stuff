<?php $title='Home | Avatars'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">
<?php
    if (isset($_SESSION['exam_loggedin']) && $_SESSION['exam_loggedin'] == true) {
        if((!isset($_POST["id-start"]) && !isset($_POST["id-end"])))
        {
            echo "<div class='flex justify-center items-center w-full h-12 bg-slate-900 shadow-sm rounded-t-md text-white text-lg font-bold'>Welcome, " . $_SESSION['exam_username'] . ". Here are the Avatars:" . "</div>";
            echo "<a class='w-full hover:underline h-12 bg-slate-900 rounded-b-md shadow-sm text-white text-lg px-4 mb-3' href='filter.php'>Filter these avatars.</a>";
            include("component/avatarslist.php");
        }
        else {
            include('service/database.php');

            $idStart = $_POST["id-start"];
            $idEnd = $_POST["id-end"];

            if($idStart == "")
                $idStart = 0;
            if($idEnd == "")
                $idEnd = 999999999;

            $sql = "SELECT * FROM Avatars WHERE id BETWEEN $idStart AND $idEnd ORDER BY ID DESC";
        
            $result = mysqli_query($connection, $sql);
        
            if (mysqli_num_rows($result) > 0) {
                while($row = mysqli_fetch_assoc($result)) {
                    echo '<div class="flex flex-col border-b border-gray-400 py-4">';
                    echo '<div class="flex">';
                    echo '<a class="text-2xl hover:underline font-bold" href="Avatars.php?id=' . $row['id'] . '">' . $row['name'] . '</a>';
                    echo '<div class="text-sm my-auto ml-2"> having rank ' . $row['rang'] . '</div>';
                    echo '<div class="ml-auto text-sm">' . $row['powers'] . '</div>';
                    echo '<div class="ml-auto text-sm">' . $row['age'] . 'yo</div>';
                    echo '</div>';
                    echo '</div>';
                    echo '<hr class="border-gray-400">';
                }
            } else {
                echo '<div class="text-2xl text-center"> No Avatars available. </div>';
            }

            echo "<a class='w-full hover:underline text-center text-white text-lg mt-4' href='index.php'>Go back to all Avatars.</a>";
        }
    } else {
        include("component/login.php");
    }
?>
</main>

<?php include("template/bottom.php");?>