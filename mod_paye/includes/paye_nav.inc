<div class="menuBar">

	<a class="menuButton" href="" onclick="return buttonClick(event, 'file');" onmouseover="buttonMouseover(event, 'file');"><u>F</u>ile</a>
	<a class="menuButton" href="" onclick="return buttonClick(event, 'edit');" onmouseover="buttonMouseover(event, 'edit');"><u>E</u>dit</a>
	<a class="menuButton" href="" onclick="return buttonClick(event, 'view');" onmouseover="buttonMouseover(event, 'view');"><u>V</u>iew</a>

	<div id="file" class="menu" onmouseover="menuMouseover(event)">
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=paye&mode=add_return">New PAYE RETURN</a>
		<a class="menuItem" href="javascript:window.print()">Print</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?session_logout=1">Log Out</a>
		<a class="menuItem" href="javascript:window.close()">Exit</a>
	</div>      
	
	<div id="edit" class="menu" onmouseover="menuMouseover(event)">
		<a class="menuItem" href="javascript:popupcenter('<?php echo $_SERVER['PHP_SELF'] ?>?function=paye&mode=display_types&template=no&display_nav=no',300,300,200,200,'Display Types')">Employees</a>
	</div>      	

	<div id="view" class="menu" onmouseover="menuMouseover(event)">
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=paye&mode=display_returns">Returns</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=paye&mode=display_report_wages">Wages Report</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=paye&mode=display_report_annual">Annual Report</a>
	</div>

</div>