<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="mainform" method="get">
<input type="hidden" name="function" value="cashbook">
<input type="hidden" name="mode" value="update_types">
<input type="hidden" name="type_id" value="<?php echo $_REQUEST['type_id'] ?>">
<input type="hidden" name="template" value="<?php echo $_REQUEST['template'] ?>">
<input type="hidden" name="display_nav" value="<?php echo $_REQUEST['display_nav'] ?>">

<div class="groupBorder">

<input type="image" src="images/icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Save">
<div class="groupHeader">Transaction Type Details</div>
<table width="100%" border="0" cellspacing="5" cellpadding="0">

<?php
	$results = mysql_query("
		SELECT *
		FROM cashbook_types
		WHERE cashbook_types.id = '{$_REQUEST['type_id']}'
		")	or die("Query failed: " . mysql_error());
		
	$rowcount = 1;
	if ($resultsarray = mysql_fetch_array($results)) {
		do {
			if (fmod_round ($rowcount++,2) == 0) {
				echo "<tr class=\"even\">";
			}
			else {
				echo "<tr class=\"odd\">";
			}
			?>			
			<td>Name</td>
			<td>
				<input type="text" name="name" value="<?php echo $resultsarray['name'] ?>">
			</td>
			</tr>
			<?php
		}
	 	while ($resultsarray = mysql_fetch_array($results));
	}	
?>

</table>

</div>

</form>