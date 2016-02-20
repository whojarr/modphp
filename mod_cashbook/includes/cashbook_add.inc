<?php
	$cashbookinsert = mysql_query("INSERT INTO cashbook (id, owner_id) VALUES (null,'{$_SESSION['uid']}')")	or die("Query failed: " . mysql_error());
	$cashbook_id = mysql_insert_id();
	
	$_REQUEST['new'] = "yes";
	$_REQUEST['cashbook_id'] = $cashbook_id;
	$_REQUEST['mode'] = "edit";
?>