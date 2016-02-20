<?php

function gstcomponent($inclusive,$gstrate)
{
	if($gstrate <> 0 && $inclusive <> 0)
	{
		$result = ROUND($inclusive*(($gstrate*100)/(($gstrate*100)+100)),2);
		return $result;
	}
	else return 0;
}

function fmod_round($x, $y) {
	$i = round($x / $y);
	return $x - $i * $y;
}
	
function paye($nett) {
	// echo "Gross Weekly=".$nett."<br>";
	// Calc Weekly Income
	$weekly = ($nett*12)/52;	
	// Remove Cents
	$round_weekly = floor($weekly);
	// echo " Weekly=".$round_weekly."<br>";
	// Calc Annual Income (if tax code !=M more cals required)
	$annual = $round_weekly*52;
//	echo " Gross=".$annual.".00<br>";
	// Calc Tax On Annual Income 
	if ($annual <= 9500) {
		$tax = 0.15 * $annual;	
	}
	elseif ($annual > 9500 && $annual <= 38000) {
		$tax1 = 1425 + (0.21 * ($annual - 9500)) ;
		$tax2 = (0.21 * $annual) - 570;
		if ($tax1 == $tax2) {
			$tax = $tax1;
		// echo " tax=".$tax1."<br>";
		}
	}
	elseif ($annual > 38000 && $annual <= 60000) {

		$tax2 = (0.33 * $annual) - 5130;
		$tax = $tax2;
		// echo " tax=".$tax2."<br>";

	}
	elseif ($annual > 60000) {
		$tax1 = 14670 + (0.39 * ($annual - 60000)) ;
		$tax2 = (0.39 * $annual) - 8730;
		if ($tax1 == $tax2) {
			$tax = $tax1;
			// echo " tax=".$tax1."<br>";
		}	
	}
	else {
		$tax = 0.00;	
	}
	// Calc Annual Earners Levy
	if ($annual > 94226) {
		$levy = 1130.7;
	}
	else {
		$levy = 0.012 * $annual;
		// echo " Levy =".$levy."<br>";
	}
	// Calc Annual Total Deductions (if tax code !=M more cals required)
	$deductions = $levy + $tax;
	// echo " Deductions = Levy + Tax (".$deductions.")"."<br>";
	// Gross down to Weekly deduction
	$weekly_deductions = round($deductions/52,2);
	// Gross up to pay period
	$gross_tax = ($weekly_deductions * 52)/12;
	// echo "Monthly Paye"; echo $gross_tax; echo")<br>";

	$paye = round($gross_tax,2);

	return $paye;					
}
?>