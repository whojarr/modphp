<?php
	if ($_REQUEST['orderby'] < ' ') {
		$orderby = "ORDER BY transaction_date";
	}
	else {
		$orderby = "ORDER BY ".$_REQUEST['orderby'];
	}

	if (!$_REQUEST['account_id'] <> '') {
		$_REQUEST['account_id'] = '%';
	}
?>

<div class="groupBorder">

<div class="groupHeader"><?php echo $filter_account_name ?> Account Report </div>

<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=id" >id	</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=account_id" >Account</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=type_id" >Transaction Type</a></td>
		<td align="center">Notes</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_entered" >Entered</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=transaction_date" >Transaction Date</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_exclusive" >Value</a></td>		
		<td align="center">GST Rate</td>
		<td align="center">GST</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_inclusive" >Value Incl</a></td>				
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
		cashbook.*, 
		users.gecos AS user_gecos
		from cashbook 
		left join cashbook_accounts on cashbook_accounts.id = cashbook.account_id
		left join cashbook_types on cashbook_types.id = cashbook.type_id
		left join users on users.uid = cashbook.owner_id
		where cashbook.owner_id like '{$_REQUEST['owner_id']}' 
		and cashbook.account_id like '{$_REQUEST['account_id']}' 
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
				<td><?php echo $transactionresultsarray['account_name'] ?></td>
				<td><?php echo $transactionresultsarray['type_name'] ?></td>
				<td><?php echo $transactionresultsarray['notes'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['date_in'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['date_trans'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['value_exclusive'] ?></td>
				<td align="center"><?php if($transactionresultsarray['gst_rate'] <> '0.00') {echo $transactionresultsarray['gst_rate'];} ?></td>
				<td align="center"><?php if($transactionresultsarray['gst_rate'] <> '0.00') {echo $transactionresultsarray['gst'];} ?></td>
				<td align="center"><?php echo $transactionresultsarray['value_inclusive'] ?></td>
			</tr>
			<?php
		}
		while ($transactionresultsarray = mysql_fetch_array($transactionresults));
	
		$sumresults = mysql_query("
			SELECT sum(value_exclusive) AS sum_value_exclusive,
			SUM(cashbook.gst) AS sum_gst,
			sum(value_inclusive) AS sum_value_inclusive
			from cashbook 
			left join cashbook_accounts on cashbook_accounts.id = cashbook.account_id
			left join cashbook_types on cashbook_types.id = cashbook.type_id
			left join users on users.uid = cashbook.owner_id
			where cashbook.owner_id like '{$_REQUEST['owner_id']}' 
			and cashbook.account_id like '{$_REQUEST['account_id']}' 
			and cashbook.status like '{$_REQUEST['status']}' 
			and cashbook.transaction_date >= '{$from_date}' 
			and cashbook.transaction_date <= '{$to_date}' 
			$orderby 	
			")	or die("Query failed: " . mysql_error());
	
		if ($sumresultsarray = mysql_fetch_array($sumresults)) {
			do {
				?>
				<tr>
					<td align="right" colspan="10">=======================================================</td>
				</tr>	
				<tr>
					<td></td>
					<td></td>
					<td></td>
					<td></td>
					<td></td>
					<td></td>
					<td align="center"><?php echo $sumresultsarray['sum_value_exclusive'] ?></td>
					<td></td>
					<td align="center"><?php echo $sumresultsarray['sum_gst'] ?></td>
					<td align="center"><?php echo $sumresultsarray['sum_value_inclusive'] ?></td>
				</tr>
				<?php
			}
			while ($sumresultsarray = mysql_fetch_array($sumresults));
		}
	}	
	else {
		?>
		<tr>
			<td colspan="9" align="center"">
				<br><br>No Results from your search<br>
				<br><br>
			</td>
		</tr>
		<?php
	}
?>
</table>

</div>
