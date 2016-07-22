<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // promt to enter input
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        
        // looks for symbol
        $stock = lookup($_POST["symbol"]);
        
        if ($stock == false)
        {
            apologize("symbol not found");
        }
        else
            render("quote_result.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
    }

?>