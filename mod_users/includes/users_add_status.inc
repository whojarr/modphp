	<if not variable="form.status is ?*">
	<set variable="form.function" value="users"/>
	<set variable="form.mode" value="add_status_Form"/>
	<set variable="form.status_error" value="true"/>
	<set variable="var.add_status_error" value="true"/>
	</if>
	
	<if not variable="var.add_status_error is true">
	
	<sqlquery source="sql" host="&var.thedatabase:none;" query="insert into userstatus (id, status, description) values (null, '&form.status:mysql;', '&form.description:mysql;')"/>
	
		<set variable="form.mode" value="mod_status"/>
	</if>