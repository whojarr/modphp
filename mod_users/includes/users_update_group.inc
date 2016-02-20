<if not variable="form.name is ?*">
	<set variable="form.function" value="users"/>
	<set variable="form.mode" value="edit_group"/>
	<set variable="form.group_name_error" value="true"/>
	<set variable="var.edit_group_error" value="true"/>
</if>
	
<if not variable="var.edit_group_error is true">
	
	<sqlquery source="sql" host="&var.thedatabase:none;" query="update groups set name = '&form.name:mysql;', description = '&form.description:mysql;' where id = '&form.group_id:mysql;'"/>

	<set variable="form.mode" value="display"/>
	
</if>