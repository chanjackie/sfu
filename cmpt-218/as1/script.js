var errors = 0;
var correct = 0;

function fill(x) {
	var a = document.getElementById(x);
	if (a.style.backgroundColor != "darkslategray") {
		a.style.backgroundColor = "darkslategray";
		if (a.className == "x") {
			errors++;
			console.log("wrong = " + errors);
		}
		else {
			correct++;
			console.log("correct = " + correct);
		}
	}
	else {
		a.style.backgroundColor = "lightyellow";
		if (a.className == "x") {
			errors--;
			console.log("wrong = " + errors);
		}
		else {
			correct--;
			console.log("correct = " + correct);
		}
	}
	if (correct == 94 && errors == 0) {
		displayCongrats();
	}
}

function reset() {
	var a = document.getElementById("myTable").getElementsByTagName("td");
	var size = a.length;
	for (var i=0; i<size; i++) {
		a[i].style.backgroundColor = "lightyellow";
	}
	errors = 0;
	correct = 0;
	return;
}

function reveal() {
	var a = document.getElementsByClassName("z");
	var size = a.length;
	for (var i=0;i<size;i++) {
		a[i].style.backgroundColor = "darkslategray";
	}
	a = document.getElementsByClassName("x");
	size = a.length;
	for (var i=0;i<size;i++) {
		a[i].style.backgroundColor = "lightyellow";
	}
	correct = 94;
	errors = 0;
}

function displayCongrats() {
	alert("Congrats! You solved it!");
}

function hover(x) {
	var k = document.getElementById(x);
	if (k.style.backgroundColor != "darkslategray") {
		k.style.backgroundColor = "lightgrey";
	}
}

function unhover(x) {
	var k = document.getElementById(x);
	if (k.style.backgroundColor == "lightgrey") {
		k.style.backgroundColor = "lightyellow";
	}	
}
