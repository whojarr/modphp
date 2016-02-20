<?php
	if ($_REQUEST['password'] < '') {
 		$major_error = "true";
 		$password_error = "true";
 		$_REQUEST['mode'] = "edit_user";
	}

 	$userresults = mysql_query("
		SELECT name 
		FROM users 
		WHERE uid = '{$_REQUEST['uid']}'
		")	or die("Query failed: " . mysql_error());
	if ($userresultsarray = mysql_fetch_array($userresults)) {
		do {
			if ($userresultsarray['name'] == $_REQUEST['login']) {
				$loginsame = "true";
			}
			else {
				$loginsame = "false";
			}
		}
		while ($userresultsarray = mysql_fetch_array($userresults));
	}

	if ($loginsame == "false") {
		$loginresults = mysql_query("
			SELECT name 
			FROM users 
			WHERE name = '{$_REQUEST['login']}'
			")	or die("Query failed: " . mysql_error());
		if ($loginresultsarray = mysql_fetch_array($loginresults)) {
			do {
				$login = $loginresultsarray['name'];
			}
			while ($loginresultsarray = mysql_fetch_array($loginresults));
		}
		if ($login == $_REQUEST['login']) {
			$new_login_dup == "true";
			$major_error = "true";
			$_REQUEST['mode'] = "edit user";
			$_REQUEST['loginerrorname'] == $_REQUEST['login'];
			$_REQUEST['login'] = "";
		}
	}

	if ($major_error != "true") {
		if ($_REQUEST['login'] > '') {
			if ($_REQUEST['password'] == "[Complete to Update]") {
				$userupdate = mysql_query("
					UPDATE users SET 
                name = '{$_REQUEST['login']}',
                gecos = '{$_REQUEST['gecos']}',
                email = '{$_REQUEST['email']}',
                phone = '{$_REQUEST['phone']}',
                web = '{$_REQUEST['web']}',
                company_id = '{$_REQUEST['company_id']}'
                WHERE uid = '{$_REQUEST['uid']}'
                ") or die("Query failed: " . mysql_error());
			}	

			else {
				$password = crypt($_REQUEST['password']);
				$userupdate = mysql_query("
					UPDATE users SET 
					password = '$password',
					name = '{$_REQUEST['login']}',
					gecos = '{$_REQUEST['gecos']}',
					email = '{$_REQUEST['email']}',
					phone = '{$_REQUEST['phone']}',
					web = '{$_REQUEST['web']}',
					company_id = '{$_REQUEST['company_id']}'
					WHERE uid = '{$_REQUEST['uid']}'
					") or die("Query failed: " . mysql_error());			
			}
		}
	$_REQUEST['mode'] = "display";		
	}
?>