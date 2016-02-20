<!-- The data encoding type, enctype, MUST be specified as below -->
<form enctype="multipart/form-data" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST">
	<input type="hidden" name="function" value="cashbook">	
	<input type="hidden" name="mode" value="import_form">	
	<input type="hidden" name="uploaded" value="yes">	
	<!-- MAX_FILE_SIZE must precede the file input field -->
	<input type="hidden" name="MAX_FILE_SIZE" value="300000" />
	<!-- Name of input element determines name in $_FILES array -->
	Send this file: <input name="userfile" type="file" />
	<input type="submit" value="Import File" />
</form>
