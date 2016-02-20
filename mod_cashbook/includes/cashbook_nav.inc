<div class="menuBar">

	<a class="menuButton" href="" onclick="return buttonClick(event, 'file');" onmouseover="buttonMouseover(event, 'file');"><u>F</u>ile</a>
	<a class="menuButton" href="" onclick="return buttonClick(event, 'edit');" onmouseover="buttonMouseover(event, 'edit');"><u>E</u>dit</a>
	<a class="menuButton" href="" onclick="return buttonClick(event, 'view');" onmouseover="buttonMouseover(event, 'view');"><u>V</u>iew</a>

	<div id="file" class="menu" onmouseover="menuMouseover(event)">
		<a class="menuItem" href="javascript:window.print()">Print</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=import_file">Import ASB CSV</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?session_logout=1">Log Out</a>
		<a class="menuItem" href="javascript:window.close()">Exit</a>
	</div>      
	
	<div id="edit" class="menu" onmouseover="menuMouseover(event)">
		<a class="menuItem" href="javascript:popupcenter('<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_types&template=no&display_nav=no',300,300,200,200,'Display Types')">Transaction Types</a>
		<a class="menuItem" href="javascript:popupcenter('<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_accounts&template=no&display_nav=no',300,300,200,200,'Display Accounts')">Accounts</a>
	</div>      	

	<div id="view" class="menu" onmouseover="menuMouseover(event)">
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_transactions">Transactions</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_accounts">Account Report</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_accounts_summary">Account Summary Report</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_gst">GST Report</a>
		<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=cashbook&mode=display_report_paye">PAYE Report</a>
	</div>

</div>