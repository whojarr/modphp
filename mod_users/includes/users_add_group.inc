	<if not variable="form.group_name is ?*">
	<set variable="form.function" value="users"/>
	<set variable="form.mode" value="add_group_Form"/>
	<set variable="form.group_name_error" value="true"/>
	<set variable="var.add_group_error" value="true"/>
	</if>
	
	<if not variable="var.add_group_error is true">
	
	<sqlquery source="sql" host="&var.thedatabase:none;" query="insert into groups (id, name, description) values (null, '&form.group_name:mysql;', '&form.description:mysql;')"/>
	
		<set variable="form.mode" value="display"/>
	</if>