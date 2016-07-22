<?php

    // configuration
    require("../includes/config.php");

    // ckecks database for stock
    $symbols = CS50::query("SELECT `symbol` FROM `portfolios` WHERE `id`= ? LIMIT 0, 30",$_SESSION["id"]);
    // testing to see qery
    //var_dump($symbols);

        // checks if user has no stock
        if (count($symbols) == 0)
        {
            // apologize if user has no stock to sell
            apologize("Nothing to sell.");
        }

            // iterating through array a
            foreach ($symbols as $symbol)
            {
                // assigning array value to new array
                $stocks[] = ["sellsymbol" => $symbol["symbol"]];

                //testing again to see what is in array
                //print_r($stocks);
            }

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
            // renders form to proceed
            render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);

            render("sell.php", ["stocks" => $stocks]);

    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {

        //foreach ($stocks as $stock)
        //$stocks[] = $stock["sellsymbol"];
        // checks for what was submitted
        //var_dump($_POST["symbol"] == 'symbol');
        //var_dump($_POST["symbol"]);

         if ($_POST["symbol"] == 'symbol')
         {
             apologize("You must select a stock to sell.");
         }

         else
         {


            // lookup user's shares of stock being sold
            $shares = CS50::query("SELECT `shares` FROM `portfolios` WHERE `symbol`= ? ", $_POST["symbol"]);
            // checks for what was submitted
            //var_dump($shares);

            // lookup stock current details
            $stock_details = lookup($_POST["symbol"]);

            // Number of shares owned
            $number_stock = $shares[0]["shares"];

            // current price of stock
            $price = number_format(floatval($stock_details["price"]), 2);

            // current wealth of stock
            $value = $number_stock*$stock_details["price"];

            // updating user's cash, history and portfolio
            $cash = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
            $history = CS50::query("INSERT INTO history (id, transaction, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?, Now())", $_SESSION["id"], 0, $stock_details["symbol"], $shares, $price);
            //var_dump($shares);
            $delete = CS50::query("DELETE FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $stock_details["symbol"]);

            // error checking
            if ($cash && $history && $delete === false)
                apologize("Error processing transaction. Please try again.");
            $_SESSION["cash"] += $value;


         }
         // redirects to portfolio
        // redirect("/");
    }

?>