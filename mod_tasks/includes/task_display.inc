<?php
	if ($_REQUEST['orderby'] < ' ') {
		$orderby = "ORDER BY id";
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
?>

<div class="groupBorder">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=add&p_mode=display">
		<img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right">
	</a>
<div class="groupHeader">Task List</div>

<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=id" >id	</a></td>
		<td align="center">Edit</td>
		<td align="center" colspan="2"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=module_name" >Module</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=title" >Title</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=group_name" >Group</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=user_gecos" >Owner</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=accountmanager" >Account Manger</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_entered" >Entered</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_modified" >Modified</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_due" >Due</a></td>
		 <td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>&orderby=date_bill" >Completed</a></td>
		<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=display&status=<?php echo $status ?>&owner_id=<?php echo $owner_id ?>orderby=status" >Status</a></td>
		<td align="center">Admin</td>
	</tr>

<?php
	$taskresults = mysql_query("
		SELECT DISTINCT tasks.id,
		date_format(tasks.date_entered, '%d-%m-%Y') AS date_in,
		date_format(tasks.date_modified, '%d-%m-%Y') AS date_up,
		date_format(tasks.date_bill, '%d-%m-%Y') AS date_bill_dmy,
		date_format(tasks.date_due, '%d-%m-%Y') AS date_due_dmy,
		if(date_format(tasks.date_due, '%Y%m%d')<(CURDATE() + 0),'yes','no') AS overdue,
		tasks.*, 
		groups.name AS group_name, 
		users.gecos AS user_gecos, 
		modules.name AS module_name,
		modules.mod_function AS mod_function,
		modules.parent_id AS mod_parent_id
		from tasks 
		left join tasks_groups on tasks_groups.task_id = tasks.id
		left join groups on groups.id = tasks_groups.group_id
		left join users_groups on users_groups.group_id = tasks_groups.group_id
		left join users on users.uid = tasks.owner_id
		left join tasks_modules on tasks_modules.task_id = tasks.id
		left join modules on modules.id = tasks_modules.module_id
		where tasks.owner_id like '{$_REQUEST['owner_id']}' 
		and tasks.status like '{$_REQUEST['status']}' 
		$orderby
		")	or die("Query failed: " . mysql_error());
		
	$rowcount = 1;
	if ($taskresultsarray = mysql_fetch_array($taskresults)) {
		do {
			if (fmod_round ($rowcount++,2) == 0) {
				echo "<tr class=\"even\">";
			}
			else {
				echo "<tr class=\"odd\">";
			}	
			?>			
				<td align="center"><?php echo $taskresultsarray['id'] ?></td>
				<td align="center"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=edit&task_id=<?php echo $taskresultsarray['id'] ?>&status=<?php echo $_REQUEST['status'] ?>&owner_id=<?php echo $_REQUEST['owner_id'] ?>&p_mode=display">[EDIT]</a></td>
				<td><a href="index.html?<?php echo $taskresultsarray['url'] ?>" target="blank">[SHOW]</a></td>
				<td align="left"><a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=<?php echo $taskresultsarray['mod_function'] ?>&nav=<?php echo $taskresultsarray['mod_parent_id'] ?>"><?php echo $taskresultsarray['module_name'] ?></a></td>
				<td align="left"><?php echo $taskresultsarray['title'] ?></td>
				<td align="center"><?php echo $taskresultsarray['group_name'] ?></td>
				<td align="center"><?php echo $taskresultsarray['user_gecos'] ?></td>
				<?php
					$amresults = mysql_query("SELECT gecos FROM users WHERE uid = '{$taskresultsarray['accountmanager']}' ")	or die("Query failed: " . mysql_error());
					if ($amresultsarray = mysql_fetch_array($amresults)) {
						do {
							echo "<td align=\"center\">";
							echo $amresultsarray['gecos'];
							echo "<input type=\"hidden\" name=\"".$amresultsarray['accountmanager']."\" value=\"1\">	</td>";
						}
						while ($amresultsarray = mysql_fetch_array($amresults));
					}					
				?>
				</emit>
				<td align="center"><?php echo $taskresultsarray['date_in'] ?></td>
				<td align="center"><?php echo $taskresultsarray['date_up'] ?></td> 
				<?php
					if ($taskresultsarray['overdue'] == "yes") {
						echo "<td align=\"center\"><font color=\"#FF0000\">".$taskresultsarray['date_due_dmy']."</font></a></td>";
					}
					else {
						echo "<td align=\"center\">".$taskresultsarray['date_due_dmy']."</a>";
					} 
					
					if (($taskresultsarray['date_bill'] == "2005-01-31") || ($taskresultsarray['date_bill'] == "2004-01-31") || ($taskresultsarray['date_bill'] == "0000-00-00")) {
						echo "<td></td>";
					}
					else {
						echo "<td align=\"center\">".$taskresultsarray['date_bill_dmy']."</td>";
					}
				?>
				<td align="center"><?php echo $taskresultsarray['status'] ?></td>
				<td nowrap align="center" width="1%">
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=delete&task_id=<?php echo $taskresultsarray['id'] ?>&status=<?php echo $_REQUEST['status'] ?>&owner_id=<?php echo $_REQUEST['owner_id'] ?>&p_mode=display"> [X] </a>
				</td>
			</tr>
			<?php
		}
		while ($taskresultsarray = mysql_fetch_array($taskresults));
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
