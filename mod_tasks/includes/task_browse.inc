<?php
function path($task) {
	if (!isset($task)) {
		$task = 0;
	}
	$pathresults = mysql_query("SELECT id, title, parent_id FROM tasks WHERE id = $task")	or die("Query failed: " . mysql_error());
	if ($pathresultsarray = mysql_fetch_array($pathresults)) {
		do {
		echo "<a href=\"".$_SERVER['PHP_SELF']."?function=tasks&mode=browse&action=add&task=".$pathresultsarray['id']."\">  ".$pathresultsarray['title']."</a>"; 
		echo "<a href=\"javascript:popup('".$_SERVER['PHP_SELF']."?function=tasks&mode=add&parent_id=".$pathresultsarray['id']."&template=no',600,600,'Edit Task');\">[sub]</a> >";
		}
		while ($pathresultsarray = mysql_fetch_array($pathresults));
	}	
}
?>

<div class="groupBorder">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=add&p_mode=browse">
		<img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right">
	</a>
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="get">
		<?php
		if (isset($_REQUEST['task'])) {
			echo "<input type=\"hidden\" name=\"task\" value=\"{$_REQUEST['task']}\">";
		}
		?>
		<input type="hidden" name="function" value="tasks">
		<input type="hidden" name="mode" value="browse">
		
		<div class="groupHeader">Task List</div>
		
		<div class="even">
	
			<table border="0" cellspacing="0" cellpadding="5" width="90%">
				<tr>
					<td>
						<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=browse&action=browse"> Home </a>
						<a href="javascript:popup('<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=add&parent_id=0&template=no',600,600,'Edit Task');">[sub]</a> > 
						<?php
						 if (isset($_REQUEST['task'])) {
						 	path($_REQUEST['task']);
						 }
						?>
					</td>
					<td align="right">					
						Show Complete:
						<select name="action" onchange="this.form.submit()">
							<option value="hide" <?php if ($_REQUEST['action'] == "hide") {echo "selected"; } ?>>Hide</option>
							<option value="show" <?php if ($_REQUEST['action'] == "show") {echo "selected"; } ?>>Show</option>
						</select>
					</td>
				</tr>
			</table>
		
		</div>
		
	</form>

	<?php
		$filter = " tasks.status = 'wip'";
		if ($_REQUEST['action'] == "show") {
			$filter = "(tasks.status = 'wip' or tasks.status = 'complete')";
		}
	?>

	<table width="100%" cellpadding="5" cellspacing="0">
		
	<?php
		
	$pathresults = mysql_query("
		SELECT *, tasks.id AS task_id,round((tasks.duration/60/60),2) AS hours 
		FROM tasks 
		LEFT JOIN users ON users.uid = tasks.owner_id
		LEFT JOIN users_groups ON users_groups.uid = tasks.owner_id
		WHERE tasks.parent_id = '{$_REQUEST['task']}' 
		AND $filter
		GROUP BY tasks.id
		")	or die("Query failed: " . mysql_error());
	$rowcount = 1;
	if ($pathresultsarray = mysql_fetch_array($pathresults)) {
		do {
			/* SUM SUB TASKS*/
			$subtasksresults = mysql_query("
				SELECT count(*) AS sum 
				FROM tasks 
				WHERE tasks.parent_id = '".$pathresultsarray['task_id']."' 
				AND $filter 
				")	or die("Query failed: " . mysql_error());
			if ($subtasksresultsarray = mysql_fetch_array($subtasksresults)) {
				do {
					$subtaskssum = $subtasksresultsarray['sum'];
				}
				while ($subtasksresultsarray = mysql_fetch_array($subtasksresults));
			}			
		
			/* COMPLETE */
			if ($pathresultsarray['status'] == "complete" && $_REQUEST['action'] == "show") {
				if (fmod_round ($rowcount++,2) == 0) {
					echo "<tr class=\"even\">";
				}
				else {
					echo "<tr class=\"odd\">";
				}		
				?>
				<td width="50%">
					&nbsp;&nbsp; <strike><?php echo $pathresultsarray['task_id'] ?> - <?php echo $pathresultsarray['title'] ?></strike>
				<?php
					if ($subtaskssum != 0) {
						echo "[$subtaskssum subtasks]";
					}
				?>
				</td>
				<td>
					<?php
					$ownerresults = mysql_query("SELECT gecos FROM users WHERE uid = '{$pathresultsarray['owner_id']}'")	or die("Query failed: " . mysql_error());
					if ($ownerresultsarray = mysql_fetch_array($ownerresults)) {
						do {
							echo $ownerresultsarray['gecos']." ";
						}
						while ($ownerresultsarray = mysql_fetch_array($ownerresults));
					}

					$managerresults = mysql_query("SELECT gecos FROM users WHERE uid = '{$pathresultsarray['accountmanager']}'")	or die("Query failed: " . mysql_error());
					if ($managerresultsarray = mysql_fetch_array($managerresults)) {
						do {
							echo $managerresultsarray['gecos'];
						}
						while ($managerresultsarray = mysql_fetch_array($managerresults));
					}
					?>				
				</td>
				<td align=right>						 
					<a href="javascript:popup('<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=edit&task_id=<?php echo $pathresultsarray['task_id'] ?>&template=no',600,600,'Edit Task');">[edit]</a>
					<a href="javascript:popup('<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=add&parent_id=<?php echo $pathresultsarray['task_id'] ?>&template=no',600,600,'Edit Task');">[sub]</a>
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=delete&task_id=<?php echo $pathresultsarray['task_id'] ?>&parent_id=<?php echo $pathresultsarray['parent_id'] ?>">[X]</a>
				</td>
			</tr>
				<?php
			}
	
			/* WIP */	
			else {
				if (fmod_round ($rowcount++,2) == 0) {
					echo "<tr class=\"even\">";
				}
				else {
					echo "<tr class=\"odd\">";
				}		
				?>				
				<td width="50%">
				<?php
					if ($subtaskssum != 0) {
						echo "&nbsp;&nbsp;   ".$pathresultsarray['task_id']."  &nbsp;&nbsp;";
						echo "<a href=\"".$_SERVER['PHP_SELF'] ."?function=tasks&mode=browse&action=".$_REQUEST['action']."&task=".$pathresultsarray['task_id']."\">".$pathresultsarray['title']." </a>
						[$subtaskssum subtasks]";
					}
					else {
						echo "&nbsp;&nbsp;   ".$pathresultsarray['task_id']."  &nbsp;&nbsp;".$pathresultsarray['title'];
					}
				?>				
				</td>
				<td>
					<?php
					$ownerresults = mysql_query("SELECT gecos FROM users WHERE uid = '{$pathresultsarray['owner_id']}'")	or die("Query failed: " . mysql_error());
					if ($ownerresultsarray = mysql_fetch_array($ownerresults)) {
						do {
							echo $ownerresultsarray['gecos']." ";
						}
						while ($ownerresultsarray = mysql_fetch_array($ownerresults));
					}

					$managerresults = mysql_query("SELECT gecos FROM users WHERE uid = '{$pathresultsarray['accountmanager']}'")	or die("Query failed: " . mysql_error());
					if ($managerresultsarray = mysql_fetch_array($managerresults)) {
						do {
							echo $managerresultsarray['gecos'];
						}
						while ($managerresultsarray = mysql_fetch_array($managerresults));
					}
					?>		
				</td>	
				<td align=right>						 
					<a href="javascript:popup('<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=edit&task_id=<?php echo $pathresultsarray['task_id'] ?>&template=no',600,600,'Edit Task');">[edit]</a>
					<a href="javascript:popup('<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=add&parent_id=<?php echo $pathresultsarray['task_id'] ?>&template=no',600,600,'Edit Task');">[sub]</a>
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=tasks&mode=delete&task_id=<?php echo $pathresultsarray['task_id'] ?>&parent_id=<?php echo $pathresultsarray['parent_id'] ?>">[X]</a>
				</td>
			</tr>				
				<?php
			}
		}
		while ($pathresultsarray = mysql_fetch_array($pathresults));
	}		
		
	?>
      
	</table> 
	
</div>	