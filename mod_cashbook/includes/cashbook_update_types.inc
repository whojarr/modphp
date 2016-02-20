<?php
	$typesupdate = mysql_query("
		UPDATE cashbook_types 
		SET
		name = '{$_REQUEST['name']}'
		WHERE id = '{$_REQUEST['type_id']}' 
		")	or die("Query failed: " . mysql_error());
		
	/* +++ close window +++ */	
	if ($_REQUEST['template'] == "no") {
		echo "<script language=\"javascript\">
			window.opener.location.reload();
			window.setTimeout('window.close()',10);
			</script>";
	}
	
	/* +++ return to previous display/browse mode +++ */
	$_REQUEST['mode'] = "display_types";
?>