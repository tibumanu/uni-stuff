<?php $title='Home | Avatars'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">

    <h1 class="text-4xl font-bold text-center mb-10"> Select what you want to see: </h1>

    <form class="bg-slate-900 rounded-md w-1/2 mx-auto p-5" action="index.php" method="POST">
        <h2 class="text-2xl mb-3">Specify set:</h2>

        <h2 class="text-2xl mb-3">Starting ID:</h2>
        <input type="number" class="w-full bg-slate-700 p-3 rounded-md mb-3" name="id-start" value=""></input>
        <h2 class="text-2xl mb-3">Ending ID:</h2>
        <input type="number" class="w-full bg-slate-700 p-3 rounded-md mb-3" name="id-end" value=""></input>
        <input type="submit" class="w-full h-12 bg-slate-700 hover:bg-slate-600 rounded-md text-white text-lg mt-3" value="Filter">
        <?php
            

        ?>
    </form>

    <a class="text-2xl hover:underline font-bold text-center mt-10" href="index.php"> Or go back by clicking here.. </a>
</main>

<?php include("template/bottom.php");?>