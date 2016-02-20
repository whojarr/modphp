<?php
/* Read INI File */
$file = "config/timesheets_config.inc";
$config->readINIfile($file,'');
$timesheets_conf = $config->ini_array;

$groups_admin = str_replace ('"', '', $timesheets_conf['admin']['groups']) ;

/* +++INCLUDE timesheets NAV+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/timesheets_nav.inc');	
}

/* +++INCLUDE timesheets SEARCH+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/timesheets_filter.inc');	
}

/* +++SET DEFAULT MODE+++ */
if (!isset($_REQUEST['mode'])) {
    $_REQUEST['mode'] = "display";
}

/* +++DELETE timesheets+++ */
if ($_REQUEST['mode']  == "delete") {
	include('mod_'.$_REQUEST['function'].'/includes/timesheets_delete.inc');
}

/* +++ADD timesheets+++ */
if ($_REQUEST['mode']  == "add") {
	include('mod_'.$_REQUEST['function'].'/includes/timesheets_add.inc');
}

/* +++EDIT timesheets+++ */
if ($_REQUEST['mode']  == "edit") {
	include('mod_'.$_REQUEST['function'].'/includes/timesheets_edit.inc');
}

/* +++DISPLAY timesheets+++ */
if ($_REQUEST['mode']  == "display") {
	include('mod_'.$_REQUEST['function'].'/includes/timesheets_display.inc');
}
?>