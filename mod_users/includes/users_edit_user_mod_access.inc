<define tag="tr_category" scope="lc">
 <attrib name="parent">0</attrib>
 <attrib name="indent">0</attrib>
 <attrib name="uid">0</attrib>
 <emit source="sql" scope="category" host="&var.thedatabase:none;" query="select * from modules where parent = '&lc.parent:mysql;'">
	<tr>
		<td valign="top">
		<b>&category.name;</b>
		</td>
		<td valign="top">
		
		 <set variable="var.access" value= " " />
		 <emit source="sql" scope="access" host="&var.thedatabase:none;" query="SELECT * FROM modules_users WHERE uid = '&lc.uid;' AND  module_id = '&category.id;'">
		 <set variable="var.access" value="1" />
		 </emit>
		  
		 <if variable="var.access is 1" >
		  <input type="checkbox" value="1" name="acc_&category.id;new" checked />
		  <input type="hidden" name="acc_&category.id;old" value="1">
		 </if>
		 <else>
		  <input type="checkbox" value="2" name="acc_&category.id;new" />
		 </else>
		
		</td>

	   <td valign="top">&nbsp;&nbsp;&nbsp;</td>
		<td valign="top">
		   <table valign="top">
		   	<tr>
		   	<td valign="top"></td>
		   	 <tr_category parent="&category.id:none;" uid="&lc.uid;" />
		   	</tr>
		   </table>
		</td>
	</tr>
 </emit>

</define>

<emit source="sql" host="&var.thedatabase:none;" query="SELECT * FROM users WHERE users.uid = '&form.uid;'" scope="sql">

<form action="&page.self;" method="get">
<input type="hidden" name="function" value="users">
<input type="hidden" name="mode" value="update_user_mod_access">
<input type="hidden" name="uid" value="&form.uid;">

<div class="groupBorder">
<input type="image" src="icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Update Access">
<a href="&page.self;?function=users&mode=mod_access">
<img src="icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>
<div class="groupHeader">Edit Module Access <b>[&sql.name;] &sql.gecos;</b></div>	
	<table>
		<tr_category uid="&form.uid;" />
	</table>	

</div>
</form>
</emit>