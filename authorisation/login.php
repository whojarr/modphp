<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post" name="login_form" id="login_form">
<input type="hidden" name="mode" value="client_login">
<br>
<p align="center"><img src="images/webhavensml.gif" alt="WebHaven Login"></p>
<table border="0" cellspacing="0" cellpadding="5" align="center" bgcolor="#EEEEEE" style="border: 1px solid; border-color: #AAAAAA;">
	<tr>
		<td>
			<table border="0" width="60%" cellspacing="0" cellpadding="2" align="center">
				<tr>
					<td colspan=2 align="center">
						<font color="maroon">
						<b>
						<?php
            			if ($login_error) {
								echo $login_error;
			            }               
						?>
						</b>
					</td>
				</tr>
				<tr>
					<td align=right nowrap>
						Login Name: 
					</td>
					<td align=right>
						<input type="text" name="login" value="" size="15">
					</td>
				</tr>
				<tr>
					<td align=right>
						Password: 
					</td>
					<td align=right>
						<input type="password" name="password" value="" size="15">
					</td>
				</tr>
				<tr>
					<td align=right>
					</td>
					<td align=right>
						<input type="submit" name="submit" value="Login">
					</td>
				</tr>                
			</table>
		</td>
	</tr>
</table>
</form>