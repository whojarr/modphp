<form action="<?php echo $_SERVER['PHP_SELF'] ?>" name="mainform" method="get">
<input type="hidden" name="function" value="users">
<input type="hidden" name="action" value="view_companies_groups">

<?php
/* +++ USERS +++ */
?>

<div class="groupBorder">

<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=add_user_form"><img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right"></a>

<div class="groupHeader">Current Users </div>
	
	<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td>
			Company
		</td>
		<td>
			Name
		</td>
		<td>
			Groups
		</td>
		<td>
			
		</td>
	</tr>

	<?php
		/* Display Users */
		$usersresults = mysql_query("
			SELECT *, users.name AS user_name, companies.name as company_name 
			FROM users 
			LEFT JOIN companies ON companies.id = users.company_id
			")	or die("Query failed: " . mysql_error());
		$rowcount = 1;
		if ($usersresultsarray = mysql_fetch_array($usersresults)) {
			do {
				if (fmod_round ($rowcount++,2) == 0) {
					echo "<tr class=\"even\">";
				}
				else {
					echo "<tr class=\"odd\">";
				}
				echo "<td>".$usersresultsarray['company_name']."</td>";
				echo "<td>".$usersresultsarray['user_name']."</td>";
				echo "<td>";
				
				$groupsresults = mysql_query("
					SELECT *
					FROM users_groups
					LEFT JOIN groups ON groups.id = users_groups.group_id
					WHERE uid = '{$usersresultsarray['uid']}'
					")	or die("Query failed: " . mysql_error());
					
				if (mysql_num_rows($groupsresults) > 0) {	
					echo "<select>";
					echo "	<option value=\"\">Groups (".mysql_num_rows($groupsresults).")</option>";
					
					if ($groupsresultsarray = mysql_fetch_array($groupsresults)) {
						do {
							echo "<option value=\"\">".$groupsresultsarray['name']."</option>";
						}
						while ($groupsresultsarray = mysql_fetch_array($groupsresults));
					}

					echo "</select>";		
				}
				?>
				</td>
				<td align="right">
			 		<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=delete_user&uid=<?php echo $usersresultsarray['uid'] ?>" onclick="return confirm('Are you sure you want to delete?')"><img src="images/icons/delete.gif" border="0" title="Trash"></a> 
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=edit_user&uid=<?php echo $usersresultsarray['uid'] ?>"><img src="images/icons/edit.gif" border="0" title="Edit"></a>
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=add_users_groups_form&uid=<?php echo $usersresultsarray['uid'] ?>"><img src="images/icons/link.gif" border="0" title="Link"></a>
		</td>
				
				<?php			
				echo "</td>";
				echo "</tr>";
			}
			while ($usersresultsarray = mysql_fetch_array($usersresults));
		}
		else {
			echo "<tr><td>No Users Available</td></tr>";
		}			
	?>	
</table>
	
</div>

<br>

<?php
/* +++ GROUPS +++ */
?>

<div class="groupBorder">

<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=add_group_form"><img src="images/icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align="right"></a>

<div class="groupHeader">Current Groups</div>
	
	<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td>
			Group
		</td>
		<td>
			Description
		</td>
		<td>
			Users
		</td>
		<td>
			Companies
		</td>
		<td>
		
		</td>
	</tr>

	<?php
		/* Display Groups */
		$groupsresults = mysql_query("
			SELECT *, groups.name AS group_name
			FROM groups 
			")	or die("Query failed: " . mysql_error());
		$rowcount = 1;
		if ($groupsresultsarray = mysql_fetch_array($groupsresults)) {
			do {
				if (fmod_round ($rowcount++,2) == 0) {
					echo "<tr class=\"even\">";
				}
				else {
					echo "<tr class=\"odd\">";
				}
				echo "<td>".$groupsresultsarray['group_name']."</td>";
				echo "<td>".$groupsresultsarray['description']."</td>";
				echo "<td>";
				/* Group Users */
				$groupusersresults = mysql_query("
					SELECT *
					FROM users_groups
					LEFT JOIN users ON users.uid = users_groups.uid
					WHERE group_id = '{$groupsresultsarray['id']}'
					")	or die("Query failed: " . mysql_error());
					
				if (mysql_num_rows($groupusersresults) > 0) {	
					echo "<select>";
					echo "	<option value=\"\">Users (".mysql_num_rows($groupusersresults).")</option>";
					
					if ($groupusersresultsarray = mysql_fetch_array($groupusersresults)) {
						do {
							echo "<option value=\"\">".$groupusersresultsarray['name']."</option>";
						}
						while ($groupusersresultsarray = mysql_fetch_array($groupusersresults));
					}

					echo "</select>";		
				}
				
				echo "</td>";
				echo "<td>";
				/* Group Companies */
				$groupusersresults = mysql_query("
					SELECT *
					FROM companies_groups
					LEFT JOIN companies ON companies.id = companies_groups.company_id
					WHERE group_id = '{$groupsresultsarray['id']}'
					")	or die("Query failed: " . mysql_error());
					
				if (mysql_num_rows($groupusersresults) > 0) {	
					echo "<select>";
					echo "	<option value=\"\">Companies (".mysql_num_rows($groupusersresults).")</option>";
					
					if ($groupusersresultsarray = mysql_fetch_array($groupusersresults)) {
						do {
							echo "<option value=\"\">".$groupusersresultsarray['name']."</option>";
						}
						while ($groupusersresultsarray = mysql_fetch_array($groupusersresults));
					}

					echo "</select>";		
				}
				
				echo "</td>";				
				?>
				
				<td align="right">
			 		<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=delete_user&uid=<?php echo $groupsresultsarray['uid'] ?>" onclick="return confirm('Are you sure you want to delete?')"><img src="images/icons/delete.gif" border="0" title="Trash"></a> 
					<a href="&page.self;?function=users&mode=edit_user&uid=<?php echo $groupsresultsarray['uid'] ?>"><img src="images/icons/edit.gif" border="0" title="Edit"></a>
					<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&mode=add_users_groups_form&uid=<?php echo $groupsresultsarray['uid'] ?>"><img src="images/icons/link.gif" border="0" title="Link"></a>
		</td>
				
				<?php			
				echo "</td>";
				echo "</tr>";
			}
			while ($groupsresultsarray = mysql_fetch_array($groupsresults));
		}
		else {
			echo "<tr><td>No Users Available</td></tr>";
		}			
	?>	
</table>
	
</div>