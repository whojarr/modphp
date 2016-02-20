<form action="&page.self;" method="post">
<input type="hidden" name="function" value="users">
<input type="hidden" name="mode" value="add_group">
	

<div class="groupBorder">
<input type="image" src="icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Add Group">
<a href="&page.self;?function=users">
<img src="icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>
<div class="groupHeader">Add New Group Section</div>	

	
<table width="100%" border="0" cellpadding="5" cellspacing="1" align="center">
	<tr>
		<td>
			Group Name: 
		</td>
		<td>
			<input type="text" name="group_name" value=""> 
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
			<textarea name="description" cols="30" rows="2"></textarea> 
		</td>
	</tr>
</table>

</div>
</form>