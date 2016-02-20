<sqlquery source="sql" host="&var.thedatabase:none;" query="delete from users_groups where uid  = '&form.uid:mysql;'"/>

<emit source="values" values="&form.name;">
	
	<if variable="form.&_.value; is CHECKED">

<sqlquery source="sql" host="&var.thedatabase:none;" query="insert into users_groups (uid, group_id) values ('&form.uid:mysql;', '&_.value:mysql;')"/>

	</if>

	<set variable="form.mode" value="display"/>
	
</emit>	
