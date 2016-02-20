<div class="groupBorder">
<a href="&page.self;?function=modules&mode=add">
<img src="icons/add.gif" border="0" title="Add" alt="Add" hspace="2" vspace="2" align=right></a>

<div class="groupHeader">Modules</div>	


<table bgcolor="#666666" cellspacing=1>

	<tr bgcolor="#ffffff">
		<TH>Name</TH>
		<TH>Approved</TH>
		<TH>&nbsp;&nbsp;&nbsp;CVS&nbsp;&nbsp;&nbsp;</TH>
		<TH>Split</TH>
		<TH>Styled</TH>
		<TH>Database</TH>
		<TH>Combed</TH>
		<TH>Complete</TH>
		<TH>Edit</TH>
    </tr>

     <emit source="sql" scope="category" host="&var.thedatabase:none;" query="select * from modules where parent = '0'">

	<tr>
	<TH colspan="9" align=left bgcolor="#ffffff">
              <b>&category.name;</b> &nbsp;&nbsp;
                         <a href="&page.self;?function=modules&mode=edit&id=&category.id:url;"><img src="icons/editsml.gif" title="Edit" border="0"/></a>

              <a href="&page.self;?function=modules&mode=add&parent=&category.id:url;"><img src="icons/addsml.gif" title="Add" border="0"/></a>

    </TH>
    </tr>
    
         <emit source="sql" scope="sub" host="&var.thedatabase:none;" query="select * from modules where parent = '&category.id:mysql;'">

    <tr>

         <td bgcolor="#ffffff">&nbsp;&nbsp;&nbsp;&sub.name; - [&sub.mod_function;]</b></td>
         <td bgcolor="#ffffff" align=center>
          <if variable="sub.development is *1*" ><input type="checkbox" value="1" name="approved" checked /></if>
		             <else><input type="checkbox" value="1" name="approved" /></else></td>
		    <td bgcolor="#ffffff" align=center>
                     <if variable="sub.development is *2*" ><input type="checkbox" value="2" name="cvs" checked /></if>
		             <else><input type="checkbox" value="2" name="cvs" /></else></td>
		  <td bgcolor="#ffffff" align=center>
                     <if variable="sub.development is *3*" ><input type="checkbox" value="3" name="split" checked /></if>
		             <else><input type="checkbox" value="3" name="split" /></else></td>
		    <td bgcolor="#ffffff" align=center>
                     <if variable="sub.development is *4*" ><input type="checkbox" value="4" name="styled" checked /></if>
		             <else><input type="checkbox" value="4" name="styled" /></else></td>
		      <td bgcolor="#ffffff" align=center>
                     <if variable="sub.development is *5*" ><input type="checkbox" value="5" name="database" checked /></if>
		             <else><input type="checkbox" value="5" name="database" /></else></td>
		     <td bgcolor="#ffffff" align=center>
                     <if variable="sub.development is *6*" ><input type="checkbox" value="6" name="combed" checked /></if>
		             <else><input type="checkbox" value="6" name="combed" /></else></td>
               <td bgcolor="#ffffff" align=center>
		             <if variable="sub.development is *7*" ><input type="checkbox" value="7" name="complete" checked /></if>
		             <else><input type="checkbox" value="7" name="complete" /></else></td>
		
         
         
         <td bgcolor="#ffffff" align=center nowrap>
    
           <a href="&page.self;?function=modules&mode=edit&id=&sub.id:url;"><img src="icons/editsml.gif" title="Edit" border="0"/></a>
             <a href="index.html?function=modules&mode=delete&id=&sub.id:url;" onclick="return confirm('Are you sure you want to delete?')"><img src="icons/delete.gif" border="0" title="Trash" ></a>
        </td>
     
		</tr>	
			
	

 </emit>
		
	

 </emit>

	</table>
          
</div>
</div>

