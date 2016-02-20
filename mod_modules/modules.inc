<?php

/* +++INCLUDE modules NAV+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/modules_nav.inc');	
}

/* +++INCLUDE modules SEARCH+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/modules_filter.inc');	
}

/* +++SET DEFAULT MODE+++ */
if (!isset($_REQUEST['mode'])) {
    $_REQUEST['mode'] = "display";
}

/*+++TRASH module FILE+++*/
if ($_REQUEST['mode']  == "delete_file") {
	include('mod_modules/includes/module_delete_file.inc');
}

/*+++UPLOAD module FILE+++*/
if ($_REQUEST['mode']  == "upload_file") {
	include('mod_modules/includes/module_upload_file.inc');
}

/*+++TRASH INSTRUCTIONS+++*/
if ($_REQUEST['mode']  == "delete") {
	include('mod_modules/includes/module_delete.inc');
}

/*+++ADD INSTRUCTIONS+++*/
if ($_REQUEST['mode']  == "add") {
	include('mod_modules/includes/module_add.inc');
}

/*+++EDIT INSTRUCTIONS+++*/
if ($_REQUEST['mode']  == "update") {
	include('mod_modules/includes/module_update.inc');
}

/*+++Report+++*/
if ($_REQUEST['mode']  == "report") {
	include('mod_modules/includes/module_report.inc');
}

/*+++Task Report+++*/
if ($_REQUEST['mode']  == "tasks") {
	include('mod_modules/includes/module_tasks.inc');
}

/*+++EDIT INSTRUCTIONS FORM+++*/
if ($_REQUEST['mode']  == "edit") {
	include('mod_modules/includes/module_edit.inc');
}

/*+++EDIT MODULE VARIABLES +++*/
if ($_REQUEST['mode']  == "edit_vars") {
	include('mod_modules/includes/module_edit_vars.inc');
}

/*+++UPDATE MODULE VARIABLES +++*/
if ($_REQUEST['mode']  == "update_vars") {
	include('mod_modules/includes/module_update_vars.inc');
}

/*+++DISPLAY MODULE VARIABLES+++*/
if ($_REQUEST['mode']  == "display_vars") {
	include('mod_modules/includes/module_display_vars.inc');
}

/*+++DISPLAY ALL CURRENT ONLINE USERS+++*/
if ($_REQUEST['mode']  == "display") {
	include('mod_modules/includes/module_display.inc');
}

?>