<?php
$userresults = mysql_query("
	SELECT *
	FROM users
	WHERE uid = {$_REQUEST['uid']}
	")	or die("Query failed: " . mysql_error());

if ($userresultsarray = mysql_fetch_array($userresults)) {
	do {
		?>
		<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="get" name="mainform">
		<input type="hidden" name="function" value="<?php echo $_REQUEST['function'] ?>">
		<input type="hidden" name="mode" value="update_user">
		<input type="hidden" name="uid" value="<?php echo $userresultsarray['uid'] ?>">

		<div class="groupBorder">
		<input type="image" src="images/icons/save.gif" border="0" title="Save" alt="Save" hspace="4" vspace="2" align=right value="Update Group">
		<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users">
		<img src="images/icons/back.gif" border="0" title="Return" alt="Return" hspace="2" vspace="2" align=right></a>
		<div class="groupHeader">Edit Client</div>	
			
		<table width="100%" border="0" cellpadding="5" cellspacing="1" align="center">
			<tr>
				<td align=right>
					Username: 
				</td>
				<td>
					<input type="text" name="login" value="<?php echo $userresultsarray['name'] ?>">
					<?php
						if ($new_login_dup == "true") {
							echo "<br>";
							echo "<font color=\"red\">Username '".$_REQUEST['loginerrorname']."' unavailable reset to '".$userresultsarray['name']."'</font>";
						}
					?> 
				</td>
			</tr>
			<tr>
				<td align=right>
					password: 
				</td>
				<td>
					<input type="password" name="password" value="[Complete to Update]">
					<?php
						if ($password_error == "true") {
							echo "<br>";
							echo "<font color=\"red\">A password is required - not changed</font>";							
						}
					?> 
				</td>
			</tr>
			<?php
				/* Company Selector */
				if ($_REQUEST['dropcomp'] == "true") {
					$userresultsarray['company_id'] = "none";
				}
						
				$companyresults = mysql_query("
					SELECT name,id 
					FROM companies 
					WHERE id LIKE '{$userresultsarray['company_id']}'
					")	or die("Query failed: " . mysql_error());
				if ($companyresultsarray = mysql_fetch_array($companyresults)) {
					do {
						?>
							<tr>
								<td align=right>
									Company Name: 
								</td>
								<td>
									<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=users&nav=3&mode=edit_user&uid=<?php echo $_REQUEST['uid'] ?>&dropcomp=true">[<?php echo $companyresultsarray['name'] ?>]</a>
									<input type="hidden" name="company_id" value="[<?php echo $companyresultsarray['company_id'] ?>">
								</td>
							</tr>
						<?php
					}
					while ($companyresultsarray = mysql_fetch_array($companyresults));
				}
				else {
					?>
						<tr>		
							<td align=right>
						 		Company Name: 
							</td>
							<td align=left>
								<table>
									<tr>
										<?php
											$alpha = array(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z);
											foreach($alpha as $letter) {
												if ($_REQUEST['companylike'] == $letter) {
													echo "<td><u>";
													echo "<a href=\"".$_SERVER['PHP_SELF']."?function=users&nav=3&mode=edit_user&uid=".$_REQUEST['uid']."&companylike=".$letter."&dropcomp=".$_REQUEST['dropcomp']."\">".$letter."</a>";
													echo "</u></td>";
												}
												else {
													echo "<td>";
													echo "<a href=\"".$_SERVER['PHP_SELF']."?function=users&nav=3&mode=edit_user&uid=".$_REQUEST['uid']."&companylike=".$letter."&dropcomp=".$_REQUEST['dropcomp']."\">".$letter."</a>";
													echo "</td>";
												}
											} 
										?>
									</tr>
								</table>
							</td>
						</tr>
						<?php
							if ($_REQUEST['companylike'] > '') {
								?>
								<tr>		
									<td></td>
									<td>
										<input type="hidden" name="companylike" value="<?php echo $_REQUEST['companylike'] ?>">
										<select name="company_id" onchange="mainform.submit()">
											<option value="">Choose Company--</option>
											<?php
												$companyresults = mysql_query("
													SELECT name,id 
													FROM companies 
													WHERE name LIKE '{$_REQUEST['companylike']}%' 
													ORDER BY name
													")	or die("Query failed: " . mysql_error());
												if ($companyresultsarray = mysql_fetch_array($companyresults)) {
													do {
													 echo "<option value=\"".$companyresultsarray['id']."\">".$companyresultsarray['name']."</option>";
													}
													while ($companyresultsarray = mysql_fetch_array($companyresults));
												}
											?>
										</select>
									</td>
								</tr>
								<?php							
							}
						?>
					<?php				
				}				
			?>
			<tr>
				<td align=right>
					Full Name: 
				</td>
				<td>
					<input type="text" name="gecos" value="<?php echo $userresultsarray['gecos'] ?>"> 
				</td>
			</tr>
			<tr>
				<td align=right>
					Email: 
				</td>
				<td>
					<input type="text" name="email" value="<?php echo $userresultsarray['email'] ?>"> 
				</td>
			</tr>
			<tr>
				<td align=right>
					Phone: 
				</td>
				<td>
					<input type="text" name="phone" value="<?php echo $userresultsarray['phone'] ?>"> 
				</td>
			</tr>
			<tr>
				<td align=right>
					Web Site: 
				</td>
				<td>
					<input type="text" name="web" value="<?php echo $userresultsarray['web'] ?>"> 
				</td>
			</tr>
			
		</table>
		</form>
		<?php
	}
	while ($userresultsarray = mysql_fetch_array($userresults));
}
?>