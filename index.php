<?php
	error_reporting(0);
	session_start();
	/* ++++ Database And Global Vars for All Modules +++ */
	$_SESSION['dd'] = date(d); 
	$_SESSION['mm'] = date(n);
	$_SESSION['yy'] = date(Y);
	$_SESSION['url'] = $_SERVER['HTTP_REFERER'];
	
	require_once('inc/config.cls.php');
	require_once('inc/filesystem.php');	
	require_once('inc/global_functions.inc');	
	
	/* Fixed Config Variables */
	$conf_dir = "config/";
	$default_file =  "modules_config.default";
	$inc_file = "modules_config.inc";	
	
	$config = new siteConfig;
	
	/* Check Config Exits and Copy Default to .inc */
	$config->configExisits($conf_dir,$default_file, $inc_file);
	if ($_GET['debug'] == "yes") {
		echo $config->output."<br>";
	}
	/* Return Error Message */
	if ($config->error == "copy") {
		$perms = filePermissions($conf_dir);
		echo "check config folder permission ".$perms."<br>";
		exit;
	}
	
	/* Read INI File */
	$file = $conf_dir.$inc_file;
	$config->readINIfile($file,'');
	$config_details = $config->ini_array;
	
	/* Setup Database Connection */
	$db_hostname = str_replace ('"', '', str_replace (';', '', $config_details['database']['db_host'])) ;
	$db_user = str_replace ('"', '', str_replace (';', '', $config_details['database']['db_user'])) ;
	$db_password = str_replace ('"', '', str_replace (';', '', $config_details['database']['db_password'])) ;
	$db_database = str_replace ('"', '', str_replace (';', '', $config_details['database']['db_database'])) ;
	$db_connection = mysql_connect($db_hostname,$db_user,$db_password) ;
	mysql_select_db($db_database,$db_connection);
	
	/* Test Login */
	if (($_GET['session_logout'] == 1) || !isset($_SESSION['user_modules'])) {
		require('authorisation/accessmanagement.php');	
	}

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"  "http://www.w3.org/TR/1999/REC-html401-19991224/loose.dtd">
<html>
<head>
	<title><?php echo $_SESSION['gecos'] ?> :: <?php echo $_REQUEST['function'] ?> > <?php echo $_REQUEST['mode'] ?></title>
	<link rel="stylesheet" href="css/style.css" type="text/css" />
	<script src="inc/javascript.js" type="text/javascript" language="javascript1.2" charset="utf-8"></script>
	<script src="mod_nav/nav_rollover.js" type="text/javascript" language="javascript1.2" charset="utf-8"></script>
	<link rel="stylesheet" rev="stylesheet" href="mod_nav/nav_css.css" type="text/css">
</head>
<body bgcolor="#ffffff">	

<?php

/* Nav */
if ($_REQUEST['template'] != "no") {
	include('mod_nav/adminnav.php');	
}
/* Functions */
if ($_REQUEST['function'] != "nav") {
	if (isset($_REQUEST['function'])) {
		include('mod_'.$_REQUEST['function'].'/'.$_REQUEST['function'].'.inc');	
	}
}
?>
</body>
</html>