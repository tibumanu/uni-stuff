<?php $title='Edit Article | Avatars'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-1/2 h-full mx-auto flex justify-center flex-col">
<?php
    include('service/database.php');

    $id = $_GET['id'];
    $id = mysqli_real_escape_string($connection, $id);
    $id = htmlspecialchars($id);
    $id = strip_tags($id);
    $id = stripslashes($id);
    $id = trim($id);

    $sql = "SELECT * FROM Avatars WHERE ID = " . $id;

    $result = mysqli_query($connection, $sql);

    if (mysqli_num_rows($result) > 0) {
        while($row = mysqli_fetch_assoc($result)) {
            

            echo '<h1 class="mx-auto text-4xl mb-3 font-bold">Edit Avatar</h1>';

            echo '<form class="flex flex-col pb-6" action="service/edit.php" method="POST">';
                echo '<input type="hidden" name="id" value="' . $row['id'] . '">';

                echo '<label class="text-2xl mb-2" for="name">Name:</label>';
                echo '<input type="text" name="name" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3" value="' . $row['name'] . '">';
                
                echo '<label class="text-2xl mb-2" for="age">Age:</label>';
                echo '<input type="text" name="age" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3" value="' . $row['age'] . '">';
                
                echo '<label class="text-2xl mb-2" for="rang">Rang:</label>';
                echo '<input type="text" name="rang" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3" value="' . $row['rang'] . '">';
                
                echo '<label class="text-2xl mb-2" for="powers">Powers:</label>';
                echo '<textarea class="bg-slate-800 rounded-md border border-slate-600 hover:border-white p-3 mb-4" name="powers">' . $row['powers'] . '</textarea>';
                
                echo '<input type="submit" class="hover:cursor-pointer bg-slate-800 mx-auto w-1/2 p-3 rounded-md active:bg-slate-600 border border-slate-600 hover:border-white" value="Submit Changes">';
            echo '</form>';
        }
    }
    else {
        include("component/404.php");
    }
?>
</main>

<?php include("template/bottom.php");?>