<div class="groupBorder">
	<div class="groupHeader">ASB Transactions</div>
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="mainform" method="post">
		<input type="hidden" name="function" value="cashbook">
		<input type="hidden" name="mode" value="import_transactions">
		<input type="hidden" name="input_method" value="asb_csv">
		<table width="100%" border="0" cellpadding="3" cellspacing="1">
			<tr bgcolor="#DDDDDD">
				<td align="center">Transaction Date</td>
				<td align="center">ID</td>
				<td align="center">Payee</td>
				<td align="center">Amount</td>
				<td align="center">GST Rate</td>
				<td align="center">Account</td>	
				<td align="center">Employee</td>			
				<td align="center">Memo</td>
				<td align="center">Transaction Type ASB</td>
				<td align="center">Transaction Type Cashbook</td>
			</tr>
		<?php
		if (is_uploaded_file ( $_FILES['userfile']['tmp_name'] )) {
			
			// Empty Import Table
			$importresults = mysql_query('TRUNCATE TABLE cashbook_tmp_asb_csv') or die('Error selecting data.<br>' . mysql_error());			
					
			// Insert Transactions into Database	
			$handle = fopen ($_FILES['userfile']['tmp_name'],"r");
			while ($data = fgetcsv ($handle, 5200, ",")) {
				$insertqry="Insert into cashbook_tmp_asb_csv
				set 
				date ='".addslashes($data[0])."',
				id ='".addslashes($data[1])."',
				transtype ='".addslashes($data[2])."',
				checkno ='".addslashes($data[3])."',
				payee ='".addslashes($data[4])."',
				memo ='".addslashes($data[5])."',
				amount ='".addslashes($data[6])."'
				";
				mysql_query($insertqry) or Die("SQL: '$strSQL'<br><br>".mysql_error());
//				echo addslashes($data[0])." - ";
//				echo addslashes($data[1])." - ";
//				echo addslashes($data[2])." - ";
//				echo addslashes($data[3])." - ";
//				echo addslashes($data[4])." - ";
//				echo addslashes($data[5])." - ";
//				echo addslashes($data[6])." - ";
//				echo "<br>";
			}
			fclose ($handle);
			
//			$query = 'LOAD DATA LOCAL INFILE "'.$_FILES['userfile']['tmp_name'].'" INTO TABLE cashbook_tmp_asb_csv FIELDS TERMINATED BY "," ENCLOSED BY "\"" LINES TERMINATED BY "\\r\\n";';
			
			$row_count = 0;
			$importresults = mysql_query('SELECT * FROM cashbook_tmp_asb_csv WHERE amount != 0.00') or die('Error selecting data.<br>' . mysql_error());
			if ($importresultsarray = mysql_fetch_array($importresults)) {
				do {
					$row_count++;
					if (fmod_round ($row_count,2) == 0) {
						echo "<tr class=\"even\">";
					}
					else {
						echo "<tr class=\"odd\">";
					}
					?>
						<td>
							<?php echo $importresultsarray['date'] ?>
							<input type="hidden" name="<?php echo $row_count ?>_transaction_date" value="<?php echo $importresultsarray['date'] ?>">
						</td>	
						<td>
							<?php echo $importresultsarray['id'] ?>
							<input type="hidden" name="<?php echo $row_count ?>_ref" value="<?php echo $importresultsarray['id'] ?>">
						</td>		
						<td><?php echo $importresultsarray['payee'] ?></td>
						<td align="right">
							<?php echo $importresultsarray['amount'] ?>
							<input type="hidden" name="<?php echo $row_count ?>_value_inclusive" value="<?php echo $importresultsarray['amount'] ?>"> 
							<input type="hidden" name="<?php echo $row_count ?>_gst" value="<?php echo round($importresultsarray['amount']/9,2); ?>">
						</td>
						<td>
							<select name="<?php echo $row_count ?>_gst_rate">
								<option value="0.125">12.5</option>
								<option value="0.15">15.0</option>
								<option value="0">Zero Rated</option>
							</select>
						</td>
						<td>
							<select name="<?php echo $row_count ?>_account_id" size="0">
							<?php echo 
								$accountresults = mysql_query('SELECT * FROM cashbook_accounts') or die(mysql_error());		
								if ($accountresultsarray = mysql_fetch_array($accountresults)) {
									do {		
										echo "<option value=\"".$accountresultsarray['id']."\">".$accountresultsarray['name']."</option>";
									}
									while ($accountresultsarray = mysql_fetch_array($accountresults));
								}
							?>
							</select>
						</td>								
						<td>
							<select name="<?php echo $row_count ?>_employee_id" size="0">
							<?php echo 
								$employeeresults = mysql_query('
									SELECT *, cashbook_employee_details.id AS employee_id, concat(contacts.firstname," ",contacts.lastname) AS employee_name
									FROM cashbook_employee_details
									LEFT JOIN contacts ON contacts.id = cashbook_employee_details.contact_id
									') or die(mysql_error());		
								if ($employeeresultsarray = mysql_fetch_array($employeeresults)) {
									do {		
										echo "<option value=\"".$employeeresultsarray['employee_id']."\">".$employeeresultsarray['employee_name']."</option>";
									}
									while ($employeeresultsarray = mysql_fetch_array($employeeresults));
								}
							?>
							</select>
						</td>							
						<td>
							<?php echo $importresultsarray['memo'] ?>
							<input type="hidden" name="<?php echo $row_count ?>_notes" value="<?php echo addslashes($importresultsarray['payee']) ?> - <?php echo addslashes($importresultsarray['memo']) ?>">
						</td>	
						<td><?php echo $importresultsarray['transtype'] ?></td>	
						<td>
							<select name="<?php echo $row_count ?>_type_id" size="0">
								<option value="0">Select Type</option>
							<?php echo 
								$typeresults = mysql_query('SELECT * FROM cashbook_types ORDER BY name') or die(mysql_error());		
								if ($typeresultsarray = mysql_fetch_array($typeresults)) {
									do {		
										echo "<option value=\"".$typeresultsarray['id']."\"";
										if ($typeresultsarray['name'] == $importresultsarray['transtype']) {
											echo " selected";
										}
										echo ">".$typeresultsarray['name']."</option>";
									}
									while ($typeresultsarray = mysql_fetch_array($typeresults));
								}
							?>
							</select>
						</td>
					</tr>
					<?php
				}
				while ($importresultsarray = mysql_fetch_array($importresults));
			}
		}
		?>
			<tr>
				<td colspan="10" align="center">
					<input type="hidden" name="row_count" value="<?php echo $row_count ?>">
					<button name="submit" value="submit" type="submit">Add Transactions</button>
				</td>
			</tr>
		</table>
	</form>
</div>