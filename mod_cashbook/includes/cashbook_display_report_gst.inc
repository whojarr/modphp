<?php
	if ($_REQUEST['orderby'] < ' ') {
		$orderby = "ORDER BY transaction_date";
	}
	else {
		$orderby = "ORDER BY ".$_REQUEST['orderby'];
	}

	if ($_REQUEST['account_id'] < ' ') {
		$_REQUEST['account_id'] = '%';
	}
?>

<div class="groupBorder">

<div class="groupHeader"><?php echo $filter_account_name ?> GST Report </div>

<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=id" >id	</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=type_id" >Transaction Type</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=cashbook_accounts.name" >Account</a></td>
		<td align="center">Notes</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_entered" >Entered</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=transaction_date" >Transaction Date</a></td>
		<td align="center">GST Rate</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_inclusive" >Sales</a></td>
		<td align="center">GST</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_inclusive" >Sales Incl</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_inclusive" >Purchases</a></td>
		<td align="center">GST</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_inclusive" >Purchases Incl</a></td>
		
	</tr>
<?php
	
	$from_date = $_REQUEST['from_yy']."-".$_REQUEST['from_mm']."-".$_REQUEST['from_dd'];
	$to_date = $_REQUEST['to_yy']."-".$_REQUEST['to_mm']."-".$_REQUEST['to_dd'];
	$transactionresults = mysql_query("
		SELECT cashbook.id,
		date_format(cashbook.date_entered, '%d-%m-%Y') AS date_in,
		date_format(cashbook.date_modified, '%d-%m-%Y') AS date_up,
		date_format(cashbook.transaction_date, '%d-%m-%Y') AS date_trans,
		cashbook_accounts.name AS account_name,
		cashbook_types.name AS type_name,
		round(if (value_exclusive <> 0.00, value_exclusive*gst_rate,value_inclusive/9),2) AS gst,
		if (value_exclusive > 0.00,value_exclusive,IF(value_inclusive > 0.00,ROUND(IF(gst_rate = 0.125,value_inclusive - (value_inclusive/9),value_inclusive - (value_inclusive*(3/23))),2),'')) AS value_sale,
		IF(cashbook.gst > 0.00,cashbook.gst,'') AS gst_sale,
		if (value_inclusive > 0.00,value_inclusive,'') AS value_inclusive_sale,
		if (value_exclusive < 0.00,value_exclusive,IF(value_inclusive < 0.00,ROUND(IF(gst_rate = 0.125,value_inclusive - (value_inclusive/9),value_inclusive - (value_inclusive*(3/23))),2),'')) AS value_purchase,
		IF(cashbook.gst < 0.00,cashbook.gst,'') AS gst_purchase,
		if (value_inclusive < 0.00,value_inclusive,IF(value_exclusive < 0.00,ROUND(value_exclusive * (1 + gst_rate),2),'')) AS value_inclusive_purchase,
		cashbook.*, 
		users.gecos AS user_gecos
		from cashbook 
		left join cashbook_accounts on cashbook_accounts.id = cashbook.account_id
		left join cashbook_types on cashbook_types.id = cashbook.type_id
		left join users on users.uid = cashbook.owner_id
		where cashbook.owner_id like '{$_REQUEST['owner_id']}' 
		and cashbook.account_id like '{$_REQUEST['account_id']}'
		and cashbook.account_id IN ($gst_ids) 
		and cashbook.status like '{$_REQUEST['status']}' 
		and cashbook.transaction_date >= '{$from_date}' 
		and cashbook.transaction_date <= '{$to_date}' 
		$orderby 	
		")	or die("Query failed: " . mysql_error());
		
	$rowcount = 1;
	if ($transactionresultsarray = mysql_fetch_array($transactionresults)) {
		do {
			if (fmod_round ($rowcount++,2) == 0) {
				echo "<tr class=\"even\">";
			}
			else {
				echo "<tr class=\"odd\">";
			}	
			?>			
				<td align="center"><?php echo $transactionresultsarray['id'] ?></td>
				<td><?php echo $transactionresultsarray['type_name'] ?></td>
				<td><?php echo $transactionresultsarray['account_name'] ?></td>
				<td><?php echo $transactionresultsarray['notes'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['date_in'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['date_trans'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['gst_rate'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['value_sale'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['gst_sale'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['value_inclusive_sale'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['value_purchase'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['gst_purchase'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['value_inclusive_purchase'] ?></td>
			</tr>
			<?php
		}
		while ($transactionresultsarray = mysql_fetch_array($transactionresults));
	
		$sumresults_sales = mysql_query("
			SELECT sum(value_exclusive) AS sum_value_exclusive,
			ROUND(SUM(cashbook.gst),2) AS sum_gst,
			sum(value_inclusive) AS sum_value_inclusive
			FROM cashbook 
			LEFT JOIN cashbook_accounts ON cashbook_accounts.id = cashbook.account_id
			LEFT JOIN cashbook_types ON cashbook_types.id = cashbook.type_id
			LEFT JOIN users ON users.uid = cashbook.owner_id
			WHERE (cashbook.value_exclusive > 0.00 
			OR cashbook.value_inclusive > 0.00)
			AND cashbook.owner_id like '{$_REQUEST['owner_id']}' 
			AND cashbook.account_id like '{$_REQUEST['account_id']}'
			AND cashbook.account_id IN ($gst_ids) 
			AND cashbook.status like '{$_REQUEST['status']}' 
			AND cashbook.transaction_date >= '{$from_date}' 
			AND cashbook.transaction_date <= '{$to_date}' 
			$orderby 	
			")	or die("Query failed: " . mysql_error());
	
		if ($sumresultsarray_sales = mysql_fetch_array($sumresults_sales)) {
			do {
				$sum_exclusive_sales = $sumresultsarray_sales['sum_value_exclusive'];
				$sum_gst_sales = $sumresultsarray_sales['sum_gst'];
				$sum_inclusive_sales = $sumresultsarray_sales['sum_value_inclusive'];
			}
			while ($sumresultsarray_sales = mysql_fetch_array($sumresults_sales));
		}
		
		$sumresults_purchases = mysql_query("
			SELECT sum(value_exclusive) AS sum_value_exclusive,
			round(sum(cashbook.gst),2) AS sum_gst,
			sum(value_inclusive) AS sum_value_inclusive
			FROM cashbook 
			LEFT JOIN cashbook_accounts ON cashbook_accounts.id = cashbook.account_id
			LEFT JOIN cashbook_types ON cashbook_types.id = cashbook.type_id
			LEFT JOIN users ON users.uid = cashbook.owner_id
			WHERE (cashbook.value_exclusive < 0.00 
			OR cashbook.value_inclusive < 0.00)
			AND cashbook.owner_id like '{$_REQUEST['owner_id']}' 
			AND cashbook.account_id like '{$_REQUEST['account_id']}'
			AND cashbook.account_id IN ($gst_ids) 
			AND cashbook.status like '{$_REQUEST['status']}' 
			AND cashbook.transaction_date >= '{$from_date}' 
			AND cashbook.transaction_date <= '{$to_date}' 
			$orderby 	
			")	or die("Query failed: " . mysql_error());
	
		if ($sumresultsarray_purchases = mysql_fetch_array($sumresults_purchases)) {
			do {
				$sum_exclusive_purchases = $sumresultsarray_purchases['sum_value_exclusive'];
				$sum_gst_purchases = $sumresultsarray_purchases['sum_gst'];
				$sum_inclusive_purchases = $sumresultsarray_purchases['sum_value_inclusive'];
			}
			while ($sumresultsarray_purchases = mysql_fetch_array($sumresults_purchases));
		}
		
		?>
			<tr>
				<td align="right" colspan="13"><hr/></td>
			</tr>	
			<tr>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td align="center"><b>Totals</b></td>
				<td align="center">Sales</td>
				<td align="center">GST</td>
				<td align="center">Sales Incl</td>
				<td align="center">Purchases</td>
				<td align="center">GST</td>
				<td align="center">Purchases Incl</td>
			</tr>			
			<tr>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td align="center"></td>
				<td align="center"><?php echo $sum_exclusive_sales ?></td>
				<td align="center"><?php echo $sum_gst_sales ?></td>
				<td align="center"><?php echo $sum_inclusive_sales ?></td>
				<td align="center"><?php echo $sum_exclusive_purchases ?></td>
				<td align="center"><?php echo $sum_gst_purchases ?></td>
				<td align="center"><?php echo $sum_inclusive_purchases ?></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
			</tr>
			<tr>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td></td>
				<td align="center"><b>GST To Pay</b></td>
				<td align="center"><?php echo round($sum_gst_sales + $sum_gst_purchases,2); ?></td>
				<td align="center"></td>
				<td align="center"></td>		
				<td align="center"></td>		
			</tr>			
			
	<?php	
		
	}	
	else {
		?>
		<tr>
			<td colspan="11" align="center"">
				<br><br>No Results from your search<br>
				<br><br>
			</td>
		</tr>
		<?php
	}
?>
</table>

</div>
