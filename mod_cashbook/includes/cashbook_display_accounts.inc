<div class="groupBorder">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=add_accounts&template=<?php echo $_REQUEST['template'] ?>&display_nav=<?php echo $_REQUEST['display_nav'] ?>">
		<img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right">
	</a>
<div class="groupHeader">Transaction Accounts List</div>
<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center">Edit</td>
		<td align="center">Name</td>
		<td align="center">GST</td>
		<td align="center">Admin</td>
	</tr>
<?php
	$accountresults = mysql_query("
		SELECT *
		FROM cashbook_accounts
		")	or die("Query failed: " . mysql_error());
		
	$rowcount = 1;
	if ($accountresultsarray = mysql_fetch_array($accountresults)) {
		do {
			if (fmod_round ($rowcount++,2) == 0) {
				echo "<tr class=\"even\">";
			}
			else {
				echo "<tr class=\"odd\">";
			}	
			?>			
				<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=edit_accounts&account_id=<?php echo $accountresultsarray['id'] ?>&template=<?php echo $_REQUEST['template'] ?>&display_nav=<?php echo $_REQUEST['display_nav'] ?>">[EDIT]</a></td>
				<td><?php echo $accountresultsarray['name'] ?></td>
				<td><?php if ($accountresultsarray['gst'] == '1') { echo "yes"; } ?></td>
				<td nowrap align="center" width="1%">
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=delete_accounts&account_id=<?php echo $accountresultsarray['id'] ?>&template=<?php echo $_REQUEST['template'] ?>&display_nav=<?php echo $_REQUEST['display_nav'] ?>"> [X] </a>
				</td>
			</tr>
			<?php
		}
		while ($accountresultsarray = mysql_fetch_array($accountresults));
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
