<div class="groupBorder">

<a href="&page.self;?function=users&mode=add_status_form"><img src="icons/add.gif" border="0" title="Add" vspace="2" hspace="2" align=right></a>

<div class="groupHeader">Status Options</div>

<table width="100%" border="0" cellpadding="3" cellspacing="1">
	<tr bgcolor="#DDDDDD">
		<td align="center">
			Status
		</td>
		<td align="center">
			Description
		</td>
		<td align="center">
		  Action
		</td>
	</tr>
	
<emit source="sql" host="&var.thedatabase:none;" query="select * from userstatus" scope="sql">	
	
	<tr>
		
		<td align="center">
			&sql.status;
		</td>
		<td align="center">
			&sql.description;
		</td>
		
		<td align="center" bgcolor="#EEEEEE">
			 <a href="&page.self;?function=users&mode=delete_status&status_id=&sql.id:url;" onclick="return confirm('Are you sure you want to delete?')"><img src="icons/delete.gif" border="0" title="Trash"></a> 
<a href="&page.self;?function=users&mode=edit_status&status_id=&sql.id:url;"><img src="icons/edit.gif" border="0" title="Edit"></a>

<a href="&page.self;?function=users&mode=add_users_groups_form&uid=&sql.uid:url;"><img src="icons/link.gif" border="0" title="Link"></a>
		</td>
	</tr>
</emit>
<else>	
	<tr>
		<td colspan="5" align="center">
			No Status Options
		</td>
	</tr>
</else>
</table>
	
</div>
