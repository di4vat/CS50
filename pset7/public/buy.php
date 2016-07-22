<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {


        // promt to enter input(symbol)
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }

        // promt to enter input(n# of shares)
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify the number of shares.");
        }

        // promt to enter a valid number of shares
        else if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares. Use non-negative whole numbers only");
        }

        // looks for symbol
        $stock = lookup($_POST["symbol"]);


        // check for a valid stock
        if ($stock == false)
        {
            apologize("Symbol not found. Enter a valid stock symbol.");
        }

         // convert symbol to uppercase
        $symbol = strtoupper($_POST["symbol"]);
        //var_dump($symbol);

        // calculate stock value
        $value = $stock["price"] * $_POST["shares"];

        // query user's available funds
        $users = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        //var_dump($users[0]["cash"]);

        //print($value);
         // check for avialability of funds
             if ($users[0]["cash"] < $value)
                {
                    apologize("Insufficient funds.");
                }

            else
            {

                CS50::query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $_POST["shares"]);
                CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $value, $_SESSION["id"]);
                CS50::query("INSERT INTO history (id, transaction, symbol, shares, price, time) VALUES(?, 1, ?, ?, ?, Now())", $_SESSION["id"], $symbol, $_POST["shares"], number_format($stock["price"], 2));
                $_SESSION["cash"] -= $value;
            }

    // redirect to portfolio when done
    redirect("/");

    }


?>