 <writefile remove filename="&form.filename;"/>
  <emit source="values" from-scope="form" sort="index">
   <if variable="_.index is mode"></if>
			<else>		
 	 <writefile filename="&form.filename;" append >
 		<maketag name='set' type='tag' >
 		 <attrib name="value">&_.value;</attrib>
 		 <attrib name="variable">var.&_.index;</attrib>
 		</maketag>
			</else>
  </emit>
 </writefile>
 
 <set variable="form.mode" value="display_vars" />