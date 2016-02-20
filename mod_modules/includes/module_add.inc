<?php
if ($_REQUEST['parent'] > -1) {
	$cashbookinsert = mysql_query("INSERT INTO modules (id, parent) VALUES (null,'{$_REQUEST['parent']}')")	or die("Query failed: " . mysql_error());
}
else {
	$cashbookinsert = mysql_query("INSERT INTO modules (id) VALUES (null)")	or die("Query failed: " . mysql_error());
}

$_REQUEST['new_id'] = mysql_insert_id();

$_REQUEST['mode'] = "edit";
?>