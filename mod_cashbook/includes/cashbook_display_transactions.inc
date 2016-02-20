<?php
	if ($_REQUEST['orderby'] < ' ') {
		$orderby = "ORDER BY transaction_date";
	}
	else {
		$orderby = "ORDER BY ".$_REQUEST['orderby'];
	}
	
	if ($_REQUEST['status'] == "%") {
		$status = "%25";
	}
	else {
		$status = $_REQUEST['status'];
	}	
	
	if ($_REQUEST['owner_id'] == "%") {
		$owner_id = "%25";
	}
	else {
		$owner_id = $_REQUEST['owner_id'];
	}		

	if ($_REQUEST['account_id'] < ' ') {
		$_REQUEST['account_id'] = '%';
	}
?>

<div class="groupBorder">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=add&p_mode=display">
		<img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right">
	</a>
<div class="groupHeader">Transaction List</div>

<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=id" >id	</a></td>
		<td align="center">Edit</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=account_id" >Account</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=type_id" >Transaction Type</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=user_gecos" >Notes</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=notes" >Owner</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=employee_id" >Employee</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_entered" >Entered</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_modified" >Modified</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=transaction_date" >Transaction Date</a></td>		
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=status" >Status</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_exclusive" >Value</a></td>
		<td align="center">GST Rate</td>
		<td align="center">GST</td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=value_inclusive" >Total</a></td>				
		<td align="center">Admin</td>
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
		users.gecos AS user_gecos,
		concat(contacts.firstname,' ',contacts.lastname) AS employee_name
		from cashbook 
		left join cashbook_accounts on cashbook_accounts.id = cashbook.account_id
		left join cashbook_types on cashbook_types.id = cashbook.type_id
		left join users on users.uid = cashbook.owner_id
		left join contacts ON contacts.id = cashbook.employee_id
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
				<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=edit&cashbook_id=<?php echo $transactionresultsarray['id'] ?>&status=<?php echo $_REQUEST['status'] ?>&p_status=<?php echo $_REQUEST['status'] ?>&owner_id=<?php echo $_REQUEST['owner_id'] ?>&p_mode=display&from_dd=<?php echo $_REQUEST['from_dd'] ?>&from_mm=<?php echo $_REQUEST['from_mm'] ?>&from_yy=<?php echo $_REQUEST['from_yy'] ?>&to_dd=<?php echo $_REQUEST['to_dd'] ?>&to_mm=<?php echo $_REQUEST['to_mm'] ?>&to_yy=<?php echo $_REQUEST['to_yy'] ?>">[EDIT]</a></td>
				<td><?php echo $transactionresultsarray['account_name'] ?></td>
				<td><?php echo $transactionresultsarray['type_name'] ?></td>
				<td><?php echo $transactionresultsarray['notes'] ?></td>
				<td align="left"><?php echo $transactionresultsarray['user_gecos'] ?></td>
				<td align="left"><?php echo $transactionresultsarray['employee_name'] ?></td>				
				<td align="center"><?php echo $transactionresultsarray['date_in'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['date_up'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['date_trans'] ?></td>
				<td align="center"><?php echo $transactionresultsarray['status'] ?></td> 
				<td align="center"><?php echo $transactionresultsarray['value_exclusive'] ?></td>
				<td align="center"><?php if($transactionresultsarray['gst_rate'] <> '0.00') {echo $transactionresultsarray['gst_rate'];} ?></td>
				<td align="center"><?php if($transactionresultsarray['gst'] <> '0.00') {echo $transactionresultsarray['gst'];} ?></td>
				<td align="center">
					<?php
						if ($transactionresultsarray['value_inclusive'] < 0) {
							echo  "<font size=\"0\" color=\"#440000\">".$transactionresultsarray['value_inclusive']."</font>";
						}
						else {
							echo "<font size=\"0\" color=\"#000044\">".$transactionresultsarray['value_inclusive']."</font>";
						}
					?>
				</td>
				<td nowrap align="center" width="1%">
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=delete&task_id=<?php echo $transactionresultsarray['id'] ?>&status=<?php echo $_REQUEST['status'] ?>&owner_id=<?php echo $_REQUEST['owner_id'] ?>&p_mode=display"> [X] </a>
				</td>
			</tr>
			<?php
		}
		while ($transactionresultsarray = mysql_fetch_array($transactionresults));
	}	
	else {
		?>
		<tr>
			<td colspan="10" align="center"">
				<br><br>No Results from your search<br>
				<br><br>
			</td>
		</tr>
		<?php
	}
?>
</table>

</div>
