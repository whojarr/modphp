<comment>+++ Users +++</comment>
<if variable="form.uid">
	
	<comment>+++ Insert +++</comment>
	<if not variable="form.uid is new">
		<sqlquery source="sql" 
			host="&var.thedatabase:none;"
			query="insert into modules_users (id, uid , module_id) 
			values (NULL, '&form.uid;', '0')"/>
		<redirect to="&page.self;?function=users&mode=edit_user_mod_access&uid=&form.uid;"/>
	</if>
	<comment>+++ Select User +++</comment>
	<else>
		Click The User To Add Module Access:
		<table width="100%" border="0" cellpadding="3" cellspacing="1">
			<tr bgcolor="#DDDDDD">
				<td  align="left">
					Name
				</td>
				<td align="left">
					Company
				</td>
			</tr>
			<set variable="var.notin" value="''" />
			<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT uid FROM modules_users" scope="notin">
			 <append variable="var.notin">,</append>
			 <append variable="var.notin">&notin.uid;</append>
			</emit>

			<emit source="sql" host="&var.thedatabase:none;" query="SELECT * FROM users WHERE users.uid NOT IN (&var.notin;)" scope="sql">
			<tr>
				<td align="left">
					&sql.counter;.
					<a href="&page.self;?function=users&mode=add_mod_access&uid=&sql.uid;"> &sql.name;</a>
				</td>
				<td align="left">
					
					<emit source="sql" host="&var.thedatabase:none;" scope="company" query="select * from companies where id = '&sql.company_id:mysql;'">	
					&company.Company;
					</emit>
				</td>
			</tr>
			
			</emit>

			<else>		
				<tr>
					<td colspan="5" align="center">
						No Users Available
					</td>
				</tr>
			</else>

		</table>
	</else>
</if>

<comment>+++ Groups +++</comment>
<if variable="form.gid">
	<comment>+++ Insert +++</comment>
	<if not variable="form.gid is new">
		<sqlquery source="sql" 
			host="&var.thedatabase:none;"
			query="insert into modules_groups (id, group_id , module_id) 
			values (NULL, '&form.gid;', '0')"/>
		<redirect to="&page.self;?mode=edit_group_mod_access&group_id=&form.gid;"/>
	</if>
	<comment>+++ Select Group +++</comment>
	<else>
		Click The Group To Add Module Access:
		<table width="100%" border="0" cellpadding="3" cellspacing="1">
			<tr bgcolor="#DDDDDD">
				<td  align="left">
					Name
				</td>
				<td align="left">
					Company
				</td>
			</tr>
			<set variable="var.notin" value="''" />
			<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT group_id FROM modules_groups" scope="notin">
			 <append variable="var.notin">,</append>
			 <append variable="var.notin">&notin.group_id;</append>
			</emit>

			<emit source="sql" host="&var.thedatabase:none;" query="SELECT * FROM groups WHERE groups.id NOT IN (&var.notin;)" scope="sql">
			<tr>
				<td align="left">
					&sql.counter;.
					<a href="&page.self;?function=users&mode=add_mod_access&gid=&sql.id;"> &sql.name;</a>
				</td>
				<td align="left">
					
					<emit source="sql" host="&var.thedatabase:none;" scope="company" query="select * from companies where id = '&sql.company_id:mysql;'">	
					&company.Company;
					</emit>
				</td>
			</tr>
			
			</emit>

			<else>		
				<tr>
					<td colspan="5" align="center">
						No Groups Available
					</td>
				</tr>
			</else>

		</table>
	</else>
</if>

