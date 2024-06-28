<?php $title='Add Avatar | Avatars'; include("template/top.php");?>

<main class="w-1/2 h-full mx-auto flex justify-center flex-col">
<?php
    include('service/database.php');

    echo '<h1 class="mx-auto text-4xl mb-3 font-bold">Add Avatar</h1>';

    echo '<form class="flex flex-col pb-6" action="service/add.php" method="POST">';
        echo '<label class="text-2xl mb-2" for="name">Name:</label>';
        echo '<input type="text" name="name" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3">';
        
        
        echo '<label class="text-2xl mb-2" for="age">Age:</label>';
        echo '<input type="number" name="age" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3">';
        echo '<label class="text-2xl mb-2" for="rang">Rank:</label>';
        echo '<input type="number" name="rang" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3">';
        echo '<label class="text-2xl mb-2" for="powers">Powers:</label>';
        echo '<textarea class="bg-slate-800 rounded-md border border-slate-600 hover:border-white p-3 mb-4" name="powers"></textarea>';
        
        echo '<input type="submit" class="hover:cursor-pointer bg-slate-800 mx-auto w-1/2 p-3 rounded-md active:bg-slate-600 border border-slate-600 hover:border-white" value="Submit Avatar">';
    echo '</form>';
?>
</main>

<?php include("template/bottom.php");?>