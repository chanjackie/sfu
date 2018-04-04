/*function register() {
	var i = document.getElementById("pword");
	var x = document.getElementById("confirmpword");
	console.log(i);
	console.log(x);
	if (i != x) {
		alert("Passwords don't match!");
		return;
	}
}
*/
function grabStats() {
	console.log("Calling GET /stats");
	$.ajax({
		method: 'get',
		url: '/stats',
		data: '',
		success: displayStats
	});
}

function displayStats(data) {
	document.getElementById("title").innerHTML = data[0]._id + " LANDING";
	document.getElementById("header").innerHTML = "Welcome " + data[0]._id;
	document.getElementById("winloss").innerHTML = data[0].win + ":" + data[0].loss;
}

function grabDate() {
	var date = new Date();
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
	document.getElementById("displayDate").innerHTML = "Current Time: "+date;
}