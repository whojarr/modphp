
<table align="center">

<eval><insert file="&form.folder;/&form.config_file;"/></eval>
<form action="&page._self;" method="get">
	<input type="hidden" name="function" value="modules">
	<input type="hidden" name="filename" value="&form.folder;/&form.mod_name;_config.inc">
	<scope scope="temp">
 		<emit source="values" from-scope="var" sort="index">
 			<if variable="_.index is &form.mod_name;_*">
				<tr>
					<td>	&_.index;</td>
					<td><input name="&_.index;" type="text" value="&_.value;"></td>
  				</tr>
  			</if>
 		</emit>
	</scope>
	<tr>
		<td><input name="mode" type="submit" value="update_vars"></td>
	</tr>
</form>

</table>