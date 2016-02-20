<table width="100%" border="0" cellpadding="3" cellspacing="1" align="center">

	<tr bgcolor="#DDDDDD">
		<td align="center">id	</td>
		<td align="center">Module</td>
		<td align="center">Title</td>
		<td align="center">Group</td>
		<td align="center">Owner</td>
		<td align="center">Date Due</td>
		<td align="center">Status</td>
		<td align="right">Cost</td>
		<td align="right">Value</td>
		<td align="center">PDF</td>
	</tr>

<emit source="sql" host="&var.thedatabase:none;" scope="sql" 
	query="
		select 
		DISTINCT tasks.id, tasks.*, 
		groups.name AS group_name, 
		users.name AS user_name, 
		modules.name AS module_name,
		modules.mod_function AS mod_function,
		modules.parent AS mod_parent
		from tasks 
		left join tasks_groups on tasks_groups.task_id = tasks.id
		left join groups on groups.id = tasks_groups.group_id
		left join users_groups on users_groups.group_id = tasks_groups.group_id
		left join users on users.uid = tasks.owner_id
		left join tasks_modules on tasks_modules.task_id = tasks.id
		left join modules on modules.id = tasks_modules.module_id
		WHERE tasks_modules.module_id > 0
		ORDER BY status, module_name
		">

	<if expr="( &sql.counter; % 2 ) == 0">
		<tr bgcolor="#e9e9e9">
	</if>
	<else>
		<tr bgcolor="#FFFFFF">
	</else>
		<td align="center">&sql.id;</td>
		<td align="left"><a href="&page.self;?function=&sql.mod_function;&nav=&sql.mod_parent;">&sql.module_name;</a></td>
		<td align="left">&sql.title;</td>
		<td align="center">&sql.group_name;</td>
		<td align="center">&sql.user_name;</td>
		<td align="center"><a href="#" title="&sql.Date_Invoice;">&sql.date_due;</a></td>
		<td align="center">&sql.status;</td>
		<td align="right">$&sql.cost;</td>
		<td align="right">$&sql.value;</td>
		<td align="center"></td>
	</tr>

</emit>

<else>
	<tr>
		<td colspan=9 align=center>
			<br><br>No Task for Current Modules<br>
			<br><br>
		</td>
	</tr>
</else>

</table>
