<?php
	$taskdelete = mysql_query("DELETE FROM tasks WHERE id = '{$_REQUEST['task_id']}' ")	or die("Query failed: " . mysql_error());
	$taskgroupdelete = mysql_query("DELETE FROM tasks_groups WHERE task_id = '{$_REQUEST['task_id']}' ")	or die("Query failed: " . mysql_error());
	
	$_REQUEST['task'] = $_REQUEST['parent_id'];
	
	/* +++ return to previous display/browse mode +++ */
	
	if ($_REQUEST['p_mode'] > " ") {
		$_REQUEST['mode'] = $_REQUEST['p_mode'];
	}
	else {
		$_REQUEST['mode'] == "browse";
	}
?>