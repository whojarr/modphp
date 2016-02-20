<?php
	require_once('inc/date.php');	
?>
<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="mainform" method="get">
<?php
	if ($_REQUEST['new_id'] > 0) {
		$record_id = $_REQUEST['new_id'];
	}
	elseif ($_REQUEST['id'] > 0) {
		$record_id = $_REQUEST['id'];
	}
?>

<input type="hidden" name="function" value="modules">
<input type="hidden" name="mode" value="update">
<input type="hidden" name="id" value="<?php echo $record_id ?>">

<div class="groupBorder">
	<input type="image" src="/images/icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Save">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=modules">	<img src="/images/icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>

	<div class="groupHeader">modules Entry</div>	
	<?php
		$moduleresults = mysql_query("SELECT * FROM modules WHERE id = '$record_id' ") or die("Query failed: " . mysql_error());
		if ($moduleresultsarray = mysql_fetch_array($moduleresults)) {
			do {
	?>
      
	<table width="100%" border="0" cellspacing="0" cellpadding="5">
	
  	<tr valign="top">
   	<td>Parent</td>
		<td>
			<select name="parent_id">
				<option value="0">Top Level</option>
				<?php
					$results = mysql_query("SELECT * FROM modules WHERE parent_id = '0' ") or die("Query failed: " . mysql_error());
					if ($resultsarray = mysql_fetch_array($results)) {
						do {
							echo "<option value=\"".$resultsarray['id']."\"";
							if ($resultsarray['id'] == $moduleresultsarray['parent_id']) {
								echo " selected "; 
							}
							echo ">".$resultsarray['name']."</option>\n";
						}
						while ($resultsarray = mysql_fetch_array($results));
					}				
				?>
			</select>
		</td>
	</tr>
	
	<tr valign="top">
		<td>Title</td>
		<td><input type="text" name="name" value="<?php echo $moduleresultsarray['name'] ?>"/></td>
	</tr>
	
	<tr valign="top">
		<td>Description</td>
		<td><textarea name="description" rows="6" cols="40"><?php echo $moduleresultsarray['description'] ?></textarea></td>
	</tr>
            
	<tr valign="top">
		<td>Priority</td>
		<td><input type="text" name="priority" value="<?php echo $moduleresultsarray['priority'] ?>"/></td>
	</tr>
            
	<tr valign="top">
		<td>Development</td>
		<td>
			Approved
			<?php
			if (ereg("1", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"1\" name=\"Approved\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"1\" name=\"Approved\" />";
				echo $moduleresultsarray['development'];
			}
			?>
			&nbsp;&nbsp;&nbsp;
			SVN
			<?php
			if (ereg("2", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"2\" name=\"SVN\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"2\" name=\"SVN\" />";
			}
			?>
			&nbsp;&nbsp;&nbsp;
			Split
			<?php
			if (ereg("3", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"3\" name=\"Split\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"3\" name=\"Split\" />";
			}
			?>
			&nbsp;&nbsp;&nbsp;
			Styled
			<?php
			if (ereg("4", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"4\" name=\"Styled\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"4\" name=\"Styled\" />";
			}
			?>
			&nbsp;&nbsp;&nbsp;
			Database
			<?php
			if (ereg("5", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"5\" name=\"Database\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"5\" name=\"Database\" />";
			}
			?>
			&nbsp;&nbsp;&nbsp;
			Combed
			<?php
			if (ereg("6", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"6\" name=\"Combed\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"6\" name=\"Combed\" />";
			}
			?>
			&nbsp;&nbsp;&nbsp;
			Complete
			<?php
			if (ereg("7", $moduleresultsarray['development'])) {
				echo "<input type=\"checkbox\" value=\"7\" name=\"Complete\" checked />";
			}
			else {
				echo "<input type=\"checkbox\" value=\"7\" name=\"Complete\" />";
			}
			?>		
		</td>
	</tr>
            
	<tr valign="top">
		<td>Function</td>
		<td><input type="text" name="mod_function" value="<?php echo $moduleresultsarray['mod_function'] ?>"/></td>
	</tr>
            
	<tr>
		<td colspan="2">
			<a href="index.html?function=modules&mode=delete&id=&var.record_id:mysql;" onclick="return confirm('Are you sure you want to delete?')"><img src="icons/delete.gif" border="0" title="Trash" align=right></a>
		</td>
	</tr>
	
</table>
 	<?php
			}
			while ($moduleresultsarray = mysql_fetch_array($moduleresults));
		}		
	?>    
</div>

</form>