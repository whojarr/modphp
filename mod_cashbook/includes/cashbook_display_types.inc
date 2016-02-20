<div class="groupBorder">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=add_types&template=<?php echo $_REQUEST['template'] ?>&display_nav=<?php echo $_REQUEST['display_nav'] ?>">
		<img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right">
	</a>
<div class="groupHeader">Transaction Types List</div>
<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center">Edit</td>
		<td align="center">Name</td>
		<td align="center">Admin</td>
	</tr>
<?php
	$typeresults = mysql_query("
		SELECT *
		FROM cashbook_types
		")	or die("Query failed: " . mysql_error());
		
	$rowcount = 1;
	if ($typeresultsarray = mysql_fetch_array($typeresults)) {
		do {
			if (fmod_round ($rowcount++,2) == 0) {
				echo "<tr class=\"even\">";
			}
			else {
				echo "<tr class=\"odd\">";
			}	
			?>			
				<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=edit_types&type_id=<?php echo $typeresultsarray['id'] ?>&template=<?php echo $_REQUEST['template'] ?>&display_nav=<?php echo $_REQUEST['display_nav'] ?>">[EDIT]</a></td>
				<td><?php echo $typeresultsarray['name'] ?></td>
				<td nowrap align="center" width="1%">
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=delete_types&type_id=<?php echo $typeresultsarray['id'] ?>&template=<?php echo $_REQUEST['template'] ?>&display_nav=<?php echo $_REQUEST['display_nav'] ?>"> [X] </a>
				</td>
			</tr>
			<?php
		}
		while ($typeresultsarray = mysql_fetch_array($typeresults));
	}	
	else {
		?>
		<tr>
			<td colspan=9 align=center>
				<br><br>No Results from your search<br>
				<br><br>
			</td>
		</tr>
		<?php
	}
?>
</table>

</div>
