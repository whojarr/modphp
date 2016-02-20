<div class="menuBar">

			<?php
						
				/* change selected nav if clicked */
				if (isset($_GET['nav'])) {
					$_SESSION['nav'] = $_GET['nav'];
				}
				/* Get Top Level Nav Items  */
				$navresults = mysql_query("
					SELECT * 
					FROM modules_users 
					LEFT JOIN modules ON modules_users.module_id = modules.id 
					WHERE modules_users.uid = '{$_SESSION['uid']}' 
					AND modules.parent_id = '0' 
					AND type = 'nav' 
					ORDER BY modules.priority
					")	or die("Query failed: " . mysql_error());
				if ($navresultsarray = mysql_fetch_array($navresults)) {
					do {
						/*  Display Top Nav Items */
						?>
						<a class="menuButton" href="" onclick="return buttonClick(event, '<?php echo $navresultsarray['name'] ?>');" onmouseover="buttonMouseover(event, '<?php echo $navresultsarray['name'] ?>');"><?php echo $navresultsarray['name'] ?></a>
						
						<div id="<?php echo $navresultsarray['name'] ?>" class="menu" onmouseover="menuMouseover(event)">
							<?php
								$subresults = mysql_query("
									SELECT * 
									FROM modules_users 
									LEFT JOIN modules ON modules_users.module_id = modules.id 
									WHERE modules.parent_id = '{$navresultsarray['id']}' 
									AND modules_users.uid = '{$_SESSION['uid']}' 
									ORDER BY modules.priority
									")	or die("Query failed: " . mysql_error());
								if ($subresultsarray = mysql_fetch_array($subresults)) {
									do {
										/*  Display Sub Items */
										?>
											<a class="menuItem" href="<?php echo $_SERVER['PHP_SELF'] ?>?function=<?php echo $subresultsarray['mod_function'] ?>&nav=<?php echo $subresultsarray['id'] ?>"><?php echo $subresultsarray['name'] ?></a>										
										<?php
									}
									while ($subresultsarray = mysql_fetch_array($subresults));
								}
							?>
						</div>
						<?php
					}
					while ($navresultsarray = mysql_fetch_array($navresults));
				}
				
				/* Display Logout */
				echo " [ <a class=\"navhead\" href=\"?session_logout=1\">Log Out</a> ]"; 
				
				/* Display Add Task */
				$groupresults = mysql_query("
					SELECT * 
					FROM users_groups
					WHERE uid = '{$_SESSION['uid']}'
					")	or die("Query failed: " . mysql_error());
				if ($groupresultsarray = mysql_fetch_array($groupresults)) {
					do {
						if($groupresultsarray['group_id'] == 1) {
							echo " [<a style=\"font-size: 9px; font-family: Arial; color: white;\" href=\"javascript:popup('".$_SERVER['PHP_SELF']."?function=tasks&mode=add&mod_function=".$_REQUEST['function']."&url=yes&template=no',600,500,'Display item');\" > Add Task </a>]";
						}
					}
					while ($groupresultsarray = mysql_fetch_array($groupresults));
				}
				
			?>
</div>