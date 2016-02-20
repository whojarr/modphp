<?php
	for ($row = 1; $row <= $_REQUEST['row_count']; $row++) {

	if($_REQUEST[$row.'_gst_rate'] > 0)
	{
		$gstcomponent = gstcomponent($_REQUEST[$row.'_value_inclusive'],$_REQUEST[$row.'_gst_rate']);
		$gstexclusive = $_REQUEST[$row.'_value_inclusive']- gstcomponent($_REQUEST[$row.'_value_inclusive'],$_REQUEST[$row.'_gst_rate']);
	}
	else
	{
		$gstcomponent = 0;
		$gstexclusive = $_REQUEST[$row.'_value_inclusive'];
	}

	$cashbooklog = mysql_query("
	INSERT INTO cashbook_log (
		input_method,
		ref,
		account_id,
		type_id,
		owner_id,
		employee_id,
		transaction_date,
		value_inclusive,
		value_exclusive,
		gst_rate,
		gst,
		notes
	)
	VALUES (
		'{$_REQUEST['input_method']}',
		'{$_REQUEST[$row.'_ref']}',
		'{$_REQUEST[$row.'_account_id']}',
		'{$_REQUEST[$row.'_type_id']}',
		'{$_SESSION['uid']}',
		'{$_REQUEST[$row.'_employee_id']}',
		'{$_REQUEST[$row.'_transaction_date']}',
		'{$_REQUEST[$row.'_value_inclusive']}',
		'{$_REQUEST[$row.'_value_exclusive']}',
		'{$_REQUEST[$row.'_gst_rate']}',
		'{$gstcomponent}',
		'{$_REQUEST[$row.'_notes']}'
	)	
	")	or die("Query failed: " . mysql_error());

	$cashbookupdate = mysql_query("
	INSERT INTO cashbook (
		input_method,
		ref,
		account_id,
		type_id,
		owner_id,
		employee_id,
		transaction_date,
		value_inclusive,
		value_exclusive,
		gst,
		gst_rate,
		notes
	)
	VALUES (
		'{$_REQUEST['input_method']}',
		'{$_REQUEST[$row.'_ref']}',
		'{$_REQUEST[$row.'_account_id']}',
		'{$_REQUEST[$row.'_type_id']}',
		'{$_SESSION['uid']}',
		'{$_REQUEST[$row.'_employee_id']}',
		'{$_REQUEST[$row.'_transaction_date']}',
		'{$_REQUEST[$row.'_value_inclusive']}',
		'{$gstexclusive}',
		'{$gstcomponent}',
		'{$_REQUEST[$row.'_gst_rate']}',
		'{$_REQUEST[$row.'_notes']}'
	)
	")	or die("Query failed: " . mysql_error());
	
}

	/* +++ close window +++ */	
	if ($_REQUEST['template'] == "no") {
		echo "<script language=\"javascript\">
			window.setTimeout('window.close()',10);
			</script>";
	}
	
	/* +++ return to display mode +++ */
	$_REQUEST['mode'] = "display_transactions";
	?>
	