<?php
	$cashbooklog = mysql_query("
	INSERT INTO cashbook_log
	SELECT *
	FROM cashbook
	WHERE id = '{$_REQUEST['cashbook_id']}'
	")	or die("Query failed: " . mysql_error());
	
	$cashbookupdate = mysql_query("
		UPDATE cashbook 
		SET
		account_id   = '{$_REQUEST['account_id']}' ,
		type_id  = '{$_REQUEST['type_id']}' ,
		owner_id  = '{$_REQUEST['owner_id']}' ,
		employee_id  = '{$_REQUEST['employee_id']}' ,
		notes =  '".addslashes($_REQUEST['notes'])."' ,
		value_exclusive =  '{$_REQUEST['value_exclusive']}' ,
		value_inclusive =  '{$_REQUEST['value_inclusive']}' ,
		gst_rate = '{$_REQUEST['gst_rate']}' ,
		gst = '{$_REQUEST['gst']}' ,
		status  = '{$_REQUEST['status']}' ,
		date_modified   = '{$_REQUEST['modified_yy']}-{$_REQUEST['modified_mm']}-{$_REQUEST['modified_dd']}' ,
		transaction_date   = '{$_REQUEST['trans_yy']}-{$_REQUEST['trans_mm']}-{$_REQUEST['trans_dd']}'
		WHERE id = '{$_REQUEST['cashbook_id']}' 
		")	or die("Query failed: " . mysql_error());
	

	/* +++ close window +++ */	
	if ($_REQUEST['template'] == "no") {
		echo "<script language=\"javascript\">
			window.setTimeout('window.close()',10);
			</script>";
	}
	
	/* +++ return to previous display/browse mode +++ */
	if ($_REQUEST['p_status'] >'') {
		$_REQUEST['status'] = $_REQUEST['p_status'];
	}
	else {
		$_REQUEST['mode'] = "browse";
	}	
	
	/* +++ return to display mode +++ */
		$_REQUEST['mode'] = "display_transactions";
	?>