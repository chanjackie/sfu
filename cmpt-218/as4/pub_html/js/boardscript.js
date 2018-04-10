// Global Variables
var win = [];
var n = 1;
var p1moves = [];
var p2moves = [];
var p1turn = true;
var count1 = 0;
var count2 = 0;
var yourturn = false;
var moves=0;


//All win paths sourced from http://jsfiddle.net/Vvwaz/1/
win[0] = [[0,0,0],[1,0,0],[2,0,0]];
win[1] = [[0,1,0],[1,1,0],[2,1,0]];
win[2] = [[0,2,0],[1,2,0],[2,2,0]];
win[3] = [[0,0,0],[0,1,0],[0,2,0]];
win[4] = [[1,0,0],[1,1,0],[1,2,0]];
win[5] = [[2,0,0],[2,1,0],[2,2,0]];
win[6] = [[0,0,0],[1,1,0],[2,2,0]];
win[7] = [[2,0,0],[1,1,0],[0,2,0]];

// Everything in the middle level (z=1)
win[8] = [[0,0,1],[1,0,1],[2,0,1]];
win[9] = [[0,1,1],[1,1,1],[2,1,1]];
win[10] = [[0,2,1],[1,2,1],[2,2,1]];
win[11] = [[0,0,1],[0,1,1],[0,2,1]];
win[12] = [[1,0,1],[1,1,1],[1,2,1]];
win[13] = [[2,0,1],[2,1,1],[2,2,1]];
win[14] = [[0,0,1],[1,1,1],[2,2,1]];
win[15] = [[2,0,1],[1,1,1],[0,2,1]];

// Everything in the top layer (z=2)
win[16] = [[0,0,2],[1,0,2],[2,0,2]];
win[17] = [[0,1,2],[1,1,2],[2,1,2]];
win[18] = [[0,2,2],[1,2,2],[2,2,2]];
win[19] = [[0,0,2],[0,1,2],[0,2,2]];
win[20] = [[1,0,2],[1,1,2],[1,2,2]];
win[21] = [[2,0,2],[2,1,2],[2,2,2]];
win[22] = [[0,0,2],[1,1,2],[2,2,2]];
win[23] = [[2,0,2],[1,1,2],[0,2,2]];

// All the straight columns
win[24] = [[0,0,0],[0,0,1],[0,0,2]];
win[25] = [[1,0,0],[1,0,1],[1,0,2]];
win[26] = [[2,0,0],[2,0,1],[2,0,2]];     
win[27] = [[0,1,0],[0,1,1],[0,1,2]];
win[28] = [[1,1,0],[1,1,1],[1,1,2]];
win[29] = [[2,1,0],[2,1,1],[2,1,2]];      
win[30] = [[0,2,0],[0,2,1],[0,2,2]];
win[31] = [[1,2,0],[1,2,1],[1,2,2]];
win[32] = [[2,2,0],[2,2,1],[2,2,2]];

// All the diagonal columns - back to front
win[33] = [[0,0,0],[0,1,1],[0,2,2]];
win[34] = [[1,0,0],[1,1,1],[1,2,2]];
win[35] = [[2,0,0],[2,1,1],[2,2,2]];

// All the diagonal columns - front to back
win[36] = [[0,2,0],[0,1,1],[0,0,2]];
win[37] = [[1,2,0],[1,1,1],[1,0,2]];
win[38] = [[2,2,0],[2,1,1],[2,0,2]];

// All the diagonal columns - left to right
win[39] = [[0,0,0],[1,0,1],[2,0,2]];
win[40] = [[0,1,0],[1,1,1],[2,1,2]];
win[41] = [[0,2,0],[1,2,1],[2,2,2]];

// All the diagonal columns - right to left
win[42] = [[2,0,0],[1,0,1],[0,0,2]];
win[43] = [[2,1,0],[1,1,1],[0,1,2]];
win[44] = [[2,2,0],[1,2,1],[0,2,2]];

// All the diagonal columns - corner to corner
win[45] = [[0,0,0],[1,1,1],[2,2,2]];
win[46] = [[0,2,0],[1,1,1],[2,0,2]];
win[47] = [[2,0,0],[1,1,1],[0,2,2]];
win[47] = [[2,2,0],[1,1,1],[0,0,2]];

var socket = io("localhost:12834");
var user = {
	"_id":"unknown",
	"win":0,
	"loss":0,
	"player1":false
}


function setData(data) {
	console.log("received data:", data);
	document.getElementById("playerName").value = data[0]._id;
	user._id = data[0]._id;
	user.win = data[0].win;
	user.loss = data[0].loss;
	user.player1 = data[0].player1;
	var msg = user._id + " has connected!";
	if (user.player1) {console.log("This is player 1!");}
	else {console.log("This is player 2!");}
	socket.emit('broadcast', msg);	
}

socket.on('connect', function() {
	console.log("received connect emit");
	$.ajax({
		method: 'get',
		url: '/stats',
		data: '',
		success: setData
	});
});

socket.on('userCon', function(msg) {
	console.log("received userCon emit");
	var p = document.createElement("p");
	p.innerText = msg;
	document.querySelector("#currentUsers").appendChild(p);
});

socket.on('changeTurn', function(data) {
	var k = document.getElementById(data);
	moves++;
	if (p1turn) {
		k.style.backgroundColor = "crimson";
		p1turn = false;
	} else {
		k.style.backgroundColor = "navy";
		p1turn = true;
	}
	if (moves == 27) {
		alert("It's a draw!");
	}
});


function hover(a) {
	var k = document.getElementById(a);
	if (user.player1) {
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
	if (p1turn && user.player1) {
		if (k.style.backgroundColor != "crimson") {
			checkwin(a);
		}
	} else if (!p1turn && !user.player1){
		if (k.style.backgroundColor != "navy") {
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
	socket.emit('updateTurn', data);
	if (p1turn) {
		p1moves.push([x,y,z]);
		var count = 0;
		if (p1moves.length >= 3) {
			for (var n=0;n<48;n++) {
				var l = 0;
				for (var i=0;i<p1moves.length;i++) {
					var inner = 0;
					for (var x=0;x<3;x++) {
						if (p1moves[i][x] == win[n][l][x]) {
							inner++;
						}
						if(inner==3) {
							console.log("l++");
							l++;
						}
					}
					if (l == 3) {
						alert("P1 Wins!");
					}
				}
			}
		}
	}
	else {
	}
}
