<?php
/* +++INCLUDE Tasks NAV+++ */
if ($_REQUEST['template'] != "no" || $_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/task_nav.inc');	
}


/* +++INCLUDE Tasks SEARCH+++ */
if ($_REQUEST['template'] != "no" || $_REQUEST['display_nav'] != "no") {
	include('mod_'.$_REQUEST['function'].'/includes/task_filter.inc');	
}


/* +++SET DEFAULT MODE+++ */

if (!isset($_REQUEST['mode'])) {
    $_REQUEST['mode'] = "browse";
}


/* +++DELETE TASK+++ */

if ($_REQUEST['mode']  == "delete") {
	include('mod_tasks/includes/task_delete.inc');
}


/* +++ADD TASK+++ */

if ($_REQUEST['mode']  == "add") {
	include('mod_tasks/includes/task_add.inc');
}


/* +++EDIT TASK+++ */

if ($_REQUEST['mode']  == "edit") {
	include('mod_tasks/includes/task_edit.inc');
}


/* +++UPDATE TASK+++ */

if ($_REQUEST['mode']  == "update") {
	include('mod_tasks/includes/task_update.inc');
}


/* +++DISPLAY TASKS+++ */

if ($_REQUEST['mode']  == "display") {
	include('mod_tasks/includes/task_display.inc');
}


/* +++BROWSE TASKS+++ */

if ($_REQUEST['mode']  == "browse") {
	include('mod_tasks/includes/task_browse.inc');
}

/*
if ($_REQUEST['prestate'] == "listall") {
	?>
	<br>
	<table bgcolor="#eeeeee" align="center" width="80%">
		<tr>
			<td>id;</td>
			<td>parent;</td>
			<td>title;</td>
			<td>notes;</td>
			<td>url;</td>
			<td>status;</td>
			<td>priority;</td>
			<td>date_due;</td>
			<td>date_modified;</td>
			<td>date_entered;</td>
			<td>type;</td>
			<td>date_bill;</td>
			<td>owner_id;</td>
			<td>duration;</td>
			<td>accountmanager;</td>
			<td>billable;</td>
			<td>budget;</td>
			<td>cost;</td>
			<td>value;</td>
		</tr>			
		<emit source="sql" host="&var.thedatabase:none;" scope="prestate" query="SELECT * FROM tasks">
			<tr>
				<td>&prestate.id;</td>
				<td>&prestate.parent;</td>
				<td>&prestate.title;</td>
				<td>&prestate.notes;</td>
				<td>&prestate.url;</td>
				<td>&prestate.status;</td>
				<td>&prestate.priority;</td>
				<td>&prestate.date_due;</td>
				<td>&prestate.date_modified;</td>
				<td>&prestate.date_entered;</td>
				<td>&prestate.type;</td>
				<td>&prestate.date_bill;</td>
				<td>&prestate.owner_id;</td>
				<td>&prestate.duration;</td>
				<td>&prestate.accountmanager;</td>
				<td>&prestate.billable;</td>
				<td>&prestate.budget;</td>
				<td>&prestate.cost;</td>
				<td>&prestate.value;</td>
			</tr>
		</emit>
	</table>
}
*/
?>