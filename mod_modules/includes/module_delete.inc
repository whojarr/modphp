<emit source="sql" host="&var.thedatabase:none;" scope="sql" query="select * from modules_files where module_id = '&form.id:mysql;'">	

<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from modules_files where id = '&sql.id:mysql;'"/>

<writefile filename="&sql.id:none;.&sql.file:none;" chroot="modules/files/" remove></writefile>

</emit>


<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from modules where id = '&form.id:mysql;'"/>


<set variable="form.mode" value="display"/>
