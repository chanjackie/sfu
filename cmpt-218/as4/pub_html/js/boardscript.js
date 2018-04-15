// Global Variables
var win = [];
var n = 1;
var pmoves = [];
var p1turn = true;
var moves=0;
//var inRoom=0;
var p1win = false;
var p2win = false;
var date;

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
	document.getElementsByClassName("playerName")[0].value = data[0]._id;
	document.getElementsByClassName("playerName")[1].value = data[0]._id;
	document.getElementsByClassName("playerName")[2].value = data[0]._id;
	user._id = data[0]._id;
	user.win = data[0].win;
	user.loss = data[0].loss;
	user.player1 = data[0].player1;
	var msg = user._id + " has connected!";
	if (user.player1) {
		console.log("This is player 1!");
		document.getElementById("yourNum").innerHTML = "You are Red (Player 1)";
		document.getElementById("turn").innerHTML = "It's your turn!";
	}
	else {
		console.log("This is player 2!");
		document.getElementById("yourNum").innerHTML = "You are Blue (Player 2)";
		document.getElementById("turn").innerHTML = "It's your opponent's turn!";
	}
	// socket.emit('broadcast', msg);	
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

/*socket.on('userCon', function(msg) {
	console.log("received userCon emit");
	inRoom++;
	if (inRoom == 2) {
		document.getElementById("waiting").innerHTML = "";
	} else if(!user.player1) {
		document.getElementById("waiting").innerHTML = "";
	}
	var p = document.createElement("p");
	p.innerText = msg;
	document.querySelector("#currentUsers").appendChild(p);
});*/

socket.on('changeTurn', function(data) {
	var k = document.getElementById(data);
	moves++;
	if (p1turn) {
		k.style.backgroundColor = "crimson";
		p1turn = false;
		if (user.player1) {
			document.getElementById("turn").innerHTML = "It's your opponent's turn!";
		} else {
			document.getElementById("turn").innerHTML = "It's your turn!";
		}
	} else {
		k.style.backgroundColor = "navy";
		p1turn = true;
		if (user.player1) {
			document.getElementById("turn").innerHTML = "It's your turn!";
		} else {
			document.getElementById("turn").innerHTML = "It's your opponent's turn!";
		}
	}
	if (moves == 27) {
		alert("It's a draw! Returning to landing page...");
		if (user.player1) {
			setTimeout(submitDraw, 3000);
		} else {
			setTimeout(submitDraw, 5000);
		}
	}
});

socket.on('quitOther', function() {
	alert("Other player disconnected. You win! Returning to landing page...")
	setTimeout(submitDC, 3000);
});

socket.on('clientWin', function(userArray, msg) {
	alert(msg);
	console.log("Player1:", user.player1);

	if ((p1win && user.player1)||(p2win && !user.player1)) {
		var index = userArray.indexOf(user._id);
		userArray.splice(index, 1);
		console.log("Calling POST /recordStats");
		$.ajax({
			method:'post',
			url:'/recordStats',
			data:'_id='+date+'&moves='+moves+'&winner='+user._id+'&loser='+userArray[0]
		});
		setTimeout(submitWin, 1000);
	} else {
		setTimeout(submitLoss, 3000);
	}
});

function submitDraw() {
	document.getElementById("drawForm").submit();
}

function submitDC() {
	document.getElementById("dcForm").submit();
}

function submitWin() {
	document.getElementById("winForm").submit();
}

function submitLoss() {
	document.getElementById("lossForm").submit();
}

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
	pmoves.push([x,y,z]);
	console.log(pmoves, "length:", pmoves.length);
	var count = 0;
	var l = 0;
	if (pmoves.length >= 3) {
		for (var n=0;n<48;n++) {
			var array1 = win[n][0];
			var array2 = win[n][1];
			var array3 = win[n][2];
			count=0;
			for (var i=0;i<pmoves.length;i++) {
				if (pmoves[i][0] == array1[0] && pmoves[i][1] == array1[1] && pmoves[i][2] == array1[2]) {
					count++;
				}
				if (pmoves[i][0] == array2[0] && pmoves[i][1] == array2[1] && pmoves[i][2] == array2[2]) {
					count++;
				}
				if (pmoves[i][0] == array3[0] && pmoves[i][1] == array3[1] && pmoves[i][2] == array3[2]) {
					count++;
				}
			}
			if (count==3) {
				var msg = user._id+" has won! Returning to landing page...";
				if (user.player1) {
					p1win = true;
				} else {
					p2win = true;
				}
				socket.emit('updateWin', msg);
			}
		}
	}
}

function discon() {
	socket.emit('oneQuit');
}

function grabDate() {
	date = new Date();
	var year = date.getFullYear();
	var month = date.getMonth()+1;
	var day = date.getDate();
	var hour = date.getHours();
	var minute = date.getMinutes();
	var ampm = "am";
	if (day<10) {
		day = '0'+day;
	}
	if (month<10) {
		month='0'+month;
	}
	if (hour>12) {
		ampm = "pm";
		hour = hour - 12;
	}
	if (minute < 10) {
		minute = "0" + minute;
	}
	date = year+"/"+month+"/"+day+" "+hour+":"+minute+ampm;
	console.log(date);
	document.getElementById("displayDate").innerHTML = "Start Time: "+date;
}