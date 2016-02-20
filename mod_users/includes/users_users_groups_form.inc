<emit source="sql" host="&var.thedatabase:none;" query="select * from users where uid = '&form.uid:mysql;'" scope="sql">	

<form action="&page.self;" method="get">
<input type="hidden" name="function" value="users">
<input type="hidden" name="mode" value="add_users_groups">
<input type="hidden" name="uid" value="&sql.uid:none;">


<div class="groupBorder">
<input type="image" src="icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Update Group">
<a href="&page.self;?function=users">
<img src="icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>
<div class="groupHeader">Add Groups to User</div>	
	
<table width="100%" border="0" cellpadding="5" cellspacing="1" align="center">
	<tr>
		<td>
		 User: &sql.name;
		</td>
		<td>
			<emit source="sql" host="&var.thedatabase:none;" scope="company" query="select * from companies where id = &sql.company_id:mysql;">	
			Company: &company.Company;
			</emit>
		</td>
	</tr>
</table>
</div>
<br>
<div class="groupBorder">

<div class="groupHeader">Groups</div>	

<table width="100%" border="0" cellpadding="5" cellspacing="1" align="center">
	
	<emit source="sql" host="&var.thedatabase:none;" query="select groups.id as id, groups.name as name from groups" scope="sql1">

<emit source="sql" host="&var.thedatabase:none;" query="select * from users_groups where group_id = '&sql1.id:mysql;' and uid = '&form.uid;'" scope="sql2">
	<set variable="var.name" value="CHECKED"/>
	<set variable="var.status" value="Member"/>
</emit>
<else>
	<unset variable="var.name"/>
	<unset variable="var.status"/>
</else>
	<tr>
		<td>
		 &sql1.name;
		</td>
		<td>
			<input type="hidden" name="name" value="&sql1.id;">  
			<input type="checkbox" name="&sql1.id;" value="CHECKED" ::=&var.name;>
		</td>
	</tr>
	</emit>
</table>
</div>
</form>
</emit>