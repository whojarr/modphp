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
	
	$from_date = $_REQUEST['from_yy']."-".$_REQUEST['from_mm']."-".$_REQUEST['from_dd'];
	$to_date = $_REQUEST['to_yy']."-".$_REQUEST['to_mm']."-".$_REQUEST['to_dd'];
?>

<div class="groupBorder">

<div class="groupHeader"><?php echo $filter_account_name ?> PAYE Report </div>

	<?php
	
		$employeeresults = mysql_query("
			SELECT groups.id, cashbook_employee_details.id AS employee_id, concat(contacts.firstname,' ',contacts.lastname) AS employee_name,cashbook_employee_details.child_support 
			FROM groups 
			LEFT JOIN contacts_groups ON contacts_groups.group_id = groups.id
			LEFT JOIN contacts ON contacts.id = contacts_groups.contact_id
			LEFT JOIN cashbook_employee_details ON cashbook_employee_details.contact_id = contacts.id
			WHERE groups.name = 'employees'
			AND type = 'contacts'
			")	or die("Query failed: " . mysql_error());
	
		if ($employeeresultsarray = mysql_fetch_array($employeeresults)) {
			do {
				?>

				<table width="100%" border="0" cellpadding="3" cellspacing="1">
					<tr bgcolor="#DDDDDD">
						<td><?php echo $employeeresultsarray['employee_id'] ?> <?php echo $employeeresultsarray['employee_name'] ?></td>
					</tr>
					</tr>
				</table>

				<table align="center">
					<tr>
						<td align="right">Cash:</td>
						<?php
					$sumresults = mysql_query("
							SELECT sum(value_exclusive) AS sum_value_exclusive,
							sum(value_inclusive) AS sum_value_inclusive
							FROM cashbook
							LEFT JOIN cashbook_accounts ON cashbook_accounts.id = cashbook.account_id
							LEFT JOIN cashbook_types on cashbook_types.id = cashbook.type_id
							LEFT JOIN users on users.uid = cashbook.owner_id
							LEFT JOIN contacts ON contacts.id = cashbook.employee_id
							WHERE cashbook.owner_id like '{$_REQUEST['owner_id']}' 
							AND cashbook.account_id like '{$_REQUEST['account_id']}' 
							AND cashbook.status like '{$_REQUEST['status']}' 
							AND cashbook.transaction_date >= '{$from_date}' 
							AND cashbook.transaction_date <= '{$to_date}' 
							AND cashbook.employee_id = '".$employeeresultsarray['employee_id']."'
							$orderby 	
							")	or die("Query failed: " . mysql_error());
						
						if ($sumresultsarray = mysql_fetch_array($sumresults)) {
							do {
								$cash = sprintf("%01.2f", -$sumresultsarray['sum_value_inclusive']);
							?>
								<td align="right"><?php echo $cash ?></td>
								<?php
							}
							while ($sumresultsarray = mysql_fetch_array($sumresults));
						}
						?>
					</tr>
					
					<tr>
						<td align="right">Child Support:</td>
						<td align="right">
							<?php
								if ($employeeresultsarray['child_support'] > 0.00) {
									$cs = $employeeresultsarray['child_support'];
									echo $employeeresultsarray['child_support'];
								}
								else {
									$cs = "0.00";
								}
							?>
						</td>						
					</tr>
					
					<tr>
						<td align="right">NETT WAGE:</td>
						<td align="right"><?php $nett = $cash+$cs; echo $nett; ?></td>
					</tr>

					<tr>
						<td align="right">GROSS WAGE:</td>
						<td align="right">
							<?php

								
								// cycle through changes to variable gross figures								
						 
/*							 $actual = $nett;
//							 echo "| actual = ".$actual."<br>";
							 $gross = paye($nett) + $nett;
//							 echo "| gross = ".$gross."<br>";
							 $adjustment = $actual;
//							 echo "| adjustment = ".$adjustment."<br>";
							 
							 $est = $gross;
							 
							 // COMPARE ESTIMATED NETT to ACTUAL NETT
							 while (round(($est - paye($est)),2) != round($actual,2)) {
//							 	echo "|| "; 	echo ($est - paye($est)); echo " != "; echo $actual; echo " || ";
							 	$hilow_prev = $hilow;
							 	$adjustment_prev = $adjustment;
							 	
							 	
							 	// IF EST < ACTUAL
							 	if (($est - paye($est)) < $actual) {
//							 		echo "| "; echo ($est - paye($est)); echo " < $actual";
							 		$hilow = 0;
									// IF SECOND TIME LOW ADD ADJUSMENT AGAIN 
							 		if ($hilow_prev == $hilow) {
							 			$adjustment = $adjustment_prev;
							 		}
							 		// IF FIRST TIME LOW SUBTRACT HALF PREVIOUS ADJUSTMENT 
							 		else {
							 			$adjustment = round($adjustment_prev/2,2);
							 		}
							 		$est = $est + $adjustment;
//							 		echo "| add $adjustment ";
							 	}
							 	
							 	
							 	// IF EST > ACTUAL							 	
							 	if (($est - paye($est)) > $actual) {
//							 		echo "| "; echo ($est - paye($est)); echo " > $actual";
							 		$hilow = 1;
							 		// IF SECOND TIME HIGH SUBTRACT ADJUSTMENT AGAIN 
							 		if ($hilow_prev == $hilow) {
							 			$adjustment = $adjustment_prev;
							 		}
							 		// IF FIRST TIME HIGH SUBTRACT HALF PREVIOUS ADJUSTMENT 
							 		else {
							 			$adjustment = round($adjustment_prev/2,2);
							 		}
							 		$est = $est - $adjustment;
//							 		echo "| subtract $adjustment ";
							 	}
							 	
//							 	echo "| $est - "; echo paye($est)." = "; echo round(($est - paye($est)),2); echo "<br>";
							 	// SET CURRENT PAYE
							 	$paye = paye($est);
							 }
							 
							echo $est;
							echo "
							</tr>
							<tr>";
							echo "<td align=\"right\">PAYE</td><td align=\"right\">";
							echo $paye;
*/							?>
						</td>
					</tr>
					<tr>
						<td align="right">IRD DED PAYMENT:</td>
						<td align="right"><?php $nett = $paye+$cs; echo $nett; ?></td>
					</tr>
				</table>	
				

				<table width="100%" border="0" cellpadding="3" cellspacing="1">
				<?php
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
					FROM cashbook
					LEFT JOIN cashbook_accounts ON cashbook_accounts.id = cashbook.account_id
					LEFT JOIN cashbook_types on cashbook_types.id = cashbook.type_id
					LEFT JOIN users on users.uid = cashbook.owner_id
					LEFT JOIN contacts ON contacts.id = cashbook.employee_id
					WHERE cashbook.owner_id like '{$_REQUEST['owner_id']}' 
					AND cashbook.account_id like '{$_REQUEST['account_id']}' 
					AND cashbook.status like '{$_REQUEST['status']}' 
					AND cashbook.transaction_date >= '{$from_date}' 
					AND cashbook.transaction_date <= '{$to_date}' 
					AND cashbook.employee_id = '".$employeeresultsarray['employee_id']."'
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
							<td><?php echo $transactionresultsarray['notes'] ?></td>
							<td align="center"><?php echo $transactionresultsarray['date_in'] ?></td>
							<td align="center"><?php echo $transactionresultsarray['date_trans'] ?></td>
							<td align="right"><?php echo $transactionresultsarray['value_exclusive'] ?></td>
							<td align="right">
								<?php
									if ($transactionresultsarray['value_inclusive'] < 0) {
										echo  "<font size=\"0\" color=\"#440000\">".$transactionresultsarray['value_inclusive']."</font>";
									}
									else {
										echo "<font size=\"0\" color=\"#000044\">".$transactionresultsarray['value_inclusive']."</font>";
									}
								?>
							</td>
						</tr>
						<?php
					}
					while ($transactionresultsarray = mysql_fetch_array($transactionresults));
				}
				?>

					<tr>
						<td align="right"></td>
						<td align="right"></td>
						<td align="right"></td>
						<td align="right"></td>
						<td align="right"></td>
						<td align="right">Total</td>
						<td align="right"><?php echo $cash ?></td>
					</tr>
						
				</table>
				
				
				
				
				
				<br>
				<br>
				<br>
				<?php
								
			}	
			while ($employeeresultsarray = mysql_fetch_array($employeeresults));
		}
	?>

</div>