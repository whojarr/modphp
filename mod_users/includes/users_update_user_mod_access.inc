<emit source="values" from-scope="form" scope="formvars" sort="index">
 
 <if variable="formvars.index is acc_*new">
  <set variable="var.newindex" value="&_.index;" />
  <set variable="var.newmod"><replace type="words" sperator="," from="acc_,new" to="">&var.newindex;</replace></set>
  <set variable="&var.newmod;" value="&var.newmod;" />
  <comment> -- Add New Access -- </comment>
  <if variable="formvars.value is 2">
   <sqlquery source="sql" host="&var.thedatabase:none;" query="INSERT INTO modules_users SET uid = '&form.uid:mysql;', module_id = '&var.newmod:mysql;'"/>
  </if>
  <comment> -- Carry Current Access -- </comment>
  <if variable="formvars.value is 1">
   <set variable="var.previous" value="&var.newmod;" />
  </if>
 </if>
 
 <if variable="formvars.index is acc_*old">
  <set variable="var.oldindex" value="&_.index;" />
  <set variable="var.oldmod"><replace type="words" sperator="," from="acc_,old" to="">&var.oldindex;</replace></set>
  <set variable="&var.oldmod;" value="&var.oldmod;" /> 
   <comment> -- Remove Access -- </comment>
   <if variable="var.oldmod != &var.previous;">
   <sqlquery source="sql" host="&var.thedatabase:none;" query="DELETE FROM modules_users WHERE module_id = '&var.oldmod:mysql;' ANDuid = '&form.uid:mysql;' "/>
   </if>
 </if>

</emit> 	

<set variable="form.mode" value="mod_access"/>