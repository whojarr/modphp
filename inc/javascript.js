function popup(page, width, height) {
	var properties = "height=" + height + ",width=" + width + ",toolbar=no,scrollbars=yes,menubar=yes,resizable=yes";  open(page, "", properties);
}

function popupmain(page) {
	var properties = "toolbar=no,scrollbars=yes,menubar=no,resizable=yes,status=no,location=no,directories=no";  open(page, "", properties); 
	window.close();
}
	
function popupcenter(page, width, height) {
	var midHeight = (document.body.clientHeight /2) + (height/2);
	var midWidth = (document.body.clientWidth /2) - (width/2);
	var properties = "height=" + height + ",width=" + width + ",top=" + midHeight + ",left=" + midWidth +",toolbar=no,scrollbars=yes,menubar=no,resizable=yes,status=no,location=no,directories=no";  open(page, "", properties);
}

// Used to Set a Form Selected Option to xxx_value whose name = xxx_name 
function selectDate(form_name,dd_name,dd_value,mm_name,mm_value,yy_name,yy_value) {
	for (var i=0; i < document.forms[form_name].elements[dd_name].length; i++) {
		if (document.forms[form_name].elements[dd_name].options[i].text == dd_value) {
			document.forms[form_name].elements[dd_name].selectedIndex=i;
		}
	}		
	for (var i=0; i < document.forms[form_name].elements[mm_name].length; i++) {
		if (document.forms[form_name].elements[mm_name].options[i].text == mm_value) {
			document.forms[form_name].elements[mm_name].selectedIndex=i;
		}
	}		
	for (var i=0; i < document.forms[form_name].elements[yy_name].length; i++) {
		if (document.forms[form_name].elements[yy_name].options[i].text == yy_value) {
			document.forms[form_name].elements[yy_name].selectedIndex=i;
		}
	}		
};	