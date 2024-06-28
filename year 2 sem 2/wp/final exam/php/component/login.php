<div class="">
    <h1 class=""> Login </h1>

    <div class="border-b my-3"></div>

    <?php
        if (isset($_SESSION['exam_loggedinerror'])) {
            echo "<div class='bg-red-500 text-white mb-3 p-3 rounded-md'>" . $_SESSION['exam_loggedinerror'] . "</div>";
            unset($_SESSION['exam_loggedinerror']);
        }
    ?>

    <form name="loginform" class="flex justify-center flex-col" method="POST" action="service/connect.php">
        <div class="mb-3">
            <label class="text-xl" for="username">Username:</label>
            <input class="w-full p-3 text-gray-100 bg-gray-700 mb-3" id="username" name="username">
        </div>
        
        <div class="mb-3">
            <label class="text-xl" for="password">Password:</label>
            <input class="w-full p-3 text-gray-100 bg-gray-700 mb-3" id="password" name="password" type="password">
        </div>

        
        <input class="" type="submit" value="Connect">
    </form>
</div>