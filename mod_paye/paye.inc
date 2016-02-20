<?php
/* SETUP ACCOUNT ID's FOR WAGES */
$wages_accounts_results = mysql_query("
SELECT id 
FROM cashbook_accounts
WHERE name = 'WAGES'
")	or die("Query failed: " . mysql_error());

if ($wages_accounts_resultsarray = mysql_fetch_array($wages_accounts_results)) {
	do {
		if (!isset($wages_ids)) {
			$wages_ids = "'".$wages_accounts_resultsarray['id']."'";
		}
		else {
			$wages_ids = $wages_ids.",'".$wages_accounts_resultsarray['id']."'";
		}
	}
	while ($wages_accounts_resultsarray = mysql_fetch_array($wages_accounts_results));
}


/* +++INCLUDE paye NAV+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/paye_nav.inc');	
}


/* +++INCLUDE paye SEARCH+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/paye_filter.inc');	
}


/* +++SET DEFAULT MODE+++ */

if (!isset($_REQUEST['mode'])) {
    $_REQUEST['mode'] = "display";
}


/* +++DELETE paye+++ */

if ($_REQUEST['mode']  == "delete") {
	include('mod_paye/includes/paye_delete.inc');
}


/* +++ADD paye+++ */

if ($_REQUEST['mode']  == "add") {
	include('mod_paye/includes/paye_add.inc');
}


/* +++ADD paye TYPE+++ */

if ($_REQUEST['mode']  == "add_types") {
	include('mod_paye/includes/paye_add_types.inc');
}


/* +++ADD paye ACCOUNT+++ */

if ($_REQUEST['mode']  == "add_accounts") {
	include('mod_paye/includes/paye_add_accounts.inc');
}


/* +++EDIT paye+++ */

if ($_REQUEST['mode']  == "edit") {
	include('mod_paye/includes/paye_edit.inc');
}


/* +++EDIT paye TYPES +++ */

if ($_REQUEST['mode']  == "edit_types") {
	include('mod_paye/includes/paye_edit_types.inc');
}


/* +++EDIT paye ACCOUNTS +++ */

if ($_REQUEST['mode']  == "edit_accounts") {
	include('mod_paye/includes/paye_edit_accounts.inc');
}

/* +++UPDATE paye+++ */

if ($_REQUEST['mode']  == "update") {
	include('mod_paye/includes/paye_update.inc');
}

/* +++UPDATE paye+++ TYPES*/

if ($_REQUEST['mode']  == "update_types") {
	include('mod_paye/includes/paye_update_types.inc');
}
/* +++UPDATE paye ACCOUNTS+++ */

if ($_REQUEST['mode']  == "update_accounts") {
	include('mod_paye/includes/paye_update_accounts.inc');
}

/* +++UPLOAD CSV +++ */

if ($_REQUEST['mode']  == "import_file") {
	include('mod_paye/includes/paye_import_file.inc');
}


/* +++ IMPORT FORM +++ */

if ($_REQUEST['mode']  == "import_form") {
	include('mod_paye/includes/paye_import_form.inc');
}


/* +++UPLOAD CSV +++ */

if ($_REQUEST['mode']  == "import_transactions") {
	include('mod_paye/includes/paye_import_transactions.inc');
}


/* +++DISPLAY paye TYPES+++ */

if ($_REQUEST['mode']  == "display_types") {
	include('mod_paye/includes/paye_display_types.inc');
}


/* +++DISPLAY paye ACCOUNTS+++ */

if ($_REQUEST['mode']  == "display_accounts") {
	include('mod_paye/includes/paye_display_accounts.inc');
}


/* +++DISPLAY paye+++ */

if ($_REQUEST['mode']  == "display") {
	include('mod_paye/includes/paye_display.inc');
}


/* +++DISPLAY paye TRANSACTIONS+++ */

if ($_REQUEST['mode']  == "display_transactions") {
	include('mod_paye/includes/paye_display_transactions.inc');
}


/* +++DISPLAY paye REPORT ACCOUNTS+++ */

if ($_REQUEST['mode']  == "display_report_accounts") {
	include('mod_paye/includes/paye_display_report_accounts.inc');
}


/* +++DISPLAY paye REPORT GST+++ */

if ($_REQUEST['mode']  == "display_report_gst") {
	include('mod_paye/includes/paye_display_report_gst.inc');
}


/* +++DISPLAY paye REPORT PAYE+++ */

if ($_REQUEST['mode']  == "display_report_paye") {
	include('mod_paye/includes/paye_display_report_paye.inc');
}
?>