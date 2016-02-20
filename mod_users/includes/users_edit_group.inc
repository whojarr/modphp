<emit source="sql" host="&var.thedatabase:none;" query="select * from groups where id = '&form.group_id:mysql;'" scope="sql">

<form action="&page.self;" method="post">
<input type="hidden" name="function" value="users">
<input type="hidden" name="mode" value="update_group">
<input type="hidden" name="group_id" value="&form.group_id:none;">

<div class="groupBorder">
<input type="image" src="icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Update Group">
<a href="&page.self;?function=users">
<img src="icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>
<div class="groupHeader">Edit Group</div>	

	
	<table width="100%" border="0" cellpadding="5" cellspacing="1" align="center">
	<tr>
		<td>
			Group Name: 
		</td>
		<td>
			<input type="text" name="name" value="&sql.name;"> 
			<if variable="form.group_name_error is true">
			<br><font color="#CC0000">Name Required</font>
			</if>
		</td>
	</tr>
	<tr valign="top">
		<td>
			Description: 
		</td>
		<td>
			<textarea name="description" cols="30" rows="2">&sql.description;</textarea> 
		</td>
	</tr>
</table>
</div>

</form>
</emit>