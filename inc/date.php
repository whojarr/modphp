<?php
function ddsel($name, $selected) {
	echo "<select name=\"$name\">";
	for ($i = 1; $i <= 31; $i++) {
   	echo "<option value=\"$i\"";
   	if ($selected == $i) {
   	echo " selected ";
   	}
   	echo ">$i</option>\n";
	}
	echo "</select>";	
}

function mmsel($name, $selected) {
	echo "<select name=\"$name\">";
	for ($i = 1; $i <= 12; $i++) {
   	echo "<option value=\"$i\"";
   	if ($selected == $i) {
   	echo " selected ";
   	}
   	echo ">$i</option>\n";
	}
	echo "</select>";	
}

function yysel($name, $selected) {
	echo "<select name=\"$name\">";
	for ($i = 2003; $i <= 2012; $i++) {
   	echo "<option value=\"$i\"";
   	echo " id=\"".$i."\" ";
   	if ($selected == $i) {
   	echo " selected ";
   	}
   	echo ">$i</option>\n";
	}
	echo "</select>";	
}

function sel_today($dd_name,$mm_name,$yy_name) {
	?>
<input type="button" value="Today" onclick="

for (var i=0; i < this.form.<?php echo $dd_name ?>.length; i++) {
	if (this.form.<?php echo $dd_name ?>.options[i].text == '<?php echo $_SESSION['dd'] ?>') {
		this.form.<?php echo $dd_name ?>.selectedIndex=i;
	}		
};

for (var i=0; i < this.form.<?php echo $mm_name ?>.length; i++) {
	if (this.form.<?php echo $mm_name ?>.options[i].text == '<?php echo $_SESSION['mm'] ?>') {
		this.form.<?php echo $mm_name ?>.selectedIndex=i;
	}		
};

for (var i=0; i < this.form.<?php echo $yy_name ?>.length; i++) {
	if (this.form.<?php echo $yy_name ?>.options[i].text == '<?php echo $_SESSION['yy'] ?>') {
		this.form.<?php echo $yy_name ?>.selectedIndex=i;
	}		
};

" />
	<?php
}	
?>