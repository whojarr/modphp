<?php
	$typeinsert = mysql_query("INSERT INTO cashbook_types (id) VALUES (null)")	or die("Query failed: " . mysql_error());
	$type_id = mysql_insert_id();
	
	$_REQUEST['type_id'] = $type_id;
	$_REQUEST['mode'] = "edit_types";
?>