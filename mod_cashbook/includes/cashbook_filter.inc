<?php
	require_once('inc/date.php');	

	if ($_REQUEST['status'] < ' ') {
		$_REQUEST['status'] = "%";	
	}
	if ($_REQUEST['owner_id'] <= 0) {
		$_REQUEST['owner_id'] = "%";	
	}
?>
<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="filter_form" method="get">
<input type="hidden" name="function" value="cashbook">
<input type="hidden" name="mode" value="<?php echo $_REQUEST['mode']; ?>">
<input type="hidden" name="p_mode" value="<?php echo $_REQUEST['mode']; ?>">
<input type="hidden" name="orderby" value="<?php echo $_REQUEST['orderby']; ?>">

<div class="menuBar">
<table align="center"><tr><td>
Filters:&nbsp;&nbsp;
Account&nbsp;
<select name="account_id">
	<option value="">select an account</option>
	<?php
		$results = mysql_query("
			SELECT *, cashbook_accounts.id AS account_id 
			FROM cashbook_accounts
			ORDER BY cashbook_accounts.name
			") or die("Query failed: " . mysql_error());
		if ($resultsarray = mysql_fetch_array($results)) {
			do {
				echo "<option value=\"".$resultsarray['account_id']."\"";
				if ($resultsarray['account_id'] == $_REQUEST['account_id']) {
				echo " selected "; 
				$filter_account_name = $resultsarray['name'];
				}
				echo ">".$resultsarray['name']."</option>";
			}
			while ($resultsarray = mysql_fetch_array($results));
		}				
	?>
</select>&nbsp;&nbsp;

Date From:&nbsp;
<?php
	ddsel('from_dd',$_REQUEST['from_dd']);
	mmsel('from_mm',$_REQUEST['from_mm']);
	yysel('from_yy',$_REQUEST['from_yy']); 
?>
<input type="button" value="Today" onclick="selectDate('filter_form','from_dd','<?php echo $_SESSION['dd'] ?>','from_mm','<?php echo $_SESSION['mm'] ?>','from_yy','<?php echo $_SESSION['yy'] ?>');" />&nbsp;&nbsp;

Date To:&nbsp;
<?php
	ddsel('to_dd',$_REQUEST['to_dd']);
	mmsel('to_mm',$_REQUEST['to_mm']);
	yysel('to_yy',$_REQUEST['to_yy']); 
?>
<input type="button" value="Today" onclick="selectDate('filter_form','to_dd','<?php echo $_SESSION['dd'] ?>','to_mm','<?php echo $_SESSION['mm'] ?>','to_yy','<?php echo $_SESSION['yy'] ?>');" />&nbsp;&nbsp;

Status:&nbsp;
<?php
	if (isset($_REQUEST['p_status'])) {
		$c_status = $_REQUEST['p_status'];
	}
	else {
		$c_status = $_REQUEST['status'];
	}
?>
<select name="status">
	<option value="%">- All -</option>
	<?php
		$statusresults = mysql_query("SELECT distinct(status) AS status FROM cashbook");
		if ($statusresultsarray = mysql_fetch_array($statusresults)) {
			do {
				if ($statusresultsarray['status'] == $c_status) {
					echo "<option value=\"".$statusresultsarray['status']."\" selected>".$statusresultsarray['status']."</option>";
				}
				else {
					echo "<option value=\"".$statusresultsarray['status']."\">".$statusresultsarray['status']."</option>";
				}
			}
			while ($statusresultsarray = mysql_fetch_array($statusresults));
		}
	?>
</select>&nbsp;&nbsp;

Owner:&nbsp;
<select name="owner_id">
	<option value="%">- All -</option>
	<?php
		$ownerresults = mysql_query("SELECT * FROM users ORDER BY name");
		if ($ownerresultsarray = mysql_fetch_array($ownerresults)) {
			do {
				if ($ownerresultsarray['uid'] == $_REQUEST['owner_id']) {
					echo "<option value=\"".$ownerresultsarray['uid']."\" selected>".$ownerresultsarray['name']."</option>";
				}
				else {
					echo "<option value=\"".$ownerresultsarray['uid']."\">".$ownerresultsarray['name']."</option>";
				}
			}
			while ($ownerresultsarray = mysql_fetch_array($ownerresults));
		}
		else {
			echo "<input type=\"hidden\" name=\"owner_id\" value=\"%\">";
		}
	?>
</select>&nbsp;&nbsp;

<input type="image" src="images/icons/view.gif" border="0" title="View"> 
</td></tr></table>
</div>
</form>
</center>
