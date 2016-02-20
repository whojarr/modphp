<comment>
<if not variable="form.company_id is ?*">
<set variable="form.function" value="users"/>
<set variable="form.mode" value="add_Form"/>
<set variable="form.company_error" value="true"/>
<set variable="var.add_error" value="true"/>
No Company id
</if>
</comment>

<if not variable="var.add_error is true">
	
	<emit source="sql" host="&var.thedatabase:none;" query="select name from users where name = '&form.login:mysql;'" scope="sql">	
	<set variable="var.login" value="&sql.name;"/>
	</emit>
	<if variable="var.login is &form.login:none;">
			<set variable="var.new_login_dup" value="true"/>
			<set variable="var.major_error" value="true"/>
			<set variable="form.mode" value="add_user_form"/>	
			<set variable="form.loginerrorname" value="&form.login:none;"/>
			<set variable="form.login" value=""/>	
	</if>
	<if not variable="form.password is ?*">
			<set variable="var.major_error" value="true"/>
			<set variable="var.password_error" value="true"/>
			<set variable="form.mode" value="add_user_form"/>		
	</if>
	<if not variable="var.major_error is true">
		<if variable="form.login is ?*">
			<sqlquery source="sql" host="&var.thedatabase:none;" query="insert into users (uid, name, password, gecos, email, web, phone, company_id) 
			values (NULL, '&form.login:mysql;', encrypt('&form.password:mysql;'),'&form.gecos:mysql;','&form.email:mysql;','&form.web:mysql;', '&form.phone:mysql;', '&form.companies_id:mysql;')"/>

	<set variable="form.mode" value="display"/>
	
	   	</if>
    </if>
</if>