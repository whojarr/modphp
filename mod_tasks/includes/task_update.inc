<?php
	$taskupdate = mysql_query("
		UPDATE tasks 
		SET
		parent_id = '{$_REQUEST['parent_id']}' ,
		title   = '{$_REQUEST['title']}' ,
		notes  = '{$_REQUEST['notes']}' ,
		url  = '{$_REQUEST['url']}' ,
		status  = '{$_REQUEST['status']}' ,
		priority = '{$_REQUEST['priority']}' ,
		date_due   = '{$_REQUEST['due_yy']}-{$_REQUEST['due_mm']}-{$_REQUEST['due_dd']}' ,
		date_bill   = '{$_REQUEST['bill_yy']}-{$_REQUEST['bill_mm']}-{$_REQUEST['bill_dd']}' ,
		type  = '{$_REQUEST['type']}' ,
		owner_id  = '{$_REQUEST['owner_id']}' ,
		duration  = '{$_REQUEST['duration']}' ,
		accountmanager = '{$_REQUEST['accountmanager']}' ,
		billable  = '{$_REQUEST['billable']}' ,
		budget   = '{$_REQUEST['budget']}' ,
		cost   = '{$_REQUEST['cost']}' ,
		value  = '{$_REQUEST['value']}'
		WHERE id = '{$_REQUEST['task_id']}' 
		")	or die("Query failed: " . mysql_error());
		
	$taskmoduleupdate = mysql_query("
		UPDATE tasks_modules 
		SET module_id = '{$_REQUEST['module_id']}'
		WHERE task_id = '{$_REQUEST['task_id']}' 
		")	or die("Query failed: " . mysql_error());
		
	/* Set Message Status */
	if ($_REQUEST['status'] == "complete") {
		$status_greeting = "completed";
	}
	else {
		$status_greeting = "updated";
	}
	
	if ($_REQUEST['new'] == "yes") {
		$status_greeting = "created";	
	}
	
	/* Get User Details */		
	$userresults = mysql_query("SELECT email, gecos FROM users WHERE uid = '{$_SESSION['uid']}'  ")	or die("Query failed: " . mysql_error());
	if ($userresultsarray = mysql_fetch_array($userresults)) {
		do {
			$user_email = $userresultsarray['email'];
			$user_name = $userresultsarray['gecos']; 
		}
		while ($userresultsarray = mysql_fetch_array($userresults));
	}		
	
	/* Send Owner Email */		
	if ($_REQUEST['send_owner'] == 1) {
		/* get owner details */	
		$ownerresults = mysql_query("SELECT email, gecos FROM users WHERE uid = '{$_REQUEST['owner_id']}' ")	or die("Query failed: " . mysql_error());
		if ($ownerresultsarray = mysql_fetch_array($ownerresults)) {
			do {			
				 taskemail($ownerresultsarray['gecos'],$ownerresultsarray['email'], $user_name, $user_email, $status_greeting, $_REQUEST['title'], $_REQUEST['task_id']);
			}
			while ($ownerresultsarray = mysql_fetch_array($ownerresults));
		}			
	}
	
	/* Send Account Manager Email */		
	if ($_REQUEST['send_manager'] == 1) {
		/* get accountmanager details */	
		$amresults = mysql_query("SELECT email, gecos FROM users WHERE uid = '{$_REQUEST['accountmanager']}'  ")	or die("Query failed: " . mysql_error());
		if ($amresultsarray = mysql_fetch_array($amresults)) {
			do {
				 taskemail($amresultsarray['gecos'],$amresultsarray['email'], $user_name, $user_email, $status_greeting, $_REQUEST['title'], $_REQUEST['task_id']);	
			}
			while ($amresultsarray = mysql_fetch_array($amresults));
		}		
	}
	
	/* Send Production Email */		
	if ($_REQUEST['send_prod'] == 1) {	
		$to_name = "David Hunter";
		$to_email = "dhunter@pauanui.net.nz";
		 taskemail($to_name,$to_email, $user_name, $user_email, $status_greeting, $_REQUEST['title'], $_REQUEST['task_id'])	;
	}

	/* +++ close window +++ */	
	if ($_REQUEST['template'] == "no") {
		echo "<script language=\"javascript\">
			window.setTimeout('window.close()',10);
			</script>";
	}
	
	/* +++ return to previous display/browse mode +++ */
	if ($_REQUEST['p_mode'] >'') {
		$_REQUEST['mode'] = $_REQUEST['p_mode'];
	}
	else {
		$_REQUEST['mode'] = "browse";
	}
	
	/*	function taskemail($to_name,$to_email, $from_name, $from_email, $status_greeting, $task_title, $task_id) { */
	function taskemail($to_name,$to_email, $from_name, $from_email, $status_greeting, $task_title, $task_id) {
		
		$subject = $_SERVER['SERVER_NAME']." Webhaven Task ".$task_title." (#".$task_id.") has been ".$status_greeting." by ".$from_name;
		
		$message = "\n";
		$message .= "Greetings $to_name,\n";
		$message .= "\n";
		$message .= $_SERVER['SERVER_NAME']." Webhaven Task '$task_title' (#$task_id') has been $status_greeting by $to_name.\n";
		$message .= "\n";
		$message .= $_REQUEST['url']."\n";
		$message .= "--------------------------------------------------\n";
		$message .= "\n";
		$message .= "Title: ".$_REQUEST['title']."\n";
		$message .= "Date Due: ".$_REQUEST['due_dd']."-".$_REQUEST['due_mm']."-".$_REQUEST['due_yy']."\n";
		$message .= "Priority: ".$_REQUEST['priority']."\n";
		$message .= "Status: ".$_REQUEST['status']."\n";
		$message .= "Notes:\n";
		$message .= $_REQUEST['notes']."\n";
			
		mail($to_name."<".$to_email.">",$subject, $message, "From: $from_name <$from_email> \r \n");
		  
	}
?>