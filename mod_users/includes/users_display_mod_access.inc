<comment>+++COMPANIES+++</comment>

<form action="&page.self;" name="viewcompany" method="get">
<input type="hidden" name="function" value="users">
<input type="hidden" name="mode" value="">
<input type="hidden" name="action" value="view_companies_mod_access">

<div class="groupBorder">

<comment>
<div class="groupHeader">Company Module Access</div>
	
<table width="100%" border="0" cellpadding="3" cellspacing="1">
<emit source="sql" host="&var.thedatabase:none;" query="select count(*) as Company_Count from companies" scope="sql">	
	
	<tr>
		<td width="1%">
		<default name="company_id" value="&form.company_id:none;">
			<select name="company_id" onchange="viewcompany.submit()">
			<option value="">Choose Company</option>
			<emit source="sql" host="&var.thedatabase:none;" scope="company" query="select * from companies order by Company">
			<option value="&company.id:none;">&company.Company;</option>
			</emit>
			</select>
		</default>
		</td>
        <if variable="form.action is view_companies_groups">
		<td width="1%">
			<a href="&page.self;?function=users&mode=edit_company&company_id=&form.company_id:url;"><img src="icons/edit.gif" border="0" title="Edit"></a>
		</td>
		<td>
            <emit source="sql" host="&var.thedatabase:none;" query="select count(*) as The_Count from companies_groups where company_id = '&form.company_id:mysql;'" scope="sql1">	
                    <set variable="var.The_Count" value="&sql1.The_Count;"/>
            </emit>
			<select>
			<option value="">Groups (&var.The_Count;)</option>
			<emit source="sql" host="&var.thedatabase:none;" query="select groups.name as name from groups left join companies_groups on groups.id = companies_groups.group_id where companies_groups.company_id = '&form.company_id:mysql;'" scope="sql2">	
			<option value="">&sql2.name;</option>
			</emit>
			</select>
		</td>
		</if>
        <else>
        <td>
        Waiting for Selection
        </td>
        </else>
	</tr>
</emit>
<else>	
	<tr>
		<td colspan="3" align="center">
			No Companies Available
		</td>
	</tr>
</else>
</table>
	
</div>

<br>
</comment>

<comment>+++USERS+++</comment>

<div class="groupBorder">

<a href="&page.self;?function=users&mode=add_mod_access&uid=new"><img src="icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align=right></a>

<div class="groupHeader">User Module Access</div>

	<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
			<!-- Count Number of Modules to Generate <TD>'s -->
			<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT modules_users.module_id, modules.name  FROM modules_users, modules WHERE modules.id = modules_users.module_id ORDER BY module_id" scope="mod_count">	
			 <set variable="var.mod_count" value="&mod_count.counter;" />
			 <!-- Generate var.(counter) for mainting columns in table -->
			 <?pike var.mod_var = "var." + mod_count.counter; ?>
			 <?pike var.mod_val = "var.val" + mod_count.counter; ?>
			 <set variable="&var.mod_var;" value="&mod_count.module_id;" />
			 <set variable="&var.mod_val;" value="&mod_count.name;" />
			</emit>
			
			<!-- Generqate The <TD>'s for Every Module -->
			<td>Name</td>
			<td></td>
			
			<for from="1" to="&var.mod_count;" variable="var.loopcount">
			<td class="bodytextsmr">
			<set variable='var.var'>&var.</set>

		   <append variable="var.var">&var.loopcount;</append>

		 	<append variable="var.var">;</append>

			<set variable='var.vr'><eval>&var.var;</eval></set>
			<set variable='var.val'>&var.val</set>

		   <append variable="var.val">&var.loopcount;</append>

		 	<append variable="var.val">;</append>

			<set variable='var.vl'><eval>&var.val;</eval></set>
			&var.vl;
			</td>
			</for>
			
			<td></td>
	</tr>
<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT modules_users.uid, users.name, users.gecos FROM modules_users, users WHERE users.uid = modules_users.uid" scope="sql">	
	
	<tr>
		<td>
			&sql.counter;. &sql.name; [&sql.gecos;]
		</td>
		
		<td align="center">
			<a href="&page.self;?function=users&mode=edit_user_mod_access&uid=&sql.uid:url;">
			<img src="icons/edit.gif" border="0" title="Edit"></a>
		</td>
		
		<for from="1" to="&var.mod_count;" variable="var.loopcount">

		<set variable='var.var'>&var.</set>

		<append variable="var.var">&var.loopcount;</append>

		<append variable="var.var">;</append>

		<set variable='var.vr'><eval>&var.var;</eval></set>
		
		<td align="center">
		<emit source="sql" host="&var.thedatabase:none;" scope="name" query="SELECT * FROM modules_users WHERE uid = '&sql.uid:mysql;' ORDER BY module_id">
		<if variable="var.vr is &name.module_id;">
		<img src="icons/icon_green_tick.gif" border="0" title="Trash">		 
		</if>
		</emit>
		</td>

		</for>
		

		
		<td align="center">
			<a href="&page.self;?function=users&mode=edit_user_mod_access&uid=&sql.uid:url;">
			<img src="icons/edit.gif" border="0" title="Edit"></a>
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
	
</div>

<br>

<comment>+++GROUPS+++</comment>	
<div class="groupBorder">

<a href="&page.self;?function=users&mode=add_mod_access&gid=new"><img src="icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align=right></a>
<div class="groupHeader">Group Module Access</div>

	<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
			<!-- Count Number of Modules to Generate <TD>'s -->
			<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT modules_groups.module_id, modules.name  FROM modules_groups, modules WHERE modules.id = modules_groups.module_id ORDER BY module_id" scope="mod_count">	
			 <set variable="var.mod_count" value="&mod_count.counter;" />
			 <!-- Generate var.(counter) for mainting columns in table -->
			 <?pike var.mod_var = "var." + mod_count.counter; ?>
			 <?pike var.mod_val = "var.val" + mod_count.counter; ?>
			 <set variable="&var.mod_var;" value="&mod_count.module_id;" />
			 <set variable="&var.mod_val;" value="&mod_count.name;" />
			</emit>
			
			<!-- Generqate The <TD>'s for Every Module -->
			<td>Name</td>
			<td></td>
			
			<for from="1" to="&var.mod_count;" variable="var.loopcount">
			<td class="bodytextsmr">
			<set variable='var.var'>&var.</set>

		   <append variable="var.var">&var.loopcount;</append>

		 	<append variable="var.var">;</append>

			<set variable='var.vr'><eval>&var.var;</eval></set>
			<set variable='var.val'>&var.val</set>

		   <append variable="var.val">&var.loopcount;</append>

		 	<append variable="var.val">;</append>

			<set variable='var.vl'><eval>&var.val;</eval></set>
			&var.vl;
			</td>
			</for>
			
			<td></td>
	</tr>
<emit source="sql" host="&var.thedatabase:none;" query="SELECT DISTINCT modules_groups.group_id, groups.name, groups.description FROM modules_groups, groups WHERE groups.id = modules_groups.group_id" scope="sql">	
	
	<tr>
		<td>
			&sql.counter;. &sql.name; [&sql.description;]
		</td>
		<td align="center">
			<a href="&page.self;?function=users&mode=edit_group_mod_access&group_id=&sql.group_id:url;">
			<img src="icons/edit.gif" border="0" title="Edit"></a>
		</td>
		
		<for from="1" to="&var.mod_count;" variable="var.loopcount">

		<set variable='var.var'>&var.</set>

		<append variable="var.var">&var.loopcount;</append>

		<append variable="var.var">;</append>

		<set variable='var.vr'><eval>&var.var;</eval></set>
		
		<td align="center">
		<emit source="sql" host="&var.thedatabase:none;" scope="name" query="SELECT * FROM modules_groups WHERE group_id = '&sql.group_id:mysql;' ORDER BY module_id">
		<if variable="var.vr is &name.module_id;">
		<img src="icons/icon_green_tick.gif" border="0" title="Trash">		 
		</if>
		</emit>
		</td>

		</for>
		

		
		<td align="center">
			<a href="&page.self;?function=users&mode=edit_group_mod_access&group_id=&sql.group_id:url;">
			<img src="icons/edit.gif" border="0" title="Edit"></a>
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
	
</div>