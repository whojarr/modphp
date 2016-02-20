<?php
	require_once('inc/date.php');	
?>
<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="mainform" method="get">
<?php
	if ($_REQUEST['new'] == "yes") {
		echo "<input type=\"hidden\" name=\"new\" value=\"yes\">";
	} 
?>
<input type="hidden" name="function" value="cashbook">
<input type="hidden" name="mode" value="update">
<input type="hidden" name="cashbook_id" value="<?php echo $_REQUEST['cashbook_id'] ?>">
<input type="hidden" name="p_status" value="<?php echo $_REQUEST['status'] ?>">
<input type="hidden" name="p_mode" value="<?php echo $_REQUEST['p_mode'] ?>">
<input type="hidden" name="p_owner_id" value="<?php echo $_REQUEST['owner_id'] ?>">
<input type="hidden" name="from_dd" value="<?php echo $_REQUEST['from_dd'] ?>">
<input type="hidden" name="from_mm" value="<?php echo $_REQUEST['from_mm'] ?>">
<input type="hidden" name="from_yy" value="<?php echo $_REQUEST['from_yy'] ?>">
<input type="hidden" name="to_dd" value="<?php echo $_REQUEST['to_dd'] ?>">
<input type="hidden" name="to_mm" value="<?php echo $_REQUEST['to_mm'] ?>">
<input type="hidden" name="to_yy" value="<?php echo $_REQUEST['to_yy'] ?>">


<input type="hidden" name="template" value="<?php echo $_REQUEST['template'] ?>">

<div class="groupBorder">

<input type="image" src="images/icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Save">

<div class="groupHeader">Transaction Details</div>
<table width="100%" border="0" cellspacing="5" cellpadding="0">

<?php

	$cashbookresults = mysql_query("
		SELECT 
		date_format(cashbook.date_entered, '%d-%m-%Y') AS date_in,
		date_format(cashbook.date_modified, '%e') as modified_dd,
		date_format(cashbook.date_modified, '%c') as modified_mm,
		date_format(cashbook.date_modified, '%Y') as modified_yy, 		
		date_format(cashbook.transaction_date, '%e') as trans_dd,
		date_format(cashbook.transaction_date, '%c') as trans_mm,
		date_format(cashbook.transaction_date, '%Y') as trans_yy, 
		cashbook_accounts.name AS account_name,
		cashbook_types.name AS type_name,
		cashbook.*, 
		users.gecos AS user_gecos
		from cashbook 
		left join cashbook_accounts on cashbook_accounts.id = cashbook.account_id
		left join cashbook_types on cashbook_types.id = cashbook.type_id
		left join users on users.uid = cashbook.owner_id
		WHERE cashbook.id = '{$_REQUEST['cashbook_id']}'
		")	or die("Query failed: " . mysql_error());
		
	$rowcount = 1;
	if ($cashbookresultsarray = mysql_fetch_array($cashbookresults)) {
		do {
			if (fmod_round ($rowcount++,2) == 0) {
				echo "<tr class=\"even\">";
			}
			else {
				echo "<tr class=\"odd\">";
			}	
			?>			

 	<tr>
		<td>Account</td>
		<td>
			<select name="account_id" onchange="
				var gst_true = 0;
				var gst_ids = new Array(<?php echo $gst_ids ?>);
				for (var i=0; i < gst_ids.length-1; i++) {
					if (gst_ids[i] == this.form.account_id.options[this.form.account_id.selectedIndex].value) {
						if (this.form.value_exclusive.value < 0.00 || this.form.value_exclusive.value > 0.00) { 
							this.form.gst.value = Math.round((this.form.value_exclusive.value*0.125)*100)/100;
						}
						if (this.form.value_inclusive.value < 0.00 || this.form.value_inclusive.value > 0.00) { 
							this.form.gst.value = Math.round((this.form.value_inclusive.value/9)*100)/100;
						};
						var gst_true = 1;
					}
				}
				if (gst_true == 0) {
					this.form.gst.value = 'NIL';
				}
				">
				<option value="0">none</option>
				<?php
					$accountsresults = mysql_query("
						SELECT *, cashbook_accounts.id AS account_id 
						FROM cashbook_accounts
						ORDER BY cashbook_accounts.name
						") or die("Query failed: " . mysql_error());
					if ($accountsresultsarray = mysql_fetch_array($accountsresults)) {
						do {
							echo "<option value=\"".$accountsresultsarray['account_id']."\"";
							if ($cashbookresultsarray['account_id'] == $accountsresultsarray['id']) {
								echo " selected "; 
							}
							echo ">".$accountsresultsarray['name']."</option>";
						}
						while ($accountsresultsarray = mysql_fetch_array($accountsresults));
					}				
				?>
			</select>
		</td>
	</tr>	
	
	<tr>
		<td>Transaction Type</td>
		<td>
			<select name="type_id">
				<option value="0">none</option>
				<?php
					$typesresults = mysql_query("SELECT * FROM cashbook_types") or die("Query failed: " . mysql_error());
					if ($typesresultsarray = mysql_fetch_array($typesresults)) {
						do {
							echo "<option value=\"".$typesresultsarray['id']."\"";
							if ($cashbookresultsarray['type_id'] == $typesresultsarray['id']) {
								echo " selected "; 
							}
							echo ">".$typesresultsarray['name']."</option>";
						}
						while ($typesresultsarray = mysql_fetch_array($typesresults));
					}				
				?>
			</select>
		</td>
	</tr>
	
	<tr>
		<td>Owner</td>
		<td>
			<select name="owner_id">
				<?php
					$ownerresults = mysql_query("SELECT * FROM users ORDER BY name") or die("Query failed: " . mysql_error());
					if ($ownerresultsarray = mysql_fetch_array($ownerresults)) {
						do {
							echo "<option value=\"".$ownerresultsarray['uid']."\"";
							if ($cashbookresultsarray['owner_id'] == $ownerresultsarray['uid']) {
								echo " selected "; 
							}
							echo ">".$ownerresultsarray['name']."</option>";
						}
						while ($ownerresultsarray = mysql_fetch_array($ownerresults));
					}				
				?>
			</select>
		</td>
	</tr>
	
	<tr>
		<td>Employee</td>
		<td>
			<select name="employee_id">
				<?php
					$employeeresults = mysql_query("
						SELECT groups.id, cashbook_employee_details.id AS employee_id, concat(contacts.firstname,' ',contacts.lastname) AS employee_name 
						FROM groups 
						LEFT JOIN contacts_groups ON contacts_groups.group_id = groups.id
						LEFT JOIN contacts ON contacts.id = contacts_groups.contact_id
						LEFT JOIN cashbook_employee_details ON cashbook_employee_details.contact_id = contacts.id
						WHERE groups.name = 'employees'
						AND type = 'contacts'
						") or die("Query failed: " . mysql_error());
					if ($employeeresultsarray = mysql_fetch_array($employeeresults)) {
						do {
							echo "<option value=\"".$employeeresultsarray['employee_id']."\"";
							if ($cashbookresultsarray['employee_id'] == $employeeresultsarray['employee_id']) {
								echo " selected "; 
							}
							echo ">".$employeeresultsarray['employee_name']."</option>";
						}
						while ($employeeresultsarray = mysql_fetch_array($employeeresults));
					}				
				?>
			</select>
		</td>
	</tr>
		
	<tr>
		<td>Notes</td>
		<td>
			<textarea name="notes" cols="55"><?php echo $cashbookresultsarray['notes'] ?></textarea>
		</td>
	</tr>

	<tr>
		<td>Value Exclusive</td>
		<td>
			<input type="text" name="value_exclusive" value="<?php echo $cashbookresultsarray['value_exclusive'] ?>" size="10" onchange="var rounded=Math.round(this.form.value_exclusive.value*0.125*100)/100;this.form.gst.value = rounded;">
		</td>
	</tr>
	
	<tr>
		<td>Value Inclusive</td>
		<td>
			<input type="text" name="value_inclusive" value="<?php echo $cashbookresultsarray['value_inclusive'] ?>" size="10"  onchange="var rounded=Math.round(this.form.value_inclusive.value/9*100)/100;this.form.gst.value = rounded;">
		</td>
	</tr>
	
	<tr>
		<td>GST Rate</td>
		<td>
			<select name="gst_rate">
				<option value="">none</option>
				<?php
				echo "<option value=\"0.125\"";
				if ($cashbookresultsarray['gst_rate'] == '0.125') {
					echo " selected "; 
				}
				echo ">0.125</option>";
				echo "<option value=\"0.15\"";
				if ($cashbookresultsarray['gst_rate'] == '0.15') {
					echo " selected "; 
				}
				echo ">0.15</option>";
				?>
			</select>
		</td>
	</tr>
	
	<tr>
		<td>GST</td>
		<td>
			<input type="text" name="gst" value="<?php echo $cashbookresultsarray['gst'] ?>" size="10" onfocus="
			if (this.form.value_exclusive.value < 0.00 || this.form.value_exclusive.value > 0.00) { 
				this.form.gst.value = Math.round((this.form.value_exclusive.value*0.125)*100)/100;
			}
			if (this.form.value_inclusive.value < 0.00 || this.form.value_inclusive.value > 0.00) { 
				this.form.gst.value = Math.round((this.form.value_inclusive.value/9)*100)/100;
			};
			">
		</td>
	</tr>

	<tr>
		<td>Total</td>
		<td>
			<?php
				if ($cashbookresultsarray['value_inclusive'] <> 0) {
					echo "<b>$".$cashbookresultsarray['value_inclusive']."</b>"; 
				}
				elseif ($cashbookresultsarray['value_exclusive'] <> 0) {
					echo "<b>$".$cashbookresultsarray['value_exclusive'] * 1.125."</b>";
				}
			?>
		</td>
	</tr>
		
	<tr>
		<td>Status</td>
		<td>
			<select name="status">
				<option value="entered" <?php if ($cashbookresultsarray['status'] == "entered") {	echo " selected "; } ?>>entered</option>
				<option value="completed" <?php if ($cashbookresultsarray['status'] == "completed") {	echo " selected "; } ?>>completed</option>
				<option value="reconciled" <?php if ($cashbookresultsarray['status'] == "on hold") {	echo " selected "; } ?>>reconciled</option>
				<option value="archived" <?php if ($cashbookresultsarray['status'] == "complete") {	echo " selected "; } ?>>archived</option>
				<option value="deleted" <?php if ($cashbookresultsarray['status'] == "deleted") {	echo " selected "; } ?>>deleted</option>				
			</select>
		</td>
	</tr>
	
	<tr>
		<td>Entered Date</td>
		<td>
			<?php
				echo $cashbookresultsarray['date_in'];
			?>
		</td>
	</tr>
	
	<tr>
		<td>Modified Date</td>
		<td>
			<?php
				ddsel('modified_dd',$cashbookresultsarray['modified_dd']);
				mmsel('modified_mm',$cashbookresultsarray['modified_mm']);
				yysel('modified_yy',$cashbookresultsarray['modified_yy']); 
			?>
			<input type="button" value="Today" onclick="selectDate('mainform','modified_dd','<?php echo $_SESSION['dd'] ?>','modified_mm','<?php echo $_SESSION['mm'] ?>','modified_yy','<?php echo $_SESSION['yy'] ?>');" />
		</td>
	</tr>
	
		<tr>
		<td>Transaction Date</td>
		<td>
			<?php
				ddsel('trans_dd',$cashbookresultsarray['trans_dd']);
				mmsel('trans_mm',$cashbookresultsarray['trans_mm']);
				yysel('trans_yy',$cashbookresultsarray['trans_yy']); 
			?>
			<input type="button" value="Today" onclick="selectDate('mainform','trans_dd','<?php echo $_SESSION['dd'] ?>','trans_mm','<?php echo $_SESSION['mm'] ?>','trans_yy','<?php echo $_SESSION['yy'] ?>');" />
		</td>
	</tr>
	
</emit>

 <tr>
    <td colspan="2">
        <a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=delete&task_id=<?php echo $_REQUEST['task_id'] ?>"><img src="images/icons/delete.gif" border="0" title="Trash" align=right></a>
       </td>
 </tr>
			<?php
		}
	 	while ($cashbookresultsarray = mysql_fetch_array($cashbookresults));
	}	
?>

</table>

</div>

</form>