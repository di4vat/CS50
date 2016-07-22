<?php

    // configuration
    require("../includes/config.php");
    $history = CS50::query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    //var_dump($history);


    render("history_form.php", ["title" => "History", "history" => $history]);
?>
