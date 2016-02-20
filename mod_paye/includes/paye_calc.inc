<center>
	<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post" name="paye_calc">
		<input type="hidden" name="function" value="paye">
		<input type="text" name="nett" value="<?php echo $_REQUEST['nett'] ?>"><br>
		<input type="submit" name="submit" value="submit">
	</form>
</center>