<?php
	if ($_REQUEST['status'] < ' ') {
		$_REQUEST['status'] = "wip";	
	}
	if ($_REQUEST['owner_id'] <= 0) {
		$_REQUEST['owner_id'] = $_SESSION['uid'];	
	}
?>
<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="get">

<input type="hidden" name="function" value="tasks">
<input type="hidden" name="mode" value="display">
<input type="hidden" name="orderby" value="<?php echo $_REQUEST['orderby']; ?>">

<div class="task_background_odd">
	
	<table border="0" cellspacing="0" cellpadding="5" align="center">
		<tr>
			<td>
				<b>Filters</b>
			<td>
				Status:
			</td>
			<td>
				<?php
					if (isset($_REQUEST['p_status'])) {
						$c_status = $_REQUEST['p_status'];
					}
					else {
						$c_status = $_REQUEST['status'];
					}
				?>
				<select name="status">
					<option value="%">- All -</option>
					<?php
						$statusresults = mysql_query("SELECT distinct(status) AS status FROM tasks");
						if ($statusresultsarray = mysql_fetch_array($statusresults)) {
							do {
								if ($statusresultsarray['status'] == $c_status) {
									echo "<option value=\"".$statusresultsarray['status']."\" selected>".$statusresultsarray['status']."</option>";
								}
								else {
									echo "<option value=\"".$statusresultsarray['status']."\">".$statusresultsarray['status']."</option>";
								}
							}
							while ($statusresultsarray = mysql_fetch_array($statusresults));
						}
					?>
				</select>
			</td>
			<td>
				Owner:
			</td>
			<td>
				<select name="owner_id">
					<option value="%">- All -</option>
					<?php
						$ownerresults = mysql_query("SELECT * FROM users ORDER BY name");
						if ($ownerresultsarray = mysql_fetch_array($ownerresults)) {
							do {
								if ($ownerresultsarray['uid'] == $_REQUEST['owner_id']) {
									echo "<option value=\"".$ownerresultsarray['uid']."\" selected>".$ownerresultsarray['name']."</option>";
								}
								else {
									echo "<option value=\"".$ownerresultsarray['uid']."\">".$ownerresultsarray['name']."</option>";
								}
							}
							while ($ownerresultsarray = mysql_fetch_array($ownerresults));
						}
						else {
							echo "<input type=\"hidden\" name=\"owner_id\" value=\"%\">";
						}
					?>
				</select>
			</td>
			<td>
			<input type="image" src="images/icons/view.gif" border="0" title="View"> 
			</td>
		</tr>
	</table>
</div>

</form>