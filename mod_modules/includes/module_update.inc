<?php
	$update = mysql_query("
		UPDATE modules 
		SET
		parent_id   = '{$_REQUEST['parent_id']}' ,
		name  = '{$_REQUEST['name']}' ,
		description  = '".addslashes($_REQUEST['description'])."' ,
		type  = 'nav' ,
		priority =  '{$_REQUEST['priority']}' ,
		development  = concat('{$_REQUEST['Approved']}',',','{$_REQUEST['SVN']}',',','{$_REQUEST['Split']}',',','{$_REQUEST['Styled']}',',','{$_REQUEST['Database']}',',','{$_REQUEST['Combed']}',',','{$_REQUEST['Complete']}') ,
		mod_function =  '{$_REQUEST['mod_function']}'
		WHERE id = '{$_REQUEST['id']}' 
		")	or die("Query failed: " . mysql_error());

	/* +++ close window +++ */	
	if ($_REQUEST['template'] == "no") {
		echo "<script language=\"javascript\">
			window.setTimeout('window.close()',10);
			</script>";
	}
	
	/* +++ return to display mode +++ */
	$_REQUEST['mode'] = "display";
?>