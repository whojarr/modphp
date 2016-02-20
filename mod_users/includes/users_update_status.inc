<if not variable="form.status is ?*">
	<set variable="form.function" value="users"/>
	<set variable="form.mode" value="edit_status"/>
	<set variable="form.status_error" value="true"/>
	<set variable="var.edit_status_error" value="true"/>
</if>
	
<if not variable="var.edit_status_error is true">
	
	<sqlquery source="sql" host="&var.thedatabase:none;" query="update userstatus set status = '&form.status:mysql;', description = '&form.description:mysql;' where id = '&form.status_id:mysql;'"/>

	<set variable="form.mode" value="mod_status"/>
	
</if>