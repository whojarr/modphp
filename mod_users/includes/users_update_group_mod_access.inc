<emit source="values" from-scope="form" scope="formvars" sort="index">
 
	<if variable="formvars.index is acc_*new">
		<set variable="var.newindex" value="&_.index;" />
		<set variable="var.newmod"><replace type="words" sperator="," from="acc_,new" to="">&var.newindex;</replace></set>
		<set variable="&var.newmod;" value="&var.newmod;" />
		<comment> -- Add New Group Access -- </comment>
		<if variable="formvars.value is 2">
			<sqlquery source="sql" host="&var.thedatabase:none;" query="INSERT INTO modules_groups SET group_id = '&form.group_id:mysql;', module_id = '&var.newmod:mysql;'"/>
   
			<comment>+++ Add Users Access to Users in Group Without id in modules_users +++</comment>
			<set variable="var.notin" value="''" />
			<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT uid FROM modules_users WHERE module_id = '&var.newmod:mysql;'" scope="notin">
				<append variable="var.notin">,</append>
				<append variable="var.notin">&notin.uid;</append>
			</emit>

			<emit source="sql" host="&var.thedatabase:none;" query="SELECT users.uid, users_groups.group_id FROM users, users_groups WHERE users_groups.uid = users.uid AND users.uid NOT IN (&var.notin;)" scope="noaccess">
				<sqlquery source="sql" host="&var.thedatabase:none;" query="INSERT INTO modules_users SET uid = '&noaccess.uid:mysql;', module_id = '&var.newmod:mysql;'"/>			 
			</emit>
			
		</if>
		<comment> -- Carry Current Group Access -- </comment>
		<if variable="formvars.value is 1">
			<set variable="var.previous" value="&var.newmod;" />
		</if>
	</if>
 
	<if variable="formvars.index is acc_*old">
		<set variable="var.oldindex" value="&_.index;" />
		<set variable="var.oldmod"><replace type="words" sperator="," from="acc_,old" to="">&var.oldindex;</replace></set>
		<set variable="&var.oldmod;" value="&var.oldmod;" /> 
		<comment> -- Remove Group and Users in Group Access -- </comment>
		<if variable="var.oldmod != &var.previous;">
			<sqlquery source="sql" host="&var.thedatabase:none;" query="DELETE FROM modules_groups WHERE module_id = '&var.oldmod:mysql;'"/>
			<emit source="sql" host="&var.thedatabase:none;" query="SELECT users.uid, users_groups.group_id FROM users, users_groups WHERE users_groups.uid = users.uid" scope="sql">	
				<sqlquery source="sql" host="&var.thedatabase:none;" query="DELETE FROM modules_users WHERE module_id = '&var.oldmod:mysql;' AND uid = '&sql.uid;'"/>
			</emit>
		</if>
	</if>

</emit> 	

<set variable="form.mode" value="mod_access"/>