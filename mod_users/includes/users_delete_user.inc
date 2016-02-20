<?php
$deleteuser = mysql_query("delete from users where uid = {$_REQUEST['uid']}")	or die("Query failed: " . mysql_error());
$deletegroupuser = mysql_query("delete from users_groups where uid = {$_REQUEST['uid']}")	or die("Query failed: " . mysql_error());
$_REQUEST['mode'] = "display";
?>