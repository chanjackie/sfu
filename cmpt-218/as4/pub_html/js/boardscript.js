// Global Variables
var win = [];
var n = 1;
var p1moves = [[]];
var p2moves = [[]];
var p1turn = true;
var count1 = 0;
var count2 = 0;

win[0] = [["0","0","0"],["1","0","0"],["2","0","0"]];


function hover(a) {
	var k = document.getElementById(a);
	if (p1turn) {
		if (k.style.backgroundColor != "crimson" && k.style.backgroundColor != "navy") {
			k.style.backgroundColor = "lightcoral";
		}
	} else {
		if (k.style.backgroundColor != "navy" && k.style.backgroundColor != "crimson") {
			k.style.backgroundColor = "teal";
		}
	}
}

function unhover(a) {
	var k = document.getElementById(a);
	if (k.style.backgroundColor == "lightcoral") {
		k.style.backgroundColor = "silver";
	} else if (k.style.backgroundColor == "teal") {
		k.style.backgroundColor = "silver";
	}
}

function fill(a) {
	var k = document.getElementById(a);
	if (p1turn) {
		if (k.style.backgroundColor != "crimson") {
			k.style.backgroundColor = "crimson";
			checkwin(a);
		}
	}
	else {
		if (k.style.backgroundColor != "navy") {
			k.style.backgroundColor = "navy";
			checkwin(a);
		}
	}
}

function checkwin(data) {
	var k = document.getElementById(data);
	var x = k.getAttribute("x");
	var y = k.getAttribute("y");
	var z = k.getAttribute("z");
	console.log(x, y, z);
	if (p1turn) {
		p1moves[count1].push([x,y,z]);
		console.log("Player 1 moves:", p1moves[count1]);
		console.log("Win[0]:", win[0]);
		console.log(p1moves[0].length);
		if (p1moves[0].length == win[0].length){
			for (var i=0;i<p1moves[0].length;i++) {
				for (var x=0;x<3;x++) {
					console.log("P1:",p1moves[count1][i][x],"WIN:",win[0][i][x]);
					if (p1moves[count1][i][x] !== win[0][i][x]) {
						console.log("not equal");
						p1turn = false;
						return;
					}
				}
			}
			alert("Player 1 wins!");
		}
		p1turn = false;
	}
	else {
		p2moves[count2].push([x,y,z]);
		console.log("Player 2 moves:", p2moves);
		/*for (var i=0;i<n;i++) {
			if (p2moves == win[i]) {
				alert("Player 2 wins!");
			}
		}*/
		//count2++;
		p1turn = true;
	}
}

function arraysEqual(a, b) {
	console.log("start check");
  if (a === b) return true;
  console.log("checking null");
  if (a == null || b == null) return false;
  console.log("checking length");
  if (a.length != b.length) return false;

  // If you don't care about the order of the elements inside
  // the array, you should sort both arrays here.
  console.log("running for loop");
  for (var i = 0; i < a.length; ++i) {
    if (a[i] !== b[i]) {
    	console.log(a[i], b[i]);
    	console.log("error in for loop");
    	return false;
    }
  }
  console.log("all clear");
  return true;
}