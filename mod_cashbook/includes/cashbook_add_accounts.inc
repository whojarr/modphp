<?php
	$accountinsert = mysql_query("INSERT INTO cashbook_accounts (id) VALUES (null)")	or die("Query failed: " . mysql_error());
	$account_id = mysql_insert_id();
	
	$_REQUEST['account_id'] = $account_id;
	$_REQUEST['mode'] = "edit_accounts";
?>