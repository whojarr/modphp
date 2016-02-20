<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from userstatus where id = '&form.status_id:mysql;'"/>


	<set variable="form.mode" value="mod_status"/>	