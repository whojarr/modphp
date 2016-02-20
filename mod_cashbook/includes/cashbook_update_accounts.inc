<?php
	$accountsupdate = mysql_query("
		UPDATE cashbook_accounts 
		SET
		name = '{$_REQUEST['name']}',
		gst = if ('{$_REQUEST['gst']}' = 1,1,0)
		WHERE id = '{$_REQUEST['account_id']}' 
		")	or die("Query failed: " . mysql_error());
		
	/* +++ close window +++ */	
	if ($_REQUEST['template'] == "no") {
		echo "<script language=\"javascript\">
			window.opener.location.reload();
			window.setTimeout('window.close()',10);
			</script>";
	}
	
	/* +++ return to previous display/browse mode +++ */
	$_REQUEST['mode'] = "display_accounts";
?>