<?php
function listcategory($parent,$indent) {
	$results = mysql_query("SELECT * FROM modules WHERE parent_id = '$parent' ") or die("Query failed: " . mysql_error());
	if ($resultsarray = mysql_fetch_array($results)) {
		do {
			for ($a=0; $a < $indent; $a++) {
				echo "&nbsp;&nbsp;";
			}
			echo $resultsarray['name'];
			echo "&nbsp;&nbsp;<a href=\"".$_SERVER['PHP_SELF']."?function=modules&mode=edit&id=".$resultsarray['id']."\"><img src=\"images/icons/editsml.gif\" title=\"Edit\" border=\"0\"/></a>";
         echo "&nbsp;&nbsp;<a href=\"&page.self;?function=modules&mode=add&parent=".$resultsarray['id']."\"><img src=\"images/icons/addsml.gif\" title=\"Add\" border=\"0\"/></a>";
         echo "<br>";
         listcategory($resultsarray['id'],'1');
		}
		while ($resultsarray = mysql_fetch_array($results));
	}				
}
?>


<div class="groupBorder">
	<a href="<?php echo $_SERVER['PHP_SELF'] ?>?function=modules&mode=add">
	<img src="/images/icons/add.gif" border="0" title="Add" alt="Add" hspace="2" vspace="2" align=right></a>

	<div class="groupHeader">Modules</div>	
	
	<table border="0" cellspacing="0" cellpadding="5" width="100%">
		<tr>
			<td>
				<?php
					listcategory('0','0');
				?>
			</td>
		</tr>
	</table>	
          
</div>