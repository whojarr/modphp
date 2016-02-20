<?php
	/* +++ Process Login +++*/

	if ($_POST['mode'] == "client_login") {
		unset($login_status);
		unset($login_error);
		$modresults = mysql_query("SELECT * FROM users WHERE name = '".$_POST['login']."' ")	or die("Query failed: " . mysql_error());
		if ($modresultsarray = mysql_fetch_array($modresults)) {
			do {
				$password = $modresultsarray['password'];
				if (crypt($_POST['password'], $password) == $password) {
					$login_status = "1";
					
					/* +++ Get Module Access +++ */
					$accessresults = mysql_query("
						SELECT *
						FROM modules_users
						WHERE modules_users.uid = '6' 
						")	or die("Query failed: " . mysql_error());
					if ($accessresultsarray = mysql_fetch_array($accessresults)) {
						do {
							if (isset($user_modules)) {
								$user_modules = $user_modules.",".$accessresultsarray['module_id'];
							}
							else {
								$user_modules = $user_modules.$accessresultsarray['module_id'];
							}
						}
						while ($accessresultsarray = mysql_fetch_array($accessresults));
					}
					
					/* +++ Set Session Variables +++ */
					$_SESSION['uid'] = $modresultsarray['uid'];
					$_SESSION['gecos'] = $modresultsarray['gecos'];
					$_SESSION['company_id'] = $modresultsarray['company_id'];
					$_SESSION['user_modules'] = $user_modules;						

				}
				else {
					$login_status = "0";
					$login_error = "password incorrect";
				}
			}
			while ($modresultsarray = mysql_fetch_array($modresults));
		}
		else {
			$login_status = "0";
			$login_error = "username incorrect";
		}
	}
	
	/* +++ Login Failed OR Logout +++ */	
	if ($login_status != "1" || $_GET['session_logout'] == "1") {
		session_destroy();
		unset($_SESSION);
		include('login.php');
		exit;
	}
	
	/* +++ Login OK +++ */	
?>