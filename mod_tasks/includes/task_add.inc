<?php
	if ($_REQUEST['module_id'] <= 0) {
		$_REQUEST['module_id'] = 0;
	}
	if ($_REQUEST['parent_id'] <= 0) {
		$_REQUEST['parent_id'] = 0;
	}
	if ($_REQUEST['url'] == yes) {
		$url = urlencode($_SESSION['url']);
	}	

	$taskinsert = mysql_query("INSERT INTO tasks (id, date_entered, date_due, owner_id,accountmanager, url, parent_id) VALUES (null, curdate(), curdate() + 2, {$_SESSION['uid']}, {$_SESSION['uid']}, '{$url}', {$_REQUEST['parent_id']})")	or die("Query failed: " . mysql_error());
	$task_id = mysql_insert_id();
	$taskmoduleinsert = mysql_query("insert into tasks_modules (task_id, module_id) values ({$task_id}, {$_REQUEST['module_id']})")	or die("Query failed: " . mysql_error());
	
	$_REQUEST['new'] = "yes";
	$_REQUEST['task_id'] = $task_id;
	$_REQUEST['mode'] = "edit";
	
	?>