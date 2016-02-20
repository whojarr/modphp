<set variable="var.major_error" value="false"/>

	<if not variable="form.wrapupafile is ?*">
		
		<set variable="var.major_error" value="true"/>
		<set variable="form.mode" value="edit_form"/>
		<set variable="form.id" value="&form.module_id:none;"/>
		
	</if>
	
	
	<if variable="var.major_error is false">
     	
	<sqlquery source="sql" host="&var.thedatabase:none;" mysql-insert-id="form.id" query="insert into modules_files (id, module_id, file, description) values (null, '&form.module_id:none;',  '&form.file_type:mysql;', '&form.description:mysql;')"/>
	
	<writefile filename="&form.id:none;.&form.file_type:mysql;" chroot="modules/files/">&form.wrapupafile:none;</writefile>
	
	<set variable="form.mode" value="edit_form"/>
    <set variable="form.id" value="&form.module_id:none;"/>
	</if>