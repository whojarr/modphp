<center> Modules With modulename_config.inc </center>

<set variable="var.colcount" value="0"/>
<table align="center" cellspacing="10">
 <tr>
	 <!-- read directorys -->
	<emit source="dir" sort-order="dwim" scope="dirname" directory="" >
		<set variable="var.ilename" value="&_.real-dirname;/&_.filename;" />
		<set variable="var.filename" value="&_.filename;" />
		<?pike
		string h;
		string i;
		h = var.ilename;
		i = var.filename;
		if (Stdio.is_dir(h)) {
			var.displaydir = var.filename;
			var.mod_name = replace(i, "mod_", "");
		}
		else {
		 var.displaydir = "";
		 var.conf_name = "";
		}
		?>
		<if variable="var.displaydir is ?*">

			<if exists exists="&var.displaydir;/&var.mod_name;_config.inc">
				<td align="center">
				<a href="&page.self;?function=modules&mode=edit_vars&folder=&var.displaydir;&config_file=&var.mod_name;_config.inc&mod_name=&var.mod_name;">
				&var.displaydir;
				</a>
				</td>

				<if variable="var.colcount is 4">
					<set variable="var.colcount" value="-1" />
						</tr>
						<tr>
				</if>
				<inc variable="var.colcount"/>
			</if>

			<elseif exists exists="&var.displaydir;/&var.mod_name;_config.default">
				<td align="center">
				<a href="&page.self;?function=modules&mode=edit_vars&folder=&var.displaydir;&config_file=&var.mod_name;_config.default&mod_name=&var.mod_name;">
				&var.displaydir;
				</a>
				</td>

				<if variable="var.colcount is 4">
					<set variable="var.colcount" value="-1" />
						</tr>
						<tr>
				</if>
				<inc variable="var.colcount"/>
			</elseif>


		</if>

	</emit>
	
  <if variable="var.colcount is 4">
   <tr>
  </if>
 </tr>
</table>