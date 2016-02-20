<form action="&page.self;" method="post">
<input type="hidden" name="function" value="users">
<input type="hidden" name="mode" value="add_user">

<div class="groupBorder">
<input type="image" src="icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Update Group">
<a href="&page.self;?function=users">
<img src="icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>
<div class="groupHeader">Add New Login</div>	
	
		
<table width="100%" border="0" cellpadding="5" cellspacing="1" align="center">
	<emit source="sql" host="&var.thedatabase:none;" scope="company" query="select name,id from companies WHERE id like '&form.companies_id;'">
		<tr>
			<td>
				Company Name: 
			</td>
			<td>
				<a href="&page.self;?function=users&nav=3&mode=add_user_form&uid=&form.uid;&dropcomp=true">[&company.name;]</a>
				<input type="hidden" name="companies_id" value="&form.companies_id:none;">
			</td>
		</tr>
	</emit>
	<else>
		<tr>	
			<td>
		 		Company Name: <small><a  href="javascript:popup('index.html?function=companies&mode=add&template=no',750, 400);">[add]</a></small>
			</td>
			<td align=left>
				<table >
					<tr >
						<emit source="values" values="A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z" split=",">
							<if variable="form.companylike is &_.value;">
							<td><u><a href="&page.self;?function=users&nav=3&mode=add_user_form&uid=&form.uid;&companylike=&_.value;&dropcomp=&form.dropcomp;">&_.value;</a></u></td>
							</if>  
							<else>
								<td ><a href="&page.self;?function=users&nav=3&mode=add_user_form&uid=&form.uid;&companylike=&_.value;&dropcomp=&form.dropcomp;">&_.value;</a></td>
							</else>
						</emit>
					</tr>
				</table>
			</td>
		</tr>
		<if variable="form.companylike is ?">
		<tr>		
			<td></td>
			<td>
					<input type="hidden" name="companylike" value="&form.companylike;">
					<default name="companies_id" value="&form.company_id:none;">
					<select name="companies_id" onchange="viewcompany.submit()">
						<option value="">Choose Company--</option>
							<emit source="sql" host="&var.thedatabase:none;" scope="company" query="select name,id from companies WHERE name like '&form.companylike;%' order by name">
								<option value="&company.id:none;">&company.name;</option>
							</emit>
					</select>
					</default>
			</td>
		</tr>
	</if>
	</else>
    <tr>
		<td>
			Username: 
		</td>
		<td>
			<input type="text" name="login" value="&form.login:none;"> 
			<if variable="var.new_login_dup is true">
				<br>
				<font color="red">Username '&form.loginerrorname;' Unavailable</font>
			</if>
		</td>
	</tr>
	<tr>
		<td>
			Password: 
		</td>
		<td>
			<input type="password" name="password" value=""> 
			<if variable="var.password_error is true">
				<br>
				<font color="red">Password Required</font>
			</if>
		</td>
	</tr>
	<tr>
		<td>
			Full Name: 
		</td>
		<td>
			<input type="text" name="gecos" value="&form.gecos:none;"> 
		</td>
	</tr>
	<tr>
		<td>
			Email: 
		</td>
		<td>
			<input type="text" name="email" value="&form.email:none;"> 
		</td>
	</tr>
	<tr>
		<td>
			Phone: 
		</td>
		<td>
			<input type="text" name="phone" value="&form.phone:none;"> 
		</td>
	</tr>
	<tr>
		<td>
			Web Site: 
		</td>
		<td>
			<input type="text" name="web" value="&form.web:none;"> 
		</td>
	</tr>
</table>
</div>
</form>