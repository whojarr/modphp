<?php
/* +++INCLUDE module NAV+++ */
if ($_REQUEST['template'] != "no" || $_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/'.$_REQUEST['function'].'_nav.inc');	
}


/* +++SET DEFAULT MODE+++ */

if (!isset($_REQUEST['mode'])) {
    $_REQUEST['mode'] = "display";
}


/* +++REMOVE USER+++ */

if ($_REQUEST['mode']  == "delete_user") {
	include('mod_users/includes/users_delete_user.inc');
}


/* +++ADD USER FORM+++ */

if ($_REQUEST['mode']  == "add_user_form") {
	include('mod_users/includes/users_add_user_form.inc');
}

/* +++ADD USER+++ */

if ($_REQUEST['mode']  == "add_user") {
	include('mod_users/includes/users_add_user.inc');
}

/* +++UPDATE USER+++ */

if ($_REQUEST['mode']  == "update_user") {
	include('mod_users/includes/users_update_user.inc');
}

/* +++EDIT USER FORM+++ */

if ($_REQUEST['mode']  == "edit_user") {
	include('mod_users/includes/users_edit_user.inc');
}


/* +++ADD USER GROUPS+++ */

if ($_REQUEST['mode']  == "add_users_groups") {
	include('mod_users/includes/users_users_groups.inc');
}


/* +++ADD USER GROUPS FORM+++ */

if ($_REQUEST['mode']  == "add_users_groups_form") {
	include('mod_users/includes/users_users_groups_form.inc');
}


/* +++ADD GROUP+++ */

if ($_REQUEST['mode']  == "add_group") {
	include('mod_users/includes/users_add_group.inc');
}

/* +++ADD STATUS+++ */

if ($_REQUEST['mode']  == "add_status") {
	include('mod_users/includes/users_add_status.inc');
}

/* +++UPDATE STATUS+++ */

if ($_REQUEST['mode']  == "update_status") {
	include('mod_users/includes/users_update_status.inc');
}


/* +++EDIT STATUS FORM+++ */ 
 
if ($_REQUEST['mode']  == "edit_status") {
	include('mod_users/includes/users_edit_status.inc');
}

/* +++ADD STATUS FORM+++ */ 
 
if ($_REQUEST['mode']  == "add_status_form") {
include('mod_users/includes/users_add_status_form.inc');
}

/* +++REMOVE STATUS+++ */

if ($_REQUEST['mode']  == "delete_status") {
	include('mod_users/includes/users_delete_status.inc');
}

/* +++DISPLAY STATUS+++ */

if ($_REQUEST['mode']  == "mod_status") {
	include('mod_users/includes/users_display_status.inc');
}

/* +++UPDATE GROUP+++ */

if ($_REQUEST['mode']  == "update_group") {
	include('mod_users/includes/users_update_group.inc');
}


/* +++REMOVE GROUP+++ */

if ($_REQUEST['mode']  == "delete_group") {
	include('mod_users/includes/users_delete_group.inc');
}


/* +++ADD MODULE ACCESS+++ */

if ($_REQUEST['mode']  == "add_mod_access") {
	include('mod_users/includes/users_add_mod_access.inc');
}

/* +++UPDATE USER MODULE ACCESS+++ */

if ($_REQUEST['mode']  == "update_user_mod_access") {
	include('mod_users/includes/users_update_user_mod_access.inc');
}

/* +++EDIT USER MODULE ACCESS+++ */

if ($_REQUEST['mode']  == "edit_user_mod_access") {
	include('mod_users/includes/users_edit_user_mod_access.inc');
}

/* +++UPDATE GROUP MODULE ACCESS+++ */

if ($_REQUEST['mode']  == "update_group_mod_access") {
	include('mod_users/includes/users_update_group_mod_access.inc');
}

/* +++EDIT GROUP MODULE ACCESS+++ */

if ($_REQUEST['mode']  == "edit_group_mod_access") {
	include('mod_users/includes/users_edit_group_mod_access.inc');
}

/* +++DISPLAY MODULE ACCESS+++ */

if ($_REQUEST['mode']  == "mod_access") {
	include('mod_users/includes/users_display_mod_access.inc');
}


/* +++DISPLAY ALL CURRENT USERS+++ */

if ($_REQUEST['mode']  == "display") {
	include('mod_users/includes/users_display.inc');
}

?>