function hover(a) {
	var k = document.getElementById(a);
	if (k.style.backgroundColor != "crimson") {
		k.style.backgroundColor = "lightcoral";
	}
}

function unhover(a) {
	var k = document.getElementById(a);
	if (k.style.backgroundColor == "lightcoral") {
		k.style.backgroundColor = "silver";
	}	
}

function fill(a) {
	var k = document.getElementById(a);
	if (k.style.backgroundColor != "crimson") {
		k.style.backgroundColor = "crimson";
	}
	else {
		k.style.backgroundColor = "silver";
	}
}