<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from groups where id = '&form.group_id:mysql;'"/>

<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from users_groups where group_id = '&form.group_id:mysql;'"/>

<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from companies_groups where group_id = '&form.group_id:mysql;'"/>

	<set variable="form.mode" value="display"/>	