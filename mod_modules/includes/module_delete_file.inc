<emit source="sql" host="&var.thedatabase:none;" scope="sql" query="select module_id from modules_files where id = '&form.id:none;'">	
    <set variable="var.module_id" value="&sql.module_id:none;"/>
    <set variable="form.file" value="&sql.file:none;"/>
</emit>


<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from modules_files where id = '&form.id:mysql;'"/>

<writefile filename="&form.id:none;.&form.file:none;" chroot="modules/files/" remove></writefile>
	
<set variable="form.mode" value="edit_form"/>		
<set variable="form.id" value="&var.module_id:none;"/>		
