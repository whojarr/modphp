<?php
	require_once('inc/date.php');	
?>
<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="mainform" method="get">
<?php
	if ($_REQUEST['new'] == "yes") {
		echo "<input type=\"hidden\" name=\"new\" value=\"yes\">";
	} 
?>
<input type="hidden" name="function" value="tasks">
<input type="hidden" name="mode" value="update">
<input type="hidden" name="task_id" value="<?php echo $_REQUEST['task_id'] ?>">
<input type="hidden" name="p_status" value="<?php echo $_REQUEST['status'] ?>">
<input type="hidden" name="p_mode" value="<?php echo $_REQUEST['p_mode'] ?>">
<input type="hidden" name="p_owner_id" value="<?php echo $_REQUEST['owner_id'] ?>">
<input type="hidden" name="template" value="<?php echo $_REQUEST['template'] ?>">

<div class="groupBorder">

<input type="image" src="images/icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Save">

<div class="groupHeader">Task Details</div>
<table width="100%" border="0" cellspacing="5" cellpadding="0">

<?php

	$taskresults = mysql_query("
		SELECT tasks.parent_id AS wt_parent_id,
		tasks_groups.group_id AS task_group_id,
		tasks_modules.module_id AS task_module_id,
		tasks.*,
		date_format(tasks.date_due, '%e') as due_dd,
		date_format(tasks.date_due, '%c') as due_mm,
		date_format(tasks.date_due, '%Y') as due_yy, 
		date_format(tasks.date_bill, '%e') as bill_dd,
		date_format(tasks.date_bill, '%c') as bill_mm,
		date_format(tasks.date_bill, '%Y') as bill_yy 
		FROM tasks
		LEFT JOIN tasks_modules ON tasks_modules.task_id = tasks.id
		LEFT JOIN modules ON modules.id = tasks_modules.module_id
		LEFT JOIN tasks_groups ON tasks_groups.task_id = tasks.id
		LEFT JOIN groups ON groups.id = tasks_groups.group_id
		WHERE tasks.id = '{$_REQUEST['task_id']}'
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

 	<tr>
		<td>Module</td>
		<td>
			<select name="module_id">
				<option value="0">none</option>
				<?php
					$modulesresults = mysql_query("
						SELECT *, modules.id AS module_id 
						FROM modules
						LEFT JOIN modules_users ON modules_users.module_id = modules.id
						WHERE modules_users.uid = '{$_SESSION['uid']}' 
						AND parent_id > 0
						ORDER BY modules.name
						") or die("Query failed: " . mysql_error());
					if ($modulesresultsarray = mysql_fetch_array($modulesresults)) {
						do {
							echo "<option value=\"".$modulesresultsarray['module_id']."\"";
							if ($taskresultsarray['task_module_id'] == $modulesresultsarray['id']) {
								echo " selected "; 
							}
							echo ">".$modulesresultsarray['name']."</option>";
						}
						while ($modulesresultsarray = mysql_fetch_array($modulesresults));
					}				
				?>
			</select>
		</td>
	</tr>	
	
	<tr>
		<td>Group</td>
		<td>
			<select name="group_id">
				<option value="0">none</option>
				<?php
					$groupsresults = mysql_query("SELECT * FROM groups") or die("Query failed: " . mysql_error());
					if ($groupsresultsarray = mysql_fetch_array($groupsresults)) {
						do {
							echo "<option value=\"".$groupsresultsarray['id']."\"";
							if ($taskresultsarray['task_group_id'] == $groupsresultsarray['id']) {
								echo " selected "; 
							}
							echo ">".$groupsresultsarray['name']."</option>";
						}
						while ($groupsresultsarray = mysql_fetch_array($groupsresults));
					}				
				?>
			</select>
		</td>
	</tr>
	
	<tr>
		<td>Parent</td>
		<td>
			
			<input type="text" name="parent_id" value="<?php echo $taskresultsarray['parent_id'] ?>" size="5">
		</td>
	</tr>
	
	<tr>
		<td>Title</td>
		<td>
			<input type="text" name="title" value="<?php echo $taskresultsarray['title'] ?>" size="55">
		</td>
	</tr>
	
	<tr>
		<td>URL</td>
		<td>
			<input type="hidden" name="urlb" value="<?php echo $taskresultsarray['url'] ?>">
			<input type="text" name="url" value="<?php echo  urldecode($taskresultsarray['url']) ?>" size="75">
			<a href="<?php echo urldecode($taskresultsarray['url']) ?>" target="blank"> [SHOW] </a>
		</td>
	</tr>
	
	<tr>
		<td>Notes</td>
		<td>
			<textarea name="notes" rows="12" cols="55"><?php echo $taskresultsarray['notes'] ?></textarea>
		</td>
	</tr>
	
	<tr>
		<td>Budget</td>
		<td>
			<input type="text" name="budget" value="<?php echo $taskresultsarray['budget'] ?>" size="10">
		</td>
	</tr>
	
	<tr>
		<td>Cost</td>
		<td>
			<input type="text" name="cost" value="<?php echo $taskresultsarray['cost'] ?>" size="10">
		</td>
	</tr>
	
	<tr>
		<td>Value</td>
		<td>
			<input type="text" name="value" value="<?php echo $taskresultsarray['value'] ?>" size="10">
		</td>
	</tr>
		
	<tr>
		<td>Status</td>
		<td>
			<select name="status">
				<option value="wip" <?php if ($taskresultsarray['status'] == "wip") {	echo " selected "; } ?>>wip</option>
				<option value="pending" <?php if ($taskresultsarray['status'] == "pending") {	echo " selected "; } ?>>pending</option>
				<option value="on hold" <?php if ($taskresultsarray['status'] == "on hold") {	echo " selected "; } ?>>on hold</option>
				<option value="complete" <?php if ($taskresultsarray['status'] == "complete") {	echo " selected "; } ?>>complete</option>
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
							if ($taskresultsarray['owner_id'] == $ownerresultsarray['uid']) {
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
		<td>Manager</td>
		<td>
			<?php
				$amresults = mysql_query("SELECT * FROM users WHERE uid = '{$taskresultsarray['accountmanager']}' ") or die("Query failed: " . mysql_error());
				if ($amresultsarray = mysql_fetch_array($amresults)) {
					do {
						echo $amresultsarray['name'];
						echo "<input type=\"hidden\" name=\"accountmanager\" value=\"".$amresultsarray['uid']."\">";
					}
					while ($amresultsarray = mysql_fetch_array($amresults));
				}				
			?>
		</td>
	</tr>
	
	<tr>
		<td>Notify</td>
		<td>
			Owner:<input type="checkbox" name="send_owner" value="1" >&nbsp;&nbsp;&nbsp;&nbsp;Manager:<input type="checkbox" name="send_manager" value="1">&nbsp;&nbsp;&nbsp;&nbsp;Production:<input type="checkbox" name="send_prod" value="1">&nbsp;&nbsp;&nbsp;
		</td>
	</tr>
	<tr>
		<td>Due Date</td>
		<td>
			<?php
				ddsel('due_dd',$taskresultsarray['due_dd']);
				mmsel('due_mm',$taskresultsarray['due_mm']);
				yysel('due_yy',$taskresultsarray['due_yy']); 
			?>
		</td>
	</tr>
	
		<tr>
		<td>Bill Date</td>
		<td>
			<?php
				ddsel('bill_dd',$taskresultsarray['bill_dd']);
				mmsel('bill_mm',$taskresultsarray['bill_mm']);
				yysel('bill_yy',$taskresultsarray['bill_yy']); 
			?>
			<input type="button" value="Today" onclick="this.form.bill_dd.selectedIndex=<?php echo $_SESSION['dd'] ?>-1;this.form.bill_mm.selectedIndex=<?php echo $_SESSION['mm'] ?>-1;this.form.bill_yy.selectedIndex=<?php echo $_SESSION['yy'] ?>-1;" />
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
	 	while ($taskresultsarray = mysql_fetch_array($taskresults));
	}	
?>

</table>

</div>

</form>
