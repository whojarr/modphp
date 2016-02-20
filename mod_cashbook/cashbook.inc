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

/* SETUP ACCOUNT ID's WHERE GST APPLIES */
$gst_accounts_results = mysql_query("
SELECT id 
FROM cashbook_accounts
WHERE gst = '1'
")	or die("Query failed: " . mysql_error());

if ($gst_accounts_resultsarray = mysql_fetch_array($gst_accounts_results)) {
	do {
		if (!isset($gst_ids)) {
			$gst_ids = "'".$gst_accounts_resultsarray['id']."'";
		}
		else {
			$gst_ids = $gst_ids.",'".$gst_accounts_resultsarray['id']."'";
		}
	}
	while ($gst_accounts_resultsarray = mysql_fetch_array($gst_accounts_results));
}

/* +++INCLUDE CashBook NAV+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/cashbook_nav.inc');	
}


/* +++INCLUDE CashBook SEARCH+++ */
if ($_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/cashbook_filter.inc');	
}


/* +++SET DEFAULT MODE+++ */

if (!isset($_REQUEST['mode'])) {
    $_REQUEST['mode'] = "display_transactions";
}


/* +++DELETE cashbook+++ */

if ($_REQUEST['mode']  == "delete") {
	include('mod_cashbook/includes/cashbook_delete.inc');
}


/* +++ADD cashbook+++ */

if ($_REQUEST['mode']  == "add") {
	include('mod_cashbook/includes/cashbook_add.inc');
}


/* +++ADD cashbook TYPE+++ */

if ($_REQUEST['mode']  == "add_types") {
	include('mod_cashbook/includes/cashbook_add_types.inc');
}


/* +++ADD cashbook ACCOUNT+++ */

if ($_REQUEST['mode']  == "add_accounts") {
	include('mod_cashbook/includes/cashbook_add_accounts.inc');
}


/* +++EDIT cashbook+++ */

if ($_REQUEST['mode']  == "edit") {
	include('mod_cashbook/includes/cashbook_edit.inc');
}


/* +++EDIT cashbook TYPES +++ */

if ($_REQUEST['mode']  == "edit_types") {
	include('mod_cashbook/includes/cashbook_edit_types.inc');
}


/* +++EDIT cashbook ACCOUNTS +++ */

if ($_REQUEST['mode']  == "edit_accounts") {
	include('mod_cashbook/includes/cashbook_edit_accounts.inc');
}

/* +++UPDATE cashbook+++ */

if ($_REQUEST['mode']  == "update") {
	include('mod_cashbook/includes/cashbook_update.inc');
}

/* +++UPDATE cashbook+++ TYPES*/

if ($_REQUEST['mode']  == "update_types") {
	include('mod_cashbook/includes/cashbook_update_types.inc');
}
/* +++UPDATE cashbook ACCOUNTS+++ */

if ($_REQUEST['mode']  == "update_accounts") {
	include('mod_cashbook/includes/cashbook_update_accounts.inc');
}

/* +++UPLOAD CSV +++ */

if ($_REQUEST['mode']  == "import_file") {
	include('mod_cashbook/includes/cashbook_import_file.inc');
}


/* +++ IMPORT FORM +++ */

if ($_REQUEST['mode']  == "import_form") {
	include('mod_cashbook/includes/cashbook_import_form.inc');
}


/* +++UPLOAD CSV +++ */

if ($_REQUEST['mode']  == "import_transactions") {
	include('mod_cashbook/includes/cashbook_import_transactions.inc');
}


/* +++DISPLAY cashbook TYPES+++ */

if ($_REQUEST['mode']  == "display_types") {
	include('mod_cashbook/includes/cashbook_display_types.inc');
}


/* +++DISPLAY cashbook ACCOUNTS+++ */

if ($_REQUEST['mode']  == "display_accounts") {
	include('mod_cashbook/includes/cashbook_display_accounts.inc');
}


/* +++DISPLAY cashbook+++ */

if ($_REQUEST['mode']  == "display") {
	include('mod_cashbook/includes/cashbook_display.inc');
}


/* +++DISPLAY cashbook TRANSACTIONS+++ */

if ($_REQUEST['mode']  == "display_transactions") {
	include('mod_cashbook/includes/cashbook_display_transactions.inc');
}


/* +++DISPLAY cashbook REPORT ACCOUNTS+++ */

if ($_REQUEST['mode']  == "display_report_accounts") {
	include('mod_cashbook/includes/cashbook_display_report_accounts.inc');
}


/* +++DISPLAY cashbook REPORT ACCOUNTS+++ */

if ($_REQUEST['mode']  == "display_report_accounts_summary") {
	include('mod_cashbook/includes/cashbook_display_report_accounts_summary.inc');
}


/* +++DISPLAY cashbook REPORT GST+++ */

if ($_REQUEST['mode']  == "display_report_gst") {
	include('mod_cashbook/includes/cashbook_display_report_gst.inc');
}


/* +++DISPLAY cashbook REPORT PAYE+++ */

if ($_REQUEST['mode']  == "display_report_paye") {
	include('mod_cashbook/includes/cashbook_display_report_paye.inc');
}
?>