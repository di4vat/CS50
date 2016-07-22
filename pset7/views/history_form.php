<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction Type</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>


    <tbody>
    <?php
	    foreach ($history as $transaction)
        {

            $type = $transaction["transaction"];
            if ($type == '1')
            {
                $type = 'BUY';
            }
            else
                $type = 'SELL';
            echo("<tr>");
            echo("<td>" . $type . "</td>");
            echo("<td>" . date('d/m/y, g:i A',strtotime($transaction["time"])) . "</td>");
            echo("<td>" . $transaction["symbol"] . "</td>");
            echo("<td>" . strtoupper($transaction["shares"]) . "</td>");
            echo("<td>$" . number_format($transaction["price"], 2) . "</td>");
            echo("</tr>");
        }
    ?>

<!--
    <tr>
        <td colspan="4">CASH</td>
        <td>$<?//=number_format($cash[0]["cash"], 2)?></td>
    </tr>
-->
    </tbody>

</table>